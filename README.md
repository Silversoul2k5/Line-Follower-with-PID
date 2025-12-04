# Line Follower Robot

# Materials Required
- 4WD or 2WD chassis
- Arduino-compatible microcontroller (UNO, Nano, Mini, ESP32* with Arduino core, etc.)
- L298N Motor Driver Module
- 5-Sensor Analog IR Array
- 7–12V Battery or Power Bank (recommended Li-ion/Li-Po pack)
- Jumper wires and basic tools

## Step 1: Assemble the Chasis and fix the Sensor to the bottom of the Car's front <br> Attach L298N Motor Driver Module and Arduino on the top of the car.
### Wiring circuits

make sure you check the polarity of motors so that it goes forward.

| From     | Pin  | <== Pin Name   | To      | Pin |
| -------- | ---- | -------------- | ------- | --- |
| L298N    | IN1  | Left Forward   | Arduino | 7   |
| L298N    | ENA  | Left Speed     | Arduino | 6   |
| L298N    | IN2  | Left Backward  | Arduino | 8   |
| L298N    | IN3  | Right Forward  | Arduino | 9   |
| L298N    | ENB  | Right Speed    | Arduino | 5   |
| L298N    | IN4  | Right Backward | Arduino | 10   |
|          |      |                |         |     |
| S1 IR    | OUT1 | Very Left      | Arduino | A0  |
| S2 IR    | OUT2 | Slight Left    | Arduino | A1  |
| S3 IR    | OUT3 | Middle         | Arduino | A2  |
| S4 IR    | OUT4 | Slight Right   | Arduino | A3  |
| S5 IR    | OUT5 | Very Right     | Arduino | A4  |
| VCC      | VCC  | VCC            | Arduino | VCC |
| GND      | GND  | GND            | Arduino | GND |

#### Note: Wiring depends on your orientation <br> This is why I have included "Pin Name" to describe which Pin I am actually referring to. You can use your own pinouts too.

### Wiring motors

| From         | Pin | To    | Pin  |
| ------------ | --- | ----- | ---- |
| Left Motors  | Vcc | L298N | OUT1 |
| Left Motors  | GND | L298N | OUT2 |
| Right Motors | Vcc | L298N | OUT3 |
| Right Motors | GND | L298N | OUT4 |

## Step 2: Power
- Power is upto you, you can use any thing that has between 7 - 12 Volts
- You simply need to connect it in the following way

  | From    | Pin | To       | Pin |
  | ------- | --- | -------- | --- |
  | Supply  | Vcc | L298N    |11.1V|
  | Supply  | GND | L298N    | GND |
  | L298N   | 5V  | Arduino  | Vin |
  | L298N   | GND | Arduino  | GND |
  | Arduino | 5V  | IR Array | 5V  |
  | Arduino | GND | IR Array | GND |

## Step 3: Upload the code
## Step 4: Try it on different tracks!
