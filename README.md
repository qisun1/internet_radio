# internet_radio

#### Hareware:

1. Esp32 module;
2. MAX98357 module: I2S decoder and amplifier;

3. Potentiometers with Switch 
4. Two Push buttons for switching stations;

Circuit modified from https://circuitdigest.com/microcontroller-projects/esp32-based-internet-radio-using-max98357a-i2s-amplifier-board

I2S_DOUT  -  GPIO12; 
I2S_BCLK  -  GPIO14; 
I2S_LRC  -  GPIO27; 
Volume Control Pot  -  GPIO35; 
channelUp button  -  GPIO33; 
channelDown button  -  32; 

##### Note:

1. The code does not work with Esp32 Arduino Core Library 2.0. V 1.0.6 was used.
2. The volume control pin (connected to pot) must be connected to one of the ADC1 pins (GPIO 32 or above). The ADC2 pins do not work with Wifi on.
3. Extra libraries: [schreibfaul1](https://github.com/schreibfaul1)/**[ESP32-audioI2S](https://github.com/schreibfaul1/ESP32-audioI2S)**

I modified Audio.h file, increasing the value of "m_buffSizeRAM"  from 1600 * 5 to 1600 *24. Otherwise, the stream constantly pause for stations with poor connections.
