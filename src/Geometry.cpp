//-----------------------------------------------------------------------
//  Simple Qt4/VTK Viewer.
//  A basic example of the usage of QVTKWidget2 in Qt4 and
//  VTK7.1 with C++11
//  Copyright (C) 2017  Edson Contreras Cardenas

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

#include "Geometry.h"

#include <vtkAlgorithmOutput.h>
#include <vtkPassThrough.h>
#include <vtkPolyData.h>
#include <vtkCubeSource.h>
#include <iostream>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkFloatArray.h>
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkJPEGReader.h"
#include "vtkPolygon.h"
#include "vtkTexture.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetSurfaceFilter.h"
#include <QDebug>


Geometry::Geometry(QObject *parent) : QObject(parent)
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();

  double center[3] = { 0.0, 0.0, 0.0 };
  int m_defaultFig;
  m_defaultFig = 0;
  m_data->ShallowCopy(CreateGeometryData(center, m_defaultFig));

  m_inputFilter->SetInputData(m_data);
}

Geometry::Geometry(double center[3], int fig, QObject *parent) : QObject(parent) //which one of these is the function's input
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();

  m_data->ShallowCopy(CreateGeometryData(center, fig));
  int i;
  for( i = 0; i < 3; i++){
      qDebug() << "center";
      qDebug() << center[i];
  }
  m_inputFilter->SetInputData(m_data);
}

Geometry::Geometry(Geometry&& geom) :
  QObject(geom.parent())
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();
  m_data->DeepCopy(geom.m_data);

  m_inputFilter->SetInputData(m_data);
  m_inputFilter->Update();
}

