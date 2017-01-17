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
#include "vtkPlaneSource.h"
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

Geometry::Geometry(double center[3], int fig, QObject *parent) : QObject(parent)
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
    fsource->SetHeight(1);
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

    vtkSmartPointer<vtkJPEGReader> jPEGReader1 =
       vtkSmartPointer<vtkJPEGReader>::New();
    jPEGReader1->SetFileName ( "/remote/cl01home/fabian/work/VtkTests/forks/try1/SimpleQt4VTKViewer/ana.jpg" );

    // Create a plane
    vtkSmartPointer<vtkPoints> points =
       vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0); //0
    points->InsertNextPoint(1.0, 0.0, 0.0); //1
    points->InsertNextPoint(1.0, 1.0, 0.0); //2
    points->InsertNextPoint(0.0, 1.0, 0.0); //3
    points->InsertNextPoint(0.0, 0.0, 1.0); //4
    points->InsertNextPoint(1.0, 0.0, 1.0); //5
    points->InsertNextPoint(1.0, 1.0, 1.0); //6
    points->InsertNextPoint(0.0, 1.0, 1.0); //7

    //Face 0

    vtkSmartPointer<vtkCellArray> polygons =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkCellArray> polygons1 =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkCellArray> polygons2 =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkCellArray> polygons3 =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkCellArray> polygons4 =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkCellArray> polygons5 =
       vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkPolygon> polygon =
       vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon->GetPointIds()->SetId(0, 0);
    polygon->GetPointIds()->SetId(1, 1);
    polygon->GetPointIds()->SetId(2, 2);
    polygon->GetPointIds()->SetId(3, 3);

    //Face 1

    vtkSmartPointer<vtkPolygon> polygon1 =
       vtkSmartPointer<vtkPolygon>::New();
    polygon1->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon1->GetPointIds()->SetId(0, 4);
    polygon1->GetPointIds()->SetId(1, 5);
    polygon1->GetPointIds()->SetId(2, 6);
    polygon1->GetPointIds()->SetId(3, 7);

    //Face 2

    vtkSmartPointer<vtkPolygon> polygon2 =
       vtkSmartPointer<vtkPolygon>::New();
    polygon2->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon2->GetPointIds()->SetId(0, 2);
    polygon2->GetPointIds()->SetId(1, 1);
    polygon2->GetPointIds()->SetId(2, 5);
    polygon2->GetPointIds()->SetId(3, 6);

    //Face 3

    vtkSmartPointer<vtkPolygon> polygon3 =
       vtkSmartPointer<vtkPolygon>::New();
    polygon3->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon3->GetPointIds()->SetId(0, 0);
    polygon3->GetPointIds()->SetId(1, 4);
    polygon3->GetPointIds()->SetId(2, 7);
    polygon3->GetPointIds()->SetId(3, 3);

    //Face 4

    vtkSmartPointer<vtkPolygon> polygon4 =
       vtkSmartPointer<vtkPolygon>::New();
    polygon4->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon4->GetPointIds()->SetId(0, 3);
    polygon4->GetPointIds()->SetId(1, 7);
    polygon4->GetPointIds()->SetId(2, 6);
    polygon4->GetPointIds()->SetId(3, 2);

    //Face 5

    vtkSmartPointer<vtkPolygon> polygon5 =
       vtkSmartPointer<vtkPolygon>::New();
    polygon5->GetPointIds()->SetNumberOfIds(4); //make a quad
    polygon5->GetPointIds()->SetId(0, 0);
    polygon5->GetPointIds()->SetId(1, 1);
    polygon5->GetPointIds()->SetId(2, 5);
    polygon5->GetPointIds()->SetId(3, 4);

    polygons->InsertNextCell(polygon);
    polygons1->InsertNextCell(polygon1);
    polygons2->InsertNextCell(polygon2);
    polygons3->InsertNextCell(polygon3);
    polygons4->InsertNextCell(polygon4);
    polygons5->InsertNextCell(polygon5);


    vtkSmartPointer<vtkPlaneSource> planeSource =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource->SetCenter(0.0, 0.5, 0.5);
    planeSource->SetNormal(0.5, 0.0, 0.0);
    planeSource->Update();

    vtkPolyData* plane = planeSource->GetOutput();

    vtkSmartPointer<vtkPlaneSource> planeSource1 =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource1->SetCenter(1.0, 0.5, 0.5);
    planeSource1->SetNormal(0.5, 0.0, 0.0);
    planeSource1->Update();

    vtkPolyData* plane1 = planeSource1->GetOutput();

    vtkSmartPointer<vtkPlaneSource> planeSource2 =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource2->SetCenter(0.5, 0.5, 0.0);
    planeSource2->SetNormal(0.0, 0.0, 0.5);
    planeSource2->Update();

    vtkPolyData* plane2 = planeSource2->GetOutput();

    vtkSmartPointer<vtkPlaneSource> planeSource3 =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource3->SetCenter(0.5, 0.5, 1.0);
    planeSource3->SetNormal(0.0, 0.0, 0.5);
    planeSource3->Update();

    vtkPolyData* plane3 = planeSource3->GetOutput();

    vtkSmartPointer<vtkPlaneSource> planeSource4 =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource4->SetCenter(0.5, 0.0, 0.5);
    planeSource4->SetNormal(0.0, 0.5, 0.0);
    planeSource4->Update();

    vtkPolyData* plane4 = planeSource4->GetOutput();

    vtkSmartPointer<vtkPlaneSource> planeSource5 =
       vtkSmartPointer<vtkPlaneSource>::New();
    planeSource5->SetCenter(0.5, 1.0, 0.5);
    planeSource5->SetNormal(0.0, 0.5, 0.0);
    planeSource5->Update();

    vtkPolyData* plane5 = planeSource5->GetOutput();

    // Apply the texture
    vtkSmartPointer<vtkTexture> texture =
       vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(jPEGReader->GetOutputPort());

    vtkSmartPointer<vtkTexture> texture1 =
       vtkSmartPointer<vtkTexture>::New();
    texture1->SetInputConnection(jPEGReader1->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> mapper =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper1 =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper2 =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper3 =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper4 =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkPolyDataMapper> mapper5 =
       vtkSmartPointer<vtkPolyDataMapper>::New();

    mapper->SetInputData(plane);
    mapper1->SetInputData(plane1);
    mapper2->SetInputData(plane2);
    mapper3->SetInputData(plane3);
    mapper4->SetInputData(plane4);
    mapper5->SetInputData(plane5);

    vtkSmartPointer<vtkActor> texturedQuad =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad->SetMapper(mapper);
    texturedQuad->SetTexture(texture);

    vtkSmartPointer<vtkActor> texturedQuad1 =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad1->SetMapper(mapper1);
    texturedQuad1->SetTexture(texture);

    vtkSmartPointer<vtkActor> texturedQuad2 =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad2->SetMapper(mapper2);
    texturedQuad2->SetTexture(texture1);

    vtkSmartPointer<vtkActor> texturedQuad3 =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad3->SetMapper(mapper3);
    texturedQuad3->SetTexture(texture1);

    vtkSmartPointer<vtkActor> texturedQuad4 =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad4->SetMapper(mapper4);
    texturedQuad4->SetTexture(texture);

    vtkSmartPointer<vtkActor> texturedQuad5 =
       vtkSmartPointer<vtkActor>::New();
    texturedQuad5->SetMapper(mapper5);
    texturedQuad5->SetTexture(texture1);

    // Visualize the textured plane

    vtkSmartPointer<vtkRenderer> renderer =
       vtkSmartPointer<vtkRenderer>::New();

    renderer->AddActor(texturedQuad);
    renderer->AddActor(texturedQuad1);
    renderer->AddActor(texturedQuad2);
    renderer->AddActor(texturedQuad3);
    renderer->AddActor(texturedQuad4);
    renderer->AddActor(texturedQuad5);
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

