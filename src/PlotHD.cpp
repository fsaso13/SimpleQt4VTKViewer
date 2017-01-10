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

#include "PlotHD.h"

#include <vtkActor.h>
#include <vtkActorCollection.h>
#include <vtkAutoInit.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyle.h>
#include <vtkTDxInteractorStyleCamera.h>
#include <vtkTDxInteractorStyleSettings.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <QVTKWidget2.h>

#include <QApplication>
#include <QVBoxLayout>

#include "Geometry.h"
#include "MainWindow.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

PlotHD::PlotHD(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout* lay = new QVBoxLayout(this);
  m_renderWidget = new QVTKWidget2(this);
  m_renderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  m_renderer = vtkSmartPointer<vtkRenderer>::New();
  m_renderer->SetBackground(1, .714, .757); // Background color green ffb6c1

  lay->addWidget(m_renderWidget);
  lay->setContentsMargins(0, 0, 0, 0);

  m_renderWidget->GetRenderWindow()->AddRenderer(m_renderer);
}

PlotHD::~PlotHD()
{
}

void PlotHD::addGeometry(std::weak_ptr<Geometry> geom)
{
  if( auto validGeom = geom.lock() )
  {
    m_geom = geom;

    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(validGeom->getGeometryConection());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.0, 0.0, 1.0);

    m_renderer->AddActor(actor);
  }
}

bool PlotHD::checkPlotDeletion()
{
  if( m_geom.expired() )
  {
    delete this;
    //    this->deleteLater();
    return true;
  }

  return false;
}
