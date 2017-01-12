#include "NewGeoDialog.h"
#include "ui_ParamsDialog.h"
//#include <QtUiTools/QUiLoader>
#include <QtUiTools>
#include <QFile>
#include <QVBoxLayout>
#include <string.h>
#include <iostream>

ParamsDialog::ParamsDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ParamsDialog)
{
    m_ui->setupUi(this);

    connect(m_ui->m_commit, SIGNAL(pressed()), this, SLOT(setParams()));
}

ParamsDialog::~ParamsDialog(){
    delete m_ui;
}

void ParamsDialog::newLayout(){

}

void ParamsDialog::setParams(){
    this->center[0] = m_ui->m_xcenter->text().toDouble();
    this->center[1] = m_ui->m_ycenter->text().toDouble();
    this->center[2] = m_ui->m_zcenter->text().toDouble();
    this->figure = m_ui->m_kek->currentIndex();
    int i;
    std::cout << this->figure << std::endl;
    for( i = 0; i < 3; i++){
        qDebug() << "Color";
        std::cout << this->center[i] << std::endl;
    }
    this->close();
}

double* ParamsDialog::getCenter(){
    return this->center;
}

int ParamsDialog::getFigure(){
    return this->figure;
}
