# -*- coding: utf-8 -*-

import xc_base
import geom
import math

pol1=geom.Polilinea3d()
pol2=geom.Polilinea3d()

pol1.agregaVertice(geom.Pos3d(0,0,0))
pol1.agregaVertice(geom.Pos3d(1,0,0))
pol1.agregaVertice(geom.Pos3d(1,1,0))
pol1.agregaVertice(geom.Pos3d(0,1,0))

longPol1=pol1.getLongitud()

o=geom.Pos3d(0.5,0,0)
p1=geom.Pos3d(0.5,1,0)
p2=geom.Pos3d(0.5,0,1)

plano=geom.Plane3d(o,p1,p2)

lp= pol1.getIntersection(plano)
ptInt= lp[0]

ratio1=(longPol1-3)/3.
ratio2= ptInt.distPos3d(o)

# print "ratio1= ", ratio1
# print "ratio2= ", ratio2

import os
fname= os.path.basename(__file__)
if (abs(ratio1)<1e-10) and (abs(ratio2)<1e-10):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


