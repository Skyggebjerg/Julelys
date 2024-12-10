#include <Arduino.h>

#include <M5Unified.h>
#include "Unit_RTC.h"

Unit_RTC RTC;
rtc_time_type RTCtime;
rtc_date_type RTCdate;

char str_buffer[64];

#define SSR     5

void setup() {
    pinMode(SSR, OUTPUT); // Set the SSR pin as output
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    // Initialize I2C communication with custom pins
    Wire.begin(13, 15); // SDA, SCL for the ADC
    Serial.print("RTC");
    RTC.begin();  // Example Initialize the RTC clock. 
    RTCtime.Hours   = 0;  // Set the RTC clock time.
    RTCtime.Minutes = 12;
    RTCtime.Seconds = 0;
    RTCdate.WeekDay = 4;  // Set the RTC clock date.
    RTCdate.Month   = 12;
    RTCdate.Date    = 11;
    RTCdate.Year    = 2024;

    //RTC.setTime(&RTCtime);  // Example Synchronize the set time to the RTC.
                            // 
    //RTC.setDate(&RTCdate);  // Synchronize the set date to the RTC.

}

void loop() {
    RTC.getTime(&RTCtime);  // To get the time. 
    RTC.getDate(&RTCdate);  // Get the date.  
    Serial.printf("RTC Time Now is \n%02d:%02d:%02d\n", RTCtime.Hours,
                  RTCtime.Minutes, RTCtime.Seconds);
    Serial.printf("RTC Date Now is \n%02d:%02d:%02d WeekDay:%02d\n",
                  RTCdate.Year, RTCdate.Month, RTCdate.Date, RTCdate.WeekDay);

// Check if the current time is between 6:30 and 9:00 or between 16:00 and 23:50
    if  ((RTCtime.Hours >= 6 && RTCtime.Hours <= 8) || (RTCtime.Hours >= 16 && RTCtime.Hours <= 23)) { // If the current time is between 6:00 and 8:59 or between 16:00 and 23:59
        digitalWrite(SSR, HIGH); // Turn on SSR
        //Serial.println(RTCtime.Hours);
        //Serial.println("SSR ON");
    } else {
        digitalWrite(SSR, LOW); // Turn off SSR
        //Serial.println(RTCtime.Hours);
        //Serial.println("SSR OFF");
    }

    delay(1000);
}