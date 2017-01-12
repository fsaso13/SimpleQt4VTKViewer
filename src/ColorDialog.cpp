#include "ColorDialog.h"
#include "ui_ColorDialog.h"
#include <QtUiTools>
#include <QFile>
#include <QVBoxLayout>
#include <string.h>
#include <iostream>
#include <QDebug>
#include <QColor>
#include <QtGui>


ColorDialog::ColorDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ColorDialog)
{
    m_ui->setupUi(this);
    connect(m_ui->m_commitBtn, SIGNAL(pressed()), this, SLOT(setParams()));
}

ColorDialog::~ColorDialog()
{
    delete m_ui;
}

void ColorDialog::setParams()
{
    QColor ccolor = QColorDialog::getColor(Qt::yellow, this );
    if( ccolor.isValid() )
    {
        qDebug() << "Color Choosen : " << ccolor.name();
    }
    this->color[0] = ccolor.redF();
    this->color[1] = ccolor.greenF();
    this->color[2] = ccolor.blueF();
    int i;
    for( i = 0; i < 3; i++)
    {
        qDebug() << "Color" ;
        std::cout << this->color[i] << std::endl;
    }
    this->close();
}

double* ColorDialog::getColor()
{
    return this->color;
}
