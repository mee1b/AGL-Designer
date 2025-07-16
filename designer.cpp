#include "designer.h"
#include "./ui_designer.h"
#include <QMessageBox>

/*Завтра делаю класс ChoiceTemplate - где, после нажатия кнопки доабвить шаблон, будет появляться окно со списком заготовок.
 * И если успею, делаю еще окно в при старте приложения, какие подсказки будут,
 * без подсказок или с подсказками(все tool и descr включены)*/

Designer::Designer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Designer)
{
    ui->setupUi(this);
    // ставим окно на полный экран
    setWindowState(Qt::WindowState::WindowMaximized);

    ui->outputHintsDev->setFocus();

    ui->outputHintsDev->setReadOnly(true);
    ui->outputHintsDev->setAccessibleDescription("Окно вывода подсказок, для создания игр");
    ui->enterTextGames->setAccessibleDescription("Поле ввода, для построения своей игры");
    ui->enterTextGames->setTabChangesFocus(true);

    ui->addScene->setShortcut(QKeySequence(Qt::Key_F1));
    ui->addScene->setAccessibleDescription("Добавляет новую сцену из шаблонов сцен");
    ui->saveFile->setShortcut(QKeySequence(Qt::Key_F2));
    ui->saveFile->setAccessibleDescription("Сохраняет написанное в JSON файл");
    ui->exporter->setShortcut(QKeySequence(Qt::Key_F3));
    ui->exporter->setAccessibleDescription("Экспортируем нашу игру в плагин");

    connect(ui->addScene, &QPushButton::clicked, this, &Designer::newScene);
    connect(ui->saveFile, &QPushButton::clicked, this, &Designer::saveJSON);
    connect(ui->exporter, &QPushButton::clicked, this, &Designer::exportFromDll);
}

Designer::~Designer()
{
    delete ui;
}

//обработчик создания новой сцены — добавляет шаблон
void Designer::newScene()
{
    QMessageBox::information(this, tr("Информация!"), tr("Добавляем новую сцену - шаблон!"));
}

//обработчик сохранения написанного текста в JSON файл
void Designer::saveJSON()
{
    if(checkReleaseText()) //временная проверка для теста GUI, если пользователь пытается сохранить пустой файл
    {
        QMessageBox::information(this, tr("Информация!"), tr("Сохраняем написанное в файл!\nИ, кстати, сохранять нечего!"));
    }
    else
    {
        QMessageBox::information(this, tr("Информация!"), tr("Сохраняем написанное в файл!"));
    }
}

//обработчик экспорта написанного текста в dll плагин
void Designer::exportFromDll()
{
    if(checkReleaseText()) //временная проверка для теста GUI, если пользователь пытается экспортировать пустой файл
    {
        QMessageBox::information(this, tr("Информация!"), tr("Переносим(экспортируем) файл в плагин!\nИ, кстати, экспортировать нечего!"));
    }
    else
    {
        QMessageBox::information(this, tr("Информация!"), tr("Переносим(экспортируем) файл в плагин!"));
    }
}

bool Designer::checkReleaseText() const //временная проверка для теста GUI, что текст не пустой
{
    return ui->enterTextGames->toPlainText().trimmed().isEmpty();
}
