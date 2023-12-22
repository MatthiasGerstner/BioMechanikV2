#include "Input.h"

Input::Input()
{
    Serial.println("Input initialized");
    return;
}

void Input::waitforenter(String message)
{
    Serial.println(message);
    while (inputEnter != '\n')
    {   
        inputEnter = (char)Serial.read();
        delay(50);
    }
    inputEnter = ' ';
    
    return;
}

float Input::enterNumber(String message)
{
  float number;
  bool numberFinished = false;
  String inputString = ""; // Use a String to accumulate input characters

  Serial.println(message);

  while (!numberFinished) {
    if (Serial.available() > 0) {
      char inputChar = (char)Serial.read(); // Read the incoming character

      // Check for newline character, which indicates the end of user input
      if (inputChar == '\n') {
        numberFinished = true; // Set the flag to true to exit the loop
      } else {
        // Append the incoming character to the input string
        inputString += inputChar;
      }
    }
  }

  // Once the input is finished, convert the input string to a float
  number = inputString.toFloat();

  return number;
}