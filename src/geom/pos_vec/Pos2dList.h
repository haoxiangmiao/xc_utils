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
//Pos2dList.

#ifndef LISTAPOS2D_H
#define LISTAPOS2D_H

#include "../d2/GeomObj2d.h"

class Polygon2d;

//! @ingroup GEOM
//
//! @brief List of 2D positions.
class Pos2dList: public GeomObj2d
  {
  public:
    typedef GeomObj::list_Pos2d list_Pos2d;
    typedef GeomObj::list_Pos2d::iterator point_iterator;
    typedef GeomObj::list_Pos2d::const_iterator point_const_iterator;
  protected:
    list_Pos2d lista_ptos;
    Pos2d &operator[](const size_t &i);
  public:
    Pos2dList(void);
    explicit Pos2dList(const GeomObj::list_Pos2d &l);
    virtual GeomObj *clon(void) const
      { return new Pos2dList(*this); }
    inline size_t getNumberOfPoints(void) const
      { return lista_ptos.size(); }
    inline point_const_iterator points_begin(void) const
      { return lista_ptos.begin(); }
    const point_const_iterator points_end(void) const
      { return lista_ptos.end(); }
    inline short unsigned int Dimension(void) const
      { return 0; }

    const GeomObj::list_Pos2d &getPoints(void) const
      { return lista_ptos; }
    const Pos2d &operator[](const size_t &i) const;

    const Pos2d *appendPoint(const Pos2d &p);
    void appendPointPy(const Pos2d &p);
    template <class InputIterator>
    //! Insert the vertices between [first,last).
    inline void assign(InputIterator first, InputIterator last)
      { lista_ptos.assign(first,last); }
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;

    //! @brief Product of inertia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const
      { return 0.0; }
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const
      { return 0.0; }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    Pos2dList GetMayores(unsigned short int i,const GEOM_FT &d) const;
    Pos2dList GetMenores(unsigned short int i,const GEOM_FT &d) const;
    const Pos2d &Point(const size_t &i) const;
    Pos2d getCenterOfMass(void) const
      { return lista_ptos.getCenterOfMass(); }

    void Transform(const Trf2d &trf2d);
    Pos2dList Offset(const GEOM_FT &d) const;

    std::deque<GEOM_FT> &GetSeparaciones(void) const;
    std::deque<GEOM_FT> &GetRecubrimientos(const Polygon2d &) const;
    double GetSeparacionMedia(void) const;

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;
  };

#endif






