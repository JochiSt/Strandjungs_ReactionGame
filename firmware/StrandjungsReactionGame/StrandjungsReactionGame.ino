/**
   Strandjungs Reaction Game

   Hardware Arduino Nano

   Select Board:
      "Arduino Nano"
   Prozessor:
      "ATmega328P (Old Bootloader)"
   Port:
      the Port, which the Arduino is connected to

   Mode:
    A - Drop single wood
    B - Drop two woods at the same time
    C - Drop two woods each at their individual time
    D - Drop all rods after each other with their individual time

   If trigger button is pressed, wait 2 to 10 seconds, then release a wooden rod, which should be catched by the player.
*/

// define all buttons
#define BTN_TRG     5 // trigger button
#define BTN_RST     6 // reset button
#define SEL_MODE_1  2 // mode selection 1
#define SEL_MODE_2  3 // mode selection 2

#define BOARD_LED   13 // on board LED

#define COIL_ON   LOW
#define COIL_OFF  HIGH

enum DROP_MODE {
  SINGLE_ROD,
  DUAL_ROD,
  DUAL_ROD_TIME,
  ALL_ROD_TIME
};

// array of the magnet outputs
int magnets[5] = {8, 9, 10, 11, 12};

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));
    
  // outputs to 5 electro magnets
  for(int i=0; i<5; i++){
    pinMode( magnets[i], OUTPUT );
    digitalWrite( magnets[i], COIL_OFF);
  }

  pinMode(BOARD_LED, OUTPUT);

  // trigger button input
  pinMode( BTN_TRG, INPUT_PULLUP );

  // reset button
  pinMode( BTN_RST, INPUT_PULLUP );

  // mode selection inputs
  pinMode( SEL_MODE_1, INPUT_PULLUP );
  pinMode( SEL_MODE_2, INPUT_PULLUP );

  for(int i=0; i<5; i++){
    digitalWrite(BOARD_LED, COIL_ON);
    digitalWrite(magnets[i], COIL_ON);
    delay(1000);
    digitalWrite(BOARD_LED, COIL_OFF);
    digitalWrite(magnets[i], COIL_OFF);
  }
}

// function to define the waiting time for the rods
void wait_rod(){
  float timewait = random(0, 400);  // wait between 0 and 800 (unit 10ms)  
  delay( (timewait * 10) + 1000);   // unit ms
}

void loop() {
  ///////////////////////////////////////////////////////
  // wait until button is pressed
  bool trigger_state = digitalRead(BTN_TRG);
  while(trigger_state == digitalRead(BTN_TRG)){
    delay(10);
  }
  // button is triggered
  // if button is pressed dice rod and wait random time
    
  ///////////////////////////////////////////////////////
  // check mode pins
  bool sel_0 = digitalRead(SEL_MODE_1);
  bool sel_1 = digitalRead(SEL_MODE_2);

  DROP_MODE mode = sel_1 << 1 | sel_0;

  // if button is pressed dice rod and wait random time
  // random(start, end) - inclusive start, exclusive end
  int rod1 = random(0, 5);          // dice the rod, which should be dropped
  int rod2 = random(0, 5);

  // ensure, that both rods are different
  while(rod1 == rod2){
    rod2 = random(0, 5);   
  }

  // wait
  float timewait = random(0, 400);  // wait between 0 and 800 (unit 10ms)  
  delay( (timewait * 10) + 1000);      // unit ms

  // drop the rods according to the mode selection
  if(mode == SINGLE_ROD || mode == DUAL_ROD ){
    digitalWrite(magnets[rod1], COIL_OFF);
  }
  if(mode == DUAL_ROD){
    digitalWrite(magnets[rod2], COIL_OFF);
  }
  if(mode == DUAL_ROD_TIME){
    wait_rod();
    digitalWrite(magnets[rod2], COIL_OFF);
  }
  if(mode == ALL_ROD_TIME){
      
  }
  
  delay(1000);  // wait for the rod(s) to fall down
  
  // set all rods to be active again
  for(int i=0; i<5; i++){
    digitalWrite( magnets[i], COIL_ON);
  }
}
