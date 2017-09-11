/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 05:26
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "switches.h"

#define LED_INTERVAL_DELAY 50

uint8_t isSwitchActive(uint8_t switchNumber )
{
    return !(PIND & (1 << switchNumber));
}

uint8_t multipleSwitchesActive()
{
    return  ( isSwitchActive(7) + isSwitchActive(6) + isSwitchActive(5) + isSwitchActive(4) > 1 );
}

void readSwitches()
{
    while ( 1 )
    {
        if ( multipleSwitchesActive()) // To many switches SOS
        {
            ledBlink( LED_INTERVAL_DELAY, 1 );
        }
        else if ( isSwitchActive( 4 )) //
        {
            ledScanLeft( LED_INTERVAL_DELAY, 1 );
        }

        else if ( isSwitchActive( 5 ))
        {
            ledScanRight( LED_INTERVAL_DELAY, 1 );
        }
        else if ( isSwitchActive( 6 ))
        {
            ledScan( LED_INTERVAL_DELAY, 1, 1 );
        }
        else if ( isSwitchActive( 7 ))
        {
			ledExpand(LED_INTERVAL_DELAY);
            slideOut( LED_INTERVAL_DELAY, 1 );
			slideScan( LED_INTERVAL_DELAY, 1);
			ledBlink( LED_INTERVAL_DELAY, 1);
			ledScanLeft(LED_INTERVAL_DELAY, 1);
			ledScanRight(LED_INTERVAL_DELAY, 1);
			ledScan( LED_INTERVAL_DELAY, 1, 0 );
			ledSlide( LED_INTERVAL_DELAY,1 );
		}
		else
		{
			PORTC = 0xFF;
		}
	}
}