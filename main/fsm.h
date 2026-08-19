#pragma once
#include "Led7Seg.h"
#include "Ticker.h"
#include "Clock.h"
#include "Alarm.h"
#include "Button.h"
#include "Buzzer.h"

#define _IDLE 0
#define _EDIT_CLOCK_MINUTE 1
#define _EDIT_CLOCK_HOUR 2
#define _EDIT_ALARM_MINUTE 3
#define _EDIT_ALARM_HOUR 4

class FSM {
	private:
		Ticker* ticker;
		Clock* clock;
		Alarm* alarm;
		Led7Seg* led7Seg;
		Button* button;
		Buzzer* buzzer;
	
		uint8_t state = _IDLE;
		bool toggleBit = true;
	public:
		FSM (Ticker* ticker, Clock* clock, Alarm* alarm, Led7Seg* led7Seg, Button* button, Buzzer* buzzer) {
			this ->ticker = ticker;
			this ->clock = clock;
			this ->alarm = alarm;
			this ->led7Seg = led7Seg;
			this ->button = button;
			this ->buzzer = buzzer;
		}
		
		void changeFromIdleToEditClockHour () {
			state = _EDIT_CLOCK_HOUR;
			clock ->turnOff ();
			led7Seg ->setMinute (clock ->getMinute());
			led7Seg ->setDot (0);
			ticker ->setTimer1 (7500);
			ticker ->setTimer2 (125);
		}
		void changeFromEditClockHourToMinute () {
			state = _EDIT_CLOCK_MINUTE;
			led7Seg ->setHour (clock ->getHour());
			ticker ->setTimer1 (7500);
			ticker ->setTimer2 (125);
		}
		void changeFromEditClockToIdle () {
			state = _IDLE;
			led7Seg -> setHour (clock ->getHour());
			led7Seg -> setMinute (clock ->getMinute());
			clock ->resetTickAndSecond ();
			clock ->turnOn ();
			alarm ->setupRing(75, 0, 1);
		}
		
		void changeFromIdleToEditAlarmHour () {
			state = _EDIT_ALARM_HOUR;
			led7Seg ->setMinute (alarm ->getMinute());
			led7Seg ->setDot (0);
			ticker ->setTimer1 (7500);
			ticker ->setTimer2 (125);
		}
		void changeFromEditAlarmHourtoMinute () {
			state = _EDIT_ALARM_MINUTE;
			led7Seg ->setHour (alarm ->getHour());
			ticker ->setTimer1 (7500);
			ticker ->setTimer2 (125);
		}
		void changeFromEditAlarmToIdle () {
			state = _IDLE;
			alarm ->turnLedOff ();
			led7Seg -> setHour (clock ->getHour());
			led7Seg -> setMinute (clock ->getMinute());
			buzzer ->enable();
			alarm ->setupRing(75, 0, 1);
		}
		
		
		void updateTick () {
			ticker ->updateTimer ();
			clock ->updateTick ();
			alarm ->updateTick ();
			switch (state) {
				case _IDLE:
					if (clock ->getUpdateFlag() == true) {
						uint8_t hour = clock ->getHour ();
						uint8_t minute = clock ->getMinute ();
						
						led7Seg ->setHour (hour);
						led7Seg ->setMinute (minute);
						
						if (alarm ->getHour() == hour) 
						if (alarm -> getMinute () == minute) alarm ->setupRing (125, 125, 5);
							
						clock ->clearUpdateFlag ();
					}
					
					if (clock ->getTick() < 125) led7Seg ->setDot (true);
					else led7Seg ->setDot (false);
				break;
				
				case _EDIT_CLOCK_HOUR:
					if (ticker ->timer1IsFinish) changeFromEditClockToIdle ();
					if (ticker ->timer2IsFinish) {
						toggleBit = !toggleBit;
						ticker ->setTimer2 (125);
					}
					
					if (toggleBit) led7Seg ->setHour (clock ->getHour());
					else led7Seg -> setHour (100);
					
				break;
				
				case _EDIT_CLOCK_MINUTE:
					if (ticker ->timer1IsFinish) changeFromEditClockToIdle ();
					if (ticker ->timer2IsFinish) {
						toggleBit = !toggleBit;
						ticker ->setTimer2 (125);
					}
					
					if (toggleBit) led7Seg ->setMinute (clock ->getMinute());
					else led7Seg -> setMinute (100);
				break;
				
				case _EDIT_ALARM_HOUR:
					if (ticker ->timer1IsFinish) changeFromEditAlarmToIdle();
					if (ticker ->timer2IsFinish) {
						toggleBit = !toggleBit;
						ticker ->setTimer2 (125);
					}
					
					if (toggleBit) {
						led7Seg ->setHour (alarm ->getHour());
						alarm ->turnLedOff ();
					}
					else {
						led7Seg ->setHour (100);
						alarm ->turnLedOn ();
					}
					
				break;
				
				case _EDIT_ALARM_MINUTE:
					if (ticker ->timer1IsFinish) changeFromEditAlarmToIdle();
					if (ticker ->timer2IsFinish) {
						toggleBit = !toggleBit;
						ticker ->setTimer2 (125);
					}
					
					if (toggleBit) {
						led7Seg ->setMinute (alarm ->getMinute ());
						alarm ->turnLedOff ();
					}
					else {
						led7Seg -> setMinute (100);
						alarm ->turnLedOn ();
					}
				break;
					
			}
			if (alarm->isRinging) buzzer ->enable ();
			else buzzer ->disable ();
			led7Seg ->refreshLed ();	
		}
		
		void updateState () {
			uint8_t sw = button ->checkButton();
			if (sw == 0) return;
			
			alarm ->setupRing(75, 0, 1);
			
			switch (state) {
				case _IDLE:
					if (sw == 3) changeFromIdleToEditClockHour ();
					else if (sw ==16) changeFromIdleToEditAlarmHour ();
				break;
				
				case _EDIT_CLOCK_HOUR:
					if (sw == 3) changeFromEditClockHourToMinute ();
					else if (sw == 6) clock ->increaseHour ();						
					else if (sw == 10) clock ->decreaseHour ();
						
				break;
				
				case _EDIT_CLOCK_MINUTE:
					if (sw == 3) changeFromEditClockToIdle ();
					else if (sw == 6) clock ->increaseMinute ();						
					else if (sw == 10) clock ->decreaseMinute ();
				break;
				
				case _EDIT_ALARM_HOUR:
					if (sw == 16) changeFromEditAlarmHourtoMinute ();
					else if (sw == 6) alarm ->increaseHour ();						
					else if (sw == 10) alarm ->decreaseHour ();
				break;
				
				case _EDIT_ALARM_MINUTE:
					if (sw == 16) {
						changeFromEditAlarmToIdle ();
						if (alarm ->getHour () != alarm ->getSavedHour () || alarm ->getMinute () != alarm ->getSavedMinute ()) {
							alarm ->saveAlarmTime ();
							alarm ->setupRing (25, 25, 3);
						}				
					}
					else if (sw == 6) alarm ->increaseMinute ();						
					else if (sw == 10) alarm ->decreaseMinute ();
				break;
			}
		}
};
			