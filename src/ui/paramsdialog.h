#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H

#include <QWidget>

namespace Ui {
class ParamsDialog;
}

class ParamsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsDialog(QWidget *parent = 0);
    ~ParamsDialog();

private:
    Ui::ParamsDialog *ui;
};

#endif // PARAMSDIALOG_H
