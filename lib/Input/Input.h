#ifndef INPUT_H
#define INPUT_H
#include <Arduino.h>

class Input
{
private:
    char inputEnter = ' ';
    char inputChar = ' ';
    float number;
    bool numberFinished;
    String inputString = "";
public:
    Input();
    void waitforenter(String message);
    float enterNumber(String message);
};

#endif