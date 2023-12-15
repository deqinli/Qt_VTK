#ifndef UTILS_H
#define UTILS_H

#include "header.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>


class vtkImageInteractionCallback : public vtkCommand
{
public:
    static vtkImageInteractionCallback* New()
    {
        return new vtkImageInteractionCallback;
    }

    vtkImageInteractionCallback()
    {
        this->Slicing = 0;
        this->ImageReslice = 0;
        this->Interactor = 0;
    }

    void SetImageReslice(vtkImageReslice* reslice)
    {
        this->ImageReslice = reslice;
    }

    vtkImageReslice* GetImageReslice()
    {
        return this->ImageReslice;
    }

    void SetInteractor(vtkRenderWindowInteractor* interactor)
    {
        this->Interactor = interactor;
    }

    vtkRenderWindowInteractor* GetInteractor()
    {
        return this->Interactor;
    }

    virtual void Execute(vtkObject*, unsigned long event, void*)
    {
        vtkRenderWindowInteractor* interactor = this->GetInteractor();

        int lastPos[2];
        interactor->GetLastEventPosition(lastPos);
        int currPos[2];
        interactor->GetEventPosition(currPos);

        if (event == vtkCommand::LeftButtonPressEvent)
        {
            this->Slicing = 1;
        }
        else if (event == vtkCommand::LeftButtonReleaseEvent)
        {
            this->Slicing = 0;
        }
        else if (event == vtkCommand::MouseMoveEvent)
        {
            if (this->Slicing)
            {
                vtkImageReslice* reslice = this->ImageReslice;

                // Increment slice position by deltaY of mouse
                int deltaY = lastPos[1] - currPos[1];

                reslice->Update();
                double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
                vtkMatrix4x4* matrix = reslice->GetResliceAxes();
                // move the center point that we are slicing through
                double point[4];
                double center[4];
                point[0] = 0.0;
                point[1] = 0.0;
                point[2] = sliceSpacing * deltaY;
                point[3] = 1.0;
                matrix->MultiplyPoint(point, center);
                matrix->SetElement(0, 3, center[0]);
                matrix->SetElement(1, 3, center[1]);
                matrix->SetElement(2, 3, center[2]);

                //printf("%f %f %f\n", center[0], center[1], center[2]);

                interactor->Render();
            }
            else
            {
                vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
                    interactor->GetInteractorStyle());
                if (style)
                {
                    style->OnMouseMove();
                }
            }
        }
    }

private:
    int Slicing;
    vtkImageReslice* ImageReslice;
    vtkRenderWindowInteractor* Interactor;
};

class Utils
{
public:
    Utils();
    ~Utils();
    void Qt_test();
    void test_ImgSlice();
    void test1();
    void test2_1();
    void test2_2_1();
    void test2_2_2();
    void test2_3();
    void test2_4();
    void test2_4_2();
    void test2_5();
    void test3_2_1();
    void test3_2_2();
    void test4_1_1();
    void test5_1_1();
    void test5_1_2();
    void test5_2_1();
    void test5_2_2();
    void test5_2_3();
    void test5_3_1();
    void test5_3_2();

    void MedicalDemo1();
    void MedicalDemo2();
    void MedicalDemo3();
    void MedicalDemo4();

    //interaction examples
    void CallBack();
    void DoubleClick();
    void EllipticalButton();

    // image reslice
    void ImageReslice();

    // opencv_vtk
    //void example_1();

public:
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindowLeftTop;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindowRightTop;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindowLeftBottom;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindowRightBottom;


private:
    vtkSmartPointer<vtkImageData>  MyFunction();


};


