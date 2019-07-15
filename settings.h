#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSize>
#include <QString>

enum class Orientation
{
    vertical,
    horizontal
};

namespace {

// main
const QSize sizeMainWindow(1200, 700);
const int widthFullHD = 1080;
const int spacingMainWindow = 5;
const int marginsMainWindow = 10;


const int widthLinesEdit = 250;
const int lengthScaleArea = 80;

// AxeCoordinate
const double widthPenAxe = 1;
const double widthPenGrid = 0.5;

// ScaleAxeWidget
const int heightFontMarks = 10;
const QString familyFont = "Arial";
const double widthPenBorderScaleWidget = 1;
const int lengthRisks = 7;
const int defaultInterval = 50;//??? возможно не будет использоваться
const int intervalForAppearNotch = 80;
const int intervalForDisappearNotch = 40;
const int maxIntervalNotch = 300;
const double valueChangeScale = 1;
const double maxScaleCoordinate = 10000;
const double minCoordinate = 0.01;

// Graphs
const double widthPenBorderGraphWidget = 1.5;

// GraphicFunction
const int numberOfPoints = 400;
const double widthPenGraphic = 2.5;
const double infinity = std::numeric_limits<int>::max();
const int defaultScaleGraphic = 50;
const double step = 0.1;


}

#endif // SETTINGS_H
