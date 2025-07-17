#ifndef DESIGNER_H
#define DESIGNER_H

#include <QMainWindow>
#include <QMessageBox>

#include "choicetemplate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Designer;
}
QT_END_NAMESPACE

class Designer : public QMainWindow
{
    Q_OBJECT

public:
    Designer(QWidget *parent = nullptr);
    ~Designer();

private slots:
    void newScene();
    void saveJSON();
    void exportFromDll();

private:
    Ui::Designer *ui;
    bool checkReleaseText() const;
    ChoiceTemplate* t = new ChoiceTemplate;
};
#endif // DESIGNER_H
