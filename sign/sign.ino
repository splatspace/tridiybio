/*
 * sign.ino - Dot Matrix Sign Display
 *
 * Display 1-3 messages with pauses in between.
 *
 * Adapted from the Adafruit_DotStarMatrix library example.
 *
 * ALWAYS PLUG IN THE LED POWER ADAPTER FIRST, THEN THE ARDUINO SECOND IF
 * THEY HAVE SEPARATE POWER CONNECTIONS.
 *
 * pete@soper.us February, May, 2018
 * MIT License (see LICENSE in this repository)
 */

// Pete's build environment is include-nesting challenged, so he needs this
#include <SPI.h>

// This comes from https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_GFX.h>

// This comes from https://github.com/adafruit/Adafruit_DotStarMatrix
#include <Adafruit_DotStarMatrix.h>

// This comes from https://github.com/adafruit/Adafruit_DotStar
#include <Adafruit_DotStar.h>

// Hardware SPI pin assignments

#define DATAPIN  11
#define CLOCKPIN 13

// Pause between matrix shifts this many milliseconds. This determines how
// fast the text moves

#define MATRIX_SHIFT_PAUSE 50

// Pause between messages in milliseconds

#define INTER_MESSAGE_PAUSE 100

// How bright the LEDs should be from 0 (off) to 255 (max)

#define BRIGHTNESS 255

// Specifies the width and height in LEDs of the matrix and magic parameters
// to get the scrolling behavior necessary with the zig-zag connection of rows.

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
  35, 8, DATAPIN, CLOCKPIN,
  DS_MATRIX_TOP     + DS_MATRIX_RIGHT +
  DS_MATRIX_ROWS + DS_MATRIX_ZIGZAG,
  DOTSTAR_BGR);

// The three parameters are red, green, and blue. So 0, 255, 0 gives solid
// green. The eye is most sensitive to green. There are many built in colors
// defined in 

const uint16_t colors[] = {
  matrix.Color(255, 0, 0),     // RED
  matrix.Color(0, 255, 0),     // GREEN
  matrix.Color(0, 0, 255)      // BLUE
};

// Convenience macros for colors

#define RED (colors[0])
#define GREEN (colors[1])
#define BLUE (colors[2])

/*
 * Initialization
 */

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  // Maximum brightness. This WILL require more than USB power if a lot of
  // pixels are trying to light at the same time. 
  matrix.setBrightness(BRIGHTNESS);
  matrix.setTextColor(GREEN);
}

/*
 * Display the first message
 */

void put1() {
  for (int x = matrix.width(); x >= -180; x--) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("TRIDIYBIO OPEN"));
    matrix.show();
    delay(MATRIX_SHIFT_PAUSE);
  }
  delay(INTER_MESSAGE_PAUSE);
}

/*
 * Display the second message
 */

void put2() {
  for (int x = matrix.width(); x >= -180; x--) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("FUTURE HOME OF SPLATSPACE OPEN"));
    matrix.show();
    delay(MATRIX_SHIFT_PAUSE);
  }
  delay(INTER_MESSAGE_PAUSE);
}

/*
 * Display the third message
 */

void put3() {
  for (int x = matrix.width(); x >= -150; x--) {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F(""));  // Add message text here
    matrix.show();
    delay(MATRIX_SHIFT_PAUSE);
  }
  delay(INTER_MESSAGE_PAUSE);
}

/*
 * This function is called over and over. 
 */

void loop() {

/*
 * Put undesired messages inside a "#if false" block 
 */

#if false
#endif

  put1();
  put2();

#if false
  put3();
#endif
}
