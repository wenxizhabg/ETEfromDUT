#pragma once
#include <SN32F400.h>

class Flash {
	public:
		bool getBusyStatus () {
			return bool (SN_FLASH ->STATUS_b .BUSY);
		}
		
		void enableModifyLastPage () {
			SN_FLASH ->WP_b .WP = 0x5AFA;
		}
		
		void disableModifyLastPage () {
			SN_FLASH ->WP_b .WP = 0x0;
		}
			
		void chooseEraseMode () {
			SN_FLASH ->CTRL_b.PER = 1;
		}
		
		void chooseProgramMode () {
			SN_FLASH ->CTRL_b .PG = 1;
		}
		
		void chooseAddress (uint32_t address) {
			SN_FLASH ->ADDR_b. ADDR = address;
		}
		
		void setData (uint32_t data) {
			SN_FLASH ->DATA_b .DATA = data;
		}
		
		void startModify () {
			SN_FLASH ->CTRL_b .START = 1;
		}		
		
};