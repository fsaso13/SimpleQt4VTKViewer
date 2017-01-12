#include "ColorDialog.h"
#include "ui_ColorDialog.h"
#include <QtUiTools>
#include <QFile>
#include <QVBoxLayout>
#include <string.h>
#include <iostream>
#include <QDebug>


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
    this->color[0] = m_ui->m_r->text().toDouble();
    this->color[1] = m_ui->m_g->text().toDouble();
    this->color[2] = m_ui->m_b->text().toDouble();
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
