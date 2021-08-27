# Play It! An electromechanical game inspired by Simon Says

Play It! is an electromechanical game designed for my electronics class Fall 2020. The game requires players to repeat a sequence of randomly generated notes using the push buttons on the breadboard for a total of 7 times in a row to beat the game.

The main electromechanical components include an Arduino MKR 1010 to power the whole system, a servo motor driving the score wheel, a piezo buzzer as a speaker, pushbuttons for user input, and LEDs to indicate which buttons are pushed. 

The computer screen displays the Arduino IDE's serial monitor to make the game more cohesive, but it can also be easily played without the computer interface.

A little breakdown of how the game is set up/works:
The Arduino: The Arduino powers the whole game by providing 5V and ground to the +/- rails of the breadboard and the servo motor. All the pushbuttons, LEDs, and piezo buzzer are connected to digital pins on the Arduino, with the servo connected to a pulse width modulation (PWM) pin. The Arduino code sets the pushbuttons as inputs whereas the LEDs and buzzer are outputs. 

The Breadboard: The main part of the circuit consists of 5 buttons and LEDs- the buttons are pulled up to 5 Volts through a 10K resistor and the LEDs are connected to the Arduino pins via a 1k resistor in series. When a button is pushed, the corresponding LED will light up and the buzzer will output the corresponding note set by the code. 

The Servo Motor: The motor drives the score wheel and will increase by 45 degrees, which is the angle of each wedge on the wheel, for each +1 score. If the player incorrectly plays back a note sequence, the motor is programmed to spin back to the starting position, or zero score. Below is an image of how the servo motor was fit inside a box that served as the frame of the wheel.

## Video
[Video linked here!](https://youtu.be/tz9NjHjXaaw)

## Images
#### Game Setup with Arduino, Breadboard Circuit, and Servo Motor Score Wheel
<img width="780" alt="Screen Shot 2021-08-27 at 6 06 56 PM" src="https://user-images.githubusercontent.com/49819466/131193406-8ea3d6f5-0d95-4273-8c76-8257d45494b7.png">

#### Rear View of Score Wheel and Servo Motor
<img width="783" alt="Screen Shot 2021-08-27 at 6 02 27 PM" src="https://user-images.githubusercontent.com/49819466/131193123-be983cae-27be-4968-9aaf-88c8620304be.png">
