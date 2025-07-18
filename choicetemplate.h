#pragma once

#include <QDialog>
#include <unordered_map>


namespace Ui {
class ChoiceTemplate;
}

class ChoiceTemplate : public QDialog
{
    Q_OBJECT

private:
    Ui::ChoiceTemplate *ui;

    //Перечисление выбора шаблонов
    enum class CurrentTemplate
    {
        None = -1,
        Linear = 0,
        WithChoice,
        WithCondition,
        //счетчик общего числа шаблонов
        Count
    };

    //мапа для быстрого поиска имени шаблона. static для единственно инициализации, чтобы не копировать постоянно
    static const std::unordered_map<CurrentTemplate, QString> m_TemplateNames;

    CurrentTemplate m_CurrentTemplate = CurrentTemplate::None;

public:
    explicit ChoiceTemplate(QWidget *parent = nullptr);
    ~ChoiceTemplate();

    //возвращаем текущее название шаблона
    QString getCurrentTemplateName() const;
    void openDialog();

protected:
    void accept() override;

};
