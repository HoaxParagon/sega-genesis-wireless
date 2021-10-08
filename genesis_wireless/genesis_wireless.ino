

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
    
    // start with a blank slate, using bitwise AND to set and track state
    state = 0b00000000;
    
    // bitmasking map
    /*
    1 C       00000001
    2 B       00000010
    4 A       00000100
    8 START   00001000
    16 DOWN   00010000
    32 UP     00100000
    64 LEFT   01000000
    128 RIGHT 10000000

    BUTTON

    */
    
    byte BUTTON_C      = 0b00000001
    byte BUTTON_B      = 0b00000010
    byte BUTTON_A      = 0b00000100
    byte BUTTON_START  = 0b00001000
    byte BUTTON_DOWN   = 0b00010000
    byte BUTTON_UP     = 0b00100000
    byte BUTTON_LEFT   = 0b01000000
    byte BUTTON_RIGHT  = 0b10000000
    
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

  //down_last = 1;
  //up_last = 1;
  //left_last = 1;
  //right_last = 1;

  //a_last = 1;
  //b_last = 1;
  //c_last = 1;

  //start_last = 1;

  if (!radio.begin()){
    Serial.println("radio hardware not responding...")
    while(1){sleep 1;}

  
  }
}//end setup()

void loop() {

  // read from buttons,
  if (MODE == "CONTROLLER"){
    // check pins
    
    //curr_state = digitalRead(controller.UP);
    // button is not pressed
    if (digitalRead(controller.UP);){state = state | BUTTON_UP;}// and the button
    else{state = state ^ BUTTON_UP;}
    // if the pin hasn't been pressed, it's HIGH, OR the MASK
    if (digitalRead(controller.DOWN)){state = state | BUTTON_DOWN;} // send radio}
    else{state = state ^ BUTTON_DOWN;}
    if {digitalRead(controller.LEFT)){state = state | BUTTON_LEFT;}
    else{state = state ^ BUTTON_LEFT;}
    if (digitalRead(controller.RIGHT)){state = state | BUTTON_RIGHT;}
    else{state = state ^ BUTTON_RIGHT;}
    if (digitalRead(controller.BUTTON_A)){state = state | BUTTON_A;}
    else{state = state ^ BUTTON_A;}
    if (digitalRead(controller.BUTTON_B)){state = state | BUTTON_B;}
    else{state = state ^ BUTTON_B;}
    if (digitalRead(controller.BUTTON_C)){state = state | BUTTON_C;}
    else{state = state ^ BUTTON_C;}
    if (digitalRead(controller.START)){state = state | BUTTON_START;}
    else{state = state ^ BUTTON_START;}
    
    //only write state ONCE from now on per loop
    radio.write(&state)
    
    // avoid writing too fast
    sleep(1)
  }
  // if buttons change,
  // send changes
  else{
    // get bit stream, change accordingly

    state = 0b00000000;

    if (radio.available()){
      radio.read(&buffer, sizeof(state));
      // deal with the flow of info

      //check C button first, that's 1 in bin
      // button state recieved check for remaineder of 1
      if (int(buffer) % 2){
        // C button NOT pressed
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.BUTTON_C, HIGH);
      }
      // C button IS pressed
      else{
        Serial.println("C pressed")
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.BUTTON_C, LOW);
      }

      // shift to drop LSB, shake 1 loose
      buffer = buffer >> 1;
      buffer = buffer << 1;
      
      //byte BUTTON_C      = 0b00000001
      //byte BUTTON_B      = 0b00000010
      //byte BUTTON_A      = 0b00000100
      //byte BUTTON_START  = 0b00001000
      //byte BUTTON_DOWN   = 0b00010000
      //byte BUTTON_UP     = 0b00100000
      //byte BUTTON_LEFT   = 0b01000000
      //byte BUTTON_RIGHT  = 0b10000000
      
      // RIGHT BUTTON IS NOT PRESSED
      if (buffer / int(BUTTON_RIGHT) >= 1){
        digitalWrite(base.SELECT, LOW);
        digitalWrite(base.RIGHT, HIGH);
      }
      // RIGHT BUTT IS PRESSED
      else{
        Serial.println("RIGHT pressed")
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.RIGHT, LOW);
      }

      // check left button
      // LEFT BUTTON IS NOT PRESSED
      if (buffer / int(BUTTON_LEFT) >= 1){
        digitalWrite(base.SELECT, LOW);
        digitalWrite(base.LEFT, HIGH);
      }
      else{
        Serial.println("LEFT pressed")
        digitalWrite(base.SELECT, LOW);
        digitalWrite(base.LEFT, LOW);
      }

      // check up button
      // UP BUTTON NOT PRESSED
      if (buffer / int(BUTTON_UP) >= 1){
        digitalWrite(base.SELECT, LOW);
        digitalWrite(base.UP, LOW);
      }
      // up button IS pressed
      else{
        Serial.println("UP pressed")
        digitalWrite(base.SELECT, LOW);
        digitalWrite(base.UP, HIGH);
      }

      // check down button
      // DOWN BUTTON NOT PRESSED
      if (buffer / int(BUTTON_DOWN) >= 1){
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.DOWN, LOW);
      }
      // DOWN BUTTON IS PRESSED
      else{
        Serial.println("DOWN pressed")
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.DOWN, HIGH);
      }

      // check start button
      // START BUTTON NOT PRESSED
      if (buffer / int(BUTTON_START) >= 1){
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.START, HIGH);
      }
      else{
        Serial.println("START pressed")
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.START, LOW);
      }

      // check a button
      // A BUTTON NOT PRESSED
      if (buffer / int(BUTTON_A) >= 1){
        digitalWrite(base.SELECT, HIGH);        
        digitalWrite(base.BUTTON_A, HIGH);

      }
      // a button IS pressed
      else{
        Serial.println("A pressed")
        digitalWrite(base.SELECT, HIGH);        
        digitalWrite(base.BUTTON_A, LOW);
      }

      // check b button
      // B BUTTON NOT PRESSED
      if (buffer / int(BUTTON_B) >= 1){
        //Serial.println("B NOT pressed")
        digitalWrite(base.SELECT, HIGH);        
        digitalWrite(base.BUTTON_B, HIGH);
      }
      else{
        Serial.println("B pressed")
        digitalWrite(base.SELECT, HIGH);
        digitalWrite(base.BUTTON_B, LOW);
      }

        //case button.UP_UP:
        //  
        //  break;
        //case button.DOWN_DOWN:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.DOWN, LOW);
        //  break;
        //case button.DOWN_UP:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.DOWN, HIGH);
        //  break;
        //case button.DOWN_DOWN:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.DOWN, LOW);
        //  break;
        //case button.LEFT_UP:
        //  digitalWrite(base.SELECT, LOW);
        //  digitalWrite(base.LEFT, HIGH);
        //  break;
        //case button.LEFT_DOWN:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.LEFT, LOW);
        //  break;
        //case button.RIGHT_UP:
        //  digitalWrite(base.SELECT, LOW);
        //  digitalWrite(base.RIGHT, HIGH);
        //  break;
        //case button.RIGHT_DOWN:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.RIGHT, LOW);
        //  break;
        //case button. START_UP:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.START, HIGH);
        //  break;
        //case button.START_DOWN:
        //  digitalWrite(base.SELECT, LOW);
        //  digitalWrite(base.START, LOW);
        //  break;
        //case button.A_UP:
        //  digitalWrite(base.SELECT, HIGH);        
        //  digitalWrite(base.BUTTON_A, HIGH);
        //  break;
        //case button.A_DOWN:
        //  digitalWrite(base.SELECT, LOW);
        //  digitalWrite(base.BUTTON_A, LOW);
        //  break;
        //case button.B_UP:
        //  digitalWrite(base.SELECT, HIGH);        
        //  digitalWrite(base.BUTTON_B, HIGH);
        //  break;
        //case button.B_DOWN:
        //  
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.BUTTON_B, LOW);
        //  break;
        //case button.C_UP: 
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.BUTTON_C, HIGH);
        //  break;
        //case button.C_DOWN:
        //  digitalWrite(base.SELECT, HIGH);
        //  digitalWrite(base.BUTTON_C, LOW);
        //  break;
        //default:
        //  //throw it out?
        //  printf("throwing out input, was unexpected")
        //  break;
        
      }//END IF RADIO AVAIALBE, READ
    }//END CHECK FOR NON-CONTROLLER
  }//END WHILE LOOP


}
