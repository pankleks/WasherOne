# WasherOne

Wash, Dry and Cure station for resin prints.
It is designed with:
- printed parts
- Ikea 365+ food storage (60393066)
- Arduino Nano

## How does it work?

There are 3 buttons (from left)
- mode (wash, dry, cure)
- time set (pressing increase time of function)
- start/stop

### Washing

Put Ikea container with the part on top of the box. Select wash mode -> set time -> start.
Washing will reverse direction every 30 seconds.

### Drying

Install fan arm. Select dry mode -> set time -> start.

### Curing

Install UV LED arm. Select cure mode -> set time -> start.

> IMPORTANT: UV LED light might be harmfull for your eyes. Do not look directly into UV light. Best use some kind of cover (for example from your resin printer).

## Printed parts

You should print all components on FDM printer.

I used 0.2mm and no support for all parts.

Use brim for larger box parts.

All should fit to 180x180 bed (Prusa Mini)

- Wash top (2 bodies) -> main box and top box plate
- Wash grid (1 body) -> goes into Ikea container
- Wash rotor (1 body) -> mounted to Wash grid with 608 bearing
- Wash motor plate (2 bodies) -> mounted to the stepper motor + plate for drying and curing
- Wash led arm (2 bodies) -> arm for UV curing LED's + block to secure arm (print 2 times -> it's used also for fan arm)
- Wash fan arm (1 body) -> arm for drying fan

> Tolerances are quie tight -> use included step files to modify if needed.

## Electronics

Control circut is quite simple. 
Arduino controls: 
- NEMA17 stepper motor via A4988 stepper driver.
- MOSFET power transistor for LED and fan
- Buttons, LED's and digital LED panel

I have designed PCB that you can order from (for example JLCPCB), however circuit is simple enough to assemble it without dedicated PCB.
Schematic and Gerber files are avaiable in `Electronics` folder.

## Assembly

Should be fairly simple, please see photos in `Assembly` folder.

Essentially:
- Assemble all electronics components on the PCB main board
- Install power socket + on/off switch and RCA plug
- Install tacktile buttons, LED diodes and LED display (you may wish to use glue to secure them)
- Screw in power regulator (use multimeter to set it for 5V)
- Screw in PCB
- Connect all cables (for all 24V connections use ticker cable)

## Ikea 365+

https://www.ikea.com/us/en/p/ikea-365-food-container-rectangular-plastic-60393066/
