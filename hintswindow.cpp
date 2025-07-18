#include "hintswindow.h"
#include "ui_hintswindow.h"

HintsWindow::HintsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HintsWindow)
{
    ui->setupUi(this);

    //TODO: Сделать логику сохранения настроек из будущего ConfigManager, по подсказкам.
    setWindowTitle("Режим работы");
    ui->b_enter->setFocus();
    ui->b_enter->setShortcut(QKeySequence(Qt::Key_Return));

    connect(ui->b_enter, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->b_esc, &QPushButton::clicked, this, &QDialog::reject);
}

HintsWindow::~HintsWindow()
{
    delete ui;
}
