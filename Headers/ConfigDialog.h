#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>


// Dialog to initialize fisrt state of world
class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog();
    int getProbabilityOfDeadCells();

public slots:
    void setProbabilityOfDeadCells(int);
    bool** getRule();

private slots:
    void setRule(int, int);
    void changeButtonColor(QPushButton *button);

private:
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QSlider *probabilitySlider;

    void createProbabilityControls();
    void createRulesControls();
    void createOKButtons();
    void createRuleButtonsGrid();

    int probabilityOfDeadCells;
    bool rule[2][9] = { {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0} };
};

#endif