#include "graphicfunction.h"
#include <QVector2D>
#include <QtMath>


GraphicFunction::GraphicFunction()
{

}

void GraphicFunction::calculatePoints()
{
    double valueX = 0;
    double valueY = 0;
    double stepX = qAbs(ScaleAxeWidget::maxValues.negativeValueX - ScaleAxeWidget::maxValues.pozitiveValueX);
    //double stepY = qAbs(ScaleAxeWidget::maxValues.negativeValueY - ScaleAxeWidget::maxValues.pozitiveValueY);
    double stepMinimal = 3 * stepX/numberOfPointsDefault;
    points.clear();
    // qDebug() << stepMinimal << ", " << lastScaleRatioX << ", " << lastScaleRatioY;

    for (int i = 0; i <= numberOfPointsDefault; i++)
    {
        valueX = (i - numberOfPointsDefault/2);

        valueX *= stepMinimal; // точки от -numberOfPoints/2 до (numberOfPoints/2)
        valueY = expressionPolish.calculate(valueX);

        points.push_back(QPointF(valueX * lastScaleRatioX, valueY * lastScaleRatioY));
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

void GraphicFunction::setInputUserExpression(const QString value)
{
    inputUserExpression = value;
    expressionPolish.setUserInputExpression(inputUserExpression);
    expressionPolish.convertToPolishExpression();
    calculatePoints();

//    lastScaleRatioX = 1;
//    lastScaleRatioY = 1;
}

void GraphicFunction::scale(const double ratioX, const double ratioY)
{
    factorX = ratioX / lastScaleRatioX;
    factorY = ratioY / lastScaleRatioY;

    for (int i = 0; i <= points.count()-1; i++)
    {
        points[i].setX(points[i].x() * factorX);
        points[i].setY(points[i].y() * factorY);
    }
    //qDebug() << ratioX/lastScaleRatioX << ", " << ratioY / lastScaleRatioY;

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
            pathAfterGap.moveTo(0, 2e9);
            path.cubicTo(c1, c2, QPoint(0, -2e9));
        }

        if (!gap)
        {

            path.cubicTo(c1, c2, points.at(j + 2));
        }
        else
        {
            pathAfterGap.cubicTo(c1, c2, points.at(j + 2));
        }
       // painter.setPen(QPen(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap));
       // painter.drawPoint(points.at(j+1));
    }
    //painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    if (gap)
    {
        painter.drawPath(pathAfterGap);
    }
    painter.drawPath(path);
    painter.setClipRect(100, 100, 300, 300);
    painter.restore();
   // painter.clipBoundingRect();
}






