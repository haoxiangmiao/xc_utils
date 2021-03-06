# -*- coding: utf-8 -*-

from __future__ import print_function
import math
from misc_utils import staircase_function as scf

xi= [0.0,1.0,2.0,3.0]

function= scf.StairCaseFunction(xi,[3.0,2.0,1.0,0.0])

retvals= []
for x in xi:
  retvals.append(function(x))

retvalTeor= [3.0, 2.0, 1.0, 0.0]
error= 0.0
for i in range(0,len(retvals)):
  error+= (retvals[i]-retvalTeor[i])**2

error= math.sqrt(error)

import os
fname= os.path.basename(__file__)
if (error<1e-15):
  print("test ",fname,": ok.")
else:
  print("test ",fname,": ERROR.")

  
