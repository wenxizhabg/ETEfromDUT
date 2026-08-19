#pragma once
#include "GPIO1.h"
#include "GPIO2.h"

class Button {
	private:
		GPIO1* gpio1;
		GPIO2* gpio2;
	public:
		Button (GPIO1* gpio1, GPIO2* gpio2) {
			this->gpio1 = gpio1;
			this->gpio2 = gpio2;
		}
		
		void setup () {
			setupMatrixButton ();
			enableInterruptWhenPress ();
		}
		
		void setupMatrixButton () {
			gpio2->setOutputAtPin(4);
			gpio2->setOutputAtPin(7);
		}
		
		void enableInterruptWhenPress () {
			gpio2->setFallingEdgeTriggerOnPin(10);
			gpio2->enableInterruptOnPin(10);
			gpio2->enableIQR();
		}
		
		uint8_t checkButton () {
			uint8_t sw = 0;
			gpio2->setDataOutAtPin(7);
			if (gpio1->getDataInAtPin(4) == 0) sw = 3;
			if (gpio1->getDataInAtPin(7) == 0) sw = 16;
			gpio2->clearDataOutAtPin(7);
			
			gpio2->setDataOutAtPin(4);
			if (gpio1->getDataInAtPin(4) == 0) sw = 6;
			if (gpio1->getDataInAtPin(5) == 0) sw = 10;
			gpio2->clearDataOutAtPin(4);
			
			return sw;
		}
};