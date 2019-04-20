/*------------------------------------------------------------------------
  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"
#include "grinch.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

/*#include "SoftwareSerial.h"*/
#define TX_PIN 0 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 2 // Arduino receive   GREEN WIRE   labeled TX on printer

//SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first*/
//Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

#include "Adafruit_FreeTouch.h"

int touch = 1000;
#define CAPTOUCH_PIN A0

long oldState = 0;


Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(CAPTOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 1 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    3
#define CLOCKPIN   4
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

uint32_t color = 0xFF0000;
uint32_t color2 = 0x42f49b;

int counter =12;
int randomNumber = 0;

void setup() {

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

   if (! qt_1.begin())  
    Serial.println("Failed to begin qt on pin A1");

    
  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(0, OUTPUT); digitalWrite(0, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  //mySerial.begin(19200);  // Initialize SoftwareSerial
  Serial1.begin(9600); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.
  

}

void loop() {

   
  Serial.println("HI");
  Serial.print(qt_1.measure());
  Serial.write(' ');
  checkpress();
  delay(20);
}


void checkpress() {
 
// Get current button state.
 
    long newState =  qt_1.measure();  
    Serial.println(qt_1.measure());
   if (newState > touch && oldState < touch) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    long newState =  qt_1.measure(); }
 
 
  if (newState < touch ) {  
     
     digitalWrite(13, HIGH);
     delay(20);
     Serial.println("Touch");
    strip.setPixelColor(0, 255, 127, 0);
    strip.show();
    }
 
    else {  
      digitalWrite(13, LOW);
      delay(20);
      strip.setPixelColor(0, 0, 255, 0);
      strip.show();
      printChristmas();
    }
 
   
   
  // Set the last button state to the old state.
  oldState = newState;
 
 
} 

void printChristmas(){

   randomSeed(analogRead(0)*analogRead(1));
   randomNumber =  random(1,12);

  printer.inverseOn();
  printer.println(F("Xmas Inc. Presents"));
  printer.inverseOff();

 switch (randomNumber) {
  case 1:
    // statements
    printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  printer.justify('L');
  printer.println(F("That's what it's all about, isn't it? That's what it's always been *about*. Gifts, gifts... gifts, gifts, gifts, gifts, gifts! You wanna know what happens to your gifts? They all come to me. In your garbage. You see what I'm saying? In your *garbage*. I could hang myself with all the bad Christmas neckties I found at the dump. And the avarice.."));
    break;
  case 2:
    // statements
    printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  printer.justify('L');
  printer.println(F("Oh, the Who-manity."));
   case 3:
    // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Oh, no, the sleigh, the presents, they'll be destroyed, and I   care!"));
    break;
  case 4:
     // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Blast this Christmas music. It'sjoyful and triumphant."));
    break;
    case 5:
     // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Am I just eating because I'm bored?"));
    break;
  case 6:
     // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("There is, however, one teeny-tiny Christmas tradition I find quite meaningful...[holds up mistletoe]Mistletoe.[puts mistletoe over his butt]Now pucker up and kiss it, Whoville![wiggles mistletoe]Boi-yoi-yoi-yoing!"));
   break;
    case 7:
       // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Now you listen to me, young lady! Even if we're *horribly mangled*, there'll be no sad faces on Christmas."));
    break;
  case 8:
      // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Holiday who-be what-ee?"));
    break;
   case 9:
     // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("Are you having a holly, jolly Christmas?"));
    break;
  case 10:
    // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("And they'll feast, feast, feast, feast. They'll eat their Who-Pudding and rare Who-Roast Beast. But that's something I just cannot stand in the least. Oh, no. I'M SPEAKING IN RHYME!"));
    break;
   case 11:
    // statements
   printer.println(F(""));
  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('L');
    printer.println(F("The avarice never ends!I want golf clubs. I want diamonds. I want a pony so I can ride it twice, get bored and sell it to make glue. Look, I don't wanna make waves, but this *whole* Christmas season is..."));
    break;
  
}

  // Test more styles
  printer.boldOn();
  printer.justify('R');
  printer.println(F("Grinch"));
  printer.boldOff();
  printer.println(F(""));
  printer.justify('L');
  // Test character double-height on & off
  printer.doubleHeightOn();
  printer.println(F("Merry Grinchmas!"));
  printer.doubleHeightOff();
  printer.println(F(""));
   printer.println(F(""));

  // Print the 75x75 pixel logo in adalogo.h:
  printer.printBitmap(grinch_width, grinch_height, grinch_data);

  printer.println(F(""));
  printer.println(F(""));

  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  
  }

