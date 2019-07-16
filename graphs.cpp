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
        //проверка валидности выражения
        Validator checker;
        int pos = 0;
        QString expression = currentCell->text();
        QValidator::State stateValidate = checker.validate(expression, pos);

        QTableWidget* tableWidget = qobject_cast<QTableWidget*> (sender());
        int numRows = tableWidget->rowCount();

        if(currentCell->row() == numRows-1 && !currentCell->text().isEmpty())
        {
            expressions.insert(currentCell->row()-1, expression);
            auto graphic = QSharedPointer<GraphicFunction>::create();
            graphic->setInputUserExpression(expression);
            graphic->setColor(getColor(currentCell->row()));
            graphicsMap.insert(expression, graphic);
            emit insertNewRow();
        }
        else
        {
            QString prevExpression = expressions[currentCell->row()-1];
            if (prevExpression != expression)
            {
                auto prevGraphicQShared = graphicsMap.take(prevExpression);
                GraphicFunction prevGraphic = *prevGraphicQShared.get();
                prevGraphic.setInputUserExpression(expression);
                QSharedPointer<GraphicFunction> graph (&prevGraphic);
                graphicsMap.insert(expression, graph);
                expressions.insert(currentCell->row(), expression);
            }
        }

    }
    update();
}

void Graphs::deleteGraphic(QString expression)
{
    graphicsMap.remove(expression);
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
    for (auto graphic : graphicsMap)
    {
        if (!graphic->getInputUserExpression().isEmpty())
        {
            graphic->scale(scaleGraphicX, scaleGraphicY);
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

    if(!graphicsMap.empty())
    {
        recountPointsGraphics();
        for (const auto graphic : graphicsMap)
        {
            if (!graphic->getInputUserExpression().isEmpty())
            {
                graphic->draw(painter);
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
