#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <cmath>
#include "utils.h"

class Parser
{
public:
    Parser(const std::string& _userInputExpression);
    void convertToPolishExpression();
    double calculate(double valueX);

    std::string getExpressionPolishNotation() const;

private:
    std::string userInputExpression;
    std::string expressionPolishNotation;
    std::stack<char> operators;
    std::stack<double> operands;
    std::string symbolsNumber;

    int getPriorityOperator(char symbol);
    void checkAndAddDigits(char symbol);
    void addDigitToExpression(size_t currentPosition, char symbol);
    void addBracketToExpression(char symbol);
    void addOperatorToExpression(char symbol);
    void addVariableToExpression();
    void addDecimalSeparatorToExpression();
    void addMathSymbolToExpression(char symbol);
    void addOperatorsFromStackToExpression();
    void addDigitToOperands(char symbol);
    void addValueVariableToOperands(double valueX);
    void calculateIntermediateResults(char symbolOperator);
    double calculateOperandsWithOperator(double leftOperand, double rightOperand, char symbolOperator);
    double getResultExpression();
    bool isDecimalSeparator(char symbol);
};

#endif // PARSER_H
