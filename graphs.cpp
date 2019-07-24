#include <QDebug>
#include <cmath>
#include <QWheelEvent>
#include <QPoint>

#include "graphs.h"
#include "settings.h"

Graphs::Graphs(QWidget *parent) :
    QWidget(parent),
    horizontalAxe(Orientation::horizontal),
    verticalAxe(Orientation::vertical)
{    
}

void Graphs::getUserInputExpression(const QString& inputExpression)
{
    expression = inputExpression; // добавить проверки
}


void Graphs::zoomInGridY(double intervalNotch)
{
    intervalGridY = intervalNotch;
    update();
}

void Graphs::zoomOutGridY(double intervalNotch)
{
    intervalGridY = intervalNotch;
    update();
}

void Graphs::zoomInGridX(double intervalNotch)
{
    intervalGridX = intervalNotch;
    update();
}

void Graphs::zoomOutGridX(double intervalNotch)
{
    intervalGridX = intervalNotch;
    update();
}

void Graphs::zoomGraphicY(double intervalCoordinate)
{
    scaleGraphicY = intervalGridY / intervalCoordinate;
    recountPointsGraphics();
}

void Graphs::zoomGraphicX(double intervalCoordinate)
{
    scaleGraphicX = intervalGridX / intervalCoordinate;
    recountPointsGraphics();
}


void Graphs::setDefaultScaleY()
{
    intervalGridY = defaultInterval;
    scaleGraphicY = defaultScaleGraphic;
    recountPointsGraphics();
    movingY = 0;
    update();
}

void Graphs::setDefaultScaleX()
{
    intervalGridX = defaultInterval;
    scaleGraphicX = defaultScaleGraphic;
    recountPointsGraphics();
    movingX = 0;
    update();
}

void Graphs::setInputExpression(QTableWidgetItem* currentCell)
{
    if (currentCell->column() == 1)
    {
        QTableWidget* tableWidget = qobject_cast<QTableWidget*> (sender());
        QString newExpression = currentCell->text();
        int totalRows = tableWidget->rowCount();
        int currentRow = currentCell->row();
        int idRow = currentCell->data(Qt::UserRole).toInt();

        // если текущая строка - последняя строчка таблицы и не пустая то создаем новый график функции
        if(currentRow == totalRows-1 && !currentCell->text().isEmpty())
        {
            GraphicData graphicData;
            graphicData.numRow = currentRow;
            graphicData.expression = newExpression;
            graphicData.graphicFunction.setInputUserExpression(newExpression);
            graphicData.graphicFunction.setColor(getColor(idRow));
            graphics.insert(idRow, graphicData);

            // создаем после этой строки пустую строку в таблице
            emit insertNewRow();
        }
        // или редактируем старое выражение
        else if (graphics.contains(idRow))
        {
            auto& currentGraphic = graphics[idRow];
            QString oldExpression = currentGraphic.expression;

            if (oldExpression != newExpression)
            {
                currentGraphic.graphicFunction.setInputUserExpression(newExpression);
                currentGraphic.expression = newExpression;
            }
        }
    }

    update();
}

void Graphs::deleteGraphic(int idRow)
{
    graphics.remove(idRow);
    update();
}

void Graphs::moveCenter(QPainter &painter)
{
    movingX += deltaMoving.x();
    movingY += -deltaMoving.y();
    painter.translate(width()/2 + movingX, height()/2 + movingY);
    painter.scale(1.0, -1.0);
    deltaMoving = QPoint(0, 0);
}

void Graphs::recountPointsGraphics()
{
    for (auto& graphic : graphics)
    {
        if (!graphic.graphicFunction.getInputUserExpression().isEmpty())
        {
            graphic.graphicFunction.scale(scaleGraphicX, scaleGraphicY);
        }
    }
}

void Graphs::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter;
    painter.begin(this);
    painter.eraseRect(0, 0, width(), height());
    painter.setPen(QPen(Qt::black, widthPenBorderGraphWidget));
    painter.drawRect(0, 0, width(), height());
    moveCenter(painter);

    horizontalAxe.draw(painter, width()/2 + abs(movingX) + abs(movingY), intervalGridY);
    verticalAxe.draw(painter, height()/2 + abs(movingY) + abs(movingX), intervalGridX);

    if(!graphics.empty())
    {
        recountPointsGraphics();
        for (auto& graphic : graphics)
        {
            if (!graphic.graphicFunction.getInputUserExpression().isEmpty())
            {
                graphic.graphicFunction.draw(painter);
            }
        }
    }

    painter.end();
}

void Graphs::wheelEvent(QWheelEvent *event)
{
    QPoint angle = event->angleDelta();

    emit scaleGraphic(angle.y());
    event->accept();
}

void Graphs::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit setDefaultScale();
    movingX = 0;
    movingY = 0;
    deltaMoving = QPoint(0, 0);
    update();
}

void Graphs::mousePressEvent(QMouseEvent* event)
{
    lastMousePosX = event->x();
    lastMousePosY = -event->y();
    event->accept();
}

void Graphs::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        deltaMoving.setX(event->x() - lastMousePosX);
        deltaMoving.setY(-event->y() - lastMousePosY);
        lastMousePosX = event->x();
        lastMousePosY = -event->y();
        emit moveCenterCoordinate(deltaMoving);
        event->accept();
        update();
    }
}
