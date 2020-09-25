#include "../Headers/ConfigDialog.h"

#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QSpinBox>
#include <QtGlobal>


ConfigDialog :: ConfigDialog()
{
    centralWidget = new QWidget(this);

    this->mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    this->createProbabilityControls();
    this->createRulesControls();
    this->createButtons();
    
    // TO DO: auto resize
    this->resize(200, 150);
    setWindowTitle(tr("Config Dialog"));
}

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

void ConfigDialog :: createButtons()
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