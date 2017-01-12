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

Geometry::Geometry(QObject *parent) : QObject(parent)
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();

//  double center[3] = { -5.0, -5.0, 5.0 };
  double center[3] = { 0.0, 0.0, 0.0 };
  int default_fig;
  default_fig = 0;
  m_data->ShallowCopy(CreateGeometryData(center, default_fig));

  m_inputFilter->SetInputData(m_data);
}

Geometry::Geometry(double center[3], int fig, QObject *parent) : QObject(parent) //which one of these is the function's input
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();

  //double center[3] = { -5.0, -5.0, 5.0 };
  //gotta figuro out how to insert some variables there
  //double center[3] = { 0.0, 0.0, 0.0 };         //initial coodinates for the figure's center
  m_data->ShallowCopy(CreateGeometryData(center, fig));
  int i;
  for( i = 0; i < 3; i++){
      std::cout << "center" << std::endl;
      std::cout << center[i] << std::endl;
  }
  m_inputFilter->SetInputData(m_data);
}

Geometry::Geometry(Geometry&& geom) :
  QObject(geom.parent()) //which one of these is the function's input
{
  m_inputFilter = vtkSmartPointer<vtkPassThrough>::New();
  m_data = vtkSmartPointer<vtkPolyData>::New();
  m_data->DeepCopy(geom.m_data);

  m_inputFilter->SetInputData(m_data);
  m_inputFilter->Update();
}

vtkSmartPointer<vtkPolyData> Geometry::CreateGeometryData(double center[3], int figure)
{
  // Create a cube
  int i;
  for( i = 0; i < 3; i++){
      std::cout << "Center" << std::endl;
      std::cout << center[i] << std::endl;
  }
  if (figure == 0){
      vtkSmartPointer<vtkCubeSource> fsource =
        vtkSmartPointer<vtkCubeSource>::New();
      fsource->SetCenter(center);
      fsource->SetBounds(
        -0.5, 0.5,
        -0.5, 0.5,
        -0.5, 0.5);
      fsource->Update();
      vtkSmartPointer<vtkPolyData> data =
        vtkSmartPointer<vtkPolyData>::New();

      data->ShallowCopy(fsource->GetOutput());
      std::cout << "center> " << fsource->GetCenter()[0] << ", " << fsource->GetCenter()[1] << ", " << fsource->GetCenter()[2] << ", " << std::endl;
      return data;
  }
  else if (figure == 1){
//  // Create a sphere
    vtkSmartPointer<vtkSphereSource> fsource =
    vtkSmartPointer<vtkSphereSource>::New();
    fsource->SetRadius(0.5);
    fsource->SetPhiResolution(20);
    fsource->SetThetaResolution(20);
    fsource->Update();
    vtkSmartPointer<vtkPolyData> data =
      vtkSmartPointer<vtkPolyData>::New();

    data->ShallowCopy(fsource->GetOutput());
    std::cout << fsource->GetCenter() << std::endl;
    return data;
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
