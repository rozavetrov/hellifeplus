#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>


class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog();
    int getProbabilityOfDeadCells();

public slots:
    // void changeConfig();
    void setProbabilityOfDeadCells(int);

private:
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QSlider *probabilitySlider;

    void createProbabilityControls();
    void createRulesControls();
    void createButtons();

    int probabilityOfDeadCells;
};

#endif