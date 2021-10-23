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

uint8_t updates_per_second = 30;

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

//extern CRGBPalette16 myRedWhiteBluePalette;
//extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


// set up instance of palette
//CRGBPalette16 tropicalPalette;





uint32_t transition_timer = 45;    // effect transitions are in seconds



#define RANDOMISE_DIRECTION true

#define START_PALETTE RainbowColors_p    // Sterile while palette to start with
//#define START_PALETTE select_palette(random(0, NUM_FX));



#define FADE_THROUGH_DELAY 1   // delay time between brightness changes during crossfade through black effect (millis)
#define PAUSE_BLACK_DELAY 1    // delay time to pause at black between crossfade for cleaner scene change effect

#include "colour_functions.h"

bool transitionActive = false;
bool animationTriggered = false;

uint32_t animationEndTime;


//uint32_t animation_delay = 33;   // 33mS delay = 30 frames per second



#define BUTTON_ADC_PIN A1

#include "tinyButton.h"

tinyButton buttons(BUTTON_ADC_PIN);


void setup() {

  buttons.begin();


  fastled_setup();

  currentPalette = START_PALETTE;
  // currentPalette = select_palette(random(0, 5));


  currentBlending = LINEARBLEND;

  // nextPalette = select_palette(random(0, NUM_FX));

  nextPalette = START_PALETTE;

}














uint8_t animationMode = 0;   // When 0 animation mode is "stock" running through pallets as normal 1 - 4 will trigger various emote animations



void loop() {

  int buttonState = buttons.tinyButtonLoop();

  animationMode = buttonState;

  if (animationMode == 0) {
    // Normal Operation Cycles through Pride Colours

    if (transitionActive or animationTriggered) {
      exitAnimation();// Picks a new pallet to exit from an animation
      exitTransition();
    } else {
      normalMode();
    }


  } else if (animationMode == 1) {

    angryMode();

  } else if (animationMode == 2) {

    rainbowFart();

  } else if (animationMode == 3) {

    powerUp();

  } else if (animationMode == 4) {

    cantChoose();

  }

  if (RANDOMISE_DIRECTION ) {
    randomise_led_directions();    // Changes the direction the LEDs are painted in
    //  randomise_colour_direction();   // < Dont like the effect this has meant to randomise the direction of the colour wheel, but causes jumps and skips
  }


  apply_fadethrough();


  apply_palette();               //applies palette to LED buffer

  FastLED.show();
  FastLED.delay(1000 / updates_per_second);



}

#define NORMAL_BLEND_SPEED 12

void normalMode() {
  updates_per_second = 30;

  nblendPaletteTowardPalette(currentPalette, nextPalette, NORMAL_BLEND_SPEED);    // slow blend between palettes
  switchPalette();                // Switches colour palette periodically (actually only changes nextPalette, which is blended into currentPalette u
}


#define ANIMATION_BLEND_SPEED 128



void angryMode() {
  updates_per_second = 100;

  animationTriggered = true;

  nextPalette = angry_red;

  nblendPaletteTowardPalette(currentPalette, nextPalette, ANIMATION_BLEND_SPEED);    // slow blend between palettes

}


void rainbowFart() {
  updates_per_second = 500;

  animationTriggered = true;

  nextPalette =  RainbowColors_p;

  nblendPaletteTowardPalette(currentPalette, nextPalette, ANIMATION_BLEND_SPEED);    // slow blend between palettes
}


void powerUp() {
  updates_per_second = 400;

  animationTriggered = true;

  ledDirection = false;

  // currentPalette = hotpink_blue;
  nextPalette =  hotpink_blue;

  nblendPaletteTowardPalette(currentPalette, nextPalette, ANIMATION_BLEND_SPEED);    // slow blend between palettes

}


void cantChoose() {
  updates_per_second = 60;

  animationTriggered = true;

  // currentPalette = hotpink_blue;
  nextPalette =  raggaPalette;

  nblendPaletteTowardPalette(currentPalette, nextPalette, ANIMATION_BLEND_SPEED);    // slow blend between palettes

}




void exitAnimation() {                      // Called once when animation ends
  if (animationTriggered) {
    // fadetoblack = true;
    currentPalette = nextPalette;
    nextPalette = select_palette(random(0, NUM_FX));
    animationTriggered = false;
    transitionActive = true;
    animationEndTime = millis();
  }
}

#define TRANSITION_TIME 1000

void exitTransition() {                          // Stays true untill pallette has been switched back to normal
  if (transitionActive) {
    // fadetoblack = true;
    nblendPaletteTowardPalette(currentPalette, nextPalette, ANIMATION_BLEND_SPEED);    // slow blend between palettes
    if (millis() - animationEndTime >= TRANSITION_TIME) {
      transitionActive = false;
    }
  }
}
