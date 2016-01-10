# -*- coding: utf-8 -*-

#Ángulo entre dos planos.
#Ejemplo 1.7 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math
import teoria_bloques

alpha1=math.radians(30)
beta1=math.radians(320)
alpha2=math.radians(50)
beta2=math.radians(160)

p=geom.Pos3d(0,0,0)

plBuz1=teoria_bloques.calcPlanoBuzamiento(alpha1,beta1,p)
P1=geom.SemiEspacio3d(plBuz1)

plBuz2=teoria_bloques.calcPlanoBuzamiento(alpha2,beta2,p)
P2=geom.SemiEspacio3d(plBuz2)

delta=P1.anguloConSemiEspacio3d(P2)
deltaTeor=math.acos(0.1968/0.8907/0.99)

ratio1= math.fabs(deltaTeor-delta)/deltaTeor
if math.fabs(ratio1)<0.021:
    print "test SemiEspacio3d 01: ok."
else:
    print "test SemiEspacio3d 01: ERROR."

