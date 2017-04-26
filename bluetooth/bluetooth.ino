// Basic Bluetooth sketch HC-05_AT_MODE_01
// Communicate with a HC-05 using the serial monitor
//
// The HC-05 defaults to communication mode when first powered on you will need to manually enter AT mode
// The default baud rate for AT mode is 38400
// See www.martyncurrey.com for details
//
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// 
 
char c = ' ';
char prev = ' ';
unsigned lasttime = 0;

#define MOTORS 2
int motor_speed[MOTORS] = {0,0};
unsigned motor_offtime[MOTORS] = {0,0};

void motor_on(int n, int speed, unsigned duration)
{
  motor_speed[n] = speed;
  motor_offtime[n] = millis() + duration;
  Serial.print("motor "); Serial.print(n); Serial.print(", offtime "); Serial.println(motor_offtime[n]);
}

void update_motor(int n)
{
  if (motor_speed[n] && (millis() >= motor_offtime[n])) {
    motor_speed[n] = 0;
    Serial.print("motor "); Serial.print(n); Serial.println(", off"); 
  }
}

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
 
    // HC-05 default serial speed for AT mode is 38400
    BTserial.begin(9600);  
}

void loop()
{
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        switch (c) {
          case 'u':
          case 'd':
          case 'l':
          case 'r':
            prev = c;
            break;
          case '1':
            switch (prev) {
              case 'u':
                motor_on(0, 100, 100);
                break;
              case 'd':
                motor_on(0, -100, 100);
                break;
              case 'l':
                motor_on(1, 100, 100);
                break;
              case 'r':
                motor_on(1, -100, 100);
                break;              
            }
            break;
        }
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c);  
    }

    update_motor(0);
    update_motor(1);
}

