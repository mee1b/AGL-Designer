#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <memory>

#include "hintswindow.h"
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
    bool isTextEmpty() const;

    void showNameTemplate() const;
    void noTemplateChoice() const;

    void updateAccessible(const QString& text) const;

    void hintsOn() const;
    void hintsOff() const;
    std::unique_ptr<ChoiceTemplate> choiceTemplate;
    std::unique_ptr<HintsWindow> hintsWindow;
};
