#include "designer.h"
#include "./ui_designer.h"
#include <QMessageBox>
#include <QAccessibleEvent>
#include <QTimer>


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
    setWindowTitle("AGL-Designer");


    ui->outputHintsDev->setFocus();

    choiceTemplate = std::make_unique<ChoiceTemplate>(this);
    hintsWindow = std::make_unique<HintsWindow>(this);

    //Ставим асинхронную задержку, чтобы основное окно успело открытся и выводим диалог с подсказками
    QTimer::singleShot(150, [this]() {hintsWindow->exec();});

    ui->outputHintsDev->setReadOnly(true);
    ui->outputHintsDev->setAccessibleDescription("Окно вывода подсказок, для создания игр");
    ui->enterTextGames->setAccessibleDescription("Поле ввода, для построения своей игры");
    ui->enterTextGames->setTabChangesFocus(true);

    ui->addScene->setShortcut(QKeySequence(Qt::Key_F1));
    ui->saveFile->setShortcut(QKeySequence(Qt::Key_F2));
    ui->exporter->setShortcut(QKeySequence(Qt::Key_F3));

    connect(ui->addScene, &QPushButton::clicked, this, &Designer::newScene);
    connect(ui->saveFile, &QPushButton::clicked, this, &Designer::saveJSON);
    connect(ui->exporter, &QPushButton::clicked, this, &Designer::exportFromDll);

    //коннекты для мониторинга диалога выбора шаблонов
    connect(choiceTemplate.get(), &QDialog::accepted, this, &Designer::showNameTemplate);
    connect(choiceTemplate.get(), &QDialog::rejected, this, &Designer::noTemplateChoice);

    //коннекты для мониторинга диалога подсказок
    connect(hintsWindow.get(), &QDialog::accepted, this, &Designer::hintsOn);
    //Пока как заглушка, при вызове диалога из главного окна будет использоваться
    connect(hintsWindow.get(), &QDialog::accepted, this, &Designer::hintsOff);
}

Designer::~Designer()
{
    delete ui;
}

//обработчик создания новой сцены — добавляет шаблон
void Designer::newScene()
{
    // QMessageBox::information(this, tr("Информация!"), tr("Добавляем новую сцену - шаблон!"));
    choiceTemplate->openDialog();
}

//обработчик сохранения написанного текста в JSON файл
void Designer::saveJSON()
{
    if(isTextEmpty()) //временная проверка для теста GUI, если пользователь пытается сохранить пустой файл
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
    if(isTextEmpty()) //временная проверка для теста GUI, если пользователь пытается экспортировать пустой файл
    {
        QMessageBox::information(this, tr("Информация!"), tr("Переносим(экспортируем) файл в плагин!\nИ, кстати, экспортировать нечего!"));
    }
    else
    {
        QMessageBox::information(this, tr("Информация!"), tr("Переносим(экспортируем) файл в плагин!"));
    }
}

bool Designer::isTextEmpty() const //временная проверка для теста GUI, что текст не пустой
{
    return ui->enterTextGames->toPlainText().trimmed().isEmpty();
}

//Временная заглушка, отображение выбранного шаблона
void Designer::showNameTemplate() const
{
    QString origin = "Вы выбрали " + choiceTemplate->getCurrentTemplateName();
    ui->outputHintsDev->setText(origin);
    updateAccessible(origin);
}

//Временная загрушка, если не выбран ни один шаблон
void Designer::noTemplateChoice() const
{
    QString info = "Вы закрыли библиотеку игр и не выбрали шаблон, пожалуйста, нажмите F1 и вернитесь к выбору!";
    ui->outputHintsDev->setText(info);
    updateAccessible(info);
}

//Делаем эвенты для обновления доступности, чтобы сринридеры видели новый текст
void Designer::updateAccessible(const QString& text) const
{
    ui->outputHintsDev->setFocus();
    //Обновление текста в виджете
    QAccessibleTextUpdateEvent ev(ui->outputHintsDev, 0, "", text);
    QAccessible::updateAccessibility(&ev);
    //Ставим фокус на виджет явно для скринридера
    QAccessibleEvent focusEv(ui->outputHintsDev, QAccessible::Focus);
    QAccessible::updateAccessibility(&focusEv);
}

//Ставим подсказки
void Designer::hintsOn() const
{
    ui->addScene->setAccessibleDescription("Добавляет новую сцену из шаблонов сцен");
    ui->addScene->setToolTip("Добавляет новую сцену из шаблонов сцен");
    ui->saveFile->setAccessibleDescription("Сохраняет написанное в JSON файл");
    ui->saveFile->setToolTip("Сохраняет написанное в JSON файл");
    ui->exporter->setAccessibleDescription("Экспортируем нашу игру в плагин");
    ui->exporter->setToolTip("Экспортируем нашу игру в плагин");
}

//Убираем подсказки
void Designer::hintsOff() const
{
    ui->addScene->setAccessibleDescription("");
    ui->addScene->setToolTip("");
    ui->saveFile->setAccessibleDescription("");
    ui->saveFile->setToolTip("");
    ui->exporter->setAccessibleDescription("");
    ui->exporter->setToolTip("");
}
