#ifndef SCALEAXEWIDGET_H
#define SCALEAXEWIDGET_H

#include <QWidget>
#include "settings.h"

class ScaleAxeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScaleAxeWidget(QWidget *parent = nullptr);
    static MaxValues maxValues;

signals:
    void moveUp(double value);
    void moveDown(double value);
    void scaleGraphicY(double value);
    void scaleGraphicX(double value);
    void setDefaultScaleY();
    void setDefaultScaleX();
    void changeStepGraphic();

public slots:
    void scaleGraphicWithWheels(double value);
    void setDefaultScale();
    void setMovingCenter(QPoint movingPoint);

private:

    Orientation orientation;
    int widthArea{0};
    int heightArea{0};
    QFont font;
    QFontMetrics fontMetrics;
    double currentIntervalNotch{0};
    int lastMousePosY;
    int lastMousePosX;
    double currentScaleCoordinate{1};
    int movingX{0};
    int movingY{0};
    QPoint deltaMoving;
    void drawNotch(QPainter& painter);
    void drawVerticalNotch(QPainter& painter);
    void drawHorizontalNotch(QPainter& painter);
    void transferCenter(QPainter& painter);
    void setOrientation();
    void scaleGraphic();
    void changeScale(double delta);
    void setDefaultValuesScale();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // SCALEAXEWIDGET_H
