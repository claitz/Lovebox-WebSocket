LoveBox Clone
===
This is a DIY clone of [Lovebox](https://en.lovebox.love/) and is inspired by the work of [julisa99](https://github.com/julisa99/Lovebox/).

This project is powered by a Wemos D1 Mini that runs a WebSocket client and controls the OLED display and servo motor. A light sensor is used to identify the messageRead status.
## Materials
(all Amazon links have my referral, please search manually for the product if you wish not to use my link.)
1. [WeMos D1 Mini](https://amzn.to/3tylYwV)
2. [Servo motor](https://amzn.to/39VxURJ)
3. [Light sensor](https://amzn.to/3oRTOJL)
4. [10kΩ resistor](https://amzn.to/3q9mT4M)
5. [OLED display](https://amzn.to/3rsBWXJ)

## Build 
Follow the diagram and solder all the components together. I'd suggest to use at least 5cm of wire for the connections between the OLED and the Wemos. Use some solid core wire to extend the photoresistor pins to allow it to be raised to the top in its slot next to the display.

![](https://i.imgur.com/6L2zcLs.png)

Print the case, i personally printed everything in black PLA+ except for the hearth that was printed in red.

Copy credentials_example.h in credentials.h and input your SSID, wifi password and WS endpoint.

If using the included server (index.js), please run it on a WS capable VPS.

All messages sent to server:8080 will be broadcasted to the Lovebox.

###### tags: `Lovebox` `Instruction`
