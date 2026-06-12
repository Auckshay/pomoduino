# Pomoduino (An Arduino UNO shield)

A little DIY Pomodoro timer to keep you focused, and away from pesky distractions.

(3D model)

<img width=50% height=50% alt="image" src="https://github.com/user-attachments/assets/fd588a66-c706-4d48-aae4-8df975b6f881" />

## How it works
To use the pomoduino, in front of an distracting object making sure that the sensor is unobscured clear path infront of it to detect movement. Then set the timer length and break length and start it.
## Why I made this
Every single time I sat down, planning to work on something, I always found myself instinctavly reaching for my phone. I knew this was an issue and I of course tried to set screen time limits and pomoduro timers to keep me locked in, but I found my self either disabling and just finding some other convluded work around subconsiously. But I knew that i've always been a person that obeys physical obstruction. Thats when I got the idea of creating a device that aided me in focus with a pomoduro timer, but also physically remind me to focus up.
## Design Images
### Schematic Design
<img width="833" height="927" alt="image" src="https://github.com/user-attachments/assets/237ae9ba-139b-428f-b13e-c526e254b021" />

### PCB Design
<img width="957" height="675" alt="image" src="https://github.com/user-attachments/assets/75b0b3f5-128b-48eb-a3ae-5199c16ffa6f" />

## B.O.M.

| Reference | Value | Datasheet | Footprint | Qty | DNP |
| --- | --- | --- | --- | --- | --- |
| DS1 | OLED_128X64_.96_I2C |  | OLED_128X64_1.3_I2C:LCD_OLED_128X64_.96_I2C | 1 |  |
| J1 | Power |  | PinHeader_1x08_P2.54mm_Vertical | 1 |  |
| J2,J4 | Digital/PWM |  | PinHeader_1x08_P2.54mm_Vertical,PinHeader_1x10_P2.54mm_Vertical | 2 |  |
| J3 | Analog |  | PinHeader_1x06_P2.54mm_Vertical | 1 |  |
| LS1 | Buzzer |  | KSSG1201-16:XDCR_KSSG1201-16 | 1 |  |
| R1 | R_220Ω |  | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal | 1 |  |
| SW1 | SW (GREEN Key Cap) |  | Button_Switch_THT:SW_PUSH-12mm | 1 |  |
| SW2 | SW (YELLOW Key Cap) |  | Button_Switch_THT:SW_PUSH-12mm | 1 |  |
| SW3 | SW (RED Key Cap) |  | Button_Switch_THT:SW_PUSH-12mm | 1 |  |
| U1 | HC-SR04 |  | HC-SR04:XCVR_HC-SR04 | 1 |  |