namespace {
    void PrintCameraOrientation(vtkCamera* cam);
    void MakeAxesActor(vtkAxesActor* axesActor);

#if defined(USE_CALLBACKCOMMAND_CLASS)
    /**
    Here we inherit from vtkCallbackCommand and set pointers to any
    client and/or call data as needed.
    When the class is implemented, it becomes the callback function.
    */
    class CameraModifiedCallback : public vtkCallbackCommand
    {
    public:
        static CameraModifiedCallback* New()
        {
            return new CameraModifiedCallback;
        }
        // Here we Create a vtkCallbackCommand and reimplement it.
        void Execute(vtkObject* caller, unsigned long evId, void*) override
        {
            // Note the use of reinterpret_cast to cast the caller to the expected type.
            auto interactor = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
            // Just do this to demonstrate who called callback and the event that
            // triggered it.
            std::cout << interactor->GetClassName() << "  Event Id: " << evId
                << std::endl;

            // Now print the camera orientation.
            PrintCameraOrientation(this->cam);
        }
        CameraModifiedCallback() : cam(nullptr)
        {
        }
        // Set pointers to any clientData or callData here.
        vtkCamera* cam;

    private:
        CameraModifiedCallback(const CameraModifiedCallback&) = delete;
        void operator=(const CameraModifiedCallback&) = delete;
    };

#else
    /**
    An alternative method is to create a function with this signature:
    void f(vtkObject* caller, long unsigned int evId, void* clientData, void*
    callData)
    and, where needed, create a vtkCallbackCommand setting its callback to the
    function we have created.
    */
    void vtkCallbackFunc(vtkObject* caller, long unsigned int evId,
        void* clientData, void* /*callData*/)
    {
        // Note the use of reinterpret_cast to cast the caller and callData to the
        // expected types.
        auto interactor = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
        std::cout << interactor->GetClassName() << "  Event Id: " << evId
            << std::endl;
        auto cam = reinterpret_cast<vtkCamera*>(clientData);

        // Now print the camera orientation.
        PrintCameraOrientation(cam);
    };
#endif
} // namespace

namespace {
    void MakeAxesActor(vtkAxesActor* axes)
    {
        axes->SetShaftTypeToCylinder();
        axes->SetXAxisLabelText("X");
        axes->SetYAxisLabelText("Y");
        axes->SetZAxisLabelText("Z");
        axes->SetTotalLength(1.0, 1.0, 1.0);
        axes->SetCylinderRadius(0.5 * axes->GetCylinderRadius());
        axes->SetConeRadius(1.025 * axes->GetConeRadius());
        axes->SetSphereRadius(1.5 * axes->GetSphereRadius());
    }

    /**
    Get a comma separated list.
    */
    template <typename T> std::string CommaSeparatedList(std::vector<T> v)
    {
        std::ostringstream os;
        std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ", "));
        os << v.back();
        return os.str();
    }

    /**
    Print the camera orientation.
    */
    void PrintCameraOrientation(vtkCamera* cam)
    {
        auto width = 16;
        double pos[3];
        cam->GetPosition(pos);
        double fp[3];
        cam->GetFocalPoint(fp);
        double vu[3];
        cam->GetViewUp(vu);
        double cr[2];
        cam->GetClippingRange(cr);
        std::cout << setw(width) << "Position: "
            << CommaSeparatedList(std::vector<double>(pos, pos + 3))
            << std::endl;
        std::cout << setw(width) << "Focal point: "
            << CommaSeparatedList(std::vector<double>(fp, fp + 3)) << std::endl;
        std::cout << setw(width) << "Clipping range: "
            << CommaSeparatedList(std::vector<double>(cr, cr + 2)) << std::endl;
        std::cout << setw(width) << "View up: "
            << CommaSeparatedList(std::vector<double>(vu, vu + 3)) << std::endl;
        std::cout << setw(width) << "Distance: " << cam->GetDistance() << std::endl;
    };
} // namespace

namespace {
    // Define interaction style
    class MouseInteractorStyleDoubleClick : public vtkInteractorStyleTrackballCamera
    {
    public:
        static MouseInteractorStyleDoubleClick* New();
        vtkTypeMacro(MouseInteractorStyleDoubleClick,
            vtkInteractorStyleTrackballCamera);

        MouseInteractorStyleDoubleClick() : NumberOfClicks(0), ResetPixelDistance(5)
        {
            this->PreviousPosition[0] = 0;
            this->PreviousPosition[1] = 0;
        }

