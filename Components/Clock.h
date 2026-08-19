#pragma once
#include <SN32F400.h>
#include "CT16B1.h"

class Clock {
    private:
		uint8_t timeHour, timeMinute, timeSecond;
		uint16_t timeTick = 0;
		bool isRunning = true;
		bool hasUpdated = true;
    public:
        void setup () {
			timeHour = timeMinute = timeSecond = timeTick = 0;
		}
		
		
        void increaseMinute (bool increase = true) {
			hasUpdated = true;
            if (increase) timeMinute ++;
            else timeMinute --;

            if (timeMinute == 60) timeMinute = 0;
            else if (timeMinute == 255)  timeMinute = 59;
        }

		void decreaseMinute () {
			increaseMinute (false);
		}
		
        void increaseHour (bool increase = true) {
            hasUpdated = true;
			if (increase) timeHour ++;
            else timeHour --;

            if (timeHour == 24) timeHour = 0;
            else if (timeHour == 255)  timeHour = 23;
        }
		
		void decreaseHour () {
			increaseHour (false);
		}
		
        void updateTick () {
			if (isRunning == true) {
				timeTick ++;
				if (timeTick < 250) return;
				
				timeTick = 0;
				timeSecond ++;
				if (timeSecond < 60) return;
				
				timeSecond = 0;
				increaseMinute ();
				if (timeMinute == 0) increaseHour ();
			}
		}
		
		void turnOn () {
			isRunning = true;
		}
		
		void turnOff () {
			isRunning = false;
		}
		
		void resetTickAndSecond () {
			timeSecond = timeTick = 0;
		}
		
        uint8_t getMinute () {
            return timeMinute;
        }

        uint8_t getHour () {
            return timeHour;
        }
		
		uint16_t getTick () {
			return timeTick;
		}
		
		bool getUpdateFlag () {
			return hasUpdated;
		}
		
		void clearUpdateFlag () {
			hasUpdated = false;
		}
};