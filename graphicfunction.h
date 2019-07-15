#ifndef GRAPHICFUNCTION_H
#define GRAPHICFUNCTION_H

#include <QPointF>
#include <string>
#include <stack>
#include <cmath>
#include <QDebug>
#include <QPainter>

#include "utils.h"
#include "parser.h"
#include "settings.h"
#include "QPolygon"

class GraphicFunction
{
public:
    GraphicFunction();

    void draw(QPainter& painter);

    void scale(const double ratioX, const double ratioY);

    QColor getColor() const;
    void setColor(const QColor& value);

    QString getInputUserExpression() const;
    void setInputUserExpression(const QString& value);

private:
    QString inputUserExpression;
    QVector<QPointF> points;
    double lastScaleRatioX{1};
    double lastScaleRatioY{1};
    void calculatePoints(Parser expression);
    QColor color{Qt::black};
};

#endif // GRAPHICFUNCTION_H
