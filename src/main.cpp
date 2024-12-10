#include <Arduino.h>

/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/rtc
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/rtc
*
* Product: RTC.  实时时钟
* Date: 2022/7/29
*******************************************************************************
  Please connect to Port A,The time is displayed on the screen.
  请连接端口A,屏幕上显示时间。
*/

//#include "M5Atom.h"
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
    //M5.begin(true, false, true);  // Init M5Atom.  初始化M5Atom
    Serial.begin(115200);
    // Initialize I2C communication with custom pins
    Wire.begin(13, 15); // SDA, SCL for the ADC

    Serial.print("RTC");
    RTC.begin();  // Example Initialize the RTC clock.  初始化RTC时钟
    RTCtime.Hours   = 23;  // Set the RTC clock time.  设置RTC时钟时间
    RTCtime.Minutes = 23;
    RTCtime.Seconds = 0;

    RTCdate.WeekDay = 3;  // Set the RTC clock date.  设置RTC时钟日期
    RTCdate.Month   = 12;
    RTCdate.Date    = 10;
    RTCdate.Year    = 2024;

    //RTC.setTime(&RTCtime);  // Example Synchronize the set time to the RTC.
                            // 将设置的时间同步至RTC
    //RTC.setDate(&RTCdate);  // Synchronize the set date to the RTC.
                            // 将设置的日期同步至RTC
    //M5.dis.fillpix(0x00ff00);
}

void loop() {
    RTC.getTime(&RTCtime);  // To get the time.  获取时间
    RTC.getDate(&RTCdate);  // Get the date.  获取日期
    Serial.printf("RTC Time Now is \n%02d:%02d:%02d\n", RTCtime.Hours,
                  RTCtime.Minutes, RTCtime.Seconds);
    Serial.printf("RTC Date Now is \n%02d:%02d:%02d WeekDay:%02d\n",
                  RTCdate.Year, RTCdate.Month, RTCdate.Date, RTCdate.WeekDay);
    delay(1000);
}