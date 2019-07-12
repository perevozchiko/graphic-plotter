#include "graphicfunction.h"
#include <QVector2D>
#include <QtMath>


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
        valueXPosititve = i/100.0;
        valueYOfPositiveX = expression.calculate(valueXPosititve);
        valueXNegatitve = -i/100.0;
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
    pointsPositiveX.insert(pointsPositiveX.begin(), pointsNegativeX[1]);
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



double calcCrossProduct(const QVector2D& v1, const QVector2D& v2)
{
    return (v1.x() * v2.y() - v1.y() * v2.x());
}


void calcBezierPoints(const QPointF& src1, const QPointF& src2, const QPointF& src3, const QPointF& src4,
                      QPointF& c1, QPointF& c2)
{
    const QPointF p1 = (src2 == src1) ? src2 - (src3 - src2) : src1;
    Q_ASSERT(src2 != src3);
    const QPointF p2 = src2;
    const QPointF p3 = src3;
    const QPointF p4 = (src4 == src3) ? src3 + (src3 - src2) : src4;

    const QVector2D v1(p2 - p1);
    const QVector2D v2(p3 - p2);
    const QVector2D v3(p4 - p3);

    const double angleV1V2 = qAcos(qMin(qMax((double) QVector2D::dotProduct(v1, v2) / v1.length() / v2.length(), -1.0), 1.0)) / 2.0;
    const double angleV2V3 = qAcos(qMin(qMax((double) QVector2D::dotProduct(v2, v3) / v2.length() / v3.length(), -1.0), 1.0)) / 2.0;

    const double heightCoef = 0.4;

    const double height1 = qTan(angleV1V2) * heightCoef * v2.length();
    const QVector2D h1 = QVector2D(-v2.y(), v2.x()).normalized() * height1;
    double sign1 = calcCrossProduct(v2, QVector2D(p1 - p2)) > 0 ? -1.0 : 1.0;
    c1 = QPointF(p2 + v2.toPointF() * heightCoef + sign1 * h1.toPointF());

    const double height2 = qTan(angleV2V3) * heightCoef * v2.length();
    const QVector2D h2 = QVector2D(-v2.y(), v2.x()).normalized() * height2;
    double sign2 = calcCrossProduct(v2, QVector2D(p4 - p2)) > 0 ? -1.0 : 1.0;
    c2 = QPointF(p2 + v2.toPointF() * (1 - heightCoef) + sign2 * h2.toPointF());
}


void GraphicFunction::draw(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(color, widthPenGraphic, Qt::SolidLine, Qt::RoundCap));
    painter.setRenderHint(QPainter::Antialiasing, true);

    QVector<QPointF> pointsQVectorPositiveX = QVector<QPointF>::fromStdVector(pointsPositiveX);
    QVector<QPointF> pointsQVectorNegativeX = QVector<QPointF>::fromStdVector(pointsNegativeX);

    QPainterPath path;
    path.moveTo(pointsQVectorPositiveX[1]);
    for (int j = 0; j < pointsQVectorPositiveX.count() - 3; j++)
    {
        QPointF c1, c2;
        calcBezierPoints(pointsQVectorPositiveX.at(j), pointsQVectorPositiveX.at(j + 1), pointsQVectorPositiveX.at(j + 2), pointsQVectorPositiveX.at(j + 3), c1, c2);
        path.cubicTo(c1, c2, pointsQVectorPositiveX.at(j + 2));
    }
    painter.drawPath(path);


    //painter.drawPolyline(QPolygonF(pointsQVectorPositiveX));
    //painter.drawPolyline(QPolygonF(pointsQVectorNegativeX));
    painter.restore();
}






