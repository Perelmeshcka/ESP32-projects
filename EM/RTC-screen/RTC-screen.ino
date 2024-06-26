#include <Wire.h>
#include <DS3231.h>
#include "screen.h"
#include "sifw.h"

DS3231 myClock;
bool century = false;
bool h12 = false;
bool pm = false;

void setup()
{
    Wire.begin();
    srn::SETUP();
}

void loop()
{
    srn::print(">>> CURRENT DATE <<<", 0);

    String day = sif::fill(String(myClock.getDate()), 2, "0", true);
    String month = sif::fill(String(myClock.getMonth(century)), 2, "0", true);
    String year = "20" + sif::fill(String(myClock.getYear()), 2, "0", true);
    String date = day + "." + month + "." + year;

    String hourTime = sif::fill(String(myClock.getHour(h12, pm)), 2, "0", true);
    String minuteTime = sif::fill(String(myClock.getMinute()), 2, "0", true);
    String secondTime = sif::fill(String(myClock.getSecond()), 2, "0", true);
    String time = hourTime + ":" + minuteTime + ":" + secondTime;

    srn::print(date + ", " + time, 1);
    delay(100);
}