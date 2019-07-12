#include "graphicfunction.h"

GraphicFunction::GraphicFunction()
{

}

void GraphicFunction::calculatePoints(Parser expression)
{
    double valueXPosititve = 0;
    double valueXNegatitve = 0;
    double valueYOfPositiveX = 0;
    double valueYOfNegativeX = 0;
    pointsNegativeX.clear();
    pointsPositiveX.clear();
    for (int i = 0; i < numberOfPoints/2; i++)
    {
        valueXPosititve = i;
        valueYOfPositiveX = expression.calculate(valueXPosititve);
        valueXNegatitve = -i;
        valueYOfNegativeX = expression.calculate(valueXNegatitve);

        // Решить проблему с плюс и минус бесконечность, при увел. массштаба минус бесконечность превращается в ноль
        if (std::isinf(valueYOfPositiveX))
        {
            valueYOfPositiveX =  2e9;
        }
        if (std::isinf(valueYOfNegativeX))
        {
            valueYOfNegativeX =  -2e9;
        }

        pointsPositiveX.push_back(QPointF(valueXPosititve, valueYOfPositiveX));
        pointsNegativeX.push_back(QPointF(valueXNegatitve, valueYOfNegativeX));
    }
}

QColor GraphicFunction::getColor() const
{
    return color;
}

void GraphicFunction::setColor(const QColor& value)
{
    color = value;
}

QString GraphicFunction::getInputUserExpression() const
{
    return inputUserExpression;
}

void GraphicFunction::setInputUserExpression(const QString& value)
{
    inputUserExpression = value;
    Parser expression(inputUserExpression);

    expression.convertToPolishExpression();
    calculatePoints(expression);

    lastScaleRatioX = 1;
    lastScaleRatioY = 1;

}

void GraphicFunction::scale(const double ratioX, const double ratioY)
{
    for (int i = 0; i < numberOfPoints/2; i++)
    {
        pointsPositiveX[i].setX(pointsPositiveX[i].x() * ratioX / lastScaleRatioX);
        pointsPositiveX[i].setY(pointsPositiveX[i].y() * ratioY / lastScaleRatioY);
        pointsNegativeX[i].setX(pointsNegativeX[i].x() * ratioX / lastScaleRatioX);
        pointsNegativeX[i].setY(pointsNegativeX[i].y() * ratioY / lastScaleRatioY);
    }
    lastScaleRatioX = ratioX;
    lastScaleRatioY = ratioY;
}


void GraphicFunction::draw(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(color, widthPenGraphic, Qt::SolidLine, Qt::RoundCap));
    painter.setRenderHint(QPainter::Antialiasing, true);

    QVector<QPointF> pointsQVectorPositiveX = QVector<QPointF>::fromStdVector(pointsPositiveX);
    QVector<QPointF> pointsQVectorNegativeX = QVector<QPointF>::fromStdVector(pointsNegativeX);
    painter.drawPolyline(QPolygonF(pointsQVectorPositiveX));
    painter.drawPolyline(QPolygonF(pointsQVectorNegativeX));
    painter.restore();
}
