# WasherOne

Wash, Dry and Cure station for resin prints.
It is designed with:
- printed parts
- Ikea 365+ food storage (60393066)
- Arduino Nano


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

Tolerances are quie tight -> use included step files to modify if needed.

## Electronics

Control circut is quite simple. 
Arduino controls: 
- NEMA17 stepper motor via A4988 stepper driver.
- MOSFET power transistor for LED and fan
- Buttons, LED's and digital LED panel

I have designed PCB that you can order from (for example JLCPCB), however circuit is simple enough to assemble it without dedicated PCB.

## Ikea 365+

https://www.ikea.com/us/en/p/ikea-365-food-container-rectangular-plastic-60393066/
