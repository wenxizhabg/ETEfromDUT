#pragma once
#include "CT16B1.h"

class Ticker {
	private:
		CT16B1* ct16b1;
		uint16_t counter1 = 0,
				 counter2 = 0,
				 counter3 = 0;
	public:
		bool timer1IsFinish = false, 
			 timer2IsFinish = false, 
			 timer3IsFinish = false;
		Ticker (CT16B1* ct16b1) {
			this ->ct16b1 = ct16b1;
		}
		
		void setup () {
			ct16b1 ->setPrescaler (250);
			ct16b1 ->setMatch0Value (192);
			ct16b1 ->enableResetWhenMatch0 ();
			ct16b1 ->enableInterruptWhenMatch0 ();
			ct16b1 ->enableIQR ();
		}
		
		void enable () {
			ct16b1 ->enableCounter ();
		}
		
		void setTimer1 (uint16_t max) {
			counter1 = max;
			timer1IsFinish = false;
		}
		
		void updateTimer1 () {
			if (timer1IsFinish == false) counter1 --;
			if (counter1 == 0) timer1IsFinish = true;
		}
		
		void setTimer2 (uint16_t max) {
			counter2 = max;
			timer2IsFinish = false;
		}
		
		void updateTimer2 () {
			if (timer2IsFinish == false) counter2 --;
			if (counter2 == 0) timer2IsFinish = true;
		}
		
		void setTimer3 (uint16_t max) {
			counter3 = max;
			timer3IsFinish = false;
		}
		
		void updateTimer3 () {
			if (timer3IsFinish == false) counter3 --;
			if (counter3 == 0) timer3IsFinish = true;
		}
		
		void updateTimer () {
			updateTimer1 ();
			updateTimer2 ();
			updateTimer3 ();
		}
		
};