//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Pos3d.cc

#include "Pos3d.h"
#include "Pos2d.h"
#include "../d2/Plano3d.h"
#include "Vector3d.h"



#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/d3/Solido3d.h"

//! @brief Suma de un vector.
Pos3d &Pos3d::operator+=(const Vector3d &v)
  {
    operator=((*this)+v);
    return *this;
  }

//! @brief Resta de un vector.
Pos3d &Pos3d::operator-=(const Vector3d &v)
  {
    operator=((*this)-v);
    return *this;
  }

//! @brief Vector between the points.
Vector3d Pos3d::operator-(const Pos3d &p) const
  {
    Vector3d retval(ToCGAL()-p.ToCGAL());
    return retval;
  }

//! @brief Point obtained by subtraction of the vector.
Pos3d Pos3d::operator-(const Vector3d &v) const
  {
    Pos3d retval(ToCGAL()-v.ToCGAL());
    return retval;
  }

//! @brief Point obtained by addition of the vector.
Pos3d Pos3d::operator+(const Vector3d &v) const
  {
    Pos3d retval(ToCGAL()+v.ToCGAL());
    return retval;
  }

//! @brief Return the position vector of the point.
Vector3d Pos3d::VectorPos(void) const
  { return (*this)-Origen3d; }

GEOM_FT Pos3d::at0(const size_t &i) const
  { return cgpt.cartesian(i); }

GEOM_FT Pos3d::operator()(const size_t &i) const
  { return cgpt.cartesian(i-1); }

void Pos3d::SetX(const GEOM_FT &vx)
  { cgpt= CGPoint_3(vx,y(),z()); }
void Pos3d::SetY(const GEOM_FT &vy)
  { cgpt= CGPoint_3(x(),vy,z()); }
void Pos3d::SetZ(const GEOM_FT &vz)
  { cgpt= CGPoint_3(x(),y(),vz); }
void Pos3d::Set(unsigned short int i,const GEOM_FT &v)
  {
    switch(i)
      {
      case 1:
        SetX(v);
        break;
      case 2:
        SetY(v);
        break;
      case 3:
        SetZ(v);
        break;
      default:
	std::cerr << "Se esperaba que el índice fuera 1, 2 ó 3." << std::endl;
        break;
      }
  }

//! @brief Return the quadrant of the point.
int Pos3d::Cuadrante(void) const
  {
    const bool x_no_neg= (x()>=0);
    const bool y_no_neg= (y()>=0);
    const bool z_no_neg= (z()>=0);
    if(x_no_neg) //(1,2,3 ó 4)
      if(y_no_neg) //1 o 4
        if(z_no_neg)
          return 1;
        else
          return 4;
      else //2 o 3
        if(z_no_neg)
          return 2;
        else
          return 3;
    else //(5,6,7 u 8)
      if(y_no_neg) //5 u 8
        if(z_no_neg)
          return 5;
        else
          return 8;
      else //6 o 7
        if(z_no_neg)
          return 6;
        else
          return 7;
  }

//! @brief Return the projection onto XY plane.
Pos3d Pos3d::XY3DProjection(void) const
  { return PlanoXY3d.Projection(*this); }
//! @brief Return the projection onto XZ plane.
Pos3d Pos3d::XZ3DProjection(void) const
  { return PlanoXZ3d.Projection(*this); }
//! @brief Return the projection onto YZ plane.
Pos3d Pos3d::YZ3DProjection(void) const
  { return PlanoYZ3d.Projection(*this); }

//! @brief Return the projection onto XY plane.
Pos2d Pos3d::XY2DProjection(void) const
  {
    Pos3d p3d= XY3DProjection();
    return Pos2d(p3d.x(),p3d.y());
  }
//! @brief Return the projection onto XZ plane.
Pos2d Pos3d::XZ2DProjection(void) const
  {
    Pos3d p3d= XZ3DProjection();
    return Pos2d(p3d.x(),p3d.z());
  }

//! @brief Return the projection onto YZ plane.
Pos2d Pos3d::YZ2DProjection(void) const
  {
    Pos3d p3d= YZ3DProjection();
    return Pos2d(p3d.y(),p3d.z());
  }

