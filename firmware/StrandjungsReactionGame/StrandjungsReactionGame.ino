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
                    //      switch positions
  SINGLE_ROD,       // 0 => 00
  DUAL_ROD,         // 1 => 01
  DUAL_ROD_TIME,    // 2 => 10
  ALL_ROD_TIME      // 3 => 11
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

  Serial.begin(115200);
  Serial.print("Strandjungs reaction game initialised...\n");

  for(int i=0; i<5; i++){
    Serial.print("Testing channel: ");
    Serial.print(i);
    Serial.print("\n");
    digitalWrite(BOARD_LED, COIL_ON);
    digitalWrite(magnets[i], COIL_ON);
    delay(1000);
    digitalWrite(BOARD_LED, COIL_OFF);
    digitalWrite(magnets[i], COIL_OFF);
  }

  digitalWrite(BOARD_LED, true);
}

// function to define the waiting time for the rods
void wait_rod(){
  float timewait = random(0, 400);  // wait between 0 and 800 (unit 10ms)
  timewait = (timewait*10) + 1000;
  Serial.print("Waiting for: ");
  Serial.print( timewait );
  Serial.print("ms \n");
  delay( timewait);   // unit ms
}

void loop() {
  Serial.print("waiting for button\n");
  digitalWrite(BOARD_LED, false);
  
  ///////////////////////////////////////////////////////
  // wait until button is pressed
  bool trigger_state = digitalRead(BTN_TRG);
  while(trigger_state == digitalRead(BTN_TRG)){
    delay(10);
  }
  // button is triggered
  // if button is pressed dice rod and wait random time
  digitalWrite(BOARD_LED, true);
  Serial.print("Button pressed\n");
  ///////////////////////////////////////////////////////
  // check mode pins
  bool sel_0 = digitalRead(SEL_MODE_1);
  bool sel_1 = digitalRead(SEL_MODE_2);

  DROP_MODE mode = sel_1 << 1 | sel_0;
  Serial.print("Mode: ");
  Serial.print(mode);
  Serial.print("\n");

  // random(start, end) - inclusive start, exclusive end
  int rod1 = random(0, 5);          // dice the rod, which should be dropped
  int rod2 = random(0, 5);
  // ensure, that both rods are different
  while(rod1 == rod2){
    rod2 = random(0, 5); 
  }

  ///////////////////////////////////////////////////////
  // wait
  wait_rod();

  ///////////////////////////////////////////////////////
  // drop the rods according to the mode selection
  if(mode == SINGLE_ROD || mode == DUAL_ROD || mode == DUAL_ROD_TIME){
    Serial.print("Dropping Rod: ");
    Serial.print(rod1);
    Serial.print("\n");
    digitalWrite(magnets[rod1], COIL_OFF);
  }
  // drop two rods at the same time
  if(mode == DUAL_ROD){
    Serial.print("Dropping Rod: ");
    Serial.print(rod2);
    Serial.print("\n");
    digitalWrite(magnets[rod2], COIL_OFF);
  }

  // some additional modes, which are more or less experimental
  // drop two rods after each other
  if(mode == DUAL_ROD_TIME){
    wait_rod();
    Serial.print("Dropping Rod: ");
    Serial.print(rod2);
    Serial.print("\n");
    digitalWrite(magnets[rod2], COIL_OFF);
  }

  // drop all rods after each other
  if(mode == ALL_ROD_TIME){
    bool dropped_rods[5] = {false, false, false, false, false};
    for(int i=0; i<5; i++){
      int rod = random(0, 5);
      while( dropped_rods[rod] ){
        rod = random(0, 5);
      }
      // we have found a rod, which is not yet dropped
      // drop rod
      Serial.print("Dropping Rod: ");
      Serial.print(rod);
      Serial.print("\n");
      digitalWrite(magnets[rod], COIL_OFF);
      // mark rod as dropped
      dropped_rods[rod] = true;
      
      if(i < 4){
        // wait for all rods, but not for the last one
        wait_rod();
      }
    }
  }
  
  delay(1000);  // wait for the rod(s) to fall down
  
  // set all rods to be active again
  for(int i=0; i<5; i++){
    digitalWrite( magnets[i], COIL_ON);
  }
  Serial.print("ready for next try\n");
}
