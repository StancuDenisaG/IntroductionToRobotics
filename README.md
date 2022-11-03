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

