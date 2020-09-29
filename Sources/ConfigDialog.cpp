#include "../Headers/ConfigDialog.h"

#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QSpinBox>
#include <QtGlobal>
#include <QGridLayout>
#include <QSize>
#include <QSpacerItem>
#include <QSizePolicy>
#include <iostream>


ConfigDialog :: ConfigDialog()
{
    centralWidget = new QWidget(this);

    this->mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    this->createProbabilityControls();
    this->createRuleButtonsGrid();
    this->createOKButtons();

    // TO DO: auto resize
    this->resize(520, 250);
    setWindowTitle(tr("Configuration"));
}

/* Create control to set probability 
   of appearance of alive cells */
void ConfigDialog :: createProbabilityControls()
{   
    QVBoxLayout* mainProbabilityLayout = new QVBoxLayout;
    QHBoxLayout* probabilityLayout = new QHBoxLayout;

    probabilitySlider = new QSlider(Qt::Horizontal);
    probabilitySlider->setMinimum(2);
    probabilitySlider->setMaximum(100);
    probabilitySlider->setTickPosition(QSlider::TicksBothSides);
    probabilitySlider->setTickInterval(10);
    probabilitySlider->setSingleStep(1);

    QSpinBox* probabilitySpinBox = new QSpinBox;
    probabilitySpinBox->setRange(2, 100);
    probabilitySpinBox->setSingleStep(1);

    QObject::connect(probabilitySlider, &QSlider::valueChanged, this, &ConfigDialog::setProbabilityOfDeadCells);
    QObject::connect(probabilitySlider, &QSlider::valueChanged, probabilitySpinBox, &QSpinBox::setValue);
    QObject::connect(probabilitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), probabilitySlider, &QSlider::setValue);

    probabilityLayout->addWidget(probabilitySpinBox);
    probabilityLayout->addWidget(probabilitySlider);

    QLabel* descriptionLabel = new QLabel(tr("Percent of alive cells: "), this);

    mainProbabilityLayout->addWidget(descriptionLabel);
    mainProbabilityLayout->addLayout(probabilityLayout);
    
    this->mainLayout->addLayout(mainProbabilityLayout);
}

/* Set rule's control */
void ConfigDialog :: createRulesControls()
{
    QVBoxLayout* mainRulesLayout = new QVBoxLayout;
    QHBoxLayout* rulesLayout = new QHBoxLayout;

    QSpinBox* rulesForDeadCellSpinBox = new QSpinBox;
    rulesForDeadCellSpinBox->setRange(0, 8);
    rulesForDeadCellSpinBox->setSingleStep(1);

    QSpinBox* rulesForAliveCellSpinBox = new QSpinBox;
    rulesForAliveCellSpinBox->setRange(0, 8);
    rulesForAliveCellSpinBox->setSingleStep(1);

    QLabel* aliveLabel = new QLabel(tr("Dead: "), this);
    QLabel* deadLabel = new QLabel(tr("Alive: "), this);

    rulesLayout->addWidget(deadLabel);
    rulesLayout->addWidget(rulesForDeadCellSpinBox);
    rulesLayout->addWidget(aliveLabel);
    rulesLayout->addWidget(rulesForAliveCellSpinBox);

    QLabel* descriptionLabel = new QLabel(tr("Count of alive cells around: "), this);

    mainRulesLayout->addWidget(descriptionLabel);
    mainRulesLayout->addLayout(rulesLayout);

    this->mainLayout->addLayout(mainRulesLayout);
}

void ConfigDialog :: createOKButtons()
{
    QHBoxLayout* buttonsLayout = new QHBoxLayout;

    QPushButton* cancel = new QPushButton(tr("&Cancel"));
    QPushButton* ok = new QPushButton(tr("&Ok"));
    
    QObject::connect(cancel, &QPushButton::clicked, this, &ConfigDialog::reject);
    QObject::connect(ok, &QPushButton::clicked, this, &ConfigDialog::accept);


    buttonsLayout->addWidget(cancel);
    buttonsLayout->addWidget(ok);

    this->mainLayout->addLayout(buttonsLayout);
}

void ConfigDialog :: setProbabilityOfDeadCells(int probability)
{
    this->probabilityOfDeadCells = probability;
}

int ConfigDialog :: getProbabilityOfDeadCells()
{
    return this->probabilityOfDeadCells;
}

void ConfigDialog :: createRuleButtonsGrid()
{   
    QVBoxLayout *mainRuleButtonLayout = new QVBoxLayout;

    QLabel *descriptionLabel = new QLabel("Count of alive cells around: ");

    QHBoxLayout *buttonsLayoutForDeadCell = new QHBoxLayout;

    buttonsLayoutForDeadCell->setSpacing(0);
    buttonsLayoutForDeadCell->setMargin(0);

    buttonsLayoutForDeadCell->addWidget(new QLabel("Dead: "));

    QPushButton *buttonsForDeadCell[9];

    const QSize buttonSize = QSize(50, 50);
    
    for (int i = 0; i < 9; i++) {
        buttonsForDeadCell[i] = new QPushButton();
        buttonsForDeadCell[i]->setFixedSize(buttonSize);
        buttonsLayoutForDeadCell->addWidget(buttonsForDeadCell[i]);
        QObject::connect(buttonsForDeadCell[i], &QPushButton::clicked, [=](){ this->changeButtonColor(buttonsForDeadCell[i]); });
        QObject::connect(buttonsForDeadCell[i], &QPushButton::clicked, [=](){ this->setRule(0, i); });
    }


    QHBoxLayout *buttonsLayoutForAliveCell = new QHBoxLayout;

    buttonsLayoutForAliveCell->setSpacing(0);
    buttonsLayoutForAliveCell->setMargin(0);

    buttonsLayoutForAliveCell->addWidget(new QLabel("Alive: "));

    QPushButton *buttonsForAliveCell[9];

    for (int i = 0; i < 9; i++) {
        buttonsForAliveCell[i] = new QPushButton();
        buttonsForAliveCell[i]->setFixedSize(buttonSize);
        buttonsLayoutForAliveCell->addWidget(buttonsForAliveCell[i]);
        QObject::connect(buttonsForAliveCell[i], &QPushButton::clicked, [=](){ this->changeButtonColor(buttonsForAliveCell[i]); });
        QObject::connect(buttonsForAliveCell[i], &QPushButton::clicked, [=](){ this->setRule(1, i); });
    }

    mainRuleButtonLayout->addWidget(descriptionLabel);
    mainRuleButtonLayout->addLayout(buttonsLayoutForDeadCell);
    mainRuleButtonLayout->addLayout(buttonsLayoutForAliveCell);

    this->mainLayout->addLayout(mainRuleButtonLayout);
}

void ConfigDialog :: setRule(int y, int x)
{
    this->rule[y][x] = !this->rule[y][x];
}

void ConfigDialog :: changeButtonColor(QPushButton *button)
{   
    QColor *defaultColor = new QColor("#efebe7");

    if(button->palette().background().color() == *defaultColor)
        button->setStyleSheet("background-color: black;");
    else
        button->setStyleSheet("background-color: #efebe7;");
}

bool** ConfigDialog :: getRule()
{   
    bool** rule = new bool*[2];

    for (int y = 0; y < 2; y++) {
        rule[y] = new bool[9];
        
        for (int x = 0; x < 9; x++)
            rule[y][x] = this->rule[y][x];
    }

    return rule;
}