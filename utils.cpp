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
    if (numColor > 9)
    {
        numColor %= 10;
    }

    switch(numColor)
    {
    case 0:
        return Qt::red;
    case 1:
        return Qt::blue;
    case 2:
        return  Qt::darkGreen;
    case 3:
        return Qt::black;
    case 4:
        return Qt::darkYellow;
    case 5:
        return  Qt::darkRed;
    case 6:
        return Qt::darkBlue;
    case 7:
        return  Qt::darkCyan;
    case 8:
        return  Qt::magenta;
    case 9:
        return  Qt::darkMagenta;
    default:
        return Qt::black;
    }
}
