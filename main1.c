This is the working code for button and RTC displayed on lcd. It includes main.c,button.c and Config_RTC_User.c.

#include "sfr.h"
#include "common.h"
#include "config.h"
#include "system.h"
#include "timer.h"
#include "watchdogtimer.h"
#include "panel.h"
#include "lcd_con.h"
#include "button.h"
#include <stdint.h>
#include <stdbool.h>

#include "r_cg_cgc.h"
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include "r_cg_rtc.h"
#include "r_cg_serial.h"
#include "Config_PORT.h"
#include "Config_RTC.h"
#include "r_cg_userdefine.h"

unsigned char 	modef 	= 0;		
unsigned char 	upf 	= 0;
unsigned char 	downf 	= 0;
unsigned char 	leftf 	= 0;
unsigned char 	rightf 	= 0;
unsigned char 	setf 	= 0;
//
unsigned char	ayear = 21;
unsigned char	amonth= 12;
unsigned char	aday  = 31;
unsigned char	ahour = 22;
unsigned char	amin  = 35;
unsigned char	asec  = 16;
//
int first = 1;
int second = 7;
//
int count = 0;
unsigned int LED_count;
unsigned int c_count;

unsigned char dpcnt[4];
//************************************************************************
//* Function Name: main
//* Description  : This function implements main function.?i???C?g?O?h?j
//* Arguments    : None
//* Return Value : None
//*************************************************************************
void main(void);
void main_loop(void);

void main(void) {
	
        /* Hardware Initiate */   
	hdwinit(); 	
	 
	/* Panel Initiate */
	panel_init0();	
	
	/*LCD Initiate */
	lcd_init();
	dispset_titl1(); 
	/*LCD display */
	// display1();	
	
	/* Main Loop */
	//main_loop();	      
          
         r_rtc_init_current_time();      
         R_Config_RTC_Start();      
       
         /* Setting for INTRTC. */
         /* Supplies input clock */
         RTCEN = 1U;
         /* Set INTRTC Low priority */
        RTCPR1 = 1U;
        RTCPR0 = 1U;
        /* Clear INTRTC interrupt flag */
        RTCIF = 0U;
         /* Enable INTRTC interrupt */
        RTCMK = 0U;           

        /* Wait an interrupt. */
        while (1U)
        {
            if (r_rtc_is_constperiod_flag_on())
            {
                RTCMK = 1U; 
		//
  		if (count == 2){
			r_rtc_display_current_time();
		}
		//
  		if (count == 3){
			clock_adj_disp();
		}
                 r_rtc_clear_constperiod_flag();
                RTCMK = 0U;
           }
                panel();		
		
		WDT_Reset();		
		
		dispset_count();
		
		op_switich_in();
		
	        op_switich_mdoef();
		
		op_switich_upf();
		
		op_switich_downf();
		
		op_switich_leftf();
		
		op_switich_rightf();
		
		op_switich_setf();
		
		if (LED_count++ > 70){
			P6 = P6 ^ 0x01;			//LED1 ”½“]
			LED_count = 0;
			c_count++;
			c_count %= 10000; 
			if (count == 1){
			       	set_cursor_position (1,12);
				lcd_2dout(c_count/100);
				lcd_2dout(c_count%100);
			}

		}
    }
}