vtkSmartPointer<vtkPolyData>Geometry::CreateGeometryData(
  double center[3],
  int figure)
{
  // Create a cube
  int i;
  for( i = 0; i < 3; i++)
  {
      qDebug() << "Center";
      qDebug() << center[i];
  }
  if (figure == 0)
  {
      vtkSmartPointer<vtkCubeSource> fsource =
        vtkSmartPointer<vtkCubeSource>::New();
      fsource->SetBounds(
        -0.5, 0.5,
        -0.5, 0.5,
        -0.5, 0.5);
      fsource->SetCenter(center);
      fsource->Update();
      vtkSmartPointer<vtkPolyData> data =
        vtkSmartPointer<vtkPolyData>::New();
      data->ShallowCopy(fsource->GetOutput());
      //std::cout << "center> " << fsource->GetCenter()[0] << ", " << fsource->GetCenter()[1] << ", " << fsource->GetCenter()[2] << ", " << std::endl;

      return data;
  }
  else if (figure == 1)
  {
//  // Create a sphere
    vtkSmartPointer<vtkSphereSource> fsource =
    vtkSmartPointer<vtkSphereSource>::New();
    fsource->SetRadius(0.5);
    fsource->SetPhiResolution(20);
    fsource->SetThetaResolution(20);
    fsource->SetCenter(center);
    fsource->Update();
    vtkSmartPointer<vtkPolyData> data =
      vtkSmartPointer<vtkPolyData>::New();

    data->ShallowCopy(fsource->GetOutput());
    std::cout << fsource->GetCenter() << std::endl;
    return data;
    }
  else if (figure == 2)
  {
    vtkSmartPointer<vtkConeSource> fsource =
    vtkSmartPointer<vtkConeSource>::New();
    fsource->SetRadius(0.5);
    //fsource->SetPhiResolution(20);
    fsource->SetHeight(1);
    //fsource->SetThetaResolution(20);
    fsource->SetCenter(center);
    fsource->Update();
    vtkSmartPointer<vtkPolyData> data =
      vtkSmartPointer<vtkPolyData>::New();
    data->ShallowCopy(fsource->GetOutput());
    std::cout << fsource->GetCenter() << std::endl;
    return data;
  }
  else if (figure == 3)
  {

      // Read the image which will be the texture
       vtkSmartPointer<vtkJPEGReader> jPEGReader =
         vtkSmartPointer<vtkJPEGReader>::New();
       jPEGReader->SetFileName ( "/remote/cl01home/fabian/work/VtkTests/forks/try1/SimpleQt4VTKViewer/gp.jpg" );

//       vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
//         vtkSmartPointer<vtkJPEGReader>::New();
//       jPEGReader1->SetFileName ( "/remote/cl01home/fabian/work/VtkTests/forks/try1/SimpleQt4VTKViewer/gp1.jpg" );

       // Create a plane
       vtkSmartPointer<vtkPoints> points =
         vtkSmartPointer<vtkPoints>::New();
       points->InsertNextPoint(0.0, 0.0, 0.0);
       points->InsertNextPoint(1.0, 0.0, 0.0);
       points->InsertNextPoint(1.0, 1.0, 0.0);
       points->InsertNextPoint(0.0, 1.0, 0.0);
       points->InsertNextPoint(0.0, 0.0, 1.0);
       points->InsertNextPoint(1.0, 0.0, 1.0);
       points->InsertNextPoint(1.0, 1.0, 1.0);
       points->InsertNextPoint(0.0, 1.0, 1.0);

       vtkSmartPointer<vtkCellArray> polygons =
         vtkSmartPointer<vtkCellArray>::New();
       vtkSmartPointer<vtkPolygon> polygon =
         vtkSmartPointer<vtkPolygon>::New();
       polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
       polygon->GetPointIds()->SetId(0, 0);
       polygon->GetPointIds()->SetId(1, 1);
       polygon->GetPointIds()->SetId(2, 2);
       polygon->GetPointIds()->SetId(3, 3);

       vtkSmartPointer<vtkCellArray> polygons1 =
         vtkSmartPointer<vtkCellArray>::New();

       vtkSmartPointer<vtkPolygon> polygon1 =
         vtkSmartPointer<vtkPolygon>::New();
       polygon1->GetPointIds()->SetNumberOfIds(4); //make a quad
       std::cout << polygon1->GetPointIds() << std::endl;
       polygon1->GetPointIds()->SetId(0, 4);
       polygon1->GetPointIds()->SetId(1, 5);
       polygon1->GetPointIds()->SetId(2, 6);
       polygon1->GetPointIds()->SetId(3, 7);

       polygons->InsertNextCell(polygon);
       polygons1->InsertNextCell(polygon1);

       /*vtkSmartPointer<vtkIntArray> index =
           vtkSmartPointer<vtkIntArray>::New();
       index->SetNumberOfComponents(1);
       index->SetName("index");
       index->InsertNextValue(0);
       index->InsertNextValue(1);*/

       vtkSmartPointer<vtkPolyData> quad =
         vtkSmartPointer<vtkPolyData>::New();
       quad->SetPoints(points);
       quad->SetPolys(polygons);
       //quad->GetCellData()->AddArray(index);

       vtkSmartPointer<vtkPolyData> quad1 =
         vtkSmartPointer<vtkPolyData>::New();
       quad1->SetPoints(points);
       quad1->SetPolys(polygons1);

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

       vtkSmartPointer<vtkFloatArray> textureCoordinates1 =
         vtkSmartPointer<vtkFloatArray>::New();
       textureCoordinates1->SetNumberOfComponents(3);
       textureCoordinates1->SetName("TextureCoordinates");


       float tuple1[3] = {0.0, 0.0, 1.0};
       textureCoordinates1->InsertNextTuple(tuple1);
       tuple1[0] = 1.0; tuple1[1] = 0.0; tuple1[2] = 1.0;
       textureCoordinates1->InsertNextTuple(tuple1);
       tuple1[0] = 1.0; tuple1[1] = 1.0; tuple1[2] = 1.0;
       textureCoordinates1->InsertNextTuple(tuple1);
       tuple1[0] = 0.0; tuple1[1] = 1.0; tuple1[2] = 1.0;
       textureCoordinates1->InsertNextTuple(tuple1);

       quad->GetPointData()->SetTCoords(textureCoordinates);
       quad1->GetPointData()->SetTCoords(textureCoordinates);

       // Apply the texture
       vtkSmartPointer<vtkTexture> texture =
         vtkSmartPointer<vtkTexture>::New();
       texture->SetInputConnection(jPEGReader->GetOutputPort());

       vtkSmartPointer<vtkTexture> texture1 =
         vtkSmartPointer<vtkTexture>::New();
       texture1->SetInputConnection(jPEGReader->GetOutputPort());

       vtkSmartPointer<vtkPolyDataMapper> mapper =
         vtkSmartPointer<vtkPolyDataMapper>::New();

       vtkSmartPointer<vtkPolyDataMapper> mapper1 =
         vtkSmartPointer<vtkPolyDataMapper>::New();

//       mapper->SetInputData(quad);
       mapper1->SetInputData(quad1);


//       vtkSmartPointer<vtkActor> texturedQuad =
//         vtkSmartPointer<vtkActor>::New();
//       texturedQuad->SetMapper(mapper);
//       texturedQuad->SetTexture(texture);

       vtkSmartPointer<vtkActor> texturedQuad1 =
         vtkSmartPointer<vtkActor>::New();
       texturedQuad1->SetMapper(mapper1);
       texturedQuad1->SetTexture(texture1);


       // Visualize the textured plane
       vtkSmartPointer<vtkRenderer> renderer =
         vtkSmartPointer<vtkRenderer>::New();


       //vtkSmartPointer<vtkActor> actor =
       //  vtkSmartPointer<vtkActor>::New();
       //vtkSmartPointer<vtkActor> actor1 =
       //  vtkSmartPointer<vtkActor>::New();

       //actor->SetMapper(mapper);
       //actor1->SetMapper(mapper1);
//       renderer->AddActor(texturedQuad);
       renderer->AddActor(texturedQuad1);
       renderer->SetBackground(1,1,1); // Background color white
       renderer->ResetCamera();

       vtkSmartPointer<vtkRenderWindow> renderWindow =
         vtkSmartPointer<vtkRenderWindow>::New();
       renderWindow->AddRenderer(renderer);

       vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
         vtkSmartPointer<vtkRenderWindowInteractor>::New();
       renderWindowInteractor->SetRenderWindow(renderWindow);

       renderWindow->Render();

       renderWindowInteractor->Start();

  }
}


vtkAlgorithmOutput* Geometry::getGeometryConection()
{
  m_inputFilter->Update();
  return m_inputFilter->GetOutputPort();
}

vtkPolyData* Geometry::getGeometryData()
{
  m_inputFilter->Update();

  return vtkPolyData::SafeDownCast( m_inputFilter->GetOutput() );
}

void Geometry::setNewCenter(double center[3])
{
  m_data->ShallowCopy(CreateGeometryData(center, 0));
}

