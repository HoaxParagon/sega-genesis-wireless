

#include String;
#include "printf.h"
#include "RF24.h"


void setup() {
  // put your setup code here, to run once:
  String MODE = "CONTROLLER";
  //String MODE = "BASE_UNIT";
  
  //radio
  RF24 radio (7, 8);


  // other pins
  // SCK 13
  // SS 10
  // MOSI 11
  // MISO 12
                            // radio
  typedef struct Controller{int RF24_CE = 0;
                            int RF24_CS = 1;
                            int RF24_SS = 10;
                            int RF24_MOSI = 11;
                            int RF24_MISO = 12;
                            int RF24_SCK = 13;

                            // sega buttons
                            int UP = 2;
                            int DOWN = 3;
                            int LEFT = 4;
                            int RIGHT = 5;
                            int BUTTON_A = 6;
                            int BUTTON_B = 7;
                            int BUTTON_C = 8;
                            int SELECT = 9;
                            int START = 10;
                            };


  if (MODE == "CONTROLLER"){
    //struct controller = Controller;
    Controller controller = Controller;
    
    pinMode(controller.UP, INPUT_PULLUP);
    pinMode(controller.DOWN, INPUT_PULLUP);
    pinMode(controller.LEFT, INPUT_PULLUP);
    pinMode(controller.RIGHT, INPUT_PULLUP);
    pinMode(controller.BUTTON_A, INPUT_PULLUP);
    pinMode(controller.BUTTON_B, INPUT_PULLUP);
    pinMode(controller.BUTTON_C, INPUT_PULLUP);
    pinMode(controller.START, INPUT_PULLUP);
    pinMode(controller.SELECT, INPUT_PULLUP);
  
  // this is for the base station that plugs
  // into the sega
  else if (MODE=="BASE_UNIT"){
    Controller base = Controller;
    pinMode(base.UP, OUTPUT);
    pinMode(base.DOWN, OUTPUT);
    pinMode(base.LEFT, OUTPUT);
    pinMode(base.RIGHT, OUTPUT);
    pinMode(base.BUTTON_A, OUTPUT);
    pinMode(base.BUTTON_B, OUTPUT);
    pinMode(base.BUTTON_C, OUTPUT);
    pinMode(base.START, OUTPUT);
    pinMode(base.SELECT, OUTPUT);
  }

};

void loop() {
  // put your main code here, to run repeatedly:

}
