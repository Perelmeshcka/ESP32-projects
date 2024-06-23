#include <Wire.h>
#include <DS3231.h>

DS3231 myRTC;
RTCDateTime datetime;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    myRTC.begin();
    myRTC.enableOutput(false);
    myRTC.setDateTime(__DATE__, __TIME__);
}

void loop()
{
    datetime = myRTC.getDateTime();
    Serial.print("Current DateTime: ");
    Serial.println(myRTC.dateFormat("d.m.Y H:i:s - l   ", datetime));
    delay(2000);
}