        virtual void OnLeftButtonDown() override
        {
            this->NumberOfClicks++;
            int pickPosition[2];
            this->GetInteractor()->GetEventPosition(pickPosition);

            int xdist = pickPosition[0] - this->PreviousPosition[0];
            int ydist = pickPosition[1] - this->PreviousPosition[1];

            this->PreviousPosition[0] = pickPosition[0];
            this->PreviousPosition[1] = pickPosition[1];

            int moveDistance = (int)sqrt((double)(xdist * xdist + ydist * ydist));

            // Reset numClicks - If mouse moved further than resetPixelDistance.
            if (moveDistance > this->ResetPixelDistance)
            {
                this->NumberOfClicks = 1;
            }

            if (this->NumberOfClicks == 2)
            {
                std::cout << "Double clicked." << std::endl;
                this->NumberOfClicks = 0;
            }

            // Forward events.
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }

    private:
        unsigned int NumberOfClicks;
        int PreviousPosition[2];
        int ResetPixelDistance;
    };
    vtkStandardNewMacro(MouseInteractorStyleDoubleClick);
} // namespace

// Callback for the interaction.
namespace {

    class vtkButtonCallback : public vtkCommand
    {
    public:
        static vtkButtonCallback* New()
        {
            return new vtkButtonCallback;
        }

        virtual void Execute(vtkObject* caller, unsigned long, void*)
        {
            auto buttonWidget = reinterpret_cast<vtkButtonWidget*>(caller);
            auto rep = reinterpret_cast<vtkProp3DButtonRepresentation*>(
                buttonWidget->GetRepresentation());
            int state = rep->GetState();
            this->Actor->GetProperty()->SetColor(
                reinterpret_cast<vtkActor*>(rep->GetButtonProp(state))
                ->GetProperty()
                ->GetColor());
            std::cout << "State: " << state << "\n";
        }

        vtkButtonCallback() : Actor(0)
        {
        }

        vtkActor* Actor;
    };

    vtkSmartPointer<vtkActor> CreateButtonActor(const char* textureFile);

} // namespace

namespace {

    vtkSmartPointer<vtkActor> CreateButtonActor(const char* textureFile)
    {
        vtkNew<vtkImageReader2Factory> readerFactory;
        vtkSmartPointer<vtkImageReader2> imageReader;
        imageReader.TakeReference(readerFactory->CreateImageReader2(textureFile));
        imageReader->SetFileName(textureFile);
        imageReader->Update();

        // Aspect ratio of image
        int dims[3];
        imageReader->GetOutput()->GetDimensions(dims);
        double aspect = static_cast<double>(dims[0]) / static_cast<double>(dims[1]);

        vtkNew<vtkTexture> texture;
        texture->SetInputConnection(imageReader->GetOutputPort());

        vtkNew<vtkEllipticalButtonSource> ellipticalButtonSource;
        ellipticalButtonSource->SetCircumferentialResolution(50);
        ellipticalButtonSource->SetShoulderResolution(10);
        ellipticalButtonSource->SetTextureResolution(10);
        ellipticalButtonSource->SetRadialRatio(1.05);
        ellipticalButtonSource->SetShoulderTextureCoordinate(0.0, 0.0);
        ellipticalButtonSource->SetTextureDimensions(dims[0], dims[1]);
        ellipticalButtonSource->SetTextureStyleToProportional();
        ellipticalButtonSource->TwoSidedOn();
        ellipticalButtonSource->SetWidth(aspect);
        ellipticalButtonSource->SetHeight(1.0);
        ellipticalButtonSource->SetDepth(.15);
        ellipticalButtonSource->SetCenter(2, 2, 0);

        ellipticalButtonSource->SetOutputPointsPrecision(
            vtkAlgorithm::SINGLE_PRECISION);

        vtkNew<vtkPolyDataMapper> buttonMapper;
        buttonMapper->SetInputConnection(ellipticalButtonSource->GetOutputPort());

        vtkNew<vtkActor> buttonActor;
        buttonActor->SetMapper(buttonMapper);
        buttonActor->SetTexture(texture);

        return buttonActor;
    }

} // namespace


#endif // UTILS_H
