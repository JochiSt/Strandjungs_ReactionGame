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
    C - Drop one or two woods each at their individual time


   If trigger button is pressed, wait 2 to 10 seconds, then release a wooden rod, which should be catched by the player.
*/

// define all buttons
#define BTN_TRG     5 // trigger button
#define BTN_RST     6 // reset button
#define SEL_MODE_1  2 // mode selection 1
#define SEL_MODE_2  3 // mode selection 2

enum DROP_MODE {
  SINGLE_ROD,
  DUAL_ROD
};

// array of the magnet outputs
int magnets[5] = {8, 9, 10, 11, 12};

void setup() {
  // put your setup code here, to run once:

  // outputs to 5 electro magnets
  for(int i=0; i<5; i++){
    pinMode( magnets[i], OUTPUT );
    digitalWrite( magnets[i], HIGH);
  }

  // trigger button input
  pinMode( BTN_TRG, INPUT_PULLUP );

  // reset button
  pinMode( BTN_RST, INPUT_PULLUP );

  // mode selection inputs
  pinMode( SEL_MODE_1, INPUT_PULLUP );
  pinMode( SEL_MODE_2, INPUT_PULLUP );
}

void loop() {
  // check mode pins
  bool sel_0 = digitalRead(SEL_MODE_1);
  bool sel_1 = digitalRead(SEL_MODE_2);

  DROP_MODE mode = sel_1 << 1 | sel_0;
  
  // if button is pressed dice rod and wait random time
  int rod1 = random(0, 4);          // dice the rod, which should be dropped
  int rod2 = random(0, 4);

  // ensure, that both rods are different
  while(rod1 == rod2){
    rod2 = random(0, 4);   
  }
   
  float timewait = random(0, 800);  // wait between 0 and 800 (unit 10ms)
  
  // wait until button is pressed
  bool trigger_state = digitalRead(BTN_TRG);
  while(trigger_state == digitalRead(BTN_TRG)){
    yield();
  }
  // button is triggered

  // wait
  delay(timewait * 10 + 2000); // unit ms

  // drop the rods according to the mode selection
  if(mode == SINGLE_ROD || mode == DUAL_ROD ){
    digitalWrite(magnets[rod1], LOW);
  }
  if(mode == DUAL_ROD){
    digitalWrite(magnets[rod2], LOW);
  }
  
  delay(200);  // wait for the rod(s) to fall down
  // set all rods to be active again
  for(int i=0; i<5; i++){
    digitalWrite( magnets[i], HIGH);
  }
}
