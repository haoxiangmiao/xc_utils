//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Xd3dCooSys.cc

#include "Xd3dCooSys.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Pos3d.h"


//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector que
//! se pasa como parámetro.
Xd3dCooSys::Xd3dCooSys(const size_t &i,const VGlobal &v)
  : CooSys(i,3)
  { XAxisVector(v); }

//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
Xd3dCooSys::Xd3dCooSys(const size_t &i,const VGlobal &v1,const VGlobal &v2)
  : CooSys(i,3)
  { vectores_unitarios(v1,v2,v1 ^ v2); }

Xd3dCooSys::Xd3dCooSys(const size_t &i,const PGlobal &o,const PGlobal &p)
  : CooSys(i,3)
  { TwoPoints(o,p); }

Xd3dCooSys::Xd3dCooSys(const size_t &i,const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : CooSys(i,3)
  { ThreePoints(p1,p2,p3); }
Xd3dCooSys::Xd3dCooSys(const size_t &i,const VGlobal &v1,const VGlobal &v2,const VGlobal &v3)
  : CooSys(i,3)
  { vectores_unitarios(v1,v2,v3); }

void Xd3dCooSys::putRow(const size_t &axis,const VGlobal &v)
  { CooSys::putRow(axis,traspuesta(v.getMatrix())); }

//! @brief Return the dirección of the axis being passed as parameter.
Xd3dCooSys::DGlobal Xd3dCooSys::getAxisDir(const size_t &axis) const
  { return DGlobal(getAxisVDir(1)); }

//! @brief Return the direction vector of the axis being passed as parameter.
Xd3dCooSys::VGlobal Xd3dCooSys::getAxisVDir(const size_t &axis) const
  { 
    const FT_matrix row= getRow(axis);
    return VGlobal(row(1,1),row(1,2),row(1,3));
  }
//! Return las componentes del vector v 
//! being passed as parameter expresado en coordenadas locales
//! expresado en global coordinates.
Xd3dCooSys::VGlobal Xd3dCooSys::GetCooGlobales(const FT_matrix &v) const
  {
    const FT_matrix tmp= CooSys::GetCooGlobales(v);
    return VGlobal(tmp(1),tmp(2),tmp(3)); 
  }
FT_matrix Xd3dCooSys::GetCooLocales(const Xd3dCooSys::VGlobal &v) const
  { return CooSys::GetCooLocales(v.getMatrix()); }
//! Hace que el sistema de coordenadas tenga por vectores unitarios:
//! - El versor correspondiente al vector i_, being passed as parameter.
//! - El versor correspondiente al vector j_, being passed as parameter.
//! - El versor correspondiente al vector k_, being passed as parameter.
//!
//! Comprueba que los tres vectores no sean coplanarios ni paralelos 2 a 2.
void Xd3dCooSys::vectores_unitarios(const VGlobal &i_,const VGlobal &j_,const VGlobal &k_)
  {
    if(coplanarios(i_,j_,k_))
      {
        std::cerr << "Xd3dCooSys::vectores_unitarios: Los tres vectores: " 
                  << i_ << ' ' << j_ << ' ' << k_ 
                  << " son coplanarios. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(i_,j_))
      {
        std::cerr << "Xd3dCooSys::vectores_unitarios: Los vectores: " 
		  << " i= " << i_ << " y j= " << j_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(i_,k_))
      {
        std::cerr << "Xd3dCooSys::vectores_unitarios: Los vectores: " 
		  << " i= " << i_ << " y k= " << k_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(j_,k_))
      {
        std::cerr << "Xd3dCooSys::vectores_unitarios: Los vectores: " 
		  << " j= " << j_ << " y k= " << k_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    const size_t ne= numberOfAxis();
    const VGlobal e1= Normaliza(i_);
    putRow(1,e1);
    if(ne>1)
      {
        const VGlobal e2= Normaliza(j_);
        putRow(2,e2);
      }
    if(ne>2)
      {
        const VGlobal e3= Normaliza(k_);
        putRow(3,e3);
      }
  }

//! @brief Construye el sistema de coordenadas formado por los vectores:
//! i_ el being passed as parameter.
//! j_ el horizontal perpendicular a i_ (si es único).
//! k_ el producto vectorial de ambos.
void Xd3dCooSys::XAxisVector(const VGlobal &i_)
  {
    if(i_.Nulo())
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; vector: " << i_ << " is zero."
	          << " System parallel to global axis will be returned."
                  << std::endl;
        identity();
      }
    else
      {
        const GEOM_FT imod= Abs2(i_); //Módulo de i.
        //const GEOM_FT tol= imod/1e8;
        VGlobal k_;
        //if( (fabs(i_(1))<tol) && (fabs(i_(2))<tol) ) //Si i es casi paralelo al z axis global.
        if(paralelos(i_,Vector3d(0,0,1))) //Si i es paralelo al z axis global.
          k_= imod*J_3d; //k paralelo a y axis global.
        else
          k_= imod*K_3d; //k paralelo a z axis global.
        const VGlobal j_= k_ ^ i_;
        k_= i_ ^ j_;
        vectores_unitarios(i_,j_,k_); //Normalizamos.
      }
  }

//! @brief Construye el sistema de coordenadas formado por los vectores:
//! i_ el vector op (ver XAxisVector).
void Xd3dCooSys::TwoPoints(const PGlobal &o,const PGlobal &p)
  { XAxisVector(p-o); }

//! @brief Create the coordinate system with axis oriented as follows:
//! x axis: from o to p1;
//! y axis: normal to x and contained in the plane defined 
//! by the three points and pointing to p2.
void Xd3dCooSys::ThreePoints(const PGlobal &o,const PGlobal &p1,const PGlobal &p2)
  {
    if(colineales(o,p1,p2))
      {
        std::cerr << getClassName() << "::" << __FUNCTION__ 
             << o << ' ' << p1 << ' ' << p2 
             << " are collinear. Doing nothing."
             << std::endl;
        return;
      }
    const VGlobal i_= p1 - o;
    VGlobal j_= p2 - o;
    const VGlobal k_= i_ ^ j_;
    j_= k_ ^ i_;
    vectores_unitarios(i_,j_,k_);
  }
