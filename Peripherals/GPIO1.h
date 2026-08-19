#pragma once
#include <SN32F400.h>

class GPIO1 {
    public:
        void setOutputAtPin (int pin) {
			 SN_GPIO1->MODE |= (1 << pin);
		}
		
		void setOutputAtOnce (int pinsCode) {
			SN_GPIO1->MODE |= pinsCode;
		}
		
		void setInputAtPin (int pin) {
            SN_GPIO1->MODE &= ~(1 << pin);
        }
		
		void setInputAtOnce (int pinsCode) {
			SN_GPIO1->MODE &= ~pinsCode;
		}
		
		void setDataOutAtPin (int pin) {
			SN_GPIO1->BSET |= (1 << pin);
		}
		
		void setDataOutAtOnce (int pinsCode) {
			SN_GPIO1->BSET |= pinsCode;
		}
		
		void clearDataOutAtPin (int pin) {
			SN_GPIO1->BCLR |= (1 << pin);
		}
		
		void clearDataOutAtOnce (int pinsCode) {
			SN_GPIO1->BCLR |= pinsCode;
		}
		
		int getDataInAtPin (int pin) {
			return (SN_GPIO1->DATA >> pin) & 1;
		}
};