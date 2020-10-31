#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h> //Blynk
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

// wifi connection
char ssid[] = "Dialog 4G";
char pass[] = "password";
char auth[] = "token_from_blynk";
SimpleTimer timer;
//int16_t adc0, adc1, adc2, adc3;



void SEND_DATA(){
  
  float currentReading = getCurrentReading();
  Blynk.virtualWrite(V1 , currentReading);
  Serial.print("data sent ");
  Serial.print(currentReading);
  
}

double getCurrentReading(){
  int16_t readingFrom712 = ads.readADC_Differential_0_1();
  
  // we have to find the right values for the offset and multiplyer. i will update with the values
  // that worked for me. values will be different for your sensor
  int16_t offset = 0;
  double multiplyer = 1.0;
  
  return  multiplyer* (readingFrom712 - offset);
  }

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Setting things up!");
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, SEND_DATA);
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
     ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop(void) 
{

  Blynk.run();
  timer.run();

  Serial.println(" ");
  
  delay(1000);
} 
