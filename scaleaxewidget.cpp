#include <QLabel>
#include <QBoxLayout>
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QMouseEvent>

#include "scaleaxewidget.h"
#include "settings.h"

ScaleAxeWidget::ScaleAxeWidget(QWidget *parent) :
    QWidget(parent),
    font(QFont(familyFont, heightFontMarks)),
    fontMetrics(font),
    currentIntervalNotch(defaultInterval),
    lastMousePosY(0),
    lastMousePosX(0)
{

}

void ScaleAxeWidget::scaleGraphicWithWheels(double value)
{
    changeScale(-value);
    update();
}

void ScaleAxeWidget::setDefaultScale()
{
    setDefaultValuesScale();
    update();
}

void ScaleAxeWidget::setMovingCenter(QPoint movingPoint)
{
    movingX += movingPoint.x();
    movingY += -movingPoint.y();
    update();
}

void ScaleAxeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    setOrientation();
    QImage scaleAxe(size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter;
    painter.begin(&scaleAxe);
    painter.eraseRect(0, 0, width(), height());
    painter.setPen(QPen(Qt::black, widthPenBorderScaleWidget));
    painter.drawRect(0, 0, width(), height());

    transferCenter(painter);
    drawNotch(painter);
    painter.end();

    painter.begin(this);
    painter.drawImage(0, 0, scaleAxe);
    painter.end();
}

void ScaleAxeWidget::drawNotch(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 1));

    if (currentIntervalNotch > intervalForAppearNotch && currentScaleCoordinate > minCoordinate)
    {
        currentIntervalNotch /= 2;
        currentScaleCoordinate /= 2;
    }
    if (currentIntervalNotch < intervalForDisappearNotch && currentScaleCoordinate < maxScaleCoordinate)
    {
        currentIntervalNotch *= 2;
        currentScaleCoordinate *= 2;
    }

    if (orientation == Orientation::vertical)
    {
        drawVerticalNotch(painter);
    }
    else
    {
        drawHorizontalNotch(painter);
    }

}

void ScaleAxeWidget::drawVerticalNotch(QPainter& painter)
{
    int numNotch = static_cast<int>(ceil((height()/2 + qAbs(movingY))/currentIntervalNotch));
    for (int i = -numNotch+1; i < numNotch; i++)
    {
        QString numberString;
        numberString = QString::number(round(-i * currentScaleCoordinate * 1000)/1000);

        painter.drawLine(QPointF(0, i * currentIntervalNotch),
                         QPointF(lengthRisks, i * currentIntervalNotch));

        int yValue = static_cast<int>(i * currentIntervalNotch + fontMetrics.height()/2); // центрирование значение координаты относительно риски
        painter.drawText(15, yValue, numberString);
    }
}

void ScaleAxeWidget::drawHorizontalNotch(QPainter& painter)
{
    int numNotch = static_cast<int>(ceil((width()/2 + qAbs(movingX))/currentIntervalNotch));
    for (int i = -numNotch+1; i < numNotch; i++)
    {
        QString numberString;
        numberString = QString::number(round(i * currentScaleCoordinate * 100)/100);

        painter.drawLine(QPointF(i * currentIntervalNotch, 0),
                         QPointF((i * currentIntervalNotch), lengthRisks));

        int xValue = static_cast<int>(i * currentIntervalNotch - fontMetrics.width(numberString)/2); // центрирование значение координаты относительно риски
        painter.drawText(xValue, 20, numberString);
    }
}

void ScaleAxeWidget::setOrientation()
{
    orientation = Orientation::vertical;
    widthArea = width();
    heightArea = height();
    if (width() > height())
    {
        orientation = Orientation::horizontal;
        widthArea = height();
        heightArea = width();
    }
}

void ScaleAxeWidget::transferCenter(QPainter &painter)
{    
    int centerWidth = heightArea/2 + movingX;
    int centerHeight = heightArea/2 + movingY;

    if(orientation == Orientation::horizontal)
    {
        centerHeight = 0;
    }
    else
    {
        centerWidth = 0;
    }

    painter.translate(centerWidth, centerHeight);
}

void ScaleAxeWidget::setDefaultValuesScale()
{
    currentIntervalNotch = defaultInterval;// установка зума по умолчанию
    currentScaleCoordinate = 1;
    if (orientation == Orientation::vertical)
    {
        movingY = 0;
    }
    else
    {
        movingX = 0;
    }
    emit setDefaultScaleY();
    emit setDefaultScaleX();
    update();
}

void ScaleAxeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setDefaultValuesScale();
}

void ScaleAxeWidget::scaleGraphic()
{
    emit scaleGraphicY(currentScaleCoordinate);
    emit scaleGraphicX(currentScaleCoordinate);
}

void ScaleAxeWidget::changeScale(double delta)
{
    if (delta > 0 && currentScaleCoordinate <= maxScaleCoordinate)
    {
        currentIntervalNotch -= valueChangeScale;
        emit moveDown(currentIntervalNotch);

        scaleGraphic();
    }
    else if (delta < 0 && currentIntervalNotch < maxIntervalNotch)
    {
        currentIntervalNotch += valueChangeScale;
        emit moveUp(currentIntervalNotch);

        scaleGraphic();
    }
}

void ScaleAxeWidget::mouseMoveEvent(QMouseEvent *event)
{

    if (orientation == Orientation::vertical)
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::SizeHorCursor);


    if (event->buttons() == Qt::LeftButton)
    {
        int delta;
        if (orientation == Orientation::vertical)
            delta = event->y() - lastMousePosY;
        else
            delta = event->x() - lastMousePosX;

        changeScale(delta);
        lastMousePosY = event->y();
        lastMousePosX = event->x();
        update();
    }
}
