
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"



const nrfx_timer_t TIMER_LED = NRFX_TIMER_INSTANCE(0); // Timer 0 Enabled
uint32_t count=0; // Declared count variable to count the every 509ms

void timer0_handler(nrf_timer_event_t event_type, void* p_context)
{
  switch(event_type)
  {
      case NRF_TIMER_EVENT_COMPARE0:

      count+=1;//count will increase for every 509ms

      break;



      default:
      // Nothing
      break;
    
  }
    

}

void timer_init(uint32_t time)
{
  uint32_t err_code = NRF_SUCCESS;// create a error code to check the error by storing the NRF_SUCCESS

  uint32_t time_ms = time;//get the desired time delay

  uint32_t time_ticks;


  nrfx_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG; // Configure the timer instance to default settings


  err_code = nrfx_timer_init(&TIMER_LED, &timer_cfg, timer0_handler); // Initialize the timer0 with default settings
  APP_ERROR_CHECK(err_code); // check if any error occured


  time_ticks = nrfx_timer_ms_to_ticks(&TIMER_LED, time_ms); // convert ms to ticks

// Assign a channel, pass the number of ticks & enable interrupt
  nrfx_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

}

int main(void)
{
    timer_init(509);// pass the time in ms 

    nrfx_timer_enable(&TIMER_LED);// Enable the timer

    while (1)
    {
         printf("Count value: %d \r\n",count);//For every 509ms count value will increament
    }
}

/** @} */
