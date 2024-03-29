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
#include <QMap>

class Graphs : public QWidget
{
    Q_OBJECT
public:
    explicit Graphs(QWidget *parent = nullptr);
    struct GraphicData
    {
        int numRow{0};
        QString expression;
        GraphicFunction function;
    };

signals:
    void scaleGraphic(double value);
    void setDefaultScale();
    void moveCenterCoordinate(QPoint value);
    void insertNewRow();
    void setInvalidItem();

public slots:
    void getUserInputExpression(const QString& inputExpression);
    void zoomInGridY(double intervalNotch);
    void zoomOutGridY(double intervalNotch);
    void zoomInGridX(double intervalNotch);
    void zoomOutGridX(double intervalNotch);
    void zoomGraphicY(double intervalCoordinate);
    void zoomGraphicX(double intervalCoordinate);
    void setDefaultScaleY();
    void setDefaultScaleX();
    void setInputExpression(QTableWidgetItem* currentCell);
    void deleteGraphic(int idRow);
    void reCalcPointsGraphic();

private:
    QMap <int, GraphicData> graphics;
    AxeCoordinates horizontalAxe;
    AxeCoordinates verticalAxe;
    QString expression;
    double scaleGraphicY{defaultInterval};
    double scaleGraphicX{defaultInterval};
    double intervalGridY{defaultInterval};
    double intervalGridX{defaultInterval};
    QPoint deltaMoving;
    int movingX{0};
    int movingY{0};
    int lastMousePosY{0};
    int lastMousePosX{0};

    void moveCenter(QPainter& painter);
    void setMovingCoordinate(QPoint point);
    void reCalcScaleGraphics();

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // GRAPHS_H
