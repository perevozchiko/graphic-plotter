#include <QtWidgets>
#include <QWindow>
#include <QApplication>
#include "graphs.h"
#include <QTranslator>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle(QObject::tr("Графики"));
    window.resize(sizeMainWindow);

    // центрирование главного окна в середине экрана
    QDesktopWidget* desktop = QApplication::desktop();

    int desktopWidth = desktop->width();
    if (desktopWidth > widthFullHD)
    {
        desktopWidth /= 2; // если два моника
    }
    const QSize desktopSize(desktopWidth,desktop->height());
    window.move((desktopSize.width() - window.width()) / 2,
                (desktopSize.height() - window.height()) / 2 - 100);
    window.show();
    return app.exec();
}
