#ifndef tinyButton_h
#define tinyButton_h

#if (ARDUINO >=100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif


#define BUTTON_PIN A1


class tinyButton {




  public:

    // Constructor

    tinyButton(int analogButtonPin):
      buttonPin(analogButtonPin)
    {

    }

    // Methods

    void begin();

    uint8_t sampleADC();

    uint8_t deriveButton();     // Derives which button has been pushed based on analog vaule   // This replaces detectButton

    uint8_t buttonArray();

    uint8_t tinyButtonLoop();

  private:

    int buttonPin = A1;
    uint8_t buttonStates[4];            // Stores the recent history of the button - Private as no need to access this outside of library (hmmmm)

};




#endif
