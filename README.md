# WasherOne

DIY Wash, Dry and Cure station for resin prints.
It is designed with:
- 3D printed parts
- Ikea 365+ food container
- Arduino Nano

> All components (excluding printed parts) should cost between 30-40$

![](https://github.com/pankleks/WasherOne/blob/main/Assembly/washer_one.jpg)

https://www.youtube.com/watch?v=Rgxfg9vZFL4&t

## How does it work?

There are 3 buttons (from left)
- mode (wash - top LED, dry - middle LED, cure - bottom LED)
- time set (pressing increase time of function)
- start/stop

### Washing

Put Ikea container with the resin part on top of the box. Select wash mode -> set time -> start.
Washing will reverse direction every 30 seconds.

### Drying

Install fan arm. Install plate. Select dry mode -> set time -> start.

### Curing

Install UV LED arm. Install plate. Select cure mode -> set time -> start.

> IMPORTANT: UV LED light is harmful for your eyes. Do not look directly into the UV light. Best use some kind of cover (for example from your resin printer).

## Printed parts

You should print all components on FDM printer.

I used 0.2mm, PLA and no support for all parts.

Use brim for larger box parts.

All should fit to 180x180 bed (Prusa Mini)

- Wash top (2 bodies) -> main box and top box plate
- Wash grid (1 body) -> goes into Ikea container
- Wash rotor (1 body) -> mounted to Wash grid with 608 bearing
- Wash motor plate (2 bodies) -> mounted to the stepper motor + plate for drying and curing
- Wash led arm (2 bodies) -> arm for UV curing LED's + block to secure arm (print 2 times -> it's used also for fan arm)
- Wash fan arm (1 body) -> arm for drying fan

> Tolerances are quite tight -> use included step files to modify if needed.
> All files are in 3MF format - some contains multiple bodies -> print them separately

## Electronics

Control circuit is quite simple. 
Arduino controls: 
- NEMA17 stepper motor via A4988 stepper driver.
- MOSFET power transistor for LED and fan
- Buttons, LED's and digital LED panel

I have designed PCB that you can order from (for example JLCPCB), however circuit is simple enough to assemble it without dedicated PCB.
Schematic and Gerber files are available in `Electronics` folder.

## Assembly

I'm sorry but I don't have time to write detailed step by step instruction. However, assembly should be fairly simple, please use photos in `Assembly` folder to guide you.

Essentially:
- Upload code to the Arduino
- Assemble all electronics components on the PCB main board
- Install power socket + on/off switch and RCA plug (you should glue RCA plug into the box as it's fairly loose)
- Install tactile buttons, LED diodes and LED display (you may wish to use glue to secure them)
- Screw in step-down converter (IMPORTANT -> use multimeter to set it for 5V)
- Screw in PCB
- Connect all cables (for all 24V connections use ticker wires)
- Install all magnets in the plates and rotor (pay attention so the magnets attract each other, you may also wish to glue in the magnets) 

## Arduino code

Code is available in `Arduino` folder. You should use platform.io to build and upload it.
All parameters are defined in `Pin.h` file, by default all pins are compatible with PCB I designed.

## Fine tunning

Use comments in the code to fine-tune all the parameters such as times, accelerations, and speeds.
The default values work well for me, but may not for you.

> For washing - if you notice skipping rotor (inside container) please regulate distance between motor plate and rotor plate. It may vary depends on your motor shaft length or magnet strength.

> A4988 should be equipped with heat-sink. Motor does not require much power. Use A4988 potentiometer to limit current so it's not overheating.

## Part list

- Arduino Nano
- A4988 stepper driver (one is required, but they may damage easily during testing, so best to equip yourself with 2-3)
- NEMA17 motor
- 2.5 (or 2.1) / 5.5 DC power socket (depending on your PSU)
- 24V PSU (~2-3 Amps) -> brick power supply
- DC On/Off switch
- IRF520 power MOSFET transistor
- 6-8 x PM2E-1LLS (or similar) UV LED (wavelength 390-410nm, 1W)
- LM2596 step-down converter
- 3 x 3mm LED dioses
- 4 digit 7 segment LED display with TM1637 controller
- 100 uF 24V+ electrolytic capacitor
- 1k ohm resistor
- 3 x 220 ohm resistors (for LED's)
- 3 x 150 ohm 5W ceramic resistors (should be connected in parallel)
- 1 x female and 2 x male RCA connectors
- 4 x 20x10x2 neodymium magnets
- 2 x 10x2 (circle) neodymium magnet
- 608 2RS bearing
- 80x80 24V Fan
- Wires

> UV LED resistors resistance should be calculated based on Ohm law depending on LED parameters. Pay attention to proper power capabilities, use multiple in parallel if needed.

- Food container: https://www.ikea.com/us/en/p/ikea-365-food-container-rectangular-plastic-60393066/
- Lock cover: https://www.ikea.com/us/en/p/ikea-365-lid-large-rectangular-plastic-30393063/

# Disclaimer

Please note that I'm not certified electrician. There might be errors in design and your own mistakes during assembly. Please use at your own risk and never leave machine unattended.
