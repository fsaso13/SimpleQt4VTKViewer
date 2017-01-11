#ifndef PARAMSDIALOG2_H
#define PARAMSDIALOG2_H

#include <QDialog>

namespace Ui {
class ParamsDialog2;
}

class ParamsDialog2 : public QDialog
{
    Q_OBJECT
    double color[3];

public:
    explicit ParamsDialog2(QWidget *parent = 0);
    ~ParamsDialog2();

public slots:
    double* getColor();

protected slots:
    //void newLayout();
    void setParams();

private:
    Ui::ParamsDialog2 *m_ui;
};

#endif // PARAMSDIALOG2_H
