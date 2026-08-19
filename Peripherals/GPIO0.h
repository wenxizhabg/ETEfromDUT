#pragma once
#include <SN32F400.h>

class GPIO0 {
    public:
        void setOutputAtPin (int pin) {
			 SN_GPIO0->MODE |= (1 << pin);
		}
		
		void setOutputAtOnce (int pinsCode) {
			SN_GPIO0->MODE |= pinsCode;
		}
		
		void setInputAtPin (int pin) {
            SN_GPIO0->MODE &= ~(1 << pin);
        }
		
		void setInputAtOnce (int pinsCode) {
			SN_GPIO0->MODE &= ~pinsCode;
		}
		
		void setDataOutAtPin (int pin) {
			SN_GPIO0->BSET |= (1 << pin);
		}
		
		void setDataOutAtOnce (int pinsCode) {
			SN_GPIO0->BSET |= pinsCode;
		}
		
		void clearDataOutAtPin (int pin) {
			SN_GPIO0->BCLR |= (1 << pin);
		}
		
		void clearDataOutAtOnce (int pinsCode) {
			SN_GPIO0->BCLR |= pinsCode;
		}
		
		int getDataInAtPin (int pin) {
			return (SN_GPIO0->DATA >> pin) & 1;
		}
};
