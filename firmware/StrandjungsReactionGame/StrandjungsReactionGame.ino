/**
   Strandjungs Reaction Game

   Hardware Arduino Nano

   Mode:
    A - Drop single wood
    B - Drop two woods at the same time
    C - Drop one or two woods each at their individual time


   If trigger button is pressed, wait 2 to 10 seconds, then release a wooden rod, which should be catched by the player.
*/

// array of the magnet outputs
int magnets = {8, 9, 10, 11, 12};

void setup() {
  // put your setup code here, to run once:

  // outputs to 5 electro magnets
  for(int i=0; i<5; i++){
    pinMode( magnets[i], OUTPUT );
    digitalWrite( magnets[i], HIGH);
  }

  // trigger button input
  pinMode( 5, INPUT_PULLUP );

  // reset button
  pinMode( 6, INPUT_PULLUP );

  // mode selection inputs
  pinMode( 2, INPUT_PULLUP );
  pinMode( 3, INPUT_PULLUP );
}

void loop() {
  // check mode pins
  bool sel_0 = digitalRead(2);
  bool sel_1 = digitalRead(3);
  
  // wait until button is pressed

  // if button is pressed dice rod and wait random time
  float rod = random(0, 4); // dice the rod, which should be dropped

  timewait = random(0, 800); // wait between 0 and 800 (unit 10ms)
  delay(timewait * 10 + 2000); // unit ms


}
