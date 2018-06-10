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
//Cuadrilatero2d.h

#ifndef CUADRILATERO2D_H
#define CUADRILATERO2D_H

#include "Poligono2d.h"

class Triangle2d;
class MatrizPos2d;

// Orden de los vértices 1->2->3->4.
//
// 4 +---------------+ 3
//   |               |
//   |               |
//   |               |
// 1 +---------------+ 2


//! @ingroup GEOM
//
//! @brief Cuadrilátero en dos dimensiones.
class Cuadrilatero2d: public Poligono2d
  {
  public:
    Cuadrilatero2d(void): Poligono2d() 
      {
        push_back(Pos2d(0,0));
        push_back(Pos2d(1,0));
        push_back(Pos2d(1,1));
        push_back(Pos2d(0,1));
      }
    Cuadrilatero2d(const Cuadrilatero2d &otro): Poligono2d(otro)
      {}
    Cuadrilatero2d(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3,const Pos2d &p4);
    Cuadrilatero2d &operator=(const Cuadrilatero2d &otro)
      {
	Poligono2d::operator=(otro);
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Cuadrilatero2d(*this); }
    inline void push_back(const Pos2d &p)
      {
        if(GetNumVertices()<5)
	  Poligono2d::push_back(p.ToCGAL());
      }
    Triangle2d getFirstTriangle(void) const;
    Triangle2d getSecondTriangle(void) const;
    MatrizPos2d genMesh(int n1,int n2) const;
    MatrizPos2d genBilinMesh(const size_t &n1,const size_t &n2) const;
  };
#endif
