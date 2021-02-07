LoveBox Clone
===

This is a DIY clone of [Lovebox](https://en.lovebox.love/) and is inspired by the work of [julisa99](https://github.com/julisa99/Lovebox/).

This project is powered by a Wemos D1 Mini that runs a WebSocket client and controls the OLED display and servo motor. A light sensor is used to identify the messageRead status.
## Details

I wanted to experiment with the Wemos platform and was constantly target by Lovebox ads and thought it would be a good idea to give it a try. I then found the work of julisa99 but didn't like that the delay between updating the gist and the message being received + I dind't have access to a laser cutter to cut the wood panels of their design.

Inspired by their work I have then designed this clone of the clone, using the same wiring but with a new Sketch that uses Websockets for an instantaneus message delivery.
Once the message is delivered to the node websocket server, the message gets propagated to all the clients pooling it such as the Wemos. The Wemos activates the servo and displays the message on the screen until the cover is removed and the light hits the photoresistor. When the analog input reads the light, stops the servo and clears the screen after some time. The time and the light reading can be configured in the Sketch to match your preferences.

![Overview](https://media3.giphy.com/media/QyOTqdEvq3LLxTvGCz/giphy.gif)
## Materials

(all Amazon links have my referral, please search manually for the product if you wish not to use my link.)

1. [WeMos D1 Mini](https://amzn.to/3tylYwV)
2. [SG90 9g micro servo motor](https://amzn.to/39VxURJ)
3. [GL5516 photoresistor](https://amzn.to/3oRTOJL)
4. [10kΩ resistor](https://amzn.to/3q9mT4M)
5. [SSD1306 I2C OLED display](https://amzn.to/3rsBWXJ)

## Build

Follow the diagram and solder all the components together.
Allow for 5-6 centimeters of solid core soldering wire between the Wemos and the OLED. The photoresistor also needs to be extended with some wire to allow its positionings on the ```Top_screen.stl```.
I have to admit I have used an awful lot of hot glue in this build. There are supports on the bottom of the ```Box.stl``` to glue the Wemos in place. 
Once the Wemos has been glued to the bottom, install the servo motor and secure it with the screws provided with the servo. There are holes in the back of the box to operate the screwdriver through.
Hold the screen and the photoresistor in place on ```Top_screen.stl``` with the hot glue and push the support on the top of the box until it *clicks* in place. Surprisingly no hot glue is needed here.
Screw the arm to the servo motor with the provided screw and then hotglue the heart in place.

![Wiring diagram](https://i.imgur.com/6L2zcLs.png)

## Print 

I have printed everything in black PLA, except for ```Heart_flat.stl``` and ```Top_cover.stl``` that were printed in red.
There is a second version of the heart included but I didn't like the finish even when printing at 0.1mm - I might remodel this later.

# Software setup

Upload ```index.JS``` in your server of choice and launch it with ```npm install``` and then ```node index.js```. A websocket server will be created at ```serverIP:8080```
Copy credentials_example.h in credentials.h and input your SSID, wifi password and WS endpoint ip address as per previous step.

Use a WebSocket client to send messages to ```serverIP:8080```, the server will aknowledge the message and forward to all clients connected to it. This means you can run multiple Lovebox on the same server and they'll all get the message.

###### tags: `Lovebox` `Instruction`
