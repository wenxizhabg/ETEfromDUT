#include "fsm.h"

FSM* fsm = nullptr;

int main () {
	SN_SYS0->EXRSTCTRL_b.RESETDIS = 0;
	SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;
	SN_SYS1->AHBCLKEN_b.CT16B0CLKEN = 1;
	
	
	GPIO0 gpio0;
	GPIO1 gpio1;
	GPIO2 gpio2;
	GPIO3 gpio3;
	CT16B0 ct16b0;
	CT16B1 ct16b1;
	PFPA pfpa;
	Flash flash;
	
	Ticker ticker (&ct16b1);
	Led7Seg led7Seg (&gpio0, &gpio1);
	Clock clock;
	Alarm alarm (&gpio3, &flash);
	Button button (&gpio1, &gpio2);
	Buzzer buzzer (&ct16b0, &pfpa);
	FSM fsm (&ticker, &clock, &alarm, &led7Seg, &button, &buzzer);
	::fsm = &fsm;
	
	ticker .setup ();
	led7Seg .setup ();
	clock .setup ();
	button .setup ();
	alarm .setLed ();
	buzzer .setup ();
	alarm .getAlarmTime();
	ticker .enable ();
	
	
	while (true) {
		__WFI ();		
	}
}

extern "C" {
	void CT16B1_IRQHandler () {
		fsm ->updateTick ();
		SN_CT16B1 ->IC_b.MR0IC = 1;  
	}
	
	void P2_IRQHandler () {
		fsm-> updateState ();
		SN_GPIO2 ->IC_b.IC10 = 1;		
	}
}
