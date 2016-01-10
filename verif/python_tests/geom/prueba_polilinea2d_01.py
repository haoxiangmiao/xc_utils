# -*- coding: utf-8 -*-

import xc_base
import geom
import math

pol1=geom.Polilinea2d()
pol2=geom.Polilinea2d()

pol1.agregaVertice(geom.Pos2d(0,0))
pol1.agregaVertice(geom.Pos2d(1,0))
pol1.agregaVertice(geom.Pos2d(1,1))
pol1.agregaVertice(geom.Pos2d(0,1))

longPol1=pol1.getLongitud()
pol2=pol1.offset(-0.25)
longPol2=pol2.getLongitud()

ratio1=(longPol1-3)/3.
ratio2=(longPol2-2)/2.

if math.fabs(ratio1)<1e-10 and math.fabs(ratio2)<1e-10:
    print "test polilinea 01: ok."
else:
    print "test polilinea 01: ERROR."

