#include "tablegraphics.h"
#include "QHBoxLayout"
#include <QtDebug>
#include <QPainter>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPaintEngine>
#include <QPushButton>
#include <QUuid>

int TableGraphics::idDataRow = 0;

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
    idDataRow++;
    auto color = getColor(idDataRow);
    int currentNumRow = rowCount()-1;
    auto cellColorGraphic = new QTableWidgetItem();
    auto cellExpression = new QTableWidgetItem();
    auto buttonWidget = new QWidget;
    auto buttonDelete = new QPushButton;
    auto buttonLayout = new QHBoxLayout(buttonWidget);

    cellExpression->setData(Qt::UserRole, idDataRow);
    cellColorGraphic->setBackground(getColor(idDataRow));
    cellColorGraphic->setFlags(Qt::NoItemFlags);
    cellExpression->setFlags(Qt::ItemIsEnabled);

    buttonDelete->setIcon(QIcon("del.jpeg"));
    buttonLayout->addWidget(buttonDelete);
    buttonLayout->setContentsMargins(3,3,3,3);
    buttonWidget->setLayout(buttonLayout);

    setItem(currentNumRow, 0, cellColorGraphic);
    setItem(currentNumRow, 1, cellExpression);
    setCellWidget(currentNumRow, 2, buttonWidget);

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
        int numberRow = indexAt(cellWidget->pos()).row();
        int idRow = item(numberRow, 1)->data(Qt::UserRole).toInt();
        emit deleteGraphic(idRow);

        if (numberRow != rowCount()-1)
        {
            removeRow(numberRow);
        }

        //setCurrentCell(indexRow, 1);
    }
}


