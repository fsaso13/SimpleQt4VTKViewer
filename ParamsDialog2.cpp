#include "ParamsDialog2.h"
#include "ui_ParamsDialog2.h"
#include <QtUiTools>
#include <QFile>
#include <QVBoxLayout>
#include <string.h>
#include <iostream>


ParamsDialog2::ParamsDialog2(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ParamsDialog2)
{
    m_ui->setupUi(this);
    connect(m_ui->m_commitBtn, SIGNAL(pressed()), this, SLOT(setParams()));
}

ParamsDialog2::~ParamsDialog2()
{
    delete m_ui;
}

void ParamsDialog2::setParams(){
    this->color[0] = m_ui->m_r->text().toDouble();
    this->color[1] = m_ui->m_g->text().toDouble();
    this->color[2] = m_ui->m_b->text().toDouble();
    int i;
    for( i = 0; i < 3; i++){
        std::cout << "kek" << std::endl;
        std::cout << this->color[i] << std::endl;
    }
    this->close();
}

double* ParamsDialog2::getColor(){
    return this->color;
}
