#pragma once

#include <QDialog>

namespace Ui {
class HintsWindow;
}

class HintsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HintsWindow(QWidget *parent = nullptr);
    ~HintsWindow();

private:
    Ui::HintsWindow *ui;
};

