msp430 based stepper driver logic
=================================

## Description

The device is using small mcu to generate pulses for stepper driver. It has 3 digital inputs (forward, backward and release), one analog input (speed) and 3 outputs (PUL, DIR, ENA). The speed (frequency of the pulses) follows ramps to make start and stop softer. If the release input is active, the motor is released (no current) when its stopped.

## Prototype and programmer

Insert image here ..

## Second prototype

Insert image here ..

TODO:
1) vyzkouset
2) doplnit dokumentaci
