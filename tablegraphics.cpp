#include "tablegraphics.h"
#include "QHBoxLayout"
#include <QtDebug>
#include <QPainter>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPaintEngine>
#include <QPushButton>

TableGraphics::TableGraphics() :
    QTableWidget(0, 3)
{
    headersColumns << "" << "Функция" << "";
    setHorizontalHeaderLabels(headersColumns);
    QHeaderView* header = horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Fixed);
    header->resizeSection(0, 35);
    header->resizeSection(2, 35);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    setMinimumSize(QSize(200, 0));

    // создание пустой строки
    insertNewRow();
}

void TableGraphics::insertNewRow()
{
    insertRow(rowCount());
    auto cellColorGraphic = new QTableWidgetItem();
    auto cellExpression = new QTableWidgetItem();
    auto buttonWidget = new QWidget;
    auto buttonDelete = new QPushButton;
    auto buttonLayout = new QHBoxLayout(buttonWidget);

    Qt::GlobalColor color = getColor(rowCount()-1);
    cellColorGraphic->setBackground(QColor(color));
    cellColorGraphic->setFlags(Qt::NoItemFlags);
    cellExpression->setFlags(Qt::ItemIsEnabled);

    buttonDelete->setIcon(QIcon("del.jpeg"));
    buttonLayout->addWidget(buttonDelete);
    buttonLayout->setContentsMargins(3,3,3,3);
    buttonWidget->setLayout(buttonLayout);

    setItem(rowCount()-1, 0, cellColorGraphic);
    setItem(rowCount()-1, 1, cellExpression);
    setCellWidget(rowCount()-1, 2, buttonWidget);

    connect(buttonDelete, &QPushButton::clicked, this, &TableGraphics::deleteRow);

    openPersistentEditor(cellExpression);
    setCurrentItem(cellExpression);
}

void TableGraphics::selectWrongCell()
{
    auto wrongItem = item(rowCount()-1, 1);
    wrongItem->setForeground(Qt::red);
}

void TableGraphics::deleteRow()
{
    QWidget* cellWidget = qobject_cast<QWidget*> (sender()->parent());
    if (cellWidget)
    {
        int indexRow = indexAt(cellWidget->pos()).row();
        QString expression = item(indexRow, 1)->text();
        emit deleteGraphic(expression);
        removeRow(indexRow);

        if(rowCount() < 1)
        {
            insertNewRow();
        }
        //setCurrentCell(indexRow, 1);
    }
}


