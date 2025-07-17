#ifndef CHOICETEMPLATE_H
#define CHOICETEMPLATE_H

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

    enum class CurrentTemplate
    {
        None = -1,
        Linear = 0,
        WithChoice,
        WithCondition,
        Count
    };

    static const std::unordered_map<CurrentTemplate, QString> m_TemplateNames;

    CurrentTemplate m_CurrentTemplate = CurrentTemplate::None;

public:
    explicit ChoiceTemplate(QWidget *parent = nullptr);
    ~ChoiceTemplate();

    QString currentTemplateName() const;
    CurrentTemplate currentTemplateType() const { return m_CurrentTemplate; }

protected:
    void accept() override;

};

#endif // CHOICETEMPLATE_H
