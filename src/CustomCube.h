#ifndef CUSTOMCUBE_H
#define CUSTOMCUBE_H

#include <QObject>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkAlgorithmOutput;
class vtkPassThrough;

class CustomCube : public QObject
{
        Q_OBJECT
public:
    CustomCube();
    vtkPolyData* getCubeData();

signals:

public slots:

protected:
    static vtkSmartPointer<vtkPolyData> CreateCubeData(double);

    vtkSmartPointer<vtkPolyData>    m_cube;
};

#endif // CUSTOMCUBE_H
