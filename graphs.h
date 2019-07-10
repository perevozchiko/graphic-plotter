#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>
#include <QPainter>
#include "axecoordinates.h"
#include "graphicfunction.h"
#include "scaleaxewidget.h"
#include <vector>
#include <QTableWidgetItem>
#include "utility"
#include "validator.h"
#include <QValidator>

class Graphs : public QWidget
{
    Q_OBJECT
public:
    explicit Graphs(QWidget *parent = nullptr);

signals:
    void scaleGraphic(double);
    void setDefaultScale();
    void moveCenterCoordinate(QPoint);
    void insertNewRow();
    void setInvalidItem();

public slots:
    void getUserInputExpression(const QString&);
    void zoomInGridY(double);
    void zoomOutGridY(double);
    void zoomInGridX(double);
    void zoomOutGridX(double);
    void zoomGraphicY(double);
    void zoomGraphicX(double);
    void setDefaultScaleY();
    void setDefaultScaleX();
    void setInputExpression(QTableWidgetItem*);

private:
    std::vector <QSharedPointer<GraphicFunction>> graphics;
    AxeCoordinates horizontalAxe;
    AxeCoordinates verticalAxe;
    QString expression;
    double scaleGraphicY{50};
    double scaleGraphicX{50};
    double intervalGridY{defaultInterval};
    double intervalGridX{defaultInterval};
    QPoint deltaMoving;
    int movingX{0};
    int movingY{0};
    int lastMousePosY{0};
    int lastMousePosX{0};

    void moveCenter(QPainter& painter);
    void setMovingCoordinate(QPoint point);
    void recountPointsGraphics();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // GRAPHS_H
