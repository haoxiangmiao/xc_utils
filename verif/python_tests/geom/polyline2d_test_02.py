# -*- coding: utf-8 -*-
#Home made test. Verification of Douglas Peucker algorithm implementation.
from __future__ import print_function
import xc_base
import geom
import math
vertices= [  geom.Pos2d(0,0), #1
  geom.Pos2d(0.5,0.09), #2 (to erase)
  geom.Pos2d(1,0), #3
  geom.Pos2d(1.001,0.5), #4 (to erase)
  geom.Pos2d(1,1), #5
  geom.Pos2d(2,1), #6
  geom.Pos2d(2,2), #7
  geom.Pos2d(1,2), #8
  geom.Pos2d(1,1), #9
  geom.Pos2d(0,1) #10
  ]

polA= geom.Polyline2d()

for v in vertices:
  polA.appendVertex(v)

polB= geom.Polyline2d(polA)

polB.appendVertex(geom.Pos2d(0,0)) #11 CAN BE CLOSED.

nv0A= polA.getNumVertices()
polA.simplify(0.1)
nv1A= polA.getNumVertices()

nv0B= polB.getNumVertices()
polB.simplify(0.1)
nv1B= polB.getNumVertices()

nv0ATeor= len(vertices)
nv1ATeor= nv0ATeor-2
ratio0=(nv0A-nv0ATeor)/nv0ATeor
ratio1=(nv1A-nv1ATeor)/nv1ATeor
nv0BTeor= len(vertices)+1
nv1BTeor= nv0BTeor-2
ratio3=(nv0B-nv0BTeor)/nv0BTeor
ratio4=(nv1B-nv1BTeor)/nv1BTeor

'''
print('****isClosed: ', polA.isClosed(1e-6))
print('vertices before simplify: ', nv0A)
print('ratio0= ', ratio0)
print('vertices after simplify: ', nv1A)
print('ratio1= ', ratio1)

print('****isClosed: ', polB.isClosed(1e-6))
print('vertices before simplify: ', nv0B)
print('ratio3= ', ratio3)
print('vertices after simplify: ', nv1B)
print('ratio4= ', ratio4)
'''

import os
fname= os.path.basename(__file__)
if math.fabs(ratio0)<1e-10 and math.fabs(ratio1)<1e-10 and math.fabs(ratio3)<1e-10 and math.fabs(ratio4)<1e-10:
  print("test ",fname,": ok.")
else:
  print("test ",fname,": ERROR.")


