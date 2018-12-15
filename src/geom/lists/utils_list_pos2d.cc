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
//utils_list_pos2d.cc

#include "utils_list_pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include <plotter.h>
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/d2/BND2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"

void plot(Plotter &plt,const GeomObj::list_Pos2d &l)
  {
    for(GeomObj::list_Pos2d::const_iterator i= l.begin();i!=l.end();i++)
      (*i).Plot(plt);
  }


//! @brief Moves the points of the list.
void mueve(GeomObj::list_Pos2d &l,const Vector2d &v)
  {
    for(register GeomObj::list_Pos2d::iterator j=l.begin();j != l.end();j++)
      (*j)= (*j) + v;
  }

//! @brief Applies the transformation to the vertices.
void transform(GeomObj::list_Pos2d &l,const Trf2d &t)
  { t.Transform(l.begin(),l.end()); }

//! @brief Return the upper right corner of the bounding rectangle. 
Pos2d getPMax(const GeomObj::list_Pos2d &l)
  { return Pos2d(l.GetMax(1),l.GetMax(2)); }

//! @brief Return the lower left corner of the bounding rectangle. 
Pos2d getPMin(const GeomObj::list_Pos2d &l)
  { return Pos2d(l.GetMin(1),l.GetMin(2)); }

//! @brief Return the bounding rectangle. 
BND2d getBnd(const GeomObj::list_Pos2d &l)
  { return BND2d(getPMin(l),getPMax(l)); }

//! @brief Compute the cover of the positions in the polygon.
std::deque<GEOM_FT> &getRecubrimientos(const GeomObj::list_Pos2d &l,const Polygon2d &plg)
  {
    const size_t sz= l.size();
    static std::deque<GEOM_FT> retval;
    retval.resize(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= plg.GetRecubrimiento(l[i]);
    return retval;
  }
