#include "utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

vtkSmartPointer<vtkImageData>  Utils::MyFunction()
{
    vtkSmartPointer<vtkImageData> myObject = vtkSmartPointer<vtkImageData>::New();
    std::cout << "MyFunction::myObject reference count = " << myObject->GetReferenceCount() << std::endl;
    return myObject;
}

void Utils::Qt_test()
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkSphereSource> sphereSource;
    vtkNew<vtkPolyDataMapper> sphereMapper;
    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> sphereActor;
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(colors->GetColor4d("LightSeaGreen").GetData());
    vtkNew<vtkRenderer> rendererLeftTop;
    rendererLeftTop->AddActor(sphereActor);
    rendererLeftTop->SetBackground(colors->GetColor3d("Silver").GetData());
    renderWindowLeftTop->AddRenderer(rendererLeftTop);
    renderWindowLeftTop->SetWindowName("leftTop");

    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetHeight(3.0);
    cylinder->SetRadius(1.0);
    cylinder->SetResolution(10);

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(colors->GetColor4d("LightSeaGreen").GetData());

    vtkSmartPointer<vtkRenderer> rendererRightTop = vtkSmartPointer<vtkRenderer>::New();
    rendererRightTop->AddActor(cylinderActor);
    rendererRightTop->SetBackground(colors->GetColor3d("Silver").GetData());
    renderWindowRightTop->AddRenderer(rendererRightTop);
    renderWindowRightTop->SetWindowName("rightTop");
}

void Utils::test_ImgSlice()
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    vtkNew<vtkNamedColors> colors;

    vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
    cylinderSource->SetCenter(0,0,0);
    cylinderSource->SetHeight(3);
    cylinderSource->SetRadius(1);
    cylinderSource->SetResolution(3);

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinderSource->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(colors->GetColor3d("LightSeaGreen").GetData());
    cylinderActor->GetProperty()->SetOpacity(0.5);

    // Create a plane to cut,here it cuts in the XZ direction
    // XZ=normal=(1,0,0);XY =(0,0,1),YZ =(0,1,0)
    vtkNew<vtkPlane> plane1,plane2,plane3;
    plane1->SetOrigin(0, 0, 0);
    plane1->SetNormal(1, 0, 0);

    plane2->SetOrigin(0, 0, 0);
    plane2->SetNormal(0, 1, 0);

    plane3->SetOrigin(0, 0, 0);
    plane3->SetNormal(0, 0, 1);

    // Create cutter
    vtkSmartPointer<vtkCutter> cutter1 = vtkSmartPointer<vtkCutter>::New();
    cutter1->SetCutFunction(plane1);
    cutter1->SetInputConnection(cylinderSource->GetOutputPort());
    cutter1->Update();

    // Create cutter
    vtkSmartPointer<vtkCutter> cutter2 = vtkSmartPointer<vtkCutter>::New();
    cutter2->SetCutFunction(plane2);
    cutter2->SetInputConnection(cylinderSource->GetOutputPort());
    cutter2->Update();

    // Create cutter
    vtkSmartPointer<vtkCutter> cutter3 = vtkSmartPointer<vtkCutter>::New();
    cutter3->SetCutFunction(plane3);
    cutter3->SetInputConnection(cylinderSource->GetOutputPort());
    cutter3->Update();

    // Create cutterMapper
    vtkSmartPointer<vtkPolyDataMapper> cutterMapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    cutterMapper1->SetInputConnection(cutter1->GetOutputPort());
    cutterMapper1->SetResolveCoincidentTopologyToPolygonOffset();

    // Create cutterMapper
    vtkSmartPointer<vtkPolyDataMapper> cutterMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    cutterMapper2->SetInputConnection(cutter2->GetOutputPort());
    cutterMapper2->SetResolveCoincidentTopologyToPolygonOffset();

    // Create cutterMapper
    vtkSmartPointer<vtkPolyDataMapper> cutterMapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
    cutterMapper3->SetInputConnection(cutter3->GetOutputPort());
    cutterMapper3->SetResolveCoincidentTopologyToPolygonOffset();

    // Create a plane actor
    vtkSmartPointer<vtkActor> planeActor1 = vtkSmartPointer<vtkActor>::New();
    planeActor1->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
    planeActor1->GetProperty()->SetLineWidth(2);
    planeActor1->GetProperty()->SetAmbient(1.0);
    planeActor1->GetProperty()->SetDiffuse(0.0);
    planeActor1->SetMapper(cutterMapper1);

    vtkSmartPointer<vtkActor> planeActor2 = vtkSmartPointer<vtkActor>::New();
    planeActor2->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
    planeActor2->GetProperty()->SetLineWidth(2);
    planeActor2->GetProperty()->SetAmbient(1.0);
    planeActor2->GetProperty()->SetDiffuse(0.0);
    planeActor2->SetMapper(cutterMapper2);

    vtkSmartPointer<vtkActor> planeActor3 = vtkSmartPointer<vtkActor>::New();
    planeActor3->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());
    planeActor3->GetProperty()->SetLineWidth(2);
    planeActor3->GetProperty()->SetAmbient(1.0);
    planeActor3->GetProperty()->SetDiffuse(0.0);
    planeActor3->SetMapper(cutterMapper3);

    vtkSmartPointer<vtkRenderer> cylinderRender = vtkSmartPointer<vtkRenderer>::New();
    cylinderRender->AddActor(cylinderActor);
    cylinderRender->AddActor(planeActor1);
    cylinderRender->AddActor(planeActor2);
    cylinderRender->AddActor(planeActor3);
    cylinderRender->SetBackground(colors->GetColor3d("Silver").GetData());

    renderWindowLeftTop->AddRenderer(cylinderRender);

}

