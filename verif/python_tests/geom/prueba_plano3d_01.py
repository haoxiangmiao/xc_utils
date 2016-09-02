import xc_base
import geom
o=geom.Pos3d(0,0,0)
p1=geom.Pos3d(1,0,0)
p2=geom.Pos3d(0,1,0)

plano=geom.Plano3d(o,p1,p2)
normal=plano.getNormal()
base1=plano.getBase1()
base2=plano.getBase2()
tp=plano.tipo()

import os
fname= os.path.basename(__file__)
if normal.x==0 and normal.y==0 and normal.z==1:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


