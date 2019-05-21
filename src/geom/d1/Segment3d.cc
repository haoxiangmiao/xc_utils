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
//Segment3d.cc

#include "Segment3d.h"

#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Pos3d.h"

//! @brief Constructor.
Segment3d::Segment3d(void): Linear3d(),cgseg(CGPoint_3(0,0,0),CGPoint_3(1,0,0)) {}

//! @brief Constructor.
Segment3d::Segment3d(const CGSegment_3 &r)
  : Linear3d(), cgseg(r) {}

//! @brief Constructor.
Segment3d::Segment3d(const Pos3d &p1,const Pos3d &p2)
  : Linear3d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        std::clog << getClassName() << "::" << __FUNCTION__
		  << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << std::endl;
      }
  }

//! @brief Constructor.
Segment3d::Segment3d(const Segment3d &r)
  : Linear3d(),cgseg(r.cgseg) {}

//! @brief Operador asignación.
Segment3d &Segment3d::operator=(const Segment3d &r)
  {
    Linear3d::operator=(r);
    cgseg= r.cgseg;
    return *this;
  }

GeomObj *Segment3d::clon(void) const
  { return new Segment3d(*this); }
GEOM_FT Segment3d::GetMax(unsigned short int i) const
  { return std::max(getFromPoint()(i),getToPoint()(i)); }
GEOM_FT Segment3d::GetMin(unsigned short int i) const
  { return std::min(getFromPoint()(i),getToPoint()(i)); }
Line3d Segment3d::getSupportLine(void) const
  { return Line3d(cgseg.supporting_line()); }
Pos3d Segment3d::getFromPoint(void) const
  { return Pos3d(cgseg.source()); }
Pos3d Segment3d::getToPoint(void) const
  { return Pos3d(cgseg.target()); }
GEOM_FT Segment3d::getSlope(void) const
  { return getSupportLine().getSlope(); }
const Pos3d Segment3d::Point(const int &i) const
  { return Pos3d(cgseg.point(i)); }

//! @brief Return a point of the line at a distance lambda from its origin.
Pos3d Segment3d::PtoParametricas(const GEOM_FT &lambda) const
  { return Point(0)+lambda*VDir(); }

//! @brief Return the parametric coordinate that corresponds
//! to the natural coordinate being passed as parameter.
double Segment3d::getParamCooNatural(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Return the parametric coordinate that corresponds
//! to the natural coordinate being passed as parameter.
Pos3d Segment3d::PtoCooNatural(const GEOM_FT &chi) const
  { return PtoParametricas(getParamCooNatural(chi)); }

inline bool Segment3d::EsDegenerada(void) const
  { return cgseg.is_degenerate(); }
//! @brief Return true if the point is in the segment.
bool Segment3d::In(const Pos3d &p, const double &tol) const
  { return cgseg.has_on(p.ToCGAL()); }

void Segment3d::TwoPoints(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Segment3d(p1,p2); }

Dir3d Segment3d::GetDir(void) const
  { return Dir3d(cgseg.direction()); }
Vector3d Segment3d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return el parámetro «lambda» tal que p= getFromPoint()+lambda*VDir()
GEOM_FT Segment3d::getLambda(const Pos3d &p) const
  {
    const Vector3d v(getFromPoint(),p);
    const Vector3d dir(Normaliza(VDir()));
    return dot(v,dir);
  }

//! @brief Return the squared distance from the point to the segment.
GEOM_FT Segment3d::dist2(const Pos3d &p) const
  {
    const Line3d r= getSupportLine();
    const Pos3d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projected point inside segment.
    const Pos3d A= getFromPoint();
    const Pos3d B= getToPoint();
    const GEOM_FT denom= (B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y())+(B.z()-A.z())*(B.z()-A.z());
    if(denom!=0)
      {
        const GEOM_FT u= ( (p.x()-A.x())*(B.x()-A.x()) + (p.y()-A.y())*(B.y()-A.y()) + (p.z()-A.z())*(B.z()-A.z()) )/denom;
        if(u<0.0) //Distance to the origin.
	  retval= p.dist2(A);
	else if(u>1.0) //Distance to the destination.
          retval= p.dist2(B);
      }
    return retval;
  }

//! @brief Return the distance from the point to the segment.
GEOM_FT Segment3d::dist(const Pos3d &p) const
  { return sqrt(dist2(p)); }

bool Segment3d::Paralelo(const Line3d &r) const
  { return paralelas(getSupportLine(),r); }
bool Segment3d::Paralelo(const Ray3d &sr) const
  { return paralelas(getSupportLine(),sr); }
bool Segment3d::Paralelo(const Segment3d &r) const
  { return paralelas(getSupportLine(),r.getSupportLine()); }

//! @brief Return the length of the segment.
GEOM_FT Segment3d::getLength(void) const
  { return getFromPoint().dist(getToPoint()); }

Pos3d Segment3d::getCenterOfMass(void) const
  {
    Pos3d retval= getFromPoint();
    const Vector3d v= (getToPoint()-retval)/2;
    retval= retval+v;
    return retval;
  }

//! @brief Return the intersection of the segment and the line,
//! if it doesn't exists return an empty list.
GeomObj3d::list_Pos3d Segment3d::getIntersection(const Line3d &r) const
  {
    const Line3d sop= getSupportLine();
    GeomObj3d::list_Pos3d retval= sop.getIntersection(r);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //the intersection point is NOT on the segment.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Return the intersection of the ray and the segment, if
//! the intersection doesn't exists returns an empty list.
GeomObj3d::list_Pos3d Segment3d::getIntersection(const Ray3d &sr) const
  {
    const Line3d sop= getSupportLine();
    GeomObj3d::list_Pos3d retval= sr.getIntersection(sop);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //the intersection point is NOT on the segment.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Return the intersection of the line with the plane defined
//! by the equation coord_i=cte.
GeomObj3d::list_Pos3d Segment3d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj3d::list_Pos3d lp;
    lp= getSupportLine().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector3d i_= VDir();
        const double l= getSupportLine().getLambda(i,d,i_);
        if( (l<0.0) || (l>getLength()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }


//! @brief Return the intersection of the segments, if
//! the intersection doesn't exists returns an empty list.
GeomObj3d::list_Pos3d Segment3d::getIntersection(const Segment3d &sg2) const
  {
    const Line3d sop= getSupportLine();
    GeomObj3d::list_Pos3d retval= sg2.getIntersection(sop);
    if(!retval.empty()) //Intersection exists
      {
        const Pos3d &pint= *retval.begin(); //This point is on sg2 and on
	                                    // the sg1 support line.
        if(!In(pint)) //the intersection point is NOT on sg1.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

GEOM_FT dist(const Pos3d &p,const Segment3d &r)
  { return sqrt_FT(dist2(r,p)); }

//! @brief Returns angle with vector.
GEOM_FT Segment3d::getAngle(const Vector3d &v) const
  { return angle(VDir(),v); }
//! @brief Returns angle with another line segment.
GEOM_FT Segment3d::getAngle(const Segment3d &s) const
  { return getAngle(s.VDir()); }
GEOM_FT angle(const Segment3d &r,const Vector3d &v)
  { return r.getAngle(v); }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segment3d::Ix(void) const
  { return 0.0; }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segment3d::Iy(void) const
  { return NAN; }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segment3d::Iz(void) const
  { return NAN; }
bool operator==(const Segment3d &r1,const Segment3d &r2)
  { return (r1.cgseg==r2.cgseg); }
void Segment3d::Print(std::ostream &os) const
  { os << getFromPoint() << " " << getToPoint(); }

