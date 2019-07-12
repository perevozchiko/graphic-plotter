#include "parser.h"


Parser::Parser(const QString& _userInputExpression) :
    userInputExpression(_userInputExpression)
{
    userInputExpression.remove(' ');
}

void Parser::addDigitToExpression(size_t currentPosition, QChar symbol)
{
    expressionPolishNotation += symbol;
    int nextPosition = currentPosition + 1;
    if (!userInputExpression[nextPosition].isDigit() && !isDecimalSeparator(userInputExpression[nextPosition]))
    {
        expressionPolishNotation += "#";
    }
}

void Parser::addBracketToExpression(QChar symbol)
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
                expressionPolishNotation += operators.pop();
            }
            operators.pop(); // выталкиваем последний оператор
        }
    }
}

void Parser::addOperatorToExpression(QChar symbol)
{
    if(!operators.empty() && getPriorityOperator(symbol) <= getPriorityOperator(operators.back()))
    {
        while(!operators.empty() && operators.top() != '(')
        {
            expressionPolishNotation += operators.pop();
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

void Parser::addMathSymbolToExpression(QChar symbol)
{
    switch (symbol.unicode())
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
        expressionPolishNotation += operators.pop();
    }
}

void Parser::convertToPolishExpression()
{
    int size = userInputExpression.size();

    for (int currentPosition = 0; currentPosition < size; ++currentPosition)
    {
        QChar symbol = userInputExpression[currentPosition];

        if (symbol.isDigit())
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

void Parser::addDigitToOperands(QChar symbol)
{
    if(symbol.isDigit() || symbol == '.')
    {
        symbolsNumber += symbol;
    }

    if (symbol == '#')
    {
        double operand = symbolsNumber.toDouble();
        operands.push(operand);
        symbolsNumber = "";
    }
}

void Parser::addValueVariableToOperands(double valueX)
{
    operands.push(valueX);
}

double Parser::calculateOperandsWithOperator(double leftOperand, double rightOperand, QChar symbolOperator)
{
    switch (symbolOperator.unicode())
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

void Parser::calculateIntermediateResults(QChar symbolOperator)
{
    double leftOperand = 0;
    double rightOperand = operands.pop();

    // для работы с отрицательными числами ("-5" будет "0-5")
    if(!operands.empty())
    {
        leftOperand = operands.pop();
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

bool Parser::isDecimalSeparator(QChar symbol)
{
    return (symbol == '.' || symbol == ',');
}

double Parser::calculate(double valueX)
{
    for (QChar symbol : expressionPolishNotation)
    {
        if (symbol.isDigit() || symbol == '#' || symbol == '.')
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

QString Parser::getExpressionPolishNotation() const
{
    return expressionPolishNotation;
}

int Parser::getPriorityOperator(QChar symbol)
{
    switch (symbol.unicode())
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
