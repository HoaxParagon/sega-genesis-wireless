

#include String;
#include "printf.h"
#include "RF24.h"


void setup() {
  
  Serial.begin(115200);
  while (!Serial){sleep 1;}
  
  String MODE = "CONTROLLER";
  //String MODE = "BASE_UNIT";
  
  //temp[][1] = {['a'], ['a'], ['a'], ['a'], ['a']};
  //RADIO_PAYLOAD_SIZE = sizeof(temp) // 5 characters

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
                            //uint8_t[2][1] UP = {['U']}
                            //uint8_t[2][1] UP = {['U']}
                            //uint8_t[2][1] UP = {['U']}
                            //uint8_t[2][1] UP = {['U']}
                            //uint8_t[2][1] UP = {['U']}
                            uint8_t[][1] UP_UP = {['U'], ['U'], ['|']}
                            uint8_t[][1] UP_DOWN = {['U'], ['D'], ['|']}
                            uint8_t[][1] LEFT_UP ={['L'], ['U'], ['|']}
                            uint8_t[][1] LEFT_DOWN ={['L'], ['D'], ['|']}
                            uint8_t[][1] RIGHT_UP ={['R'], ['U'], ['|']}
                            uint8_t[][1] RIGHT_DOWN ={['R'], ['D'], ['|']}
                            uint8_t[][1] DOWN_UP ={['D'], ['U'], ['|']}
                            uint8_t[][1] DOWN_DOWN ={['D'], ['D'], ['|']}

                            uint8_t[][1] A_UP ={['A'], ['U'], ['|']}
                            uint8_t[][1] A_DOWN ={['A'], ['D'], ['|']}
                            uint8_t[][1] B_UP ={['B'], ['U'], ['|']}
                            uint8_t[][1] B_DOWN ={['B'], ['D'], ['|']}
                            uint8_t[][1] C_UP ={['C'], ['U'], ['|']}
                            uint8_t[][1] C_DOWN ={['C'], ['D'], ['|']}

                            uint8_t[][1] START_UP = {['S'], ['U'], ['|']}
                            uint8_t[][1] START_DOWN = {['S'], ['D'], ['|']}
                            };
  
  // just button messages
  ButtonMessages button = ButtonMessages;
  
  // Let these addresses be used for the pair
  uint8_t address[][5] = {"base", "cont"};

  if (MODE == "CONTROLLER"){
    //struct controller = Controller;
    Controller controller = Controller;
    
    //radio
    RF24 radio (controller.RF24_CE, controller.RF24_CS);
    radio.setPAlevel(RF24_PA_MED); // set to medium for testing
    radio.setPayloadSize(sizeof(button.UP_DOWN));
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
  }//end of CONTROLLER check


  // this is for the base station that plugs
  // into the sega
  else if (MODE=="BASE_UNIT"){
    // struct
    Controller base = Controller;
    
    //radio
    RF24 radio (controller.RF24_CE, controller.RF24_CS);
    radio.setPAlevel(RF24_PA_MED); // set to medium for testing
    radio.setPayloadSize(sizeof(button.UP_DOWN));
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

  down_last = 1;
  up_last = 1;
  left_last = 1;
  right_last = 1;

  a_last = 1;
  b_last = 1;
  c_last = 1;

  start_last = 1;

  if (!radio.begin()){
    Serial.println("radio hardware not responding...")
    while(1){sleep 1;}
  }
}//end setup()

void loop() {
  // read from buttons,
  if (MODE == "CONTROLLER"){
    // check pins
    down_last = True
    
    curr_state = digitalRead(controller.UP)
    if (curr_state != down_last){down_last = curr_state;radio.write(&button.UP_DOWN);} // send radio command}
    else if(curr_state == 0){radio.write(&button.UP_UP);}

    if (digitalRead(controller.DOWN)){radio.write(&button.DOWN_UP)} // send radio}
    else{radio.write(&button.DOWN_DOWN);}
    
    if {digitalRead(controller.LEFT)){radio.write(&button.LEFT_DOWN);}
    else{radio.write(&button.LEFT_UP)}

    if (digitalRead(controller.RIGHT)){radio.write(&button.RIGHT_DOWN);}
    else{radio.write(&button.RIGHT_UP);}

    if (digitalRead(controller.BUTTON_A)){radio.write(&button.A_DOWN);}
    else{radio.write(&button.A_UP);}
    if (digitalRead(controller.BUTTON_B)){radio.write(&button.B_DOWN);}
    else{radio.write(&button.B_UP);}
    if (digitalRead(controller.BUTTON_B)){radio.write(&button.C_DOWN);}
    else{radio.write(&button.C_UP);}
    
    if (digitalRead(controller.START)){radio.write(&button.START_DOWN);}
    else{radio.write(&button.START_UP);}
  }
  // if buttons change,
  // send changes
  else{
    // get bit stream, change accordingly
    if (radio.available()){
      radio.read(&buffer, sizeof(button.UP_DOWN));
      // deal with the flow of info
      switch (buffer){
        case button.UP_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.UP, LOW);
          break;
        case button.UP_UP:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.UP, HIGH);
          break;
        case button.DOWN_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.DOWN, LOW);
          break;
        case button.DOWN_UP:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.DOWN, HIGH);
          break;
        case button.DOWN_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.DOWN, LOW);
          break;
        case button.LEFT_UP:
          digitalWrite(base.SELECT, LOW);
          digitalWrite(base.LEFT, HIGH);
          break;
        case button.LEFT_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.LEFT, LOW);
          break;
        case button.RIGHT_UP:
          digitalWrite(base.SELECT, LOW);
          digitalWrite(base.RIGHT, HIGH);
          break;
        case button.RIGHT_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.RIGHT, LOW);
          break;
        case button. START_UP:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.START, HIGH);
          break;
        case button.START_DOWN:
          digitalWrite(base.SELECT, LOW);
          digitalWrite(base.START, LOW);
          break;
        case button.A_UP:
          digitalWrite(base.SELECT, HIGH);        
          digitalWrite(base.BUTTON_A, HIGH);
          break;
        case button.A_DOWN:
          digitalWrite(base.SELECT, LOW);
          digitalWrite(base.BUTTON_A, LOW);
          break;
        case button.B_UP:
          digitalWrite(base.SELECT, HIGH);        
          digitalWrite(base.BUTTON_B, HIGH);
          break;
        case button.B_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.BUTTON_B, LOW);
          break;
        case button.C_UP:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.BUTTON_C, HIGH);
          break;
        case button.C_DOWN:
          digitalWrite(base.SELECT, HIGH);
          digitalWrite(base.BUTTON_C, LOW);
          break;
        default:
          //throw it out?
          printf("throwing out input, was unexpected")
          break;
        
      }
    }
  }


}
