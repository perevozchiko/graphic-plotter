#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QValidator>

class Validator : public QValidator
{
    Q_OBJECT
public:
    Validator(QObject *parent = nullptr);
    State validate(QString& expression, int& pos) const override;

private:
    QString expression;
};

#endif // VALIDATOR_H
