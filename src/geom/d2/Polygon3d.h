// -*-c++-*-
//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//Polygon3d.h

#ifndef POLYGON3D_H
#define POLYGON3D_H

#include "xc_utils/src/geom/d2/D2to3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
#include "../cgal_types.h"


//! @ingroup GEOM
//
//! @brief Polígono en tres dimensiones.
class Polygon3d: public D2to3d
  {
    Polygon2d plg2d;

  protected:
    Polygon3d(const Ref2d3d &rf,const Polygon2d &p)
      : D2to3d(rf), plg2d(p) {}

  public:
    Polygon3d(void): D2to3d(),plg2d() {}
    Polygon3d(const Polygon3d &other)
      :  D2to3d(other),plg2d(other.plg2d) {}
    template <typename InputIterator>
    Polygon3d(InputIterator first,InputIterator last);
    Polygon3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Polygon3d &operator =(const Polygon3d &other) 
      {
	D2to3d::operator=(other);
        plg2d=other.plg2d;
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Polygon3d(*this); }

    inline void push_back(const Pos3d &p)
      { plg2d.push_back(to_2d(p)); }

    inline virtual unsigned int GetNumVertices(void) const
      { return plg2d.GetNumVertices(); }
    inline virtual unsigned int GetNumLados(void) const
      { return plg2d.GetNumLados(); }
    //! @brief Return the length of the object.
    inline GEOM_FT getLength(void) const
      { return plg2d.getLength(); }
    //! @brief Return the area of the object.
    inline GEOM_FT getArea(void) const
      { return plg2d.getArea(); }
    std::vector<Polygon3d> getTributaryPolygons(void) const;
    inline std::vector<double> getTributaryAreas(void) const
      { return plg2d.getTributaryAreas(); }
    //! @brief Return the position of the i-th vertex.
    inline Pos3d Vertice(unsigned int i) const
      { return to_3d(plg2d.Vertice(i)); }
    //! @brief Return the position of the i-th vertex
    //! (0 based: j=0..GetNumVertices()-1)
    inline Pos3d Vertice0(unsigned int j) const
      { return to_3d(plg2d.Vertice0(j)); }
    GeomObj::list_Pos3d getVertexList(void) const;
    Segment3d Lado0(unsigned int i) const;
    Segment3d Lado(unsigned int i) const;

    inline bool Horario(void) const
      { return plg2d.Horario(); }
    inline bool Antihorario(void) const
      { return plg2d.Antihorario(); }

    Plane getPlaneFromSide0(unsigned int i) const;
    Plane getPlaneFromSide(unsigned int i) const;

    Pos3d getCenterOfMass(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Iz(void) const;

    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    bool In(const Pos3d &p,const double &tol);
    bool TocaCuadrante(const int &) const;

    GEOM_FT distSigno(const Pos3d &p,const bool &sentido_horario= false) const;
    GEOM_FT dist(const Pos3d &p) const;
    GEOM_FT distSigno2(const Pos3d &p,const bool &sentido_horario= false) const;
    GEOM_FT dist2(const Pos3d &p) const;

    std::list<Polygon3d> Corta(const Plane &p) const;

    void Print(std::ostream &os) const;
  };

template <typename InputIterator>
Polygon3d::Polygon3d(InputIterator first,InputIterator last)
  : D2to3d(),plg2d()
  {
    InputIterator i= first;
    const Pos3d p1= *i; i++;
    const Pos3d p2= *i; i++;
    const Pos3d p3= *i; i++;
    ThreePoints(p1,p2,p3);
    push_back(p1);
    push_back(p2);
    push_back(p3);
    for(;i!=last;i++)
      push_back(*i);
  }

inline std::list<Polygon3d> corta(const Polygon3d &pol,const Plane &pl)
  { return pol.Corta(pl); }

#endif
