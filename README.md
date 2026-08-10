# LED Motion & Light Controller (ESP8266 / NodeMCU)

An automatic LED lighting system that turns a light on or off based on **ambient light level** and **motion detection**, using a NodeMCU (ESP8266) programmed with the Arduino IDE.

## Overview

The system combines two sensors to avoid unnecessary lighting:
- A **photoresistor (LDR)** measures ambient light.
- A **PIR motion sensor** detects presence in the room.

The LED only turns on when **both** conditions are met: motion is detected **and** the room is dark enough. This avoids turning the light on during the day even if motion is detected, and avoids false triggers from light changes alone.

## Hysteresis logic

Using a single fixed brightness threshold causes the light to flicker on/off rapidly when ambient light hovers right around that value (e.g. at dusk, or from passing shadows). To prevent this, the system uses **two separate thresholds** instead of one:

- Turn **ON** when the light level drops below **100** (LDR analog reading).
- Turn **OFF** only when the light level rises above **110**.

This creates a buffer zone between the two thresholds so the system doesn't oscillate rapidly near the switching point — a common technique (hysteresis) for stabilizing sensor-driven systems.

## Hardware

| Component        | Role                          |
|-------------------|-------------------------------|
| NodeMCU (ESP8266) | Main microcontroller          |
| LDR (photoresistor) | Ambient light sensing       |
| PIR motion sensor  | Motion / presence detection  |
| LED (+ resistor)   | Output / lighting            |

Pin assignments are defined as variables at the top of the code and can be changed depending on the wiring used.

## Known issue / Work in progress

The PIR sensor currently **over-triggers**, registering motion almost continuously even without significant movement in the room. The likely cause is that the sensor's sensitivity is set too high (most common PIR modules have an onboard potentiometer for this).

**Next steps:**
- Lower the sensitivity via the PIR module's onboard potentiometer.
- If the issue persists, investigate power supply stability and sensor placement (PIR sensors are also sensitive to heat sources and direct sunlight in their field of view).
