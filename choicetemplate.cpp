#include "choicetemplate.h"
#include "ui_choicetemplate.h"
#include <QMessageBox>

ChoiceTemplate::ChoiceTemplate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChoiceTemplate)
{
    ui->setupUi(this);
    setWindowTitle("Библиотека шаблонов");

    for(const auto& pair : m_TemplateNames)
    {
        ui->TemplateList->addItem(pair.second);
    }

    ui->TemplateList->setCurrentRow(0);

    ui->b_Choice->setShortcut(QKeySequence(Qt::Key_Return));
    ui->b_Cancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(ui->b_Choice, &QPushButton::clicked, this, &ChoiceTemplate::accept);
    connect(ui->b_Cancel, &QPushButton::clicked, this, &QDialog::reject);
}

const std::unordered_map<ChoiceTemplate::CurrentTemplate, QString> ChoiceTemplate::m_TemplateNames = {
    {CurrentTemplate::Linear, "Линейная сцена"},
    {CurrentTemplate::WithChoice, "Сцена с выбором"},
    {CurrentTemplate::WithCondition, "Сцена с условием для завершения"}
};

ChoiceTemplate::~ChoiceTemplate()
{
    delete ui;
}

QString ChoiceTemplate::getCurrentTemplateName() const
{
    auto it = m_TemplateNames.find(m_CurrentTemplate);
    if(it != m_TemplateNames.end()) return it->second;
    return QString{};
}

void ChoiceTemplate::openDialog()
{
    //Ставим в None, чтобы не было нежелательных состояний
    m_CurrentTemplate = CurrentTemplate::None;
    //возвращаем фокус на первую строку
    ui->TemplateList->setCurrentRow(0);
    exec();
}

void ChoiceTemplate::accept()
{
    auto currentItem = ui->TemplateList->currentItem();
    //В случае, если ни один шаблон не выбрал
    if(!currentItem) { QMessageBox::warning(this, tr("Внимание"), tr("Пожалуйста, выберете шаблон!")); return;}

    auto selectedText = currentItem->text();
    //Поиск названия шаблона, который выбрал пользователь
    for(const auto& pair : m_TemplateNames)
    {
        if(pair.second == selectedText) { m_CurrentTemplate = pair.first; break; }
    }

    return QDialog::accept();
}
