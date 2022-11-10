# Introduction To Robotics (2022 - 2023)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homework 1:  RGB led controlled by three potentiometers
**Task Requirements:**
Use a separat potentiometer in controlling each of the color of the RGB led (Red,Green andBlue).  The control must be done with digital electronics(aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led).\
**Setup picture:**\
![RGB led image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework%201/rgb_led1.jpeg)
**Video:**\
https://youtu.be/qROK8o1n01I

## Homework 2:  RGB led controlled by three potentiometers
**Task Requirements:**
Building  the  traffic  lights  for  a  crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through. The system has the following states:\
1.State 1(default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  by pressing the button.\
2.State 2 (initiated by counting down 8 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds. Duration:  3 seconds.\
3.State 3 (initiated after state 2 ends):  red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.\
4.State 4 (initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer,  at a constant interval,  faster than the beeping in state 3.  This state should last 4 seconds.\
Be  careful:  pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.\
**Setup picture:**\
![Crosswalk image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework2/crosswalk_2.jpeg)
![Crosswalk image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework2/crosswalk_1.jpeg)
**Video:**\
https://youtu.be/HRBZzg-lszI

## Homework 3:  RGB led controlled by three potentiometers
**Task Requirements:**\
  •Components:  1  7-segment  display,  1  joystick,  resistors  and  wires  (per logic)\
  •General description: You will use the joystick to control the position of the segment and ”draw” on the display.  The movement between segments should be natural (meaning they should jump from the current positiononly to neighbors, but without passing through ”walls”. The system has the following states:\
  1.State  1(default,  but  also  initiated  after  a  button  press  in  State2):  Current  position  blinking.   Can  use  the  joystick  to  move  from one  position  to  neighbors.   Short  pressing  the  button  toggles  state 2.  Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to thedecimal point.\
  2.State  2 (initiated  after  a  button  press  in  State  1):   The  current segment  stops  blinking,  adopting  the  state  of  the  segment  before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back tostate 1.
**Setup picture:**\
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/7-seg_2.jpeg)
**Video:**\
https://youtu.be/pED1BRWcBgk

