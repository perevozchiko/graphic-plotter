#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSize>
#include <QString>

enum class Orientation
{
    vertical,
    horizontal
};

// максимальные значения в окне графика
struct MaxValues
{
    double negativeValueY{-10};
    double pozitiveValueY {10};
    double negativeValueX{-10};
    double pozitiveValueX{10};
};

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
const QString familyFont = "Consolas";
const double widthPenBorderScaleWidget = 1;
const int lengthRisks = 7;
const int defaultInterval = 50;
const int intervalForAppearNotch = 80;
const int intervalForDisappearNotch = 40;
const int maxIntervalNotch = 300;
const double valueChangeScale = 1;
const double maxScaleCoordinate = 10000;
const double minCoordinate = 0.01;

// Graphs
const double widthPenBorderGraphWidget = 1.5;

// GraphicFunction
const int numberOfPointsDefault = 401;
const double widthPenGraphic = 2.5;
const double infinity = std::numeric_limits<int>::max();
const int defaultScaleGraphic = 50;
const double stepDefault = 1;


#endif // SETTINGS_H
