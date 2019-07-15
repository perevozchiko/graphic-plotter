#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    auto graphs = new Graphs;
    graphs->setMinimumSize(800, 800);
    auto scaleVerticalWidget = new ScaleAxeWidget;
    scaleVerticalWidget->setMinimumSize(lengthScaleArea, graphs->height());
    auto scaleHorizontalWidget = new ScaleAxeWidget;
    scaleHorizontalWidget->setMinimumSize(graphs->width(), lengthScaleArea);

    auto tableGraphics = new TableGraphics;

    connect(graphs, &Graphs::insertNewRow, tableGraphics, &TableGraphics::insertNewRow);
    connect(tableGraphics, &TableGraphics::itemChanged, graphs, &Graphs::setInputExpression);
    connect(graphs, &Graphs::setInvalidItem, tableGraphics, &TableGraphics::selectWrongCell);

    connect(tableGraphics, &TableGraphics::deleteGraphic, graphs, &Graphs::deleteGraphic);

    connect(scaleVerticalWidget, &ScaleAxeWidget::moveUp, graphs, &Graphs::zoomInGridY);
    connect(scaleVerticalWidget, &ScaleAxeWidget::moveDown, graphs, &Graphs::zoomOutGridY);
    connect(scaleHorizontalWidget, &ScaleAxeWidget::moveUp, graphs, &Graphs::zoomInGridX);
    connect(scaleHorizontalWidget, &ScaleAxeWidget::moveDown, graphs, &Graphs::zoomOutGridX);

    connect(scaleVerticalWidget, &ScaleAxeWidget::scaleGraphicY, graphs, &Graphs::zoomGraphicY);
    connect(scaleHorizontalWidget, &ScaleAxeWidget::scaleGraphicX, graphs, &Graphs::zoomGraphicX);
    connect(scaleVerticalWidget, &ScaleAxeWidget::setDefaultScaleY, graphs, &Graphs::setDefaultScaleY);
    connect(scaleHorizontalWidget, &ScaleAxeWidget::setDefaultScaleX, graphs, &Graphs::setDefaultScaleX);

    connect(graphs, &Graphs::scaleGraphic, scaleVerticalWidget, &ScaleAxeWidget::scaleGraphicWithWheels);
    connect(graphs, &Graphs::scaleGraphic, scaleHorizontalWidget, &ScaleAxeWidget::scaleGraphicWithWheels);

    connect(graphs, &Graphs::setDefaultScale, scaleVerticalWidget, &ScaleAxeWidget::setDefaultScale);
    connect(graphs, &Graphs::setDefaultScale, scaleHorizontalWidget, &ScaleAxeWidget::setDefaultScale);

    connect(graphs, &Graphs::moveCenterCoordinate, scaleHorizontalWidget, &ScaleAxeWidget::setMovingCenter);
    connect(graphs, &Graphs::moveCenterCoordinate, scaleVerticalWidget, &ScaleAxeWidget::setMovingCenter);

    auto layout = new QHBoxLayout;
    auto layoutMain = new QVBoxLayout;
    auto layoutButtonField = new QHBoxLayout;

    auto graphLayout = new QGridLayout;

    layoutMain->setSpacing(spacingMainWindow);
    layoutMain->setMargin(marginsMainWindow);

    layoutMain->addLayout(layoutButtonField);

    layoutMain->addStretch(1);
    graphLayout->addWidget(graphs, 0, 0);
    graphLayout->addWidget(scaleVerticalWidget, 0, 1);
    graphLayout->addWidget(scaleHorizontalWidget, 1, 0);

    graphLayout->setSpacing(0);
    graphLayout->setMargin(0);
    graphLayout->setColumnStretch(2, 1);

    layoutMain->addLayout(graphLayout);
    layout->addWidget(tableGraphics);
    layout->addLayout(layoutMain);
    setLayout(layout);
}
