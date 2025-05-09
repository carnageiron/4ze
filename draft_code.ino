/**********************************************************************************
 * 
 * Interfacing Arduino with KS0108 Monochrome GLCD.
 * This example is for KS0108 GLCD modules with 128x64 Pixel resolution (two CS pins).
 * This is a free software with NO WARRANTY - Use it at your own risk!
 * http://simple-circuit.com/
 *
***********************************************************************************
 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
************************************************************************************
* Modified to work with KS0108 monochrome GLCD. More information including circuit
*   diagram on:
* http://simple-circuit.com/
* 
 **********************************************************************************/

#include <Adafruit_GFX.h>   // include adafruit GFX library
#include <KS0108_GLCD.h>    // include KS0108 GLCD library


// KS0108 GLCD library initialization according to the following connection:
// KS0108_GLCD(DI, RW, E, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7, CS1, CS2, RES);
KS0108_GLCD display = KS0108_GLCD(A0, A1, A2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
static const unsigned char PROGMEM logo_bmp[] =
{0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B01100000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B11000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000001, 0B11000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000011, 0B11000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000111, 0B11000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00011111, 0B11000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B01111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B11111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000001, 0B11111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00001111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00011111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B01111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000001, 
0B11111111, 0B11111110, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000011, 
0B11111111, 0B11111110, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000111, 
0B11111111, 0B11111110, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00001111, 
0B11011111, 0B11111110, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B11111100, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B01111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B11111000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B11111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B11100000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000001, 0B11111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B11000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000011, 0B11111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00001111, 0B11111111, 
0B11111111, 0B11111111, 0B11111111, 0B11111111, 
0B11111111, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11111000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11111011, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B11110000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11111011, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B11100000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11111011, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B11100000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11110011, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B11100000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11110011, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B11100000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11110000, 0B00000001, 0B11111110, 
0B11111111, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11110000, 0B00000011, 0B11111100, 
0B11111110, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11100000, 0B00000111, 0B11111000, 
0B11111110, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11100000, 0B00001111, 0B11110000, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11100000, 0B00111111, 0B11100001, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11100000, 0B01111111, 0B10000001, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11100000, 0B11111111, 0B00000001, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11000001, 0B11111110, 0B00000001, 
0B11111100, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11000011, 0B11111100, 0B00000001, 
0B11111100, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11001111, 0B11110000, 0B00000011, 
0B11111100, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B11011111, 0B11100000, 0B00000011, 
0B11111111, 0B11111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B10011111, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B10000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B10111111, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B10111111, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B10111111, 0B11111111, 0B11111111, 
0B11111111, 0B11111111, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B01111111, 0B11000000, 0B11111000, 
0B00011111, 0B10000111, 0B10011110, 0B00111000, 
0B01111111, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B01111111, 0B11100000, 0B11111000, 
0B01111111, 0B11000111, 0B00111110, 0B00111000, 
0B11111111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B01111001, 0B11100001, 0B11111000, 
0B01111001, 0B11100111, 0B00111111, 0B00111001, 
0B11100011, 0B11000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000011, 0B01110001, 0B11100001, 0B11111000, 
0B11110001, 0B11101111, 0B00111111, 0B00111011, 
0B11000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000010, 0B01111111, 0B11100011, 0B10111100, 
0B11110000, 0B00001111, 0B00111111, 0B11111011, 
0B11000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000010, 0B11111111, 0B11000011, 0B10111100, 
0B11110000, 0B00001111, 0B00111011, 0B11110011, 
0B11001111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000010, 0B11110111, 0B10000111, 0B11111100, 
0B11110001, 0B11001110, 0B01111011, 0B11110011, 
0B11011111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000010, 0B11110011, 0B10001111, 0B11111100, 
0B11110011, 0B11001110, 0B01110001, 0B11110011, 
0B11100111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000010, 0B11100011, 0B11001110, 0B00011100, 
0B01111111, 0B10011110, 0B01110000, 0B11110001, 
0B11111111, 0B10000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000001, 0B11100011, 0B11011100, 0B00011110, 
0B00111111, 0B00011110, 0B01110000, 0B11100000, 
0B11111111, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000, 
0B00000000, 0B00000000, 0B00000000, 0B00000000};

void setup()   {                
  Serial.begin(9600);

  // initialize KS0108 GLCD module with active high CS pins
  if ( display.begin(KS0108_CS_ACTIVE_HIGH) == false ) {
    Serial.println( F("display initialization failed!") );    // lack of RAM space
    while(true);  // stay here forever!
  }

  display.display();
  //delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  //display.drawPixel(10, 10, KS0108_ON);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  //display.display();
  //delay(2000);

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  //testdrawchar();      // Draw characters of the default font
  testdrawbitmap();    // Draw a small bitmap image
  delay(1000);

  testdrawstyles();    // Draw 'stylized' characters

  //testscrolltext();    // Draw scrolling text

  /*display.invertDisp(true);
  display.display();
  delay(1000);
  display.invertDisp(false);
  display.display();
  delay(1000);*/

  //testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps

}

// main loop (nothing here!)
void loop() {
  testdrawstyles(); 
}

/*void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, KS0108_ON);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, KS0108_ON);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, KS0108_ON);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, KS0108_ON);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, KS0108_ON);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, KS0108_ON);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, KS0108_ON);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, KS0108_ON);
    display.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, KS0108_ON);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testfillrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=3) {
    // The INVERSE color is used so rectangles alternate white/KS0108_ON
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, KS0108_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}

void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, KS0108_ON);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, KS0108_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}

void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, KS0108_ON);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/KS0108_ON
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, KS0108_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, KS0108_ON);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, KS0108_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}*/

void testdrawstyles(void) {
  int speed = analogRead(A3);
int speed1=map(speed,0,1023,0,90);
  
  display.clearDisplay();

  display.setTextSize(5);             // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON);        // Draw white text
  display.setCursor(5,15);             // Start at top-left corner
  display.print(speed1);
  display.setTextSize(2); 
  display.setCursor(65,32);
  display.print(F("KM/H"));

  //display.setTextColor(KS0108_OFF, KS0108_ON); // Draw 'inverse' text
  //display.println(3.141592);

  //display.setTextSize(2);             // Draw 2X-scale text
  //display.setTextColor(KS0108_ON);
  //display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
}
/*
void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(KS0108_ON);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(1000);

  // Scroll in various directions, pausing in-between:
  // scroll right
  for (uint8_t scroll = 0; scroll < 0x0F; scroll++) {
    display.scrollRight(1);
    display.display();
    delay(10);
  }
  delay(1000);
  // scroll left
  for (uint8_t scroll = 0; scroll < 0x0F; scroll++) {
    display.scrollLeft(1);
    display.display();
    delay(10);
  }
  delay(1000);
  // diagonal scroll right-up
  for (uint8_t scroll = 0; scroll < display.height()/2; scroll++) {
    display.scrollRight(1);
    display.scrollUp(1);
    display.display();
    delay(10);
  }
  delay(1000);
  // diagonal scroll left-up
  for (uint8_t scroll = 0; scroll < display.height()/2; scroll++) {
    display.scrollLeft(1);
    display.scrollUp(1);
    display.display();
    delay(10);
  }
  delay(1000);
}
*/
void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, KS0108_ON);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

// end of code.