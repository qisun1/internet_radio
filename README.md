# internet_radio

Physical buttons were used so that a visually impaired person can use it.
![](https://github.com/qisun1/internet_radio/blob/main/radio.jpg?raw=true)

##### Hareware:

1. Esp32 module (The ESP32-audioI2S library used in this sketch only works on multi-core ESP32 chips like the ESP32-WROOM-32. It does not work on the ESP32-S2 or the ESP32-C3 );
2. MAX98357 module: I2S decoder and amplifier;

3. Potentiometers with Switch;
4. Two Push buttons for switching stations;
5. LED light;

Circuit modified from https://circuitdigest.com/microcontroller-projects/esp32-based-internet-radio-using-max98357a-i2s-amplifier-board

I2S_DOUT  -  GPIO12; 
I2S_BCLK  -  GPIO14; 
I2S_LRC  -  GPIO27; 
Volume Control Pot  -  GPIO35; 
channelUp button  -  GPIO33; 
channelDown button  -  32; 

##### Build:
Differen sizes of Hole saws or drill bits were used to cut out holes in the plastic box. 
Hot glue was used to fix the buttons, LED, and speaker to the box cover.

##### Note:

1. The volume control pin (connected to pot) must be connected to one of the ADC1 pins (GPIO 32 or above). The ADC2 pins do not work with Wifi on.
2. Extra libraries: [schreibfaul1](https://github.com/schreibfaul1)/**[ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S)**

I modified Audio.h file, increasing the value of "m_buffSizeRAM"  from 1600 * 5 to 1600 *24. Otherwise, the stream constantly pause for stations with poor connections.
