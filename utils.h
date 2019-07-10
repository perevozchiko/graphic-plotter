#ifndef UTILS_H
#define UTILS_H
#include <stack>
#include <string>
#include <QString>

double popAndTop(std::stack<double>& stackInput);

double charToInt(char symbol);

std::string charToStr(char symbol);

void removeSpaces(std::string &str);

Qt::GlobalColor getColor(int numColor);

#endif // UTILS_H
