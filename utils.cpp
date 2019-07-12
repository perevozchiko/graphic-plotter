#include "utils.h"

double popAndTop(std::stack<double> &stackInput)
{
    if(!stackInput.empty())
    {
        double data = stackInput.top();
        stackInput.pop();
        return data;
    }
    else
    {
        // todo  error no items in stack
        return 0;
    }
}

double charToInt(char symbol)
{
    return symbol - '0';
}

std::string charToStr(char symbol)
{
    std::string string(1, symbol);
    return string;
}

void removeSpaces(QString& str)
{
    str.remove(" ");
}

Qt::GlobalColor getColor(int numColor)
{
    numColor += 7;
    if (numColor > 18)
    {
        numColor %= 18;
        // поправить если numColor = 27 то получаем цвет 19 (Qt::GlobalColor только до 18)
        numColor += 3;
    }

    Qt::GlobalColor colorGraphic = static_cast<Qt::GlobalColor>(numColor);
    return colorGraphic;
}
