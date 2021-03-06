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
#include "MyVTKApplication.h"
#include "ParamsDialog.h"
int main(int argc, char** argv)
{
  MyVTKApplication a(argc, argv);

//  MyDialog dialog;
//  dialog.exec();
//  ParamsDialog params;
//  params.exec();

  MainWindow& w = MainWindow::GetWindowInstance();
//  w.setbackground(dalog.getbackgroundcolor());
//  ...

  w.show();

  return a.exec();
}

