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

|Reference  |Name                          |Purpose                                   |Qty|Cost (USD)                    |LINK                                                                                  |
|-----------|------------------------------|------------------------------------------|---|------------------------------|--------------------------------------------------------------------------------------|
|DS1        |Monochrome_OLED_128X64_.96_I2C|Display Count Down, Distraction Notif, ect|1  |6.99                          |https://a.co/d/0dFfSqWY                                                               |
|J1,J2      |Male Pin Header-1x8-P2.54mm   |For mounting to Arduino UNO               |2  |11.99                         |https://a.co/d/0gofrzR4 (Bulk order applicable for other projects)                    |
|J3         |Male Pin Header-1x6-P2.54mm   |For mounting to Arduino UNO               |1  |N/A                           |bundled above                                                                         |
|J4         |Male Pin Header-1x10-P2.54mm  |For mounting to Arduino UNO               |1  |N/A                           |bundled above                                                                         |
|LS1        |Passive Buzzer                |Auditory input                            |1  |Owned                         |N/A                                                                                   |
|R1         |220Ω Resistor                 |Current limiting                          |1  |Owned                         |N/A                                                                                   |
|SW1,SW2,SW3|Push Button-12mm              |Human Interaction                         |3  |Owned                         |N/A                                                                                   |
|U1         |HC-SR04                       |Distance measurement                      |1  |Owned                         |N/A                                                                                   |
|           |PCB                           |For mounting and connecting all components|1  |(Global Direct Shipping) 11.31|https://www.pcbway.com/orderonline.aspx?outsideid=d9d46809-3d4a-4ff4-aac3-b91ac39b3b48|

### External Hardware Required
- 1x Arduino UNO (R3 or R4) – The host board.
- 1x USB-C Cable or USB-B, depending on the Arduino version.
