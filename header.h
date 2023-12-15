#ifndef HEADER_H
#define HEADER_H

//#include <opencv2/viz.hpp>
//#include <opencv2/viz/viz3d.hpp>
//#include <opencv2/viz/vizcore.hpp>
//#include <opencv2/viz/widgets.hpp>
#include <array>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkAxisActor.h>
#include <vtkArrowSource.h>
#include <vtkBMPReader.h>
#include <vtkButtonWidget.h>
#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkCell.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkClipDataSet.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkColorTransferFunction.h>
#include <vtkCubeSource.h>
#include <vtkCutter.h>
#include <vtkCylinderSource.h>
#include <vtkDataSetMapper.h>
#include <vtkEllipticalButtonSource.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkFloatArray.h>
#include <vtkFlyingEdges3D.h>
#include <vtkGlyph3D.h>
#include <vtkImageActor.h>
#include <vtkImageBlend.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkImageRange3D.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReslice.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkLine.h>
#include <vtkLookupTable.h>
#include <vtkMarchingCubes.h>
#include <vtkMaskPoints.h>
#include <vtkMatrix4x4.h>
#include <vtkMergePoints.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkOutlineFilter.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPLYReader.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolygon.h>
#include <vtkProbeFilter.h>
#include <vtkProp3DButtonRepresentation.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkSuperquadricSource.h>
#include <vtkStringArray.h>
#include <vtkStripper.h>
#include <vtkStructuredPointsReader.h>
#include <vtkTextProperty.h>
#include <vtkTexture.h>
#include <vtkTransform.h>
#include <vtkTransformTextureCoords.h>
#include <vtkTriangle.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkXMLPolyDataReader.h>

// vtkFlyingEdges3D was introduced in VTK >= 8.2
#if VTK_MAJOR_VERSION >= 9 || (VTK_MAJOR_VERSION >= 8 && VTK_MINOR_VERSION >= 2)
#define USE_FLYING_EDGES
#else
#undef USE_FLYING_EDGES
#endif

#ifdef USE_FLYING_EDGES
#include <vtkFlyingEdges3D.h>
#else
#include <vtkMarchingCubes.h>
#endif

//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)

#endif // HEADER_H
