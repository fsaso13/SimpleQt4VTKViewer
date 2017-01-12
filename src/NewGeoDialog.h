#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H


#include <QDialog>

namespace Ui {
    class ParamsDialog;
}

class ParamsDialog : public QDialog
{
    Q_OBJECT
    double center[3];
    int figure;

public:
    explicit ParamsDialog(QWidget *parent = 0);
    ~ParamsDialog();

public slots:
    double* getCenter();
    int getFigure();

protected slots:
    void newLayout();
    void setParams();


private:
    Ui::ParamsDialog *m_ui;

};

#endif // PARAMSDIALOG_H
