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
//    struct RowData
//    {
//        RowData(int _numRow = 0,
//                Qt::GlobalColor _color = Qt::black,
//                QString _inputExpression = "") :
//            numRow{_numRow},
//            color{_color},
//            inputExpression{_inputExpression}
//        {
//        }

//        int numRow{0};
//        Qt::GlobalColor color{Qt::black};
//        QString inputExpression;
//    };

//    QMap<int, RowData> rowsData;

signals:
    void deleteGraphic(int idRow);

public slots:
    void insertNewRow();
    void selectWrongCell();
    void deleteRow();

private:
    QStringList headersColumns;
    static int idDataRow;

};

#endif // TABLEGRAPHICS_H
