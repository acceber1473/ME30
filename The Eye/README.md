# The Eye

The Eye is the final project completed for my Fall 2020 electronics class. I worked with a partner to create a public art installation that utilized server-client infrastructure by connecting two Raspberry Pis (one acting as the sensor, another as the actuator) over the internet. What made this project especially interesting and challenging was that my partner, and therefore half of the project, was located 120 miles away from me.

My partner's Raspberry Pi served as the actuator (a stepper motor attached to the eye), whereas my Raspberry Pi was connected to our light sensor. The premise of our design is that when a certain light lux threshold is detected by the sensor, the stepper motor will rotate accordingly and thus open or close the blades of the mechanical iris. Our project was able to run without any connection from our computers; we just needed power sources for the eye and the sensor. 

The Sensor: The light sensor is powered by the Raspberry Pi and the data received was able to be accessed on a web server using port forwarding on my wifi router. We tested the sensor at different points of the day and found a reasonable lux range, which was then used to calculate rotational degrees for the stepper motor.

The Actuator: My partner's Raspberry Pi was able to access my Pi's IP address and receive the light lux data. Our code then took those lux values, translated them to stepper motor degrees, which then would close or open the eye's blades. 

Unfortunately, we ran into some issues with our fabrication, resulting in the motor not providing enough torque to open and close the blades. Our eye is able to open and close manually, and the stepper motor is able to correctly rotate based on lux values based on outputting values using code. However, more work is needed to make the system fully operational. We learned a lot from our mistakes, and this project overall, especially in terms of client-server infrastructure and combining hardware with software. 

## Video 
[Video linked here!](https://youtu.be/_CRtaVYgQiY)

## Images

#### Planning Diagram
<image align="center" src = "https://user-images.githubusercontent.com/49819466/131192796-d366aaee-7db9-4f9a-a5b4-f2d90e2638fb.jpg" height=30% width=30%>
  
#### Eye Frame
![Actuator 1](https://user-images.githubusercontent.com/49819466/131192822-f2c5df77-13cc-4544-97ab-5084423581e6.jpeg)

#### Light Sensor 
<img width="1437" alt="Actuator 2" src="https://user-images.githubusercontent.com/49819466/131192826-40b9d22c-64e0-4670-b226-a1b662a19370.png">
