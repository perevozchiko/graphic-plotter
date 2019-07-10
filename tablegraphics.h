#ifndef TABLEGRAPHICS_H
#define TABLEGRAPHICS_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <graphicfunction.h>
#include <vector>
#include "utils.h"


class TableGraphics : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableGraphics();

public slots:
    void insertNewRow();
   void selectWrongCell();

private:
    QStringList headersColumns;

};

#endif // TABLEGRAPHICS_H
