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
//Ray2d.cc

#include "Ray2d.h"

#include <plotter.h>
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

Ray2d::Ray2d(const Pos2d &p1,const Pos2d &p2)
  : Linear2d(), cgsr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        clog << getClassName() << "::" << __FUNCTION__
	     << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << endl;
      }
  }
Ray2d::Ray2d(const Pos2d &p1,const Vector2d &vdir)
  : Linear2d(), cgsr(p1.ToCGAL(),vdir.ToCGAL()) {}

//! @brief Comparison operator.
bool Ray2d::operator==(const Ray2d &other) const
  {
    bool retval= false;
    if(this==&other)
      retval= true;
    else
      {
        retval= Linear2d::operator==(other);
        if(retval)
          retval= (cgsr==other.cgsr); 
       }
    return retval;
  }

void Ray2d::TwoPoints(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Ray2d(p1,p2); }

Dir2d Ray2d::GetDir(void) const
  { return Dir2d(cgsr.direction()); }
Vector2d Ray2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return the squared distance 
//! from the point to the ray.
GEOM_FT Ray2d::dist2(const Pos2d &p) const
  {
    Line2d r= getSupportLine();
    Pos2d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projection inside half-line.
    const Vector2d vDir= VDir();
    const Vector2d v= proj-getFromPoint();
    const GEOM_FT dt= dot(v,vDir);
    if(dt<0) //Projection outside half-line.
      retval= std::max(retval,p.dist2(getFromPoint()));
    return retval;
  }

//! @brief Return the distance 
//! from the point to the ray.
GEOM_FT Ray2d::dist(const Pos2d &p) const
  { return sqrt_FT(dist2(p)); }

bool Ray2d::intersects(const Line2d &r) const
  { return do_intersect(r.cgr,cgsr); }

//! @brief Return the intersection of the ray with the plane
//! defined by the equation coord_i= d.
GeomObj2d::list_Pos2d Ray2d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= getSupportLine().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= getSupportLine().getLambda(i,d,i_);
        if(l<0.0)
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the point intersection of the line and the ray, if it
//! doesn't exists return an empty list.
GeomObj2d::list_Pos2d Ray2d::getIntersection(const Line2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgsr,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << getClassName() << "::" << __FUNCTION__
	         << "; unknown error." << endl
                 << "sg: " << *this << endl
                 << "r: " << r << endl;
          }
      }
    return retval;
  }

//! @brief Return the point intersection of both lines, if doesn't exists
//! returns an empty list.
GeomObj2d::list_Pos2d Ray2d::getIntersection(const Ray2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(*this == r2)
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; rays are the same, all its points belong"
	     << " to the intersection." << std::endl;
        return retval;
      }
    if(intersects(r2))
      {
        CGAL::Object result;
        Pos2d ptoi;
        result = CGAL::intersection(this->cgsr,r2.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "intersection(Ray2d,Ray2d): unknown error." 
                 << endl;
          }
      }
    return retval;
  }


//! @brief Applies to the ray the transformation argument.
void Ray2d::Transform(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transform(getFromPoint());
    const Pos2d p2= trf2d.Transform(Point(100));
    (*this)= Ray2d(p1,p2);
  }

void Ray2d::Print(std::ostream &os) const
  { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
void Ray2d::Plot(Plotter &psos) const
  {
    //Ray is not drawn, it must be clipped first.
  }

