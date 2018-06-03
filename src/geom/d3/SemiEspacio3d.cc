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
//SemiEspacio3d.cc

#include "SemiEspacio3d.h"



#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"


//! @brief Constructor por defecto.
SemiEspacio3d::SemiEspacio3d(const Plane &p)
  : GeomObj3d(), lim(p) {}

//! @brief Return el plano que limita el semiespacio.
const Plane &SemiEspacio3d::getBoundaryPlane(void) const
  { return lim; }

void SemiEspacio3d::setBoundaryPlane(const Plane &p)
  { lim= p; }

//! @brief Return true if the point is inside the half-plane.
//! The points of the edge line belong to the half-plane.
bool SemiEspacio3d::In(const Pos3d &p, const double &tol) const
  {
    bool retval= false;
    if(lim.LadoNegativo(p))
      retval= true;
    else if(lim.In(p,tol))
      retval= true;
    return retval;
  }

//! @brief Return the signed distance from the point to the half plane.
GEOM_FT SemiEspacio3d::distSigno(const Pos3d &p) const
  { return lim.PseudoDist(p); }

//! @brief Return the signed squared distance from the point to the half plane.
GEOM_FT SemiEspacio3d::distSigno2(const Pos3d &p) const
  { return lim.PseudoDist2(p); }

//! @brief Return the distance from the point to the half plane.
GEOM_FT SemiEspacio3d::dist(const Pos3d &p) const
  { return fabs(distSigno(p)); }

//! @brief Return the squared distance from the point to the half plane.
GEOM_FT SemiEspacio3d::dist2(const Pos3d &p) const
  { return fabs(distSigno2(p)); }

//! @brief Return el ángulo que forma con el half-space que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const SemiEspacio3d &se) const
  { return angulo(lim,se.getPlane()); }

//! @brief Return el ángulo que forma con el plano que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const Plane &p) const
  { return angulo(lim,p); }

//! @brief Return el ángulo que forma con el vector que
//! se pasa como parámetro.
GEOM_FT SemiEspacio3d::getAngulo(const Vector3d &v) const
  { return angulo(v,lim); }

//! @brief Return la arista de la intersección entre semiespacios.
Recta3d SemiEspacio3d::getLima(const SemiEspacio3d &se) const
  {
     const Recta3d retval= lim.Interseccion(se.lim);
     if(!retval.exists())
       std::cerr << "getLima: los planos que limitan los semiespacios no se cortan."
                 << std::endl;
     return retval;
  }

//!brief Return the dimension of the object 0, 1, 2 or 3.
unsigned short int SemiEspacio3d::Dimension(void) const
  { return 3; }

//! @brief Return the lenght of the object.
GEOM_FT SemiEspacio3d::getLength(void) const
  { return NAN; }
//! @brief Return the object area.
GEOM_FT SemiEspacio3d::getArea(void) const
  { return NAN; }
//! @brief Return the object volume
GEOM_FT SemiEspacio3d::getVolume(void) const
  { return NAN; }
Pos3d SemiEspacio3d::getCenterOfMass(void) const
  { return lim.getCenterOfMass(); }

//! @brief Return el moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT SemiEspacio3d::Ix(void) const
  { return NAN; }

//! @brief Return el moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT SemiEspacio3d::Iy(void) const
  { return NAN; }

//! @brief Return el product of inertia.
GEOM_FT SemiEspacio3d::Pxy(void) const
  { return NAN; }

//! @brief Return el moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT SemiEspacio3d::Iz(void) const
  { return NAN; }

//! @brief Return verdadero si los semiespacios son iguales.
bool operator==(const SemiEspacio3d &r1,const SemiEspacio3d &r2)
  {
    if(&r1.lim==&r2.lim)
      return true;
    else
      return (r1.lim==r2.lim); 
  }

//! @brief Return un vector normal al plano que limita
//! el half-space dirigido hacia el exterior del mismo.
Vector3d SemiEspacio3d::NormalExterior(void) const
  { return lim.Normal(); }

//! @brief Return un vector normal al plano que limita
//! el half-space dirigido hacia el exterior del mismo.
Vector3d SemiEspacio3d::NormalInterior(void) const
  { return -NormalExterior(); }

//! @brief Imprime el semiespacio
void SemiEspacio3d::Print(std::ostream &os) const
      { os << lim; }

//! @brief Return de points of intersection between half-spaces.
TripletMap<Pos3d> intersection_points(const std::deque<SemiEspacio3d> &se)
  {
    TripletMap<Pos3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        for(size_t k=j+1;k<sz;k++)
	  {
            const Pos3d p= intersection_point(se[i].getPlane(),se[j].getPlane(),se[k].getPlane());
            if(p.exists())
              retval[Triplete(i,j,k)]= p;
          }
    return retval;
  }

//! @brief Return los vertices del poliedro intersección de los semiespacios.
TripletMap<Pos3d> vertices_poliedro(const std::deque<SemiEspacio3d> &se, const double &tol)
  {
    TripletMap<Pos3d> tmp= intersection_points(se);
    TripletMap<Pos3d> retval= tmp;
    for(std::deque<SemiEspacio3d>::const_iterator j=se.begin();j!=se.end();j++)
      for(TripletMap<Pos3d>::const_iterator i= tmp.begin();i!=tmp.end();i++)
        if((*j).Out((*i).second,tol))
          {
            retval.erase(i->first);
            continue;
          }
    if(retval.size()<4)
      std::cerr << "vertices_poliedro; se obtuvieron menos de cuatro vértices."
                << std::endl;
    for(TripletMap<Pos3d>::const_iterator i= retval.begin();i!=retval.end();i++)
      {
        for(TripletMap<Pos3d>::const_iterator j= retval.begin();j!=retval.end();j++)
          if(j!=i)
            {
              const GEOM_FT d2= dist2(i->second,j->second);
              if(d2<1e-4)
                {
		  std::cerr << "Los vértices: ";
                  retval.PrintMember(std::cerr,i);
		  std::cerr << " y ";
                  retval.PrintMember(std::cerr,j);
		  std::cerr << " están muy próximos. d= "
                            << sqrt(d2) << std::endl;
                }
            }
      }
    return retval;
  }

//! @brief Return las rectas de intersección entre los semiespacios.
std::deque<Recta3d> rectas_interseccion(const std::deque<SemiEspacio3d> &se)
  {
    std::deque<Recta3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        {
          const Recta3d r= recta_interseccion(se[i].getPlane(),se[j].getPlane());
          if(r.exists())
            retval.push_back(r);
        }
    return retval;
  }

//! @brief Return los vectores normales a cada uno de los semiespacios.
std::deque<Vector3d> vectores_normales(const std::deque<SemiEspacio3d> &se)
  {
    std::deque<Vector3d> retval;
    const size_t sz= se.size();
    for(size_t i=0;i<sz;i++)
      retval.push_back(se[i].NormalExterior());
    return retval;
  }

//! @brief Return el ángulo entre los semiespacios.
GEOM_FT angulo(const SemiEspacio3d &se1,const SemiEspacio3d &se2)
  { return se1.getAngulo(se2); }

//! @brief Return el ángulo entre el half-space y el vector.
GEOM_FT angulo(const Vector3d &v,const SemiEspacio3d &se)
  { return se.getAngulo(v); }

//! @brief Return el ángulo entre el half-space y el vector.
GEOM_FT angulo(const SemiEspacio3d &se,const Vector3d &v)
  { return se.getAngulo(v); }
