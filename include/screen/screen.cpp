#ifndef SCREEN_INTERFACE
#define SCREEN_INTERFACE

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class SCREEN{
public:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
    SCREEN(){};

    void initScreen(){
        //Serial.begin(9600);
        //Wire.begin(PIN1,PIN2);

        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
        if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for(;;); // Don't proceed, loop forever
        }

        // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.
        display.display();
        delay(1000); // Pause for 1 seconds

        // Clear the buffer
        display.clearDisplay();
    }

    void clearDisplay(){
        display.clearDisplay();
    }
    
    template <class T>
    void writeText(T txt, int setX, int setY, int txtSize = 1){
        display.setTextSize(txtSize);
        display.setTextColor(WHITE);
        display.setCursor(setX, setY);
        // Display static text
        display.println(txt);
        display.display(); 
    }
};
#endif