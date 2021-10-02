

#include String;
#include "printf.h"
#include "RF24.h"





void setup() {
  // put your setup code here, to run once:
  String MODE = "CONTROLLER";
  //String MODE = "BASE_UNIT";
  
  RF24 radio (7, 8);

  typedef struct Controller{int UP = 3;
                            int DOWN = 4;
                            int LEFT = 5;
                            int RIGHT = 6;
                            int BUTTON_A = 7;
                            int BUTTON_B = 8;
                            int BUTTON_C = 9;
                            int SELECT = 10;
                            int START = 11;
                            };

  

  if (MODE == "CONTROLLER"){
    Controller controller = Controller;
    
    pinMode(controller.UP, INPUT);
    pinMode(controller.DOWN, INPUT);
    pinMode(controller.LEFT, INPUT);
    pinMode(controller.RIGHT, INPUT);
    pinMode(controller.BUTTON_A, INPUT);
    pinMode(controller.BUTTON_B, INPUT);
    pinMode(controller.BUTTON_C, INPUT);
    pinMode(controller.START, INPUT);
    pinMode(controller.SELECT, INPUT);
  }

  // this is for the base station that plugs
  // into the sega
    else{
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
