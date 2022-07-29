# Reaction Game

The idea of this game is that you press a button and after some time (random)
one or two (selectable) wooden rods are dropped. The player has to catch these 
falling rods.

## Modes

There are four different modes implemented. The selection of the modes is done 
via the binary encoded input from the switch (marked with Drop 1/2).
Switch 1 is the LSB and two the MSB.

| Switch 2 	| Switch 1 	| Mode 	| Action                                                                   	|
|----------	|----------	|------	|--------------------------------------------------------------------------	|
| 0        	| 0        	| 0    	| dropping a single random rod                                             	|
| 0        	| 1        	| 1    	| dropping two random rods at the same time                                	|
| 1        	| 0        	| 2    	| dropping two random rods at different times                              	|
| 1        	| 1        	| 3    	| dropping all rods after each other (with waiting time) in a random order 	|