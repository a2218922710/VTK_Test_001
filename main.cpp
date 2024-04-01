#include "mainwindow.h"
#include "define.h"

#include <QApplication>

int main(int argc, char *argv[])
{
//    QSurfaceFormat format;
//    format.setVersion(4, 3);    // 关键是这一句，设置opengl版本号
//    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();


//    //QVTKOpenGLNativeWidget a;
//    vtkSmartPointer<vtkSphereSource> sphereSource =vtkSmartPointer<vtkSphereSource>::New();
//    sphereSource->SetCenter(0.0, 0.0, 0.0);
//    sphereSource->SetRadius(5.0);
//    vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(sphereSource->GetOutputPort());
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    vtkSmartPointer<vtkRenderer> renderer =vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> renderWindow =vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//    renderer->AddActor(actor);
//    renderer->SetBackground(.3, .6, .3); // Background color green
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//    return EXIT_SUCCESS;


}