//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al x axis.
Pos3d Pos3d::getModArgX(const GEOM_FT &mod,const GEOM_FT &giroX) const
  { return Pos3d(x(),y()+mod*cos(giroX),z()+mod*sin(giroX)); }

//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al y axis.
Pos3d Pos3d::getModArgY(const GEOM_FT &mod,const GEOM_FT &giroY) const
  { return Pos3d(x()+mod*cos(giroY),y(),z()-mod*sin(giroY)); }


//! @brief Equivalente a la función de autocad @mod<arg con el giro en
//! torno al z axis.
Pos3d Pos3d::getModArgZ(const GEOM_FT &mod,const GEOM_FT &giroZ) const
  { return Pos3d(x()+mod*cos(giroZ),y()+mod*sin(giroZ),z()); }

bool Pos3d::domina_a(const Pos3d &b) const
  {
    for(register size_t i= 1;i<=dimension();i++)
      if ((*this)(i)<b(i)) return false;
    return true;
  }

//! @brief Return the distance to the point.
GEOM_FT Pos3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Return the squared distance to the point.
GEOM_FT Pos3d::dist2(const Pos3d &p) const
  { return squared_distance(cgpt,p.cgpt); }

//! @brief Return el cuadrado de la distance a la recta.
GEOM_FT Pos3d::dist2(const Recta3d &r) const
  { return r.dist2(*this); }
  
//! @brief Return the distance a la recta.
GEOM_FT Pos3d::dist(const Recta3d &r) const
  { return r.dist(*this); }

//! @brief Return el cuadrado de la distance a la semirrecta.
GEOM_FT Pos3d::dist2(const SemiRecta3d &sr) const
  { return sr.dist2(*this); }

//! @brief Return the distance a la semirrecta.
GEOM_FT Pos3d::dist(const SemiRecta3d &sr) const
  { return sr.dist(*this); }

//! @brief Return el cuadrado de la distance al segmento.
GEOM_FT Pos3d::dist2(const Segmento3d &sg) const
  { return sg.dist2(*this); }

//! @brief Return the distance al segmento.
GEOM_FT Pos3d::dist(const Segmento3d &sg) const
  { return sg.dist(*this); }

//! @brief Return el cuadrado de la distance al plano.
GEOM_FT Pos3d::dist2(const Plano3d &p) const
  { return p.dist2(*this); }

//! @brief Return the distance al plano.
GEOM_FT Pos3d::dist(const Plano3d &p) const
  { return p.dist(*this); }

//! @brief Return el cuadrado de la distance al semiespacio.
GEOM_FT Pos3d::dist2(const SemiEspacio3d &se) const
  { return se.dist2(*this); }

//! @brief Return the distance al semiespacio.
GEOM_FT Pos3d::dist(const SemiEspacio3d &se) const
  { return se.dist(*this); }

//! @brief Return the distance al sólido.
GEOM_FT Pos3d::dist(const Solido3d &s) const
  { return s.dist(*this); }

std::ostream &operator<<(std::ostream &stream,const Pos3d &n)
  {
//     stream << "x= " << to_double(n.x()) << ','
//            << "y= " << to_double(n.y()) << ','
//            << "z= " << to_double(n.z());
    stream << "x= " << n.x() << ','
           << "y= " << n.y() << ','
           << "z= " << n.z();
    return stream;
  }


Pos3d To3dXY2d(const Pos2d &p,const GEOM_FT &z)
  { return Pos3d(p.x(),p.y(),z); }
Pos3d To3dXZ2d(const Pos2d &p,const GEOM_FT &y)
  { return Pos3d(p.x(),y,p.y()); }
Pos3d To3dYZ2d(const Pos2d &p,const GEOM_FT &x)
  { return Pos3d(x,p.x(),p.y()); }
Pos3d To3d(const Pos2d &p,const size_t &coo,const GEOM_FT &u)
  { 
    const size_t i= (coo-1)%3+1;
    if(i==3) return To3dXY2d(p,u);
    if(i==2) return To3dXZ2d(p,u);
    return To3dYZ2d(p,u);
  }

bool colineales(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  { return collinear(p1.cgpt,p2.cgpt,p3.cgpt); } 
bool coplanarios(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4)
  { return coplanar(p1.cgpt,p2.cgpt,p3.cgpt,p4.cgpt); } 




