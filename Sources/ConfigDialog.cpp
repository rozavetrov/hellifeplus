#include "../Headers/ConfigDialog.h"

#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


ConfigDialog :: ConfigDialog()
{
    centralWidget = new QWidget(this);

    this->mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    this->createControls();
    this->createButtons();

    setWindowTitle(tr("Config Dialog"));
}

void ConfigDialog :: createControls()
{
    probOfZerosSlider = new QSlider(Qt::Horizontal);
    probOfZerosSlider->setMinimum(2);
    probOfZerosSlider->setMaximum(100);
    probOfZerosSlider->setTickPosition(QSlider::TicksBothSides);
    probOfZerosSlider->setTickInterval(10);
    probOfZerosSlider->setSingleStep(1);

    QObject::connect(probOfZerosSlider, &QSlider::valueChanged, this, &ConfigDialog::setProbabilityOfDeadCells);
    this->mainLayout->addWidget(probOfZerosSlider);
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