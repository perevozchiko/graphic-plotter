#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QWindow>
#include <QApplication>
#include "graphs.h"
#include <QTranslator>
#include "scaleaxewidget.h"
#include "settings.h"
#include "tablegraphics.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
private:

};

#endif // MAINWINDOW_H
