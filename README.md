# IR-RFID-Speed-Detector-using-Arduino
'''New sensors used: RFID and IR

An IR sensor has 3 pins – 5V pwer, GND and OUTPUT. I runs on negative logic, where output is high when not triggered and low when an object is sensed.

The RFID reader has 8 pins, out of which 2 are 3.3V power and GND. 
RST is an input for Reset. It resets the device in case of an error or when the device isn’t giving any response.
IRQ is an interrupt pin that can alert the microcontroller when an RFID tag comes into its vicinity. In simple terms, the device can go into sleep mode to save power. So, the IRQ helps to wake it.
MISO pin stands for Master-In-Slave-Out when SPI interface is enabled, acts as serial clock when I2C interface is enabled and acts as serial data output when UART interface is enabled.
MOSI (Master Out Slave In) is SPI pin that takes input data. 
SCK (Serial Clock) accepts clock pulses from the Arduino.
SDA pin acts as Signal input and can be used for communication from all 3 interfaces. This pin is usually marked in a square so it can be used as a reference for identifying the other pins.'''
