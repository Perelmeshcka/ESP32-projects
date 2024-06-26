#include <Wire.h>
#include <LiquidCrystal_I2C.h>

namespace srn {
    const int WIDTH = 20, HEIGHT = 4, SLEEP = 10;
    LiquidCrystal_I2C lcd(0x27, WIDTH, HEIGHT);
    
    void SETUP() {
        lcd.init();
        lcd.backlight();
        lcd.setCursor(0, 0);
        // lcd.cursor();
        // lcd.blink();
    }

    void print(String text, int line, bool fade = false) {
        if (text.length() != WIDTH || line >= HEIGHT || line < 0) {
            text = "ERROR IN PRINT FUNC!";
            if (line < 0) line = 0;
            if (line >= HEIGHT) line = HEIGHT - 1;
            fade = true;
        }

        for (int i = 0; i < WIDTH; ++i) {
            lcd.setCursor(i, line);
            lcd.print(text[i]);
            if (fade) delay(SLEEP);
        }
    }

    void clear() {
        lcd.clear();
    }
};