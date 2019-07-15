#include "graphicfunction.h"
#include <QVector2D>
#include <QtMath>


GraphicFunction::GraphicFunction()
{

}

void GraphicFunction::calculatePoints(Parser expression)
{
    double valueX = 0;
    double valueY = 0;

    points.clear();
    for (int i = 0; i < numberOfPoints; i++)
    {
        valueX = (i - numberOfPoints/2) * step; // точки от -numberOfPoints/2 до (numberOfPoints/2)
        valueY = expression.calculate(valueX);

        //Решить проблему с плюс и минус бесконечность, при увел. массштаба минус бесконечность превращается в ноль
        if (std::isinf(valueY))
        {
//            if (valueY > 0)
//            {
//                valueY =  2e9;
//            }
//            else
//            {
//                valueY =  -2e9;
//            }
            //points.push_back(QPointF(valueX, -valueY));
        }

        points.push_back(QPointF(valueX, valueY));
    }
    // points.insert(points.begin(), pointsNegativeX[1]);
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
    for (int i = 0; i < numberOfPoints; i++)
    {
        points[i].setX(points[i].x() * ratioX / lastScaleRatioX);
        points[i].setY(points[i].y() * ratioY / lastScaleRatioY);
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

    QPainterPath path;
    QPainterPath pathAfterGap;
    path.moveTo(points[0]);
    bool gap = false;
    for (int j = 0; j < points.count() - 3; j++)
    {
        QPointF c1, c2;
        calcBezierPoints(points.at(j), points.at(j + 1), points.at(j + 2), points.at(j + 3), c1, c2);
        if (j && std::isinf(points.at(j).y()))
        {
            gap = true;
            pathAfterGap.moveTo(points.at(j+1).x(), points.at(j+1).y());
        }

        if (!gap)
        {
            path.cubicTo(c1, c2, points.at(j + 2));
        }
        else
        {
            pathAfterGap.cubicTo(c1, c2, points.at(j + 2));
        }
    }
    painter.drawPath(path);
    if (gap)
    {
        painter.drawPath(pathAfterGap);
    }
    painter.restore();
}






