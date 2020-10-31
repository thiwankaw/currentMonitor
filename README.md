In this project we try to use the 16bit DAC module ADS1115 to read the current sensor value with higher accuracy

The built-in DAC of an arduino is 10bit, if we are using a esp8266 we have a 12bit DAC. But this may be not enough for some applications.
We can use and external DAC like ADS1115 for this purpose

The sample code is in the src/currentSensor folder. Before compiling it install the three libraries included in the libs folder.

This code is written to send data to a blynk app. You can also use the terminal monitor to view the value. You can also add a display unit like 
the 1602 to show the reading on the device itself

You will have to change the two variables "offset" and "multiplyer" in the below method "getCurrentReading" to work with your current sensor.


double getCurrentReading(){
  int16_t readingFrom712 = ads.readADC_Differential_0_1();
  
  // we have to find the right values for the offset and multiplyer. i will update with the values
  // that worked for me. values will be different for your sensor
  int16_t offset = 0;
  double multiplyer = 1.0;
  
  return  multiplyer* (readingFrom712 - offset);
  }
