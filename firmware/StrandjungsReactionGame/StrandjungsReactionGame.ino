/**
   Strandjungs Reaction Game

   Hardware Arduino Nano

   Mode:
    A - Drop single wood
    B - Drop two woods at the same time
    C - Drop one or two woods each at their individual time


   If trigger button is pressed, wait 2 to 10 seconds, then release a wooden rod, which should be catched by the player.
*/



void setup() {
  // put your setup code here, to run once:

  // outputs to 5 electro magnets

  // trigger button input

  // mode selection inputs

}

void loop() {
  // wait until button is pressed

  // if button is pressed dice rod and wait random time
  rod = random(0, 4); // dice the rod, which should be dropped

  timewait = random(0, 800); // wait between 0 and 800 (unit 10ms)
  delay(timewait * 10 + 2000); // unit ms




  // check, which mode we are operating


}
