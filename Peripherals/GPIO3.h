#pragma once
#include <SN32F400.h>

class GPIO3 {
    public:
        void setOutputAtPin (int pin) {
			 SN_GPIO3->MODE |= (1 << pin);
		}
		
		void setOutputAtOnce (int pinsCode) {
			SN_GPIO3->MODE |= pinsCode;
		}
		
		void setInputAtPin (int pin) {
            SN_GPIO3->MODE &= ~(1 << pin);
        }
		
		void setInputAtOnce (int pinsCode) {
			SN_GPIO3->MODE &= ~pinsCode;
		}
		
		void setDataOutAtPin (int pin) {
			SN_GPIO3->BSET |= (1 << pin);
		}
		
		void setDataOutAtOnce (int pinsCode) {
			SN_GPIO3->BSET |= pinsCode;
		}
		
		void clearDataOutAtPin (int pin) {
			SN_GPIO3->BCLR |= (1 << pin);
		}
		
		void clearDataOutAtOnce (int pinsCode) {
			SN_GPIO3->BCLR |= pinsCode;
		}
		
		int getDataInAtPin (int pin) {
			return (SN_GPIO3->DATA >> pin) & 1;
		}
		
		void setFallingEdgeTriggerOnPin (int pin) {
			SN_GPIO3->IEV |= (1 << pin);
		}
		
		void enableInterruptOnPin (int pin) {
			SN_GPIO3->IE |= (1 << pin);
		}
		
		void enableIQR () {
			NVIC_EnableIRQ (P3_IRQn);
		}
};