import vtk
from vtk_utils import displayVtk
outputFileName= "/tmp/plot_cone.jpeg"
 
# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
WIDTH=640
HEIGHT=480
renWin.SetSize(WIDTH,HEIGHT)
 
# create cone
cone = vtk.vtkConeSource()
cone.SetResolution(60)
cone.SetCenter(-2,0,0)
 
# mapper
coneMapper = vtk.vtkPolyDataMapper()
coneMapper.SetInput(cone.GetOutput())
 
# actor
coneActor = vtk.vtkActor()
coneActor.SetMapper(coneMapper)
 
# assign actor to the renderer
ren.AddActor(coneActor)
 
import os
os.system("rm -f "+outputFileName)
renWin.Render()
displayVtk.plotToFile(outputFileName,renWin,ren,750,400)
