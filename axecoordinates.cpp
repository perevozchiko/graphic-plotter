#include "axecoordinates.h"

#include <cmath>
#include <QDebug>

AxeCoordinates::AxeCoordinates(Orientation _orientation) :
    orientation(_orientation)
{ 
}

void AxeCoordinates::draw(QPainter& painter, double centerCoordinate, double _interavGrid)
{
    painter.setPen(QPen(Qt::black, widthPenAxe, Qt::SolidLine, Qt::FlatCap));
    setStartAndEndPoints(centerCoordinate);
    painter.drawLine(startAxePoint, endAxePoint);
    drawGrid(painter, _interavGrid);
}

void AxeCoordinates::drawGrid(QPainter &painter, double intervalGrid)
{
    double lengthAxe = 0;
    if (orientation == Orientation::vertical)
    {
        lengthAxe = qMax(qAbs(endAxePoint.y()), qAbs(startAxePoint.y()));
    }
    else
    {
        lengthAxe = qMax(qAbs(endAxePoint.x()), qAbs(startAxePoint.x()));
    }

    int numsLine = static_cast<int>(ceil(lengthAxe/intervalGrid)); // если ось Y то количество сетки  в зависимость от оси X
    painter.setPen(QPen(Qt::gray, widthPenGrid));
    for (int i = -numsLine; i < numsLine; i++)
    {
        if (orientation == Orientation::horizontal)
        {
            painter.drawLine(QPointF(startAxePoint.x(), i * intervalGrid),
                             QPointF(endAxePoint.x(), i * intervalGrid));
        }
        else
        {
            painter.drawLine(QPointF(i * intervalGrid, startAxePoint.y()),
                             QPointF(i * intervalGrid, endAxePoint.y()));
        }
    }
}

void AxeCoordinates::setStartAndEndPoints(double lengthAxeWithMoving)
{
    double startPointX = 0;
    double startPointY = 0;
    double endPointX = 0;
    double endtPointY = 0;

    if (orientation == Orientation::vertical)
    {
        startPointY = -lengthAxeWithMoving;
        endtPointY = lengthAxeWithMoving;
    }
    if (orientation == Orientation::horizontal)
    {
        startPointX = -lengthAxeWithMoving;
        endPointX = lengthAxeWithMoving;
    }
    startAxePoint = QPointF(startPointX, startPointY);
    endAxePoint = QPointF(endPointX, endtPointY);
}
