#include "paramsdialog.h"
#include "ui_Paramsdialog.h"

ParamsDialog::ParamsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsDialog)
{
    ui->setupUi(this);
}

ParamsDialog::~ParamsDialog()
{
    delete ui;
}
