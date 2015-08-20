// Do not remove the include below
#include "test_TLC.h"
#include "Tlc5940/Tlc5940.h"

int led=13;

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(led,OUTPUT);
	digitalWrite(led,HIGH);
	delay(2000);
	digitalWrite(led,LOW);
	delay(1000);
	digitalWrite(led,HIGH);

	Tlc.init(4095);
	Tlc.update();
	delay(75);

	Tlc.clear();
	Tlc.update();
	delay(75);

	Tlc.init(4095);

	// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{

	int direction = 1;
	for (int channel = 0; channel < NUM_TLCS * 16; channel += direction) {

		/* Tlc.clear() sets all the grayscale values to zero, but does not send
	       them to the TLCs.  To actually send the data, call Tlc.update() */
		Tlc.clear();

		/* Tlc.set(channel (0-15), value (0-4095)) sets the grayscale value for
	       one channel (15 is OUT15 on the first TLC, if multiple TLCs are daisy-
	       chained, then channel = 16 would be OUT0 of the second TLC, etc.).

	       value goes from off (0) to always on (4095).

	       Like Tlc.clear(), this function only sets up the data, Tlc.update()
	       will send the data. */
		if (channel == 0) {
			direction = 1;
		} else {
			Tlc.set(channel - 1, 1000);
		}
		Tlc.set(channel, 4095);
		if (channel != NUM_TLCS * 16 - 1) {
			Tlc.set(channel + 1, 1000);
		} else {
			direction = -1;
		}

		/* Tlc.update() sends the data to the TLCs.  This is when the LEDs will
	       actually change. */
		Tlc.update();

		delay(75);
	}
	//Add your repeated code here
}
