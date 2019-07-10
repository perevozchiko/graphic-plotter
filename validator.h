#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QValidator>

class Validator : public QValidator
{
    Q_OBJECT
public:
    Validator(QObject *parent = nullptr);

signals:

public slots:

private:
    QString expression;

public:
    State validate(QString& expression, int& pos) const override;
};

#endif // VALIDATOR_H
