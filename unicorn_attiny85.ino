#include <FastLED.h>

#include <autoDelay.h>





#define LED_PIN     0
#define NUM_LEDS    16
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGBArray <NUM_LEDS> leds;

#define UPDATES_PER_SECOND 30
#define HUE_STEPS 5                // Number of steps to advance through palette between each for loop. Origionally 3

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

#include "colour_palettes.h"
#include "pride_palettes.h"


#include "globals.h"

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


// set up instance of palette
//CRGBPalette16 tropicalPalette;





uint32_t transition_timer = 45;    // effect transitions are in seconds

#define PRIDE_ONLY true      // When true it overwrites switching and only does pride flags mode

#define PRIDE_ACTIVE true           // When true, pride flag mode is one of the options

#define RANDOMISE_DIRECTION true
#define START_PALETTE RainbowColors_p    // Sterile while palette to start with
//#define START_PALETTE select_palette(random(0, NUM_FX));


#define FADE_THROUGH_DELAY 1   // delay time between brightness changes during crossfade through black effect (millis)
#define PAUSE_BLACK_DELAY 100    // delay time to pause at black between crossfade for cleaner scene change effect

#define PROGRAM_DELAY 10   // Delay to switch progams in minuites





uint32_t animation_delay = 33;   // 33mS delay = 30 frames per second



#define BUTTON_ADC_PIN A7

#include "tinyButton.h"

tinyButton buttons(BUTTON_ADC_PIN);


void setup() {

  buttons.begin();

  animation_delay = calculate_framerate_delay(UPDATES_PER_SECOND);   // Sets up framerate for new smoothed animation style

  fastled_setup();

  currentPalette = START_PALETTE;
  // currentPalette = select_palette(random(0, 5));


  currentBlending = LINEARBLEND;

  // nextPalette = select_palette(random(0, NUM_FX));

  nextPalette = START_PALETTE;

}


















void loop() {

 buttons.tinyButtonLoop();

  if (RANDOMISE_DIRECTION ) {
    randomise_led_directions();    // Changes the direction the LEDs are painted in
    //  randomise_colour_direction();   // < Dont like the effect this has meant to randomise the direction of the colour wheel, but causes jumps and skips
  }

  switchProgram();


  switchPalette();                // Switches colour palette periodically (actually only changes nextPalette, which is blended into currentPalette u


  if (solar_system_mode or PRIDE_ONLY) {
    // No blending between palettes, apply fadethrough used instead (although this also can be called for other palettes so is in main loop)
  } else {
    nblendPaletteTowardPalette(currentPalette, nextPalette, 12);    // slow blend between palettes
  }


  apply_palette();               //applies palette to LED buffer

  apply_fadethrough();               // Changes master brightness in response to fadethrough triggers (Only active if fadethrough is true)

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

  // if (DEBUG_DELAY) {
  //   delay(DEBUG_DELAY_TIME);
  // }


}
