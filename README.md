# Pomoduino (An Arduino UNO shield)

A little DIY Pomodoro timer to keep you focused and away from pesky distractions.

(3D model)

<img width=50% height=50% alt="image" src="https://github.com/user-attachments/assets/fd588a66-c706-4d48-aae4-8df975b6f881" />

## How it works
To use the pomoduino, in front of a distracting object, making sure that the sensor is unobscured, and a clear path in front of it to detect movement. Then set the timer length and break length, and start it.
## Why I made this
Every single time I sat down, planning to work on something, I always found myself instinctively reaching for my phone. I knew this was an issue, and I, of course, tried to set screen time limits and pomodoro timers to keep me locked in. Still, I found myself either disabling them or just finding some other convoluted workaround subconsciously. But I knew that I've always been a person who obeys physical obstruction. That's when I got the idea of creating a device that aided me in focus with a pomoduro timer, but also physically reminded me to focus up.
## Design Images
### Schematic Design
<img width="833" height="927" alt="image" src="https://github.com/user-attachments/assets/237ae9ba-139b-428f-b13e-c526e254b021" />

### PCB Design
<img width="957" height="675" alt="image" src="https://github.com/user-attachments/assets/75b0b3f5-128b-48eb-a3ae-5199c16ffa6f" />

## B.O.M.

|Name                                                                                                                  |Purpose                                   |Qty|Cost (USD)|LINK                                                                                  |Distributor|
|----------------------------------------------------------------------------------------------------------------------|------------------------------------------|---|----------|--------------------------------------------------------------------------------------|-----------|
|Monochrome_OLED_128X64_.96_I2C-1pc                                                                                    |Display Count Down, Distraction Notif, ect|1  |6.99$     |https://a.co/d/0dFfSqWY                                                               |Amazon     |
|2.54mm Pin Header, Male Straight Single Row Header Pin 180 Degree Connector,1x2 1x3 1x4 1x5 1x6 1x7 1x8 1x9 1x10 1x12 |For mounting to Arduino UNO               |1  |11.99$    |https://a.co/d/0gofrzR4                                                               |Amazon     |
|Passive Buzzer-5pc                                                                                                    |Auditory Output                           |1  |1.18$     |https://www.aliexpress.us/item/3256806074013807.html                                  |AliExpress |
|220Ω Resistor-10pc                                                                                                    |Current limiting                          |1  |1.46$     |https://www.aliexpress.us/item/3256802927431747.html                                  |AliExpress |
|Colorful Push Button-12mm-15pc                                                                                        |Human Interaction                         |1  |5.95$     |https://www.adafruit.com/product/1010                                                 |Adafruit   |
|HC-SR04-1pc                                                                                                           |Distance measurement                      |1  |6.17$     |https://www.aliexpress.us/item/3256810043926609.html?gatewayAdapt=glo2usa             |AliExpress |
|PCB-5pc                                                                                                               |For mounting and connecting all components|1  |5.00$     |https://www.pcbway.com/orderonline.aspx?outsideid=d9d46809-3d4a-4ff4-aac3-b91ac39b3b48|PCBWAY     |

### External Hardware Required
- 1x Arduino UNO (R3 or R4) – The host board.
- 1x USB-C Cable or USB-B, depending on the Arduino version.
