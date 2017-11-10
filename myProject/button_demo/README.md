## Description
This program uses interrupts to detect when the button is pressed or not.

All buttons of the expansion board are functional, all buttons create a tone
in the buzzer, a unique tone for every butto. Buttons S2 and S4 dim the green
LED in the msp430, the buttons S1 and S3 turn on the red LED and when pressed
turns on the green LED.

I used Professor Fraudenthal's original code from the button_demo file, and
added the buzzer file and header. What I did in the buzzer was adding more
casse for each of the other buttons in the expansion board, and did the same
thing for the buzzer tones, by creating 2 variables it make it easier to manipulate
the LED and buzzer for each button. 

For the LED file i changed the led_update method so the LED would dim and also turn
brightly when an expecific button is pressed. 

To run the program you would write 

$ make load

which will create the .o files required to run the program.

To clean all the .o file you must write

$ make clean

this will remove all the of the .o files.
