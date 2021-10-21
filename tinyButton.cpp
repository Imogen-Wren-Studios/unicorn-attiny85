

#include "tinyButton.h"



void tinyButton::begin() {
  Serial.println("tinyButton Libary");
  delay(1000);

}

uint8_t tinyButton::sampleADC() {      // returns the true analog state of the ADC

  int buttonSample = analogRead(buttonPin);

  return buttonSample;

}

// define boundaries between analog reads

#define NULL_BOUNDARY 5
//#define BOUNDARY_0 0
#define BOUNDARY_1 50
#define BOUNDARY_2 80
#define BOUNDARY_3 100
#define BOUNDARY_4 1024



uint8_t tinyButton::deriveButton() {   // Returns integers 1 - 4 depending on button pressed 0 = NULL or no button pressed

  int buttonSample = sampleADC();

  if (buttonSample <= NULL_BOUNDARY) {
    return 0;
  } else if (buttonSample > NULL_BOUNDARY && buttonSample <= BOUNDARY_1) {
    return 1;
  } else if (buttonSample > BOUNDARY_1 && buttonSample <= BOUNDARY_2) {
    return 4;
  } else if (buttonSample > BOUNDARY_2 && buttonSample <= BOUNDARY_3) {
    return 2;
  } else if (buttonSample > BOUNDARY_3) {
    return 3;
  } else {
    return false;
  }
}


uint8_t tinyButton::buttonArray() {

  int buttonDetected = deriveButton();
  // Set all variables to zero
  uint8_t buttonBits[4] = {0, 0, 0, 0};

  // Then turn it into a 1 if that button has been detected

  if (buttonDetected > 0) {
    buttonBits[buttonDetected - 1] = 1;
  }
  // for (int i = 0; i < 4; i++) {
  //   Serial.print(buttonBits[i]);
  // }
  // Serial.println("");
}


void tinyButton::tinyButtonLoop() {

 activeButton = tinyButton::deriveButton(): // Use this line to return ints
  
 // tinyButton::buttonArray();   // Use this line to return bits

 return activeButton;
}
