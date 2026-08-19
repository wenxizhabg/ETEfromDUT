#pragma once
#include <SN32F400.h>

class CT16B0 {
	public:
		void setPrescaler (uint8_t prescaler) {
			SN_CT16B0->PRE_b.PRE = prescaler;
		}
		
		void setMatch0Value (uint16_t match0Value) {
			SN_CT16B0->MR0_b.MR = match0Value;
		}
		
		void setEnableResetWhenMatch0 () {
			SN_CT16B0->MCTRL_b.MR0RST = 1;
		}
		
		void setEnableResetWhenMatch1 () {
			SN_CT16B0->MCTRL_b.MR1RST = 1;
		}
		
		void setPWM0Mode2 () {
			SN_CT16B0->PWMCTRL_b.PWM0MODE = 1;
		}
			
		void setPWM0Output (bool en = true) {
			SN_CT16B0->PWMCTRL_b.PWM0IOEN = en;
		}
		
		void setPWM0Enable () {
			SN_CT16B0->PWMCTRL_b.PWM0EN = 1;
		}
		
		void setPWM0Disable () {
			SN_CT16B0->PWMCTRL_b.PWM0EN = 0;
		}
		
		void setMatch1Value (uint16_t match1Value) {
			SN_CT16B0->MR1_b.MR = match1Value;
		}
		
		
		void enableCounter () {
			SN_CT16B0->TMRCTRL_b.CEN = 1;
		}
		
		void disableCounter () {
			SN_CT16B0->TMRCTRL_b.CEN = 0;
		}
		
};