#ifndef NEWGEODIALOG_H
#define NEWGEODIALOG_H


#include <QDialog>

namespace Ui {
    class NewGeoDialog;
}

class NewGeoDialog : public QDialog
{
    Q_OBJECT
    double center[3];
    int figure;

public:
    explicit NewGeoDialog(QWidget *parent = 0);
    ~NewGeoDialog();

public slots:
    double* getCenter();
    int getFigure();

protected slots:
    void newLayout();
    void setParams();


private:
    Ui::NewGeoDialog *m_ui;

};

#endif // NEWGEODIALOG_H
