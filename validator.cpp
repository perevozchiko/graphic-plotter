#include "validator.h"

Validator::Validator(QObject *parent) :
    QValidator(parent)
{

}

QValidator::State Validator::validate(QString& expression, int& pos) const
{

    for (auto symbol : expression)
    {
        if (symbol != QLatin1Char(symbol.cell()))
        {
            return  QValidator::Invalid;
        }
    }

    return  QValidator::Acceptable;
}
