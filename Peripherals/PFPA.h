#pragma once
#include <SN32F400.h>

class PFPA {
	public:
		void setCT16B0_PWM0PinAs3_0 () {
			SN_PFPA->CT16B0_b.PWM0 = 1;
		}
};