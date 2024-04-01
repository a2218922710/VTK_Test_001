#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkPNGReader.h>
#include <vtkBMPReader.h>
#include <vtkTIFFReader.h>
#include <vtkDICOMImageReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>

#include <QFileInfo>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DrawVtkCube();

    //奇怪的是不知道为什么 使用qrc路径并不能读取 :/images/1.bmp
    SetReaderImage("E:/mySpace/MyGitProject/VTK_Test/images/1.bmp");
    SetReaderImage("E:/mySpace/MyGitProject/VTK_Test/images/1.dcm");
    SetReaderImage("E:/mySpace/MyGitProject/VTK_Test/images/1.jpeg");
    SetReaderImage("E:/mySpace/MyGitProject/VTK_Test/images/1.png");
    SetReaderImage("E:/mySpace/MyGitProject/VTK_Test/images/1.tiff");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetReaderImage(const QString &imagePath)
{
    QFileInfo imageFileInfo(imagePath);
    vtkSmartPointer<vtkImageReader2> render;
    int imageWindow = 0;

    if("jpg" == imageFileInfo.suffix().toLower()
            || "jpeg" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkJPEGReader>::New();
        imageWindow = 0;
    }else if("png" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkPNGReader>::New();
        imageWindow = 1;
    }else if("bmp" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkBMPReader>::New();
        imageWindow = 2;
    }else if("tif" == imageFileInfo.suffix().toLower()
             || "tiff" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkTIFFReader>::New();
        imageWindow = 3;
    }else if("dcm" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkDICOMImageReader>::New();
        imageWindow = 4;
    }else if("png" == imageFileInfo.suffix().toLower()) {
        render = vtkSmartPointer<vtkPNGReader>::New();
        imageWindow = 5;
    }

    /**
         * @brief 读取本地图片
         * 1. 获取本地资源地址
         * 2. 新建渲染对象
         * 3. 设置图像名称
         * 4. 更新
         */

    render -> SetFileName(imagePath.toUtf8());
    render -> Update();
    /**
         * @brief 设置图片视图
         * 1. 新建视图
         * 2. 设置视图输入
         * 3. 设置视图窗口
         * 4. 视图渲染
         */
    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer -> SetInputData(render -> GetOutput());


    switch (imageWindow) {
    case 0:
        viewer -> SetRenderWindow(ui->widget->renderWindow());
        break;
    case 1:
        viewer -> SetRenderWindow(ui->widget_2->renderWindow());
        break;
    case 2:
        viewer -> SetRenderWindow(ui->widget_3->renderWindow());
        break;
    case 3:
        viewer -> SetRenderWindow(ui->widget_4->renderWindow());
        break;
    case 4:
        viewer -> SetRenderWindow(ui->widget_5->renderWindow());
        break;
    case 5:
        viewer -> SetRenderWindow(ui->widget_6->renderWindow());
        break;
    default:
        break;
    }
    viewer->GetRenderer()->SetBackground(.3, .6, .3);   //背景色改变为绿色
    viewer -> Render();

}

void MainWindow::DrawVtkCube()
{
    vtkNew <vtkNamedColors> colors;
    std::array<std::array<double, 3>, 8> pts = {{{{0, 0, 0}},
                                                 {{0.2, 0, 0}},
                                                 {{0.2, 0.2, 0}},
                                                 {{0, 0.2, 0}},
                                                 {{0, 0, 0.2}},
                                                 {{0.2, 0, 0.2}},
                                                 {{0.2, 0.2, 0.2}},
                                                 {{0, 0.2, 0.2}}}};
    std::array<std::array<vtkIdType,4>,6> ording = {{{{0, 1, 2, 3}},
                                                     {{4, 5, 6, 7}},
                                                     {{0, 1, 5, 4}},
                                                     {{1, 2, 6, 5}},
                                                     {{2, 3, 7, 6}},
                                                     {{3, 0, 4, 7}}}};
    vtkNew <vtkPolyData> cube;
    vtkNew <vtkPoints> points;
    vtkNew <vtkCellArray> polys;
    vtkNew <vtkFloatArray> scalars;
    for (auto i = 0ul;i < pts.size();++i)
    {
        points -> InsertPoint(i,pts[i].data());
        scalars -> InsertTuple1(i,i);
    }
    for (auto &&i : ording)
        polys -> InsertNextCell(vtkIdType(i.size()),i.data());
    cube -> SetPoints(points);
    cube -> SetPolys(polys);
    cube -> GetPointData() -> SetScalars(scalars);
    vtkNew<vtkPolyDataMapper> cubeMapper;
    cubeMapper->SetInputData(cube);
    cubeMapper->SetScalarRange(cube->GetScalarRange());
    vtkNew<vtkActor> cubeActor;
    cubeActor->SetMapper(cubeMapper);
    vtkNew<vtkCamera> camera;
    camera->SetPosition(1, 1, 1);
    camera->SetFocalPoint(0, 0, 0);
    vtkNew<vtkRenderer> render;
    render -> AddActor(cubeActor);
    render -> SetActiveCamera(camera);
    render -> SetBackground(colors -> GetColor3d("Cornsilk").GetData());
    ui->widget_6->renderWindow()->AddRenderer(render);
}

