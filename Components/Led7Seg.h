#pragma once
#include <SN32F400.h>
#include "GPIO0.h"
#include "GPIO1.h"

class Led7Seg {
    private:
        GPIO0* gpio0;
        GPIO1* gpio1;
    
        int hour1, hour0, minute1, minute0;
        bool dot;
        int positionLight;
        
        uint8_t charCode [12]  = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 0, 128};
    public:
        Led7Seg (GPIO0* gpio0, GPIO1* gpio1) {
            this ->gpio0 = gpio0;
            this ->gpio1 = gpio1;
            
			positionLight = 0;
            hour1 = 1;
			hour0 = 10;
			minute1 = 1;
			minute0 = 10;
			dot = 1;
			
        }
		
		void setup() {
			gpio0 ->setOutputAtOnce (0b11111111);
            gpio1 ->setOutputAtOnce (0b1111 << 9);
		}
		
		void setDot (bool dot) {
			this ->dot = dot;
		}
		
        void setHour (uint8_t hour) {
			if (hour < 100) {
				this ->hour1 = hour/10;
				this ->hour0 = hour%10;
			}
			else {
				this ->hour1 = 10;
				this ->hour0 = 10;
			}
		}
		
		void setMinute (uint8_t minute) {
			if (minute < 100) {
				this ->minute1 = minute/10;
				this ->minute0 = minute%10;
			}
			else {
				this ->minute1 = 10;
				this ->minute0 = 10;
			}
        }

		
		void refreshLed () {
            gpio0 ->clearDataOutAtOnce (0b11111111);
            gpio1 ->clearDataOutAtOnce (0b1111<<9);
            
            switch (positionLight) {
                case 0:
                    gpio0 ->setDataOutAtOnce (charCode[hour1]);
                    gpio1 ->setDataOutAtPin (9);
                    positionLight = 1;
                    break;  
                case 1:
                    gpio0 ->setDataOutAtOnce (charCode[hour0]);
                    gpio1 ->setDataOutAtPin (10);
                    positionLight = 2;
                    break;
                case 2:
                    if (dot) {
                        gpio0 ->setDataOutAtOnce (charCode[11]);
                        gpio1 ->setDataOutAtPin (10);
                    }
                    positionLight = 3;
                    break;
                case 3:
                    gpio0 ->setDataOutAtOnce (charCode[minute1]);
                    gpio1 ->setDataOutAtPin (11);
                    positionLight = 4;
                    break;
                case 4:
                    gpio0 ->setDataOutAtOnce (charCode[minute0]);
                    gpio1 ->setDataOutAtPin (12);
                    positionLight = 0;
                    break;
                default: positionLight = 0;
            }
                
        }     


};
