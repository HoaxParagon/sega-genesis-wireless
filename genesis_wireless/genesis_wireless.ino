

#include String;
#include "printf.h"
#include "RF24.h"


void setup() {
  
  Serial.begin(115200);
  while (!Serial){sleep 1;}
  
  String MODE = "CONTROLLER";
  //String MODE = "BASE_UNIT";
  
  temp[][1] = {['a'], ['a'], ['a'], ['a'], ['a']};
  RADIO_PAYLOAD_SIZE = sizeof(temp) // 5 characters

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
  typedef struct ButtonMessages{

  };
  // Let these addresses be used for the pair
uint8_t address[][5] = {"base", "cont"};

  if (MODE == "CONTROLLER"){
    //struct controller = Controller;
    Controller controller = Controller;
    
    //radio
    RF24 radio (controller.RF24_CE, controller.RF24_CS);
    radio.setPAlevel(RF24_PA_MED); // set to medium for testing
    radio.setPayloadSize(RADIO_PAYLOAD_SIZE);
    radio.openWritingPipe(1,address[0]);// reads from buttons, writes to base

    pinMode(controller.UP, INPUT_PULLUP);
    pinMode(controller.DOWN, INPUT_PULLUP);
    pinMode(controller.LEFT, INPUT_PULLUP);
    pinMode(controller.RIGHT, INPUT_PULLUP);
    pinMode(controller.BUTTON_A, INPUT_PULLUP);
    pinMode(controller.BUTTON_B, INPUT_PULLUP);
    pinMode(controller.BUTTON_C, INPUT_PULLUP);
    pinMode(controller.START, INPUT_PULLUP);
    //pinMode(controller.SELECT, INPUT_PULLUP); //not a real pin, used in base station
  
  // this is for the base station that plugs
  // into the sega
  else if (MODE=="BASE_UNIT"){
    // struct
    Controller base = Controller;
    
    //radio
    RF24 radio (controller.RF24_CE, controller.RF24_CS);
    radio.setPAlevel(RF24_PA_MED); // set to medium for testing
    radio.setPayloadSize(RADIO_PAYLOAD_SIZE):
    radio.openReadingPipe(0, address[1]); //reads from controller, does stuff

    // pin setups
    pinMode(base.UP, OUTPUT);
    pinMode(base.DOWN, OUTPUT);
    pinMode(base.LEFT, OUTPUT);
    pinMode(base.RIGHT, OUTPUT);
    pinMode(base.BUTTON_A, OUTPUT);
    pinMode(base.BUTTON_B, OUTPUT);
    pinMode(base.BUTTON_C, OUTPUT);
    pinMode(base.START, OUTPUT);
    pinMode(base.SELECT, OUTPUT); // pulled high/low to use other alt pins
  }

  if (!radio.begin()){
    Serial.println("radio hardware not responding...")
    while(1){sleep 1;}
  }
}

void loop() {
  // read from buttons,
  // if buttons change,
  // send changes

  // read from radio stream
  // if stream changes
  // change button states

}
