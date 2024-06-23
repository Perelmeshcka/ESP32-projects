#include <Wire.h>
#include <DS3231.h>

DS3231 myRTC;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.print("Current date: ");
    Serial.println(F(__DATE__));
    Serial.print("Current time: ");
    Serial.println(F(__TIME__));
    delay(2000);
}