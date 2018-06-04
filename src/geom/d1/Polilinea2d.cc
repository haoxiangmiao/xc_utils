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
//Polilinea2d.cc

#include "Polilinea2d.h"
#include "Segmento2d.h"
#include <plotter.h>

#include "xc_utils/src/geom/listas/utils_list_pos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"


#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"

//! @brief Constructor por defecto.
Polilinea2d::Polilinea2d(void)
  : Linea2d(), GeomObj::list_Pos2d() {}

//! @brief Constructor.
Polilinea2d::Polilinea2d(const GeomObj::list_Pos2d &l)
  : Linea2d(), GeomObj::list_Pos2d(l){}

//! @brief Constructor.
Polilinea2d::Polilinea2d(const ListaPos2d &l)
  : Linea2d(), GeomObj::list_Pos2d(l.getPoints()){}

const Pos2d *Polilinea2d::AgregaVertice(const Pos2d &p)
  {
    GeomObj::list_Pos2d::push_back(p);
    return &(*GeomObj::list_Pos2d::rbegin());
  }

size_t Polilinea2d::GetNumSegmentos(void) const
  {
    size_t retval= GetNumVertices();
    if(retval>0)
      retval-=1;
    return retval;
  }

//! @brief Applies the transformation to the points que se pasa como parámetro.
void Polilinea2d::Transforma(const Trf2d &trf2d)
  { trf2d.Transforma(begin(),end()); }

//! @brief Return true if the point is in the polyline.
bool Polilinea2d::In(const Pos2d &p, const double &tol) const
  {
    for(register const_iterator j=begin();j != end();j++)
      if(GetSegmento(j).In(p,tol)) return true;
    return false;
  }

//! @brief Return the maximum value of the i coordinate.
GEOM_FT Polilinea2d::GetMax(unsigned short int i) const
  { return GeomObj::list_Pos2d::GetMax(i); }

//! @brief Return the minimum value of the i coordinate.
GEOM_FT Polilinea2d::GetMin(unsigned short int i) const
  { return GeomObj::list_Pos2d::GetMin(i); }

//! @brief Return una Polilinea2d con los vertices cuya coordenada i
//! es mayor que d.
Polilinea2d Polilinea2d::GetMayores(unsigned short int i,const GEOM_FT &d) const
  {
    Polilinea2d retval(GeomObj::list_Pos2d::GetMayores(i,d));
    return retval;
  }
//! @brief Return una Polilinea2d con los vertices cuya coordenada i
//! es menor que d.
Polilinea2d Polilinea2d::GetMenores(unsigned short int i,const GEOM_FT &d) const
  {
    Polilinea2d retval(GeomObj::list_Pos2d::GetMenores(i,d));
    return retval;
  }
// //Return the intersection of the polyline with the plane defined by
// // the equation coord_i= d
// Polilinea2d::list_Pos2d Polilinea2d::Int(unsigned short int i,const double &d) const
//   {
//     list_Pos2d l_int; //Lista de intersecciones
// 	const_iterator ultimo= end();
//     ultimo--;
//     for(register const_iterator j=begin();j != ultimo;j++)
//       {
//         Segmento2d s= GetSegmento(j);
//         list_Pos2d l_temp= s.Int(i,d);
//         copy(l_temp.begin(),l_temp.end(), back_inserter(l_int)); 
//       }
// 	//l_int.unique();
//      return l_int;
//   }
// //Return the 2D polyline defined by the vertex obtained from cutting
// // this polyline with the plane defined by
// // the equation coord_i= d
// Polilinea2d Polilinea2d::Corta(unsigned short int i,const double &d) const
//   {
//     Polilinea2d result; //Lista de intersecciones
// 	const_iterator ultimo= end();
//     ultimo--;
//     for(register const_iterator j=begin();j != ultimo;j++)
//       {
//         Segmento2d s= GetSegmento(j);
//         list_Pos2d l_temp= s.Int(i,d);
//         result.push_back(*j);
//         if (!l_temp.empty()) result.push_back(*l_temp.begin());
//       }
//      result.push_back(*ultimo);
//      //result.unique();
//      return result;
//   }

//! @brief Return el vértice i-ésimo (el primero es el 1).
const Pos2d &Polilinea2d::Vertice(const size_t &i) const
  { return GeomObj::list_Pos2d::operator[](i-1); }

//! @brief Return una polilínea paralela a ésta a la distancia
//! que se pasa como parámetro. Si la distance es positiva,
//! la nueva polilínea quedará a la derecha de la anterior.
Polilinea2d Polilinea2d::Offset(const GEOM_FT &d) const
  {
    ListaPos2d tmp(*this);
    Polilinea2d retval(tmp.Offset(d));
    return retval;
  }

//! @brief Return el segmento a continuación del vértice *i
Segmento2d Polilinea2d::GetSegmento(const const_iterator &i) const
  {
    const_iterator j= i; j++;
    if(j==end())
      {
        std::cerr << "Polilinea2d::GetSegmento: el vértice es el último"
             << " de la polilinea." << std::endl;
        return Segmento2d();
      }
    return Segmento2d(*i,*j);
  }

