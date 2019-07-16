#ifndef TABLEGRAPHICS_H
#define TABLEGRAPHICS_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <graphicfunction.h>
#include <QVector>
#include "utils.h"
#include <QMap>


class TableGraphics : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableGraphics();

signals:
    void deleteGraphic(QString expression);
public slots:
    void insertNewRow();
    void selectWrongCell();

private slots:
    void deleteRow();


private:
    QStringList headersColumns;

};

#endif // TABLEGRAPHICS_H
