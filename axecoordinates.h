#ifndef AXECOORDINATES_H
#define AXECOORDINATES_H

#include <QPainter>
#include "settings.h"
//#include "scaleaxewidget.h"

class AxeCoordinates
{
public:
    AxeCoordinates(Orientation _orientation);
    void draw(QPainter& painter, double lengthAxe, double _interavGrid);

private:
    Orientation orientation;
    QPointF startAxePoint;
    QPointF endAxePoint;

    void drawGrid(QPainter& painter, double intervalGrid);
    void setStartAndEndPoints(double lengthAxeWithMoving);
};

#endif // AXECOORDINATES_H
