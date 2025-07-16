#ifndef DESIGNER_H
#define DESIGNER_H

#include <QMainWindow>

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
};
#endif // DESIGNER_H
