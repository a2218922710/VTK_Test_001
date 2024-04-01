#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SetReaderImage(const QString & imagePath);
    //Cube实现
    void DrawVtkCube();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
