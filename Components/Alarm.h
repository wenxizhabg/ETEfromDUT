#pragma once
#include "GPIO3.h"
#include "FLASH.h"


class Alarm {
	private:
		GPIO3* gpio3;
		Flash* flash;
		union {
			uint32_t data;
			struct {
				uint8_t hour;
				uint8_t minute;
				uint16_t reversed = 0xFFFF;
			};
		} alarm;
		uint8_t savedHour = 0, savedMinute = 0;
		uint16_t tick = 0, tickOn = 0, tickOff = 0;
		uint8_t repeatNumber = 0;
		
	public:
		bool isRinging = false;
		Alarm (GPIO3* gpio3, Flash* flash) {
			this ->gpio3 = gpio3;
			this ->flash = flash;
		}
		
		void setMinute (uint8_t minute) {
			alarm.minute = minute;
		}
		
		uint8_t getMinute () {
			return alarm.minute;
		}
		
		uint8_t getHour () {
			return alarm.hour;
		}
		
		void setHour (uint8_t hour) {
			alarm.hour = hour;
		}
		
		void increaseMinute (bool increase = 1) {
            if (increase) alarm.minute ++;
            else alarm.minute --;

            if (alarm.minute == 60) alarm.minute = 0;
            else if (alarm.minute == 255)  alarm.minute = 59;
        }

		void decreaseMinute () {
			increaseMinute (0);
		}
		
        void increaseHour (bool increase = 1) {
            if (increase) alarm.hour ++;
            else alarm.hour --;

            if (alarm.hour == 24) alarm.hour = 0;
            else if (alarm.hour == 255)  alarm.hour = 23;
        }
		
		void decreaseHour () {
			increaseHour (0);
		}
		
		void setLed () {
			gpio3 ->setOutputAtPin (8);
			turnLedOff ();
			
		}
		
		void setup () {
			setLed ();
		}
		void turnLedOff () {
			gpio3 ->setDataOutAtPin (8);
		}
		
		void turnLedOn () {
			gpio3 ->clearDataOutAtPin (8);
		}
		
		void setupRing (uint16_t tickOn, uint16_t tickOff, uint8_t repeatNumber) {
			this ->tickOn = tickOn;
			this ->tickOff = tickOff;
			this ->repeatNumber = repeatNumber;
			this ->tick = 1;
		}
		
		void updateTick () {
			if (repeatNumber == 0) {
				isRinging = false;
				return;
			}
			if (tick <= tickOn) isRinging = true;
			else isRinging = false;
			if (tick >= tickOn + tickOff) {
				tick = 1;
				repeatNumber --;
				if (repeatNumber == 0) isRinging = false;
			}
			else tick++;
		}
		
		void getAlarmTime () {
			alarm.data = *(volatile uint32_t*)0x00007C00;
			savedHour = alarm.hour;
			savedMinute = alarm.minute;
		}
		
		void saveAlarmTime () {
			//__disable_irq ();
			flash ->chooseAddress (0x00007C00);
			
			flash ->chooseEraseMode ();
			flash ->startModify ();
			while (flash ->getBusyStatus ());
			
			flash ->chooseProgramMode ();
			flash ->setData (alarm.data);
			flash ->startModify ();
			while (flash ->getBusyStatus ());
			
			savedHour = alarm.hour;
			savedMinute = alarm.minute;
			//__enable_irq ();
		}
		
		uint8_t getSavedHour () {
			return savedHour;
		}
		
		uint8_t getSavedMinute () {
			return savedMinute;
		}	
};