void Utils::test1()
{
    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->Render();

    renderWindowLeftTop->SetWindowName("TestVTKInstall");
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();

    std::cin.get();
}

void Utils::test2_1()
{
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetHeight(3.0);
    cylinder->SetRadius(1.0);
    cylinder->SetResolution(10);

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer);
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("RenderCylinder");

    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renderWindowLeftTop);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    iren->Initialize();
    iren->Start();
}

void Utils::test2_2_1()
{
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetHeight(3.0);
    cylinder->SetRadius(1.0);
    cylinder->SetResolution(10);

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer);
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("RenderCylinder-Lights");

    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renderWindowLeftTop);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    vtkSmartPointer<vtkLight> myLight = vtkSmartPointer<vtkLight>::New();
    myLight->SetColor(0, 1, 0);
    myLight->SetPosition(0, 0, 1);
    myLight->SetFocalPoint(
        renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight);

    vtkSmartPointer<vtkLight> myLight2 = vtkSmartPointer<vtkLight>::New();
    myLight2->SetColor(0, 0, 1);
    myLight2->SetPosition(0, 0, -1);
    myLight2->SetFocalPoint(
        renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight2);

    iren->Initialize();
    iren->Start();
}

void Utils::test2_2_2()
{
    std::string strFileName = "./data/texture.jpg";

    vtkSmartPointer< vtkJPEGReader > reader =
        vtkSmartPointer< vtkJPEGReader >::New();
    reader->SetFileName(strFileName.c_str());

    vtkSmartPointer< vtkTexture > texture =
        vtkSmartPointer< vtkTexture >::New();
    texture->SetInputConnection(reader->GetOutputPort());
    texture->InterpolateOn();

    vtkSmartPointer< vtkPlaneSource > plane =
        vtkSmartPointer< vtkPlaneSource >::New();
    vtkSmartPointer< vtkPolyDataMapper > mapper =
        vtkSmartPointer< vtkPolyDataMapper >::New();
    mapper->SetInputConnection(plane->GetOutputPort());

    vtkSmartPointer< vtkActor > actor =
        vtkSmartPointer< vtkActor >::New();
    actor->SetMapper(mapper);
    actor->SetTexture(texture);

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer);
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("TextureExample");

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renderWindowLeftTop);
    iren->Initialize();
    iren->Start();

}

void Utils::test2_3()
{
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInputConnection(cone->GetOutputPort());
    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cube->GetOutputPort());
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputConnection(sphere->GetOutputPort());

    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);
    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
    sphereActor->SetMapper(sphereMapper);


    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(coneActor);
    renderer1->SetBackground(1.0, 0.0, 0.0);
    renderer1->SetViewport(0.0, 0.0, 0.5, 0.5);
    vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
    renderer2->AddActor(cubeActor);
    renderer2->SetBackground(0.0, 1.0, 0.0);
    renderer2->SetViewport(0.5, 0.0, 1.0, 0.5);
    vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
    renderer3->AddActor(cylinderActor);
    renderer3->SetBackground(0.0, 0.0, 1.0);
    renderer3->SetViewport(0.0, 0.5, 0.5, 1.0);
    vtkSmartPointer<vtkRenderer> renderer4 = vtkSmartPointer<vtkRenderer>::New();
    renderer4->AddActor(sphereActor);
    renderer4->SetBackground(1.0, 1.0, 0.0);
    renderer4->SetViewport(0.5, 0.5, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer1);
    renderWindowLeftTop->AddRenderer(renderer2);
    renderWindowLeftTop->AddRenderer(renderer3);
    renderWindowLeftTop->AddRenderer(renderer4);
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("Viewport");

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindowLeftTop);

    renderWindowLeftTop->Render();
    interactor->Initialize();
    interactor->Start();
}

void Utils::test2_4()
{
    std::string strFileileName = "./data/head.vtk";
    //读入Structured_Points类型的vtk文件。
    vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
    reader->SetFileName(strFileileName.c_str());

    //用移动立方体法提取等值面。
    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    marchingCubes->SetInputConnection(reader->GetOutputPort());
    marchingCubes->SetValue(0, 500);

    //将生成的等值面数据进行Mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(marchingCubes->GetOutputPort());

    //把Mapper的输出送入渲染引擎进行显示
    //////////////////////////////////////渲染引擎部分////////////////////////////////////
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer);
    renderWindowLeftTop->SetSize(640, 480);
    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("vtkPipelineDemo");

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindowLeftTop);

    interactor->Initialize();
    interactor->Start();
}

void Utils::test2_4_2()
{
    std::string strFileName = "./data/VTK-logo.bmp";


    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    std::cout << "Modification Time of reader (After New()): " << reader->GetMTime() << std::endl;
    reader->SetFileName(strFileName.c_str());
    std::cout << "Modification Time of reader (After SetFileName()): " << reader->GetMTime() << std::endl;

    vtkImageData* imageData = reader->GetOutput();
    std::cout << "Modification Time of reader (After GetOutput()): " << reader->GetMTime() << std::endl;
    reader->Update();
    std::cout << "Modification Time of reader (After Update()): " << reader->GetMTime() << std::endl;

    int extent[6];
    imageData->GetExtent(extent);
    std::cout << "Extent of image: " << extent[0] << " "
        << extent[1] << " " << extent[2] << " " << extent[3] << " "
        << extent[4] << " " << extent[5] << " " << std::endl;

    vtkSmartPointer<vtkImageViewer2> viewer =
        vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    viewer->SetupInteractor(interactor);
    viewer->SetInputData(imageData);
    viewer->Render();

    viewer->SetSize(640, 480);
    viewer->GetRenderWindow()->SetWindowName("vtkPipelineExecute");

    interactor->Initialize();
    interactor->Start();
}

void Utils::test2_5()
{
    std::string strFileName = "./data/VTK-logo.bmp";
    //演示引用计数：
    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    std::cout << "Reference Count of reader->GetOutput (Before Assignment) = "
        << reader->GetOutput()->GetReferenceCount() << std::endl;

    vtkSmartPointer<vtkImageData> image1 = reader->GetOutput();
    std::cout << "Reference Count of reader->GetOutput (Assign to image1) = "
        << reader->GetOutput()->GetReferenceCount() << std::endl;
    std::cout << "Reference Count of image1 = "
        << image1->GetReferenceCount() << std::endl;

    vtkSmartPointer<vtkImageData> image2 = reader->GetOutput();
    std::cout << "Reference Count of reader->GetOutput (Assign to image2) = "
        << reader->GetOutput()->GetReferenceCount() << std::endl;
    std::cout << "Reference Count of image2 = "
        << image2->GetReferenceCount() << std::endl;
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //演示智能指针可以作为函数返回值
    //由于函数MyFunction()的返回值是通过拷贝的方式，
    //将数据赋予调用的变量，因此该数据的引用计数保持不变
    std::cout << "myObject reference count = "
        << MyFunction()->GetReferenceCount() << std::endl;

    vtkSmartPointer<vtkImageData> MyImageData = MyFunction();
    std::cout << "MyFunction return value reference count = "
        << MyFunction()->GetReferenceCount() << std::endl;

    std::cout << "MyImageData reference count = "
        << MyImageData->GetReferenceCount() << std::endl;
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //如果没有给对象分配内存，仍然可以使用智能指针:
    vtkSmartPointer<vtkBMPReader> Reader = vtkSmartPointer<vtkBMPReader>::New();
    vtkImageData* pd = Reader->GetOutput();
    //////////////////////////////////////////////////////////////////////////

    system("pause");
}

void Utils::test3_2_1()
{
    //创建三个坐标点
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(1.0, 0.0, 0.0); //返回第一个点的ID：0
    points->InsertNextPoint(0.0, 0.0, 1.0); //返回第二个点的ID：1
    points->InsertNextPoint(0.0, 0.0, 0.0); //返回第三个点的ID：2

    //每两个坐标点之间分别创建一条线
    //SetId()的第一个参数是线段的端点ID，第二个参数是连接的点的ID
    vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
    line0->GetPointIds()->SetId(0, 0);
    line0->GetPointIds()->SetId(1, 1);

    vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
    line1->GetPointIds()->SetId(0, 1);
    line1->GetPointIds()->SetId(1, 2);

    vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
    line2->GetPointIds()->SetId(0, 2);
    line2->GetPointIds()->SetId(1, 0);

    //创建Cell数组，用于存储以上创建的线段
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(line0);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);

    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //将点和线加入到数据集中，前者指定数据集的几何，后者指定其拓扑
    polydata->SetPoints(points);
    polydata->SetLines(lines);

    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName("TriangleLines.vtk");
    writer->SetInputData(polydata);
    writer->Write();
}

void Utils::test3_2_2()
{
    //创建点数据
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);

    //创建vtkPolyData类型的数据，vtkPolyData派生自vtkPointSet，
    //vtkPointSet是vtkDataSet的子类。
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //将创建的点数据加入到vtkPolyData数据里
    polydata->SetPoints(points);

    //将vtkPolyData类型的数据写入到一个vtk文件，保存位置是工程当前目录
    vtkSmartPointer< vtkPolyDataWriter > writer = vtkSmartPointer< vtkPolyDataWriter >::New();
    writer->SetFileName("./data/triangle.vtk");
    writer->SetInputData(polydata);
    writer->Write();
}

void Utils::test4_1_1()
{
    //生成图像序列的文件名数组
    vtkSmartPointer< vtkStringArray > fileArray = vtkSmartPointer< vtkStringArray >::New();
    char fileName[128];
    for (int i = 1; i < 100; i++)
    {
        sprintf_s(fileName, "./data/Head/head%03d.jpg", i);
        vtkStdString fileStr(fileName);
        fileArray->InsertNextValue(fileStr);
    }

    //读取JPG序列图像
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileNames(fileArray);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

    //显示读取的JPG图像
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    imageViewer->SetSlice(50); //默认显示第50个切片(即第50层)
    imageViewer->SetSliceOrientationToXY();
    //imageViewer->SetSliceOrientationToYZ();
    //imageViewer->SetSliceOrientationToXZ();
    imageViewer->SetupInteractor(renderWindowInteractor);
    imageViewer->Render();

    imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    imageViewer->SetSize(640, 480);
    imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages1");

    renderWindowInteractor->Start();
}

void Utils::test5_1_1()
{
    vtkSmartPointer<vtkImageCanvasSource2D> canvas = vtkSmartPointer<vtkImageCanvasSource2D>::New();
    canvas->SetScalarTypeToUnsignedChar();
    canvas->SetNumberOfScalarComponents(1);
    canvas->SetExtent(0, 100, 0, 100, 0, 0);
    canvas->SetDrawColor(0, 0, 0, 0);
    canvas->FillBox(0, 100, 0, 100);
    canvas->SetDrawColor(255, 0, 0, 0);
    canvas->FillBox(20, 40, 20, 40);
    canvas->Update();

    // Create actors
    vtkSmartPointer<vtkImageActor> redActor = vtkSmartPointer<vtkImageActor>::New();
    redActor->SetInputData(canvas->GetOutput());

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double redViewport[4] = { 0.0, 0.0, 1.0, 1.0 };
    // Setup renderers
    vtkSmartPointer<vtkRenderer> redRenderer = vtkSmartPointer<vtkRenderer>::New();
    redRenderer->SetViewport(redViewport);
    redRenderer->AddActor(redActor);
    redRenderer->ResetCamera();
    redRenderer->SetBackground(1.0, 1.0, 1.0);

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(redRenderer);
    renderWindow->SetSize(640, 480);
    renderWindow->Render();
    renderWindow->SetWindowName("ImageCanvasSource2D");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(style);
    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

void Utils::test5_1_2()
{
    vtkSmartPointer<vtkImageData> img = vtkSmartPointer<vtkImageData>::New();
    img->SetDimensions(10, 10, 10);
    //img->SetScalarTypeToUnsignedChar();
    //img->SetNumberOfScalarComponents(1);
    //img->AllocateScalars();

    unsigned char* ptr = (unsigned char*)img->GetScalarPointer();
    for (int i = 0; i < 16 * 16 * 1; i++)
    {
        *ptr++ = i % 256;
    }

    vtkSmartPointer<vtkImageActor> redActor =
        vtkSmartPointer<vtkImageActor>::New();
    redActor->SetInputData(img);

    double redViewport[4] = { 0.0, 0.0, 1.0, 1.0 };

    vtkSmartPointer<vtkRenderer> redRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    redRenderer->SetViewport(redViewport);
    redRenderer->AddActor(redActor);
    redRenderer->ResetCamera();
    redRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(redRenderer);
    renderWindow->SetSize(640, 480);
    renderWindow->Render();
    renderWindow->SetWindowName("CreateVTKImageData");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

void Utils::test5_2_1()
{
    std::string strFileName = "./data/brain.mhd";

    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);

    imageViewer->SetColorLevel(500);
    imageViewer->SetColorWindow(2000);
    imageViewer->SetSlice(40);
    imageViewer->SetSliceOrientationToXY();
    imageViewer->Render();

    imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    imageViewer->SetSize(640, 480);
    imageViewer->GetRenderWindow()->SetWindowName("DisplayImageExample");

    renderWindowInteractor->Start();
}

void Utils::test5_2_2()
{
    std::string strFileName = "./data/lena.bmp";
    vtkSmartPointer<vtkBMPReader> reader =
        vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    vtkSmartPointer<vtkImageActor> imgActor =
        vtkSmartPointer<vtkImageActor>::New();
    imgActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(imgActor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(640, 480);
    renderWindow->Render();
    renderWindow->SetWindowName("DisplayImageExample2");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();

    renderWindowInteractor->Start();
}

void Utils::test5_2_3()
{
    std::string strFileName = "./data/lena-gray.jpg";
    vtkSmartPointer<vtkJPEGReader> reader =
        vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
        vtkSmartPointer<vtkImageCanvasSource2D>::New();
    imageSource->SetNumberOfScalarComponents(1);
    imageSource->SetScalarTypeToUnsignedChar();
    imageSource->SetExtent(0, 512, 0, 512, 0, 0);
    imageSource->SetDrawColor(0.0);
    imageSource->FillBox(0, 512, 0, 512);
    imageSource->SetDrawColor(255.0);
    imageSource->FillBox(100, 400, 100, 400);
    imageSource->Update();

    vtkSmartPointer<vtkImageBlend> imageBlend = vtkSmartPointer<vtkImageBlend>::New();
    //imageBlend->SetInputData(0, reader->GetOutput());
    //imageBlend->SetInputData(1, imageSource->GetOutput());
    imageBlend->SetInputDataObject(0,reader->GetOutput());
    imageBlend->SetOpacity(0, 0.5);
    imageBlend->SetInputDataObject(1,imageSource->GetOutput());
    imageBlend->SetOpacity(1, 0.5);
    imageBlend->Update();

    // Create actors
    vtkSmartPointer<vtkImageActor> originalActor1 =
        vtkSmartPointer<vtkImageActor>::New();
    originalActor1->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> originalActor2 =
        vtkSmartPointer<vtkImageActor>::New();
    originalActor2->SetInputData(imageSource->GetOutput());

    vtkSmartPointer<vtkImageActor> blendActor =
        vtkSmartPointer<vtkImageActor>::New();
    blendActor->SetInputData(imageBlend->GetOutput());

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    double leftViewport[4] = { 0.0, 0.0, 0.33, 1.0 };
    double midViewport[4] = { 0.33, 0.0, 0.66, 1.0 };
    double rightViewport[4] = { 0.66, 0.0, 1.0, 1.0 };

    // Setup renderers
    vtkSmartPointer<vtkRenderer> originalRenderer1 =
        vtkSmartPointer<vtkRenderer>::New();
    originalRenderer1->SetViewport(leftViewport);
    originalRenderer1->AddActor(originalActor1);
    originalRenderer1->ResetCamera();
    originalRenderer1->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> originalRenderer2 =
        vtkSmartPointer<vtkRenderer>::New();
    originalRenderer2->SetViewport(midViewport);
    originalRenderer2->AddActor(originalActor2);
    originalRenderer2->ResetCamera();
    originalRenderer2->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> blendRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    blendRenderer->SetViewport(rightViewport);
    blendRenderer->AddActor(blendActor);
    blendRenderer->ResetCamera();
    blendRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originalRenderer1);
    renderWindow->AddRenderer(originalRenderer2);
    renderWindow->AddRenderer(blendRenderer);
    renderWindow->SetSize(640, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("ImageBlendExample3");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

void Utils::test5_3_1()
{
    std::string strFileName = "./data/brain.mhd";
    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutput()->GetExtent(extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    static double axialElements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();

    vtkSmartPointer<vtkLookupTable> colorTable = vtkSmartPointer<vtkLookupTable>::New();
    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

    vtkSmartPointer<vtkImageMapToColors> colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());

    vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
    imgActor->SetInputData(colorMap->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(imgActor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->Render();
    renderWindow->SetSize(640, 480);
    renderWindow->SetWindowName("ImageResliceExample");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> imagestyle = vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(imagestyle);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

void Utils::test5_3_2()
{
    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("../data/brain.mhd");
    reader->Update();

    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutput()->GetExtent(extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    static double axialElements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
    resliceAxes->DeepCopy(axialElements);

    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();

    vtkSmartPointer<vtkLookupTable> colorTable = vtkSmartPointer<vtkLookupTable>::New();
    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

    vtkSmartPointer<vtkImageMapToColors> colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());

    vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
    imgActor->SetInputData(colorMap->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(imgActor);
    renderer->SetBackground(.4, .5, .6);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(500, 500);
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> imagestyle = vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(imagestyle);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();

    vtkSmartPointer<vtkImageInteractionCallback> callback = vtkSmartPointer<vtkImageInteractionCallback>::New();
    callback->SetImageReslice(reslice);
    callback->SetInteractor(renderWindowInteractor);

    imagestyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
    imagestyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
    imagestyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);

    renderWindowInteractor->Start();
}

void Utils::MedicalDemo1()
{
    std::string strFileName = "./data/FullHead.mhd";

    vtkNew<vtkNamedColors> colors;

    std::array<unsigned char, 4> skinColor{ {240, 184, 160, 255} };
    colors->SetColor("SkinColor", skinColor.data());
    std::array<unsigned char, 4> backColor{ {255, 229, 200, 255} };
    colors->SetColor("BackfaceColor", backColor.data());
    std::array<unsigned char, 4> bkg{ {51, 77, 102, 255} };
    colors->SetColor("BkgColor", bkg.data());

    // Create the renderer, the render window, and the interactor. The renderer
    // draws into the render window, the interactor enables mouse- and
    // keyboard-based interaction with the data within the render window.
    //
    vtkNew<vtkRenderer> aRenderer;
    //vtkNew<vtkRenderWindow> renderWindowLeftTop;
    renderWindowLeftTop->AddRenderer(aRenderer);

    //vtkNew<vtkRenderWindowInteractor> iren;
    //iren->SetRenderWindow(renderWindowLeftTop);

    vtkNew<vtkMetaImageReader> reader;
    reader->SetFileName(strFileName.c_str());
    reader->Update();

    // An isosurface, or contour value of 500 is known to correspond to the
    // skin of the patient.
#ifdef USE_FLYING_EDGES
    vtkNew<vtkFlyingEdges3D> skinExtractor;
#else
    vtkNew<vtkMarchingCubes> skinExtractor;
#endif

    skinExtractor->SetInputConnection(reader->GetOutputPort());
    skinExtractor->SetValue(0, 500);

    vtkNew<vtkPolyDataMapper> skinMapper;
    skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
    skinMapper->ScalarVisibilityOff();

    vtkNew<vtkActor> skin;
    skin->SetMapper(skinMapper);
    skin->GetProperty()->SetDiffuseColor(
        colors->GetColor3d("SkinColor").GetData());

    vtkNew<vtkProperty> backProp;
    backProp->SetDiffuseColor(colors->GetColor3d("BackfaceColor").GetData());
    skin->SetBackfaceProperty(backProp);

    // An outline provides context around the data.
    //
    vtkNew<vtkOutlineFilter> outlineData;
    outlineData->SetInputConnection(reader->GetOutputPort());

    vtkNew<vtkPolyDataMapper> mapOutline;
    mapOutline->SetInputConnection(outlineData->GetOutputPort());

    vtkNew<vtkActor> outline;
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

    // It is convenient to create an initial view of the data. The FocalPoint
    // and Position form a vector direction. Later on (ResetCamera() method)
    // this vector is used to position the camera to look at the data in
    // this direction.
//    vtkNew<vtkCamera> aCamera;
//    aCamera->SetViewUp(0, 0, -1);
//    aCamera->SetPosition(0, -1, 0);
//    aCamera->SetFocalPoint(0, 0, 0);
//    aCamera->ComputeViewPlaneNormal();
//    aCamera->Azimuth(30.0);
//    aCamera->Elevation(30.0);

    // Actors are added to the renderer. An initial camera view is created.
    // The Dolly() method moves the camera towards the FocalPoint,
    // thereby enlarging the image.
    aRenderer->AddActor(outline);
    aRenderer->AddActor(skin);
    //aRenderer->SetActiveCamera(aCamera);
    //aRenderer->ResetCamera();
    //aCamera->Dolly(1.5);

    // Set a background color for the renderer and set the size of the
    // render window (expressed in pixels).
    aRenderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    //renderWindowLeftTop->SetSize(640, 480);
    //renderWindowLeftTop->Render();
    //renderWindowLeftTop->SetWindowName("MedicalDemo1");

    // Note that when camera movement occurs (as it does in the Dolly()
    // method), the clipping planes often need adjusting. Clipping planes
    // consist of two planes: near and far along the view direction. The
    // near plane clips out objects in front of the plane; the far plane
    // clips out objects behind the plane. This way only what is drawn
    // between the planes is actually rendered.
    //aRenderer->ResetCameraClippingRange();

    // Initialize the event loop and then start it.
    //renderWindowLeftTop->Render();
    //iren->Initialize();
    //iren->Start();
}
void Utils::MedicalDemo2()
{

}
void Utils::MedicalDemo3()
{

}
void Utils::MedicalDemo4()
{

}

void Utils::CallBack()
{
    vtkNew<vtkNamedColors> colors;

    // Create the Renderer, RenderWindow and RenderWindowInteractor.
    vtkNew<vtkRenderer> ren;
    vtkNew<vtkRenderWindow> renderWindowLeftTop;
    renderWindowLeftTop->AddRenderer(ren);
    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renderWindowLeftTop);

    // Use a cone as a source.
    vtkNew<vtkConeSource> source;
    source->SetCenter(0, 0, 0);
    source->SetRadius(1);
    // Use the golden ratio for the height. Because we can!
    source->SetHeight(1.6180339887498948482);
    source->SetResolution(128);
    source->Update();

    // Pipeline
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(source->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("peacock").GetData());
    // Lighting
    actor->GetProperty()->SetAmbient(0.3);
    actor->GetProperty()->SetDiffuse(0.0);
    actor->GetProperty()->SetSpecular(1.0);
    actor->GetProperty()->SetSpecularPower(20.0);

    // Get an outline of the data set for context.
    vtkNew<vtkOutlineFilter> outline;
    outline->SetInputData(source->GetOutput());
    vtkNew<vtkPolyDataMapper> outlineMapper;
    outlineMapper->SetInputConnection(outline->GetOutputPort());
    vtkNew<vtkActor> outlineActor;
    outlineActor->SetMapper(outlineMapper);
    outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

    // Add the actors to the renderer, set the background and size.
    ren->AddActor(actor);

    ren->AddActor(outlineActor);
    ren->SetBackground(colors->GetColor3d("AliceBlue").GetData());
    renderWindowLeftTop->SetSize(512, 512);

    // Set up a nice camera position.
    vtkNew<vtkCamera> camera;
    camera->SetPosition(4.6, -2.0, 3.8);
    camera->SetFocalPoint(0.0, 0.0, 0.0);
    camera->SetClippingRange(3.2, 10.2);
    camera->SetViewUp(0.3, 1.0, 0.13);
    ren->SetActiveCamera(camera);

    renderWindowLeftTop->Render();
    renderWindowLeftTop->SetWindowName("CallBack");

    vtkNew<vtkAxesActor> axes;
    MakeAxesActor(axes);
    vtkNew<vtkOrientationMarkerWidget> om;
    om->SetOrientationMarker(axes);
    // Position lower left in the viewport.
    om->SetViewport(0, 0, 0.2, 0.2);
    om->SetInteractor(iren);
    om->EnabledOn();
    om->InteractiveOn();

#if defined(USE_CALLBACKCOMMAND_CLASS)
    // When we implement the class, it automatically becomes the callback
    // function.
    vtkNew<CameraModifiedCallback> getOrientation;
    // Set the camera to use.
    getOrientation->cam = ren->GetActiveCamera();
#else
    // Create the vtkCallbackCommand.
    vtkNew<vtkCallbackCommand> getOrientation;
    // Set the callback to the function we created.
    getOrientation->SetCallback(vtkCallbackFunc);
    // Set the client data.
    getOrientation->SetClientData(ren->GetActiveCamera());
#endif
    iren->AddObserver(vtkCommand::EndInteractionEvent, getOrientation);
    iren->Initialize();
    iren->Start();
}

void Utils::DoubleClick()
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(5.0);
    sphereSource->Update();

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

    vtkNew<vtkRenderer> renderer;
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderer->AddActor(actor);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkNew<MouseInteractorStyleDoubleClick> style;
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindow->SetWindowName("DoubleClick");
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}

void Utils::EllipticalButton()
{
    vtkNew<vtkNamedColors> color;

    std::string strFileName = "./data/lena.jpg";

    vtkNew<vtkSuperquadricSource> source;
    source->SetPhiResolution(64);
    source->SetThetaResolution(64);
    source->SetThetaRoundness(1.5);
    source->SetThickness(1.5);
    source->SetSize(2);
    source->Update();

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(source->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(color->GetColor3d("Burlywood").GetData());

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(200, 200);
    renderWindow->AddRenderer(renderer);
    renderWindow->Render();
    renderWindow->SetWindowName("EllipticalButton");

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Create the widget and its representation
    vtkSmartPointer<vtkActor> buttonActor1 = CreateButtonActor(strFileName.c_str());
    buttonActor1->GetProperty()->SetColor(color->GetColor3d("Tomato").GetData());
    vtkSmartPointer<vtkActor> buttonActor2 = CreateButtonActor(strFileName.c_str());
    buttonActor2->GetProperty()->SetColor(color->GetColor3d("Banana").GetData());

    vtkNew<vtkProp3DButtonRepresentation> buttonRepresentation;
    buttonRepresentation->SetNumberOfStates(2);
    buttonRepresentation->SetButtonProp(0, buttonActor1);
    buttonRepresentation->SetButtonProp(1, buttonActor2);
    buttonRepresentation->FollowCameraOn();

    vtkNew<vtkButtonCallback> callback;
    callback->Actor = actor;
    actor->GetProperty()->SetColor(
        reinterpret_cast<vtkActor*>(buttonRepresentation->GetButtonProp(0))
        ->GetProperty()
        ->GetColor());

    renderWindowInteractor->Initialize();

    vtkNew<vtkButtonWidget> buttonWidget;
    buttonWidget->SetInteractor(renderWindowInteractor);
    buttonWidget->SetRepresentation(buttonRepresentation);
    buttonWidget->AddObserver(vtkCommand::StateChangedEvent, callback);
    buttonWidget->SetEnabled(1);

    renderer->ResetCamera();
    //renderer->
    renderer->Render();

    renderWindowInteractor->Start();
}
#if 0
void Utils::example_1()
{
    cv::viz::Viz3d window("Example_1");

    window.showWidget("Coordinate", cv::viz::WCoordinateSystem());

    cv::viz::WPlane plane1(cv::Size2d(1.0, 1.0), cv::viz::Color::red());

    window.showWidget("plane1", plane1);

    //创建平面
    cv::viz::WPlane plane2(cv::Point3d(0.5, 0.0, 0.5), cv::Vec3d(1.0, 0.0, 0.0), cv::Vec3d(0.0, 1.0, 0.0), cv::Size(1.0, 1.0), cv::viz::Color::white());

    //添加平面部件，并显示到可视化窗口中
    window.showWidget("plane2", plane2);

    //创建平面
    cv::viz::WPlane plane3(cv::Point3d(0.0, 0.0, 1), cv::Vec3d(0.0, 0.0, 1.0), cv::Vec3d(0.0, 1.0, 0.0), cv::Size(1.0, 1.0), cv::viz::Color::red());

    //添加平面部件，并显示到可视化窗口中
    window.showWidget("plane3", plane3);

    //创建平面
    cv::viz::WPlane plane4(cv::Point3d(-0.5, 0.0, 0.5), cv::Vec3d(1.0, 0.0, 0.0), cv::Vec3d(0.0, 1.0, 0.0), cv::Size(1.0, 1.0), cv::viz::Color::white());

    //添加平面部件，并显示到可视化窗口中
    window.showWidget("plane4", plane4);

    // 永久循环暂留
    //spin()函数开启一个事件永远循环。直观的用处就是让画面停在那里
    //按q键或者e键，可结束循环
    //void spinOnce(int time = 1, bool force_redraw = false);此函数是该函数的变种，可指定循环事件time(以毫秒为单位)，参数force_redraw(暴力重画)，作用未知
    window.spin();


}
#endif

void Utils::ImageReslice()
{
    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("../data/brain.mhd");
    reader->Update();

    //vtkSmartPointer<vtkImageData>

    vtkNew<vtkNamedColors> colors;

    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutput()->GetExtent(extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
    //*****************************************************************//
    static double axialElements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();
    //*****************************************************************//
    vtkSmartPointer<vtkLookupTable> colorTable = vtkSmartPointer<vtkLookupTable>::New();
    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();
    vtkSmartPointer<vtkImageMapToColors> colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());
    colorMap->Update();
    //*****************************************************************//
    vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
    imgActor->SetInputData(colorMap->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(imgActor);
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

    vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> renderer4 = vtkSmartPointer<vtkRenderer>::New();
    renderer2->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    renderer3->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    renderer4->SetBackground(colors->GetColor3d("SteelBlue").GetData());

    //vtkSmartPointer<vtkRenderWindow> renderWindowLeftTop = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindowLeftTop->AddRenderer(renderer);
    renderWindowLeftBottom->AddRenderer(renderer2);
    renderWindowRightTop->AddRenderer(renderer3);
    renderWindowRightBottom->AddRenderer(renderer4);
    //renderWindowLeftTop->Render();
    //renderWindowLeftTop->SetSize(640, 480);
    //renderWindow->SetWindowName("Extract3Dslice");

//    vtkSmartPointer<vtkRenderWindowInteractor> rwi =
//        vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    vtkSmartPointer<vtkInteractorStyleImage> imagestyle =
//        vtkSmartPointer<vtkInteractorStyleImage>::New();
//    rwi->SetInteractorStyle(imagestyle);
//    rwi->SetRenderWindow(renderWindow);
//    rwi->Initialize();
//    rwi->Start();
}
