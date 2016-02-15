/*     ---------------------------------------------------------
*     |  Arduino Experimentation Kit Example Code             |
*     |  CIRC-10 .: Temperature :. (TMP36 Temperature Sensor) |
*     ---------------------------------------------------------
*
*  A simple program to output the current temperature(F) in bianary to the LEDs
*
*  For more details on this circuit: http://tinyurl.com/c89tvd
*/

/*
 Name:		Thermometer.ino
 Created:	2/14/2016 5:27:06 PM
 Author:	Candelario Daniel Eguia
*/

//TMP36 Pin Variables
int temperaturePin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
						//the resolution is 10 mV / degree centigrade 
						//(500 mV offset) to make negative temperatures an option
						/*
						* getVoltage() - returns the voltage on the analog input defined by
						* pin
						*/

//LED Pin Variables
int ledPins[] = { 2,3,4,5,6,7,8 }; //An array to hold the pin each LED is connected to
									 //i.e. LED #0 is connected to pin 2, LED #1, 3 and so on
									 //to address an array use ledPins[0] this would equal 2
									 //and ledPins[7] would equal 9

float getVoltage(int pin) {
	return ((analogRead(pin) * 5.0)/1024.0); //converting from a 0 to 1023 digital range
										   // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

/*
* BianaryReadOut() - Will light LED according to the Temperature
*/
void BianaryReadOut(float temp) {
	int bianaryArray[7];//holds the bianary conversion of the temperature
	int t = temp;		//holds the value of temp in integer form
	int x = 6;			//iterates through the array
	while (t != 0 && x >= 0) {			//Reduces the Temp by half each time
		 int rem = t % 2;		//Gets the remainder if any
		 bianaryArray[x] = rem; // into stack at position x
		 t = t / 2;
		 x--;
	}
	for (int i = 0; i < 7; i++) {
		if(digitalRead(ledPins[i]) == HIGH && bianaryArray[i] == 0)	digitalWrite(ledPins[i], LOW); //turn off an active LED
		//Serial.print(bianaryArray[i]);
		if (bianaryArray[i]==1) digitalWrite(ledPins[i], HIGH);     //turn on LED #i
		bianaryArray[i] = 0;
	}

}

						/*
						* setup() - this function runs once when you turn your Arduino on
						* We initialize the serial connection with the computer
						*/
void setup()
{
	Serial.begin(9600);  //Start the serial connection with the copmuter
						 //to view the result open the serial monitor 
						 //last button beneath the file bar (looks like a box with an antenae)
	for (int i = 0; i < 8; i++) {         //this is a loop and will repeat eight times
		pinMode(ledPins[i], OUTPUT); //we use this to set each LED pin to output
	}
}

void loop()                     // run over and over again
{
	
	float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
	temperature = (((temperature - .5) * 100) * 1.8) + 32;          //converting from 10 mv per degree wit 500 mV offset
													 //to degrees ((volatge - 500mV) times 100)
	Serial.print("F: ");
	Serial.println(temperature);                     //printing the result
	
	BianaryReadOut(temperature);
	delay(1000);                                     //waiting a second
}