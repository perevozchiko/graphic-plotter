#include "tablegraphics.h"
#include "QHBoxLayout"
#include <QtDebug>
#include <QPainter>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPaintEngine>

TableGraphics::TableGraphics() :
    QTableWidget(0, 2)
{
    headersColumns << "" << "Функция";
    setHorizontalHeaderLabels(headersColumns);
    QHeaderView* header = horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Fixed);
    header->resizeSection(0, 35);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    setMinimumSize(QSize(200, 0));

    // создание пустой строки
    insertNewRow();
}

void TableGraphics::insertNewRow()
{
    insertRow(rowCount());
    auto cellColorGraphic = new QTableWidgetItem();
    auto cellExpression = new QTableWidgetItem( );
    Qt::GlobalColor color = getColor(rowCount()-1);
    cellColorGraphic->setBackground(QColor(color));
    cellColorGraphic->setFlags(Qt::NoItemFlags);
    cellExpression->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
    setItem(rowCount()-1, 0, cellColorGraphic);
    setItem(rowCount()-1, 1, cellExpression);
    openPersistentEditor(cellExpression);
    setCurrentItem(cellExpression);
}

void TableGraphics::selectWrongCell()
{
    auto wrongItem = item(rowCount()-1, 1);
    //wrongItem->setBackground(QColor(255, 224, 212));
    wrongItem->setForeground(Qt::red);
}

