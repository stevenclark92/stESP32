# stESP32

A super simple logic analyser designed to work with an ESP32.

## How it works

This project provides a simple way to monitor the state of an 8-Bit CPU, such as a 6502 or Z-80. It monitors the CPU clock signal (or any external clock signal) and at each rising edge of the pulse it will record the send of the data and address buses in both Binary and Hexadecimal via USB Serial. It will also output whether the current operation is Read or Write, based on the logic level of the R/Wb pin if this is present.

Outputs are deliberately as barebones as possible:
<img width="206" alt="image" src="https://github.com/stevenclark92/stESP32/assets/11930796/63af3ec3-2945-4b93-8b5c-a74abec775e3">

## Getting Started

I intended for this code to be used with the Arduino IDE or VSCode using Arduino extensions. Either should work. I haven't tested this with other boards, but I imagine this will work for RPi and Arduino boards, too, provided they are clocked fast enough.

Getting started is easy. Compile and write the code to your MCU, and attach pins to your 8-Bit CPU via jumpers in the following order:

### Non-bus connections:

| ESP32 Pin   | CPU Pin     |
| ----------- | ----------- |
| GND         | GND         |
| D15         | CLK Out     |
| D13         | RWb         |

### Data bus connections:

| ESP32 Pin   | Data Bus    |
| ----------- | ----------- |
| D12         | D0          |
| D14         | D1          |
| D27         | D2          |
| D26         | D3          |
| D25         | D4          |
| D33         | D5          |
| D32         | D6          |
| D35         | D7          |

### Address bus connections:

| ESP32 Pin   | Address Bus |
| ----------- | ----------- |
| D2          | A0          |
| D4          | A1          |
| D5          | A2          |
| D18         | A3          |
| D19         | A4          |
| D21         | A5          |
| D22         | A6          |
| D23         | A7          |

Pin 34 on the ESP32 is left unconnected, but in future I plan to figure out a way of using this for paging.

## Caveats & Considerations

Due to the number of available input pins on the ESP32 board, it's not possible to read the full 16-Bit address bus and the 8-Bit data bus at the same time. If you're using a different board, simply add the missing pin assignments to be able to read the full bus. 

This code was written quickly without error handling or logic to prevent the ESP32 from spamming the serial connection where the clock signal is floating on boot. Please ensure you have a clock signal available, or you'll probably crash your IDE. I'll fix this eventually.

## Credits

This project was inspired by multiple YouTube projects I've been following, and draws heavily from [Ben Eater's 6502 series](https://www.youtube.com/watch?v=LnzuMJLZRdU) where he uses an Arduino to achieve a similar goal. I opted to rewrite the code to prevent serial writes during interrupts because the microcontrollers I had available had a habit of crashing intermittently if I tried that.


## TODO

I'd like to eventually be able to manage this via a web interface using the ESP32's Wifi, managing the logic analysis with one core and the webserver/websockets with the other. This may not be possible due to hardware constraints, but I plan to have a go.

I'd also like to figure out a way of reading the whole address bus, likely using shift registers. It's not something I have a lot of experience with so far, but I'll crack out the breadboards at some point and figure it out.

Enjoy!
