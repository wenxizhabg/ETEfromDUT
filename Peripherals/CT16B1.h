#pragma once
#include <SN32F400.h>

class CT16B1 {
	public:
		void setPrescaler (uint8_t prescaler) {
			SN_CT16B1->PRE_b.PRE = prescaler;
		}
		
		void setMatch0Value (uint16_t match0Value) {
			SN_CT16B1->MR0_b.MR = match0Value;
		}
		
		void enableInterruptWhenMatch0 () {
			SN_CT16B1->MCTRL_b.MR0IE = 1;
		}
		
		void enableResetWhenMatch0 () {
			SN_CT16B1->MCTRL_b.MR0RST = 1;
		}
		
		void setMatch1Value (uint16_t match1Value) {
			SN_CT16B1->MR1_b.MR = match1Value;
		}
		
		uint16_t getTimeCounterValue () {
			return SN_CT16B1->TC_b.TC;
		}
		
		void enableInterruptWhenMatch1 () {
			SN_CT16B1->MCTRL_b.MR1IE = 1;
		}
	
		void disableInterruptWhenMatch1 () {
			SN_CT16B1->MCTRL_b.MR1IE = 0;
		}
		
		void enableIQR () {
			NVIC_EnableIRQ (CT16B1_IRQn);
		}
		
		void enableCounter () {
			SN_CT16B1->TMRCTRL_b.CEN = 1;
		}
};