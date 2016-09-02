# -*- coding: utf-8 -*-

import xc_base
import geom
import math

pos1=geom.Pos3d(0.5,0,0)
ptoAplica=geom.Pos3d(5,0,0)
vectorDir=geom.Vector3d(0,2,0)
vec1=geom.VDesliz3d(ptoAplica,vectorDir)

brazo=vec1.getOrg().x-pos1.x
m=vec1.getMomentoPos3d(pos1)

fuerza=vec1.y
mTeor=fuerza*brazo

import os
fname= os.path.basename(__file__)
if m.x==0 and m.y==0and m.z==mTeor:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


