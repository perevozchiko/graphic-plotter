#include "parser.h"
#include <cmath>

Parser::Parser(const std::string& _userInputExpression) :
    userInputExpression(_userInputExpression)
{
    removeSpaces(userInputExpression);
}

void Parser::addDigitToExpression(size_t currentPosition, char symbol)
{
    expressionPolishNotation += charToStr(symbol);
    size_t nextPosition = currentPosition + 1;
    if (!std::isdigit(userInputExpression[nextPosition]) && !isDecimalSeparator(userInputExpression[nextPosition]))
    {
        expressionPolishNotation += "#";
    }
}

void Parser::addBracketToExpression(char symbol)
{
    if (symbol == '(')
    {
        operators.push(symbol);
    }
    else
    {
        if (!operators.empty())
        {
            while(operators.top() != '(')
            {
                expressionPolishNotation += charToStr(operators.top());
                operators.pop();
            }
            operators.pop(); // выталкиваем последний оператор
        }
    }
}

void Parser::addOperatorToExpression(char symbol)
{
    if(!operators.empty() && getPriorityOperator(symbol) <= getPriorityOperator(operators.top()))
    {
        while(!operators.empty() && operators.top() != '(')
        {
            expressionPolishNotation += charToStr(operators.top());
            operators.pop();
        }
    }
    operators.push(symbol);
}

void Parser::addVariableToExpression()
{
    expressionPolishNotation += "x";
}

void Parser::addDecimalSeparatorToExpression()
{
    expressionPolishNotation += ".";
}

void Parser::addMathSymbolToExpression(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    {
        addOperatorToExpression(symbol);
        break;
    }
    case '(':
    case ')':
    {
        addBracketToExpression(symbol);
        break;
    }
    case '.':
    case ',':
    {
        addDecimalSeparatorToExpression();
        break;
    }
    case 'x':
    case 'X':
    {
        addVariableToExpression();
        break;
    }
    }
}

void Parser::addOperatorsFromStackToExpression()
{
    while(!operators.empty())
    {
        expressionPolishNotation += charToStr(operators.top());
        operators.pop();
    }
}

void Parser::convertToPolishExpression()
{
    size_t size = userInputExpression.size();

    for (size_t currentPosition = 0; currentPosition < size; ++currentPosition)
    {
        char symbol = userInputExpression[currentPosition];

        if (std::isdigit(symbol))
        {
            addDigitToExpression(currentPosition, symbol);
        }
        else
        {
            addMathSymbolToExpression(symbol);
        }
    }

    // перекидываем из стэка в выражение оставшиеся операторы, при их наличии
    addOperatorsFromStackToExpression();
}

void Parser::addDigitToOperands(char symbol)
{
    if(std::isdigit(symbol) || symbol == '.')
    {
        symbolsNumber += symbol;
    }

    if (symbol == '#')
    {
        double operand = std::atof(symbolsNumber.c_str());
        operands.push(operand);
        symbolsNumber = "";
    }
}

void Parser::addValueVariableToOperands(double valueX)
{
    operands.push(valueX);
}

double Parser::calculateOperandsWithOperator(double leftOperand, double rightOperand, char symbolOperator)
{
    switch (symbolOperator)
    {
    case '+':
        return leftOperand + rightOperand;
    case '-':
        return leftOperand - rightOperand;
    case '*':
        return leftOperand * rightOperand;
    case '/':
        if (rightOperand != 0)
        {
            return leftOperand / rightOperand;
        }
        else
        {
            return std::numeric_limits<double>::infinity();
        }
    case '^':
        return std::pow(leftOperand, rightOperand);
    default:
        return 0; // вызов исключения
    }
}

void Parser::calculateIntermediateResults(char symbolOperator)
{
    double leftOperand = 0;
    double rightOperand = popAndTop(operands);

    // для работы с отрицательными числами ("-5" будет "0-5")
    if(!operands.empty())
    {
        leftOperand = popAndTop(operands);
    }
    else
    {
        leftOperand = 0;
    }

    double intermediateResult = calculateOperandsWithOperator(leftOperand, rightOperand, symbolOperator);

    operands.push(intermediateResult);
}

double Parser::getResultExpression()
{
    if(!operands.empty())
    {
        double resultExpression = operands.top();
        operands.pop();
        return resultExpression;
    }
    else
    {
        return 0;//заглушка (необходим вызов исключения)
    }
}

bool Parser::isDecimalSeparator(char symbol)
{
    return (symbol == '.' || symbol == ',');
}

double Parser::calculate(double valueX)
{
    for (char symbol : expressionPolishNotation)
    {
        if (std::isdigit(symbol) || symbol == '#' || symbol == '.')
        {
            addDigitToOperands(symbol);
        }
        else if (symbol == 'x')
        {
            addValueVariableToOperands(valueX);
        }
        else
        {
            calculateIntermediateResults(symbol);
        }
    }
    return getResultExpression();
}

std::string Parser::getExpressionPolishNotation() const
{
    return expressionPolishNotation;
}

int Parser::getPriorityOperator(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}
