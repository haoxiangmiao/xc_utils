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
//Segment3d.h

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "Linear3d.h"
#include "Line3d.h"
#include "Ray3d.h"
#include "../pos_vec/Pos3d.h"

class Dir3d;


//! @ingroup GEOM
//
//! @brief Segment en tres dimensiones.
class Segment3d : public Linear3d
  {
    CGSegment_3 cgseg;
  public:
    Segment3d(void);
    Segment3d(const CGSegment_3 &r);
    Segment3d(const Pos3d &p1,const Pos3d &p2);
    Segment3d(const Segment3d &r);
    Segment3d &operator=(const Segment3d &r);

    const CGSegment_3 &ToCGAL(void) const
      { return cgseg; }
    virtual GeomObj *clon(void) const;
    void TwoPoints(const Pos3d &p1,const Pos3d &p2);
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    Line3d getSupportLine(void) const;
    Pos3d getFromPoint(void) const;
    Pos3d getToPoint(void) const;
    GEOM_FT getSlope(void) const;
    const Pos3d Point(const int &i) const;
    Pos3d PtoParametricas(const GEOM_FT &lambda) const;
    double getParamCooNatural(const GEOM_FT &) const;
    Pos3d PtoCooNatural(const GEOM_FT &chi) const;
    GEOM_FT getLambda(const Pos3d &p) const;
    bool EsDegenerada(void) const;
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    virtual GEOM_FT dist2(const Pos3d &p) const;
    GEOM_FT dist(const Pos3d &p) const;
    void Put(const Pos3d &p1,const Pos3d &p2);

    bool Paralelo(const Line3d &r) const;
    bool Paralelo(const Ray3d &sr) const;
    bool Paralelo(const Segment3d &r) const;

    GeomObj3d::list_Pos3d getIntersection(unsigned short int, const double &) const;
    GeomObj3d::list_Pos3d getIntersection(const Line3d &r) const;
    GeomObj3d::list_Pos3d getIntersection(const Ray3d &sr) const;
    GeomObj3d::list_Pos3d getIntersection(const Segment3d &sg) const;

    virtual GEOM_FT getLength(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    Dir3d GetDir(void) const;
    Vector3d VDir(void) const;
    GEOM_FT getAngle(const Vector3d &v) const;
    GEOM_FT getAngle(const Segment3d &v) const;
    friend GEOM_FT angle(const Segment3d &r,const Vector3d &v);
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;
    friend bool operator==(const Segment3d &r1,const Segment3d &r2);
    void Print(std::ostream &os) const;
    
  };

inline GEOM_FT dist2(const Pos3d &p,const Segment3d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Segment3d &r,const Pos3d &p)
  { return dist2(p,r); }
GEOM_FT dist(const Pos3d &p,const Segment3d &r);
inline GEOM_FT dist(const Segment3d &r,const Pos3d &p)
  { return dist(p,r); }

inline bool paralelas(const Segment3d &sg,const Line3d &r)
  { return sg.Paralelo(r); }
inline bool paralelas(const Line3d &r, const Segment3d &sg)
  { return paralelas(sg,r); }
inline bool paralelas(const Segment3d &sg,const Ray3d &sr)
  { return sg.Paralelo(sr); }
inline bool paralelas(const Ray3d &sr, const Segment3d &sg)
  { return paralelas(sg,sr); }
inline bool paralelas(const Segment3d &r1,const Segment3d &r2)
  { return r1.Paralelo(r2); }

inline bool colineales(const Segment3d &sg,const Line3d &r)
  { return colineales(sg.getSupportLine(),r); }
inline bool colineales(const Line3d &r,const Segment3d &sg)
  { return colineales(sg,r); }
inline bool colineales(const Segment3d &sg,const Ray3d &sr)
  { return colineales(sg.getSupportLine(),sr); }
inline bool colineales(const Ray3d &sr,const Segment3d &sg)
  { return colineales(sg,sr); }
inline bool colineales(const Segment3d &sg1,const Segment3d &sg2)
  { return colineales(sg1,sg2.getSupportLine()); }

inline GeomObj3d::list_Pos3d intersection(const Segment3d &sg,const Line3d &r)
  { return sg.getIntersection(r); }
inline GeomObj3d::list_Pos3d intersection(const Line3d &r, const Segment3d &sg)
  { return sg.getIntersection(r); }
inline GeomObj3d::list_Pos3d intersection(const Segment3d &sg,const Ray3d &sr)
  { return sg.getIntersection(sr); }
inline GeomObj3d::list_Pos3d intersection(const Ray3d &sr, const Segment3d &sg)
  { return sg.getIntersection(sr); } 
inline GeomObj3d::list_Pos3d intersection(const Segment3d &sg1,const Segment3d &sg2)
  { return sg1.getIntersection(sg2); }



#endif
