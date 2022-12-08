# Introduction To Robotics (2022 - 2023)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homework 1: 
Use a separat potentiometer in controlling each of the color of the RGB led (Red,Green andBlue).  The control must be done with digital electronics(aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led).\
**Setup picture:**\
![RGB led image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework%201/rgb_led1.jpeg)
**Video:**\
https://youtu.be/qROK8o1n01I

## Homework 2: 
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

## Homework 3:  
**Task Requirements:**\
  •Components:  1  7-segment  display,  1  joystick,  resistors  and  wires  (per logic)\
  •General description: You will use the joystick to control the position of the segment and ”draw” on the display.  The movement between segments should be natural (meaning they should jump from the current positiononly to neighbors, but without passing through ”walls”. The system has the following states:\
  1.State  1(default,  but  also  initiated  after  a  button  press  in  State2):  Current  position  blinking.   Can  use  the  joystick  to  move  from one  position  to  neighbors.   Short  pressing  the  button  toggles  state 2.  Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to thedecimal point.\
  2.State  2 (initiated  after  a  button  press  in  State  1):   The  current segment  stops  blinking,  adopting  the  state  of  the  segment  before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back to state 1.\
**Setup picture:**\
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/7-seg_2.jpeg)
**Video:**\
https://youtu.be/pED1BRWcBgk

## Homework 4:  
**Task Requirements:**\
  A joystick will be used as means of navigating through a 4-digit 7-segment display's digits and changing their values. Pressing the joystick's button will lock the system in on the current digit, and the Y axis will be made available, so as to increment or decrement the number shown on the current display digit. Keeping the button pressed will reset the values of all digits, and the system's current position will be moved to the rightmost digit, in the first state.\
  1.State  1(default, but also initiated after a button press in state 2): The X axis of the joystick can be used to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the joystick's button, the system locks in on the selected digit, and it enters the second state. Long pressing the button in state 1 resets the entire display by changing each display digit's value to the number 0, and moving the current position to the rightmost display digit.\
  2.State  2 (initiated after a button press in state 1): The decimal point of the current digit stops blinking, adopting the ON state. In this state, the X axis can no longer be used to cycle through the 4 digits. Instead, by using the Y axis, the number on the current display digit can be incremented or decremented, being able to show numbers IN HEX (aka from 0 to F). Pressing the button again returns the system to state 2. Moreover, when changing the numbers, they should not be changed continuously, while holding the joystick in one direction, but rather, they should change only for every joystick movement.\
**Setup picture:**\
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/homework4/4-digits-7-seg_1.jpeg)
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/homework4/4-digits-7-seg_2.jpeg)

**Video:**\
https://youtu.be/fmM2-AkIZMY
## Homework 5: 
**Task Requirements:**\
Create a menu for the game, using a joystick to scroll on the LCD.\
**Setup picture:**\
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework%205/menu_1.jpeg)
![image](https://github.com/StancuDenisaG/IntroductionToRobotics/blob/main/Homework%205/menu_2.jpeg)

**Video:**\
https://youtube.com/shorts/QEg3OmvJ8NY?feature=share

