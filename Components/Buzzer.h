#pragma once
#include "CT16B0.h"
#include "PFPA.h"

class Buzzer {
	private:
		CT16B0* ct16b0;
		PFPA* pfpa;
	public:
		Buzzer (CT16B0* ct16b0, PFPA* pfpa) {
			this ->ct16b0 = ct16b0;
			this ->pfpa = pfpa;
		}
	
		void setup() {
			ct16b0 ->setPrescaler (250-1);
			ct16b0 ->setMatch1Value (96-1);
			ct16b0 ->setEnableResetWhenMatch1();
			
			ct16b0 ->setMatch0Value (48-1);	
			ct16b0 ->setPWM0Mode2 ();
			ct16b0 ->setPWM0Output ();	
			pfpa ->setCT16B0_PWM0PinAs3_0 ();
			ct16b0 ->setPWM0Enable ();
		}
		
		void enable () {
			ct16b0 ->enableCounter();
			ct16b0 ->setPWM0Output (true);
		}
		
		void disable () {
			ct16b0 ->setPWM0Output (false);
			ct16b0 ->disableCounter ();
		}
		
		
	};