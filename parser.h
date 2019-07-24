#ifndef PARSER_H
#define PARSER_H

#include <cmath>
#include "utils.h"
#include <qchar.h>
#include <qstack.h>
#include <qstring.h>

class Parser
{
public:
    Parser();
    Parser(const QString& _userInputExpression);
    void convertToPolishExpression();
    double calculate(double valueX);

    QString getExpressionPolishNotation() const;

    void setUserInputExpression(const QString& value);

private:
    QString userInputExpression;
    QString expressionPolishNotation;
    QStack<QChar> operators;
    QStack<double> operands;
    QString symbolsNumber;

    int getPriorityOperator(QChar symbol);
    void checkAndAddDigits(QChar symbol);
    void addDigitToExpression(size_t currentPosition, QChar symbol);
    void addBracketToExpression(QChar symbol);
    void addOperatorToExpression(QChar symbol);
    void addVariableToExpression();
    void addDecimalSeparatorToExpression();
    void addMathSymbolToExpression(QChar symbol);
    void addOperatorsFromStackToExpression();
    void addDigitToOperands(QChar symbol);
    void addValueVariableToOperands(double valueX);
    void calculateIntermediateResults(QChar symbolOperator);
    double calculateOperandsWithOperator(double leftOperand, double rightOperand, QChar symbolOperator);
    double getResultExpression();
    bool isDecimalSeparator(QChar symbol);
};

#endif // PARSER_H
