
/*
    All functions used to manage program switching and applying colours



*/









autoDelay fadeBlack;


bool fadetoblack = false;
bool fadetocolour = false;
bool blackpause = false;




int16_t p = 0;    // Global variable used to fade out from max brightness


void apply_fadethrough() {

  if (fadetoblack) {
    //  Serial.println("Fading To Black");
    if (fadeBlack.millisDelay(FADE_THROUGH_DELAY)) {
      if (BRIGHTNESS - p >= 0) {
        FastLED.setBrightness(BRIGHTNESS - p);
        p++;
      } else {

        fadetoblack = false;
        blackpause = true;
        currentPalette = nextPalette;              // Nextpalette has been preloaded with the new palette ready for after the fadeout, so we apply that now.
        p = 0;
      }
    }

  } else if (blackpause) {
    //   Serial.println("Black Pause");
    if (fadeBlack.millisDelay(PAUSE_BLACK_DELAY)) {
      blackpause = false;
      fadetocolour = true;
    }
  } else if (fadetocolour) {
    //  Serial.println("Fade to Colour");
    if (fadeBlack.millisDelay(FADE_THROUGH_DELAY)) {
      if (p <= BRIGHTNESS) {
        FastLED.setBrightness(p);
        p++;
      } else {
        fadetocolour = false;
        p = 0;
      }
    }
  }
}




uint8_t startIndex = 0;


int16_t index_addr = 1;


// Fills led buffer from palette
void apply_palette() {


  startIndex = startIndex + 1;        /* motion speed */

  FillLEDsFromPaletteColors(startIndex);


}







// Elements to change things at different times for randomness

autoDelay hueShiftDelay;

int hue_steps = 3;
uint32_t hue_shift_timing = 5000;


void randomise_colour_direction() {
  if (hueShiftDelay.millisDelay(hue_shift_timing)) {
    //   hue_steps = random(-10, 10);
    index_addr = random(-10, 10);
  //  Serial.print("Randomising Direction: ");
  //  Serial.println(index_addr);

    //  sprintf(debugPrint, "hue_steps: [%i]", hue_steps);
    //  Serial.println(debugPrint);
  }

}








autoDelay directionDelay;   // Controls the delay between rolling dice on a direction change

uint32_t direction_timing = 5000;

bool ledDirection = true;         // Sets the LEDs to update in a positive direction if true, or reverse direction if false


void randomise_led_directions() {
  if (directionDelay.millisDelay(direction_timing)) {    // if delay time is up,
    byte diceRoll = random(0, 5);                               // Roll the dice
  //  Serial.print("Roll Dice: [");
  //  Serial.print(diceRoll);
  //  Serial.println("]");
    if (diceRoll < 1) {                                     // if less than 2, //do nothing
      //   Serial.println("Dice Roll Failed, Direction Unchanged");
    } else {
      if (ledDirection) {
        ledDirection = false;
        //  Serial.println("LED Direction Backwards");
      } else {
        ledDirection = true;                                 // Else Change the directions
        //  Serial.println("LED Direction Forwards.");
      }
      startIndex = startIndex - NUM_LEDS;
    }
    // Function here to randomise direction_timing
    direction_timing = random(500, 15000);                       // Randomise changing direction again from between 0.5s to 10s
    //  sprintf(debugPrint, "Direction Timing: [%u]", direction_timing);
    //Serial.println(debugPrint);

    // Serial.println(debugPrint);
  }
}











autoDelay shift_effect;


// Cycles through banks of palettes based on program type
void switchPalette() {
  if (shift_effect.secondsDelay(transition_timer)) {
//    Serial.println("Fading into New Palette");

    currentPalette = nextPalette;
    if (solar_system_mode or SOLAR_SYSTEM) {
      fadetoblack = true;     // triggers the apply_fade function
      nextPalette = select_planet();    // next palette now is not used because crossfading function is removed HOWEVER, we can now fade to black, then place nextPallet into currentPallet before the fade in,
      // making the crossover seamless
    } else {
      nextPalette = select_palette(random(0, NUM_FX));
    }
  }
}




autoDelay programDelay;

// Function to change program from colours to planets periodically (10 mins?)

void switchProgram() {
  if (programDelay.minutesDelay(PROGRAM_DELAY)) {
    if (solar_system_mode) {
   //   Serial.print("Timer For Colour Mode");
      // solar_system_mode = false;                         // Not switched here because it loops once through and changes elsewhere
      //  Serial.print("Colour Palette Mode");
    } else {
      solar_system_mode = true;
      current_planet = 0;     // reset current planet to the sun
  //    Serial.print("Solar System Mode");
    }
  }
}








// Utilities

void FillLEDsFromPaletteColors( uint8_t colorIndex) {

  if (ledDirection) {
    for ( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
      colorIndex += hue_steps;
    }
  } else {                                                                                              // Same for loop as before but runs in reverse order
    for ( int i = NUM_LEDS; i >= 0; i--) {
      leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
      colorIndex += hue_steps;

    }
  }

}
