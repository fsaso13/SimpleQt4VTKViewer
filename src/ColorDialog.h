#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QErrorMessage;


namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT
    double color[3];

public:
    explicit ColorDialog(QWidget *parent = 0);
    ~ColorDialog();

public slots:
    double* getColor();

protected slots:
    //void newLayout();
    void setParams();

private:
    Ui::ColorDialog *m_ui;
};

#endif // COLORDIALOG_H
