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
//Ray3d.cc

#include "Ray3d.h"

#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Pos3d.h"

Ray3d::Ray3d(const Pos3d &p1,const Pos3d &p2)
  : Linear3d(), cgsr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        std::clog << getClassName() << "::" << __FUNCTION__
		  << "; degenerate line, the points: "
             << p1 << " and " << p2 << " are the same." << std::endl;
      }
  }
void Ray3d::TwoPoints(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Ray3d(p1,p2); }

Dir3d Ray3d::GetDir(void) const
  { return Dir3d(cgsr.direction()); }
Vector3d Ray3d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Returns the squared distand from the point.
GEOM_FT Ray3d::dist2(const Pos3d &p) const
  {
    const Line3d r= getSupportLine();
    const Pos3d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //OK if projection inside half-line.
    if(!In(proj)) //Projection outside half-line.
      retval= p.dist2(getFromPoint());
    return retval;
  }

//! @brief Return the distance 
//! from the point to the ray.
GEOM_FT Ray3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Return true if son paralelas.
bool Ray3d::Paralela(const Ray3d &r) const
  { return (GetDir()== r.GetDir()); }

//! @brief Return true if son paralelas.
bool Ray3d::Paralela(const Line3d &r) const
  { return (GetDir()== r.GetDir()); }

//! @brief Return the intersection point with the argument line
//! if it doesn't exist return an empty list.
GeomObj3d::list_Pos3d Ray3d::getIntersection(const Line3d &r) const
  {
    const Line3d sop= getSupportLine();
    GeomObj3d::list_Pos3d retval= sop.getIntersection(r);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //intersection point is NOT on the ray.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Return the intersection of the ray with the plane
//! defined by the equation coord_i= d.
GeomObj3d::list_Pos3d Ray3d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj3d::list_Pos3d lp;
    lp= getSupportLine().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector3d i_= VDir();
        const double l= getSupportLine().getLambda(i,d,i_);
        if(l<0.0)
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the intersection point of both rays, if it doesn't exists
//! return an empty list.
GeomObj3d::list_Pos3d Ray3d::getIntersection(const Ray3d &sr) const
  {
    const Line3d sop1= getSupportLine();
    GeomObj3d::list_Pos3d retval= sr.getIntersection(sop1);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //intersection point is NOT on the ray.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }



