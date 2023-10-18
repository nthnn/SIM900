# Arduino SIM900 Shield Comprehensive Library

![Arduino CI](https://github.com/nthnn/SIM900/actions/workflows/arduino_ci.yml/badge.svg) ![Arduino Lint](https://github.com/nthnn/SIM900/actions/workflows/arduino_lint.yml/badge.svg)
![Arduino Release](https://img.shields.io/badge/Library%20Manager-None-red?logo=Arduino)
[![License: LGPL3.0](https://img.shields.io/badge/License-LGPL3.0-yellow.svg)](https://github.com/nthnn/SIM900/blob/main/LICENSE)

The SIM900 Arduino Shield Library is a versatile and powerful Arduino library for interfacing with the SIM900 GSM/GPRS module. This library provides a wide range of functionalities for working with the SIM900 module, including sending and receiving calls, sending and receiving SMS, updating and extracting real-time clock data, sending HTTP requests, and retrieving various information about the SIM900 module's status and the network it is connected to.

<table align="center">
    <tr>
        <td>SIM900 Arduino Shield</td>
        <td>SIM900 Vector</td>
    </tr>
    <tr>
        <td><img src="assets/sim900-shield.png" height="350" /></td>
        <td><img src="assets/sim900-vector.png" height="350" /></td>
    </tr>
</table>

## Features

- **Call Handling**: Make and receive calls with ease.
- **SMS Communication**: Send and receive SMS messages effortlessly.
- **Real-Time Clock**: Update and extract real-time clock data from the module.
- **HTTP Requests**: Send HTTP requests and retrieve responses.
- **Information Retrieval**: Gather data about network operator, module status, SIM card information, and more.
- **Extensive Documentation**: Well-documented code and usage examples.

## Getting Started

### Installation

To use this library, follow these steps:

1. Download the library from the GitHub [repository](https://github.com/nthnn/SIM900).
2. Open your Arduino IDE.
3. Click on `Sketch` -> `Include Library` -> `Add .ZIP Library...`
4. Select the downloaded library ZIP file.

Alternatively, you can click on the `Library Manager` then type "SIM900" to install this library for your projects.

### Hardware Setup

Make sure you have the following components:

- Arduino board compatible with the SIM900 Shield.
- SIM900 Shield with a SIM card inserted.
- 3V CR1220 coin battery for RTC (optional).

Connect the SIM900 Shield to your Arduino board, ensuring it's properly powered and connected. Refer to your hardware documentation for detailed instructions on connecting the module.

## Usage

To use the SIM900 module in your Arduino sketch:

```cpp
#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);  //RX and TX

void setup() {
  Serial.begin(9600);               // Initialize serial communication
  SIM900 sim900(&shieldSerial);     // Initialize the SIM900 shield

  // Your code goes here...
}

void loop() { }
```

## Examples

The repository includes a variety of example sketches that demonstrate the library's features. You can find them in the [examples](examples) folder.

## Contribution and Feedback

Contributions and feedback are all welcome to enhance this library. If you encounter any issues, have suggestions for improvements, or would like to contribute code, please do so.

## Credits

- The SIM900 vector image above was from a [Fritzing](https://fritzing.org) part, found at [https://forum.fritzing.org/t/sim900-part-request/17688](https://forum.fritzing.org/t/sim900-part-request/17688).

## License

Copyright 2023 - Nathanne Isip

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.