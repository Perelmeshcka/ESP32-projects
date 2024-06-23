#include <PZEM004Tv30.h>
#include "screen.h"
#include "sifw.h"

HardwareSerial PZEM_Serial(2);

PZEM004Tv30 pzem(PZEM_Serial, 16, 17);

void setup()
{
    srn::SETUP();
    PZEM_Serial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() 
{
    float voltage = pzem.voltage();
    if (voltage != NAN) {
        srn::print("= VOLTAGE: " + sif::fill(String(voltage), 6, " ", true) + "V =", 0, true);
    } else {
        srn::print("== VOLTAGE: ERROR ==", 0, true);
    }

    float current = pzem.current();
    if (current != NAN) {
        srn::print("= CURRENT: " + sif::fill(String(current), 6, " ", true) + "A =", 1, true);
    } else {
        srn::print("== CURRENT: ERROR ==", 1, true);
    }

    float power = pzem.power();
    if (power != NAN) {
        srn::print("= POWER: " + sif::fill(String(power), 8, " ", true) + "W =", 2, true);
    } else {
        srn::print("=== POWER: ERROR ===", 2, true);
    }

    float energy = pzem.energy();
    if (energy != NAN) {
        srn::print("= ENERGY: " + sif::fill(String(power), 5, " ", true) + "kWh =", 3, true);
    } else {
        srn::print("== ENERGY:  ERROR ==", 3, true);
    }

    Serial.println();
    delay(2000);
}