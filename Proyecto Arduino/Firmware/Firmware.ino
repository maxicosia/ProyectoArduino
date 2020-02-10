
// Include Libraries
#include "Arduino.h"
#include "NewPing.h"
#include "LED.h"
#include "Servo.h"


// Pin Definitions
#define HCSR04_PIN_TRIG	3
#define HCSR04_PIN_ECHO	2
#define LEDG_PIN_VIN	5
#define LEDR_PIN_VIN	6
#define SERVO9G_PIN_SIG	4



// Global variables and defines
const int servo9gRestPosition   = 3;  //Starting position
const int servo9gTargetPosition = 93; //Position when event is detected
// object initialization
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LED ledG(LEDG_PIN_VIN);
LED ledR(LEDR_PIN_VIN);
Servo servo9g;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    servo9g.attach(SERVO9G_PIN_SIG);
    servo9g.write(servo9gRestPosition);
    delay(100);
    servo9g.detach();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);

    if(hcsr04Dist < 15){
      Serial.print(F("Verde! ")); Serial.print(hcsr04Dist); Serial.print(F(" "));

      servo9g.attach(SERVO9G_PIN_SIG);        
      servo9g.write(servo9gTargetPosition);
      
      for(int i=255 ; i> 0 ; i -= 5)
    {
    ledG.dim(i);                     
    delay(15);                           
    }                                          
    ledG.off();                       
    }

     
    if(hcsr04Dist >=15){
      Serial.print(F("ROJO! ")); Serial.print(hcsr04Dist); Serial.print(F(" "));
      
      servo9g.attach(SERVO9G_PIN_SIG);   
      servo9g.write(servo9gRestPosition);
      
      for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR.dim(i);                      
    delay(15);                               
    }                                          
    ledR.off(); 
    }
    
    }
    else if(menuOption == '2') {
    // LED - Basic Green 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledG.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledG.off();                        // 3. turns off
    }
    else if(menuOption == '3') {
    // LED - Basic Red 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR.off();                        // 3. turns off
    }
    else if(menuOption == '4') {
    // 9G Micro Servo - Test Code
    // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds) 
    servo9g.attach(SERVO9G_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo9g.write(servo9gTargetPosition);  // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.write(servo9gRestPosition);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.detach();                    // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    
    if (millis() - time0 > timeout)
    {
        servo9g.write(servo9gRestPosition);
        servo9g.detach();
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(2) LED - Basic Green 5mm"));
    Serial.println(F("(3) LED - Basic Red 5mm"));
    Serial.println(F("(4) 9G Micro Servo"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing LED - Basic Green 5mm"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LED - Basic Red 5mm"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing 9G Micro Servo"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
