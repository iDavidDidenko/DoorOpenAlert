# ESP32 Door Sensor SMS Notifier

## Description

The ESP32 Door Sensor SMS Notifier is an embedded program designed to monitor a door using a magnetic sensor and send an SMS notification when the door is opened. It utilizes an ESP32 microcontroller, a TFT 1.77-inch screen for display, and the Twilio SMS API for notifications.

## Installation
NODE: THE PROGRAM DEVELOPED IN ARDUINO-IDE

1. Clone the repository to your local machine.

2. Install the required libraries: 
   - Adafruit_ST7735.h
   - WiFi.h
   - HTTPClient.h
   - base64.h
3. Connect the ESP32 to your development environment and upload the code.

## Usage

1. Power on the ESP32 and connect it to your WiFi network.
2. When the magnetic sensor detects that the door has been opened, the program will connect to the Twilio SMS API and send a notification to the specified phone number.
3. The TFT screen will display status messages and notifications.

## Dependencies

- Adafruit_ST7735.h
- WiFi.h
- HTTPClient.h
- base64.h

## Configuration

- Update the WiFi credentials and Twilio API credentials in the code to match your network and Twilio account.
- Adjust any other settings or parameters as needed.

## Contributing

Contributions are welcome! Please submit bug reports, feature requests, or code contributions through GitHub issues and pull requests. 

## License
This project is licensed under the [MIT License](LICENSE).
