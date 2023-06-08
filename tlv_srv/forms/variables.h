#ifndef VARIABLES_H
#define VARIABLES_H

#include <QWidget>

namespace Ui {
class Variables;
}

class Variables : public QWidget
{
    Q_OBJECT

public:
    explicit Variables(QWidget *parent = nullptr);
    ~Variables();

private:
    Ui::Variables *ui;
};

#endif // VARIABLES_H