//! @brief Return el segmento i-ésimo (el primero es el 1).
Segmento2d Polilinea2d::GetSegmento(const size_t &i) const
  {
    const size_t ns= GetNumSegmentos();
    if(i>ns)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; you asked for the " << i
	        << "-th and " << ns
                << "-th is the last one." << std::endl;
    Segmento2d s(Vertice(i),Vertice(i+1));
    return s;
  }

GEOM_FT Polilinea2d::Ix(void) const
  {
    std::cerr << "Polilinea2d Ix() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT Polilinea2d::Iy(void) const
  {
    std::cerr << "Polilinea2d Iy() not implemented" << std::endl;
    return 0.0;
  }
GEOM_FT Polilinea2d::Iz(void) const
  {
    std::cerr << "Polilinea2d Iz() not implemented" << std::endl;
    return 0.0;
  }

//! @brief Suponemos que p es vertice de la Polilinea2d
//! Return el trozo de Polilinea2d:
//! hasta p si sgn < 0
//! desde p si sgn >= 0
Polilinea2d Polilinea2d::Separa(const Pos2d &p,const short int &sgn) const
  {
    Polilinea2d result;
    const_iterator i= find(p);
    if (i == end()) return result;
    if (sgn < 0)
      copy(begin(),++i,back_inserter(result));
    else
      copy(i,end(),back_inserter(result));
    return result;
  }

//! @brief Return the points of intersection of the polyline with
//! the argument.
GeomObj::list_Pos2d Polilinea2d::Interseccion(const Recta2d &r) const
  {
    list_Pos2d retval;
    register const_iterator j=begin();
    register const_iterator k= j;k++;
    for(;k != end();j++,k++)
      {
        Segmento2d s(*j,*k);
        list_Pos2d tmp= interseccion(r,s);
        if(!tmp.empty())
          retval.Agrega(tmp);
      }
    return retval;
  }

//! @brief Return the points of intersection of the polyline with
//! the argument.
GeomObj::list_Pos2d Polilinea2d::Interseccion(const SemiRecta2d &sr) const
  {
    list_Pos2d retval;
    register const_iterator j=begin();
    register const_iterator k= j;k++;
    for(;k != end();j++,k++)
      {
        Segmento2d s(*j,*k);
        list_Pos2d tmp= interseccion(sr,s);
        if(!tmp.empty())
          retval.Agrega(tmp);
      }
    return retval;
  }

//! @brief Return the points of intersection of the polyline with
//! the argument.
GeomObj::list_Pos2d Polilinea2d::Interseccion(const Segmento2d &sg) const
  {
    list_Pos2d retval;
    register const_iterator j=begin();
    register const_iterator k= j;k++;
    for(;k != end();j++,k++)
      {
        Segmento2d s(*j,*k);
        list_Pos2d tmp= interseccion(sg,s);
        if(!tmp.empty())
          retval.Agrega(tmp);
      }
    return retval;
  }

/**
   * @param i1 iterator to the first point.
   * @param i2 iterator to the second point.
   * @param pMaxDist pointer to the maximum distance of _line[return index].
   * @return the index of the point farthest fromthe segment (t1,t2).
   */
Polilinea2d::iterator Polilinea2d::getFarthestPointFromSegment(iterator it1, iterator it2, GEOM_FT &pMaxDist)
  {
    // Keep track of the point with the maximum distance.
    iterator maxIt = it1;
    maxIt++;
    Segmento2d s= Segmento2d(*it1,*it2);
    GEOM_FT maxDist= s.dist(*maxIt);

    iterator it = it1;
    it++;
    while(it != it2)
      {
        Segmento2d s= Segmento2d(*it1,*it2);
        GEOM_FT dist= s.dist(*it);
        if(dist > maxDist)
	  {
            maxIt = it;
            maxDist = dist;
          }

        it++;
      }
    // Assign pMaxDist.
    pMaxDist = maxDist;
    return maxIt;
  }


void Polilinea2d::Print(std::ostream &stream) const
  {
    if(empty()) return;
    register const_iterator i= begin();
    stream << *i; i++;
    for(; i!=end(); i++)
      stream << ", " << *i;
  }
void Polilinea2d::Plot(Plotter &plotter) const
  {
    if(size()<2) return;
    register const_iterator i= begin();
    Pos2d pto1= *i; i++;
    for(; i!=end(); i++)
      {
        Pos2d pto2= *i;
        plotter.fline(pto1.x(),pto1.y(),pto2.x(),pto2.y());
        pto1= pto2;
      }
  }

GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const Recta2d &r)
  { return p.Interseccion(r); }
GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const SemiRecta2d &sr)
  { return p.Interseccion(sr); }
GeomObj::list_Pos2d interseccion(const Polilinea2d &p,const Segmento2d &sg)
  { return p.Interseccion(sg); }
GeomObj::list_Pos2d interseccion(const Recta2d &r,const Polilinea2d &p)
  { return p.Interseccion(r); }
GeomObj::list_Pos2d interseccion(const SemiRecta2d &sr,const Polilinea2d &p)
  { return p.Interseccion(sr); }
GeomObj::list_Pos2d interseccion(const Segmento2d &sg,const Polilinea2d &p)
  { return p.Interseccion(sg); }
