#include "CustomCube.h"

CustomCube::CustomCube(QObject *parent) : QObjetct(parent)
{
    m_cube = vtkSmartPointer<vtkPolyData>::New();

    //First plane

    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);

    vtkSmartPointer<vtkCellArray> polygons =
      vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPolygon> polygon =
      vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon->GetPointIds()->SetId(0, 0);
    polygon->GetPointIds()->SetId(1, 1);
    polygon->GetPointIds()->SetId(2, 2);
    polygon->GetPointIds()->SetId(3, 3);

    polygons->InsertNextCell(polygon);

    vtkSmartPointer<vtkPolyData> quad =
      vtkSmartPointer<vtkPolyData>::New();
    quad->SetPoints(points);
    quad->SetPolys(polygons);

    vtkSmartPointer<vtkFloatArray> textureCoordinates =
      vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(3);
    textureCoordinates->SetName("TextureCoordinates");

    float tuple[3] = {0.0, 0.0, 0.0};
    textureCoordinates->InsertNextTuple(tuple);
    tuple[0] = 1.0; tuple[1] = 0.0; tuple[2] = 0.0;
    textureCoordinates->InsertNextTuple(tuple);
    tuple[0] = 1.0; tuple[1] = 1.0; tuple[2] = 0.0;
    textureCoordinates->InsertNextTuple(tuple);
    tuple[0] = 0.0; tuple[1] = 1.0; tuple[2] = 0.0;
    textureCoordinates->InsertNextTuple(tuple);

    quad->GetPointData()->SetTCoords(textureCoordinates);

}
