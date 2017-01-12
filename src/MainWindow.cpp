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

#include "MainWindow.h"
#include "ui_MainWindow.h"

//C++ Includes
#include <iostream>

//Qt Includes
#include <QHBoxLayout>

//VTK Includes
#include <vtkDebugLeaks.h>

//Project Includes
#include "AboutDialog.h"
#include "Geometry.h"
#include "PlotHD.h"
#include "NewGeoDialog.h"


MainWindow* MainWindow::m_winInstance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  new QHBoxLayout(m_ui->m_plotsWidget);

  connect(
    m_ui->m_addBtn, SIGNAL(pressed()),
    this,           SLOT(addPlot()));

  connect(
    m_ui->m_removeBtn, SIGNAL(pressed()),
    this,              SLOT(removePlot()));

  connect(
    m_ui->m_addGeomBtn, SIGNAL(pressed()),
    this,               SLOT(addGeometry()));

  connect(
    m_ui->m_removeGeomBtn, SIGNAL(pressed()),
    this,                  SLOT(removeGeometry()));

  connect(
    m_ui->action_About, SIGNAL(triggered(bool)),
    this,               SLOT(showAboutDialog()));

  connect(
    m_ui->m_fig2plot, SIGNAL(pressed()),
    this,               SLOT(addFig2Plot()));

  m_geomList.append(std::make_shared<Geometry>(this));

  addPlot();
}

MainWindow::~MainWindow()
{
  delete m_ui;

//  qDeleteAll(m_plotList);
}

void MainWindow::addPlot()
{
  m_plotList.append(new PlotHD(m_ui->m_plotsWidget));

  m_ui->m_plotsWidget->layout()->addWidget(m_plotList.last());

  if( m_geomList.isEmpty() )
  {
    addGeometry();
  }
  int indice;
  indice = m_plotList.size();
  std::string s = std::to_string(indice);
  char const *pchar = s.c_str();
  m_plotList.last()->addGeometry(m_geomList.last(), pchar);

//  vtkDebugLeaks::PrintCurrentLeaks();
}

void MainWindow::removePlot()
{
  if( m_plotList.isEmpty() )
  {
    std::cout << "No more plots left!!!" << std::endl;
    return;
  }

  m_plotList.last()->deleteLater();
  m_plotList.pop_back();

//  vtkDebugLeaks::PrintCurrentLeaks();
}

void MainWindow::addGeometry()
{
  NewGeoDialog params;
  params.exec();
  double* center;
  center = params.getCenter();
  int fig;
  fig = params.getFigure();
  int i;
  for( i = 0; i < 3; i++)
  {
      std::cout << "Center" << std::endl;
      std::cout << center[i] << std::endl;
  }

  m_geomList.append(std::make_shared<Geometry>(center,fig,this));

//  vtkDebugLeaks::PrintCurrentLeaks();
}

void MainWindow::removeGeometry()
{
  if( m_geomList.isEmpty() )
  {
    std::cout << "No more geometries left!!!" << std::endl;
    return;
  }

  m_geomList.last().reset();
  m_geomList.pop_back();

  QVector<PlotHD*> newPlotList;

  for( PlotHD* plt : m_plotList )
  {
    if( !plt->checkPlotDeletion() )
    {
      newPlotList << plt;
    }
  }

  m_plotList = newPlotList;

//  vtkDebugLeaks::PrintCurrentLeaks();
}

void MainWindow::customEvent(QEvent* ev)
{
  if( ev->type() == QEvent::User )
  {
    std::cout << "Event post Plot deletion." << std::endl;
    //    vtkDebugLeaks::PrintCurrentLeaks();
  }
}

MainWindow& MainWindow::GetWindowInstance()
{
  if( !m_winInstance )
  {
    m_winInstance = new MainWindow();
  }

  return *m_winInstance;
}

void MainWindow::removeAllPlots()
{
  for( PlotHD* plt : m_plotList )
  {
    delete plt;
  }
  m_plotList.clear();
}

void MainWindow::removeAllGeometries()
{
  for( auto geom : m_geomList )
  {
    geom.reset();
  }

  m_geomList.clear();
}

void MainWindow::showAboutDialog()
{
//  AboutDialog* dialog = new AboutDialog();
  AboutDialog dialog;
  dialog.setModal(true);
  if( dialog.exec() == QDialog::Accepted )
  {
    std::cout << dialog.getLabelText().toStdString() << std::endl;
  }
//  dialog->show();
}

void MainWindow::showTextline()
{
    //std::cout << m_ui->m_field1->text().toStdString() <<std::endl;
    //m_ui->m_field1->setText("nope");
}

void MainWindow::addFig2Plot()
{
    NewGeoDialog params;
    params.exec();
    double* center;
    center = params.getCenter();
    int fig;
    fig = params.getFigure();
    int i;
    for( i = 0; i < 3; i++)
    {
        std::cout << "Center" << std::endl;
        std::cout << center[i] << std::endl;
    }

    m_geomList.append(std::make_shared<Geometry>(center,fig,this));
    m_plotList.last()->addGeometry(m_geomList.last());

}
