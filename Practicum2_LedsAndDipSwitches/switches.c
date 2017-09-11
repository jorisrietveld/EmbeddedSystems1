/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 05:26
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "switches.h"

#define LED_INTERVAL_DELAY 50

/**
 * Test if an certain switch is active by testing pins D input bit.
 * @param switchNumber The number of the D input port.
 * @return Is this switch activated?
 */
uint8_t isSwitchActive( uint8_t switchNumber )
{
    return !( PIND & ( 1 << switchNumber ));
}

/**
 * Test all switches and return 1 if there are more than one active switches.
 * @return boolean Is there more than one switch on?
 */
uint8_t multipleSwitchesActive()
{
    return ( isSwitchActive( 7 ) + isSwitchActive( 6 ) + isSwitchActive( 5 ) + isSwitchActive( 4 ) > 1 );
}

/**
 * Listen for state changes in the connected dip switches.
 */
void readSwitches()
{
    if ( multipleSwitchesActive()) // To many switches SOS
    {
        void blinkSOS(); // Blink an SOS signal.
    }
    else if ( isSwitchActive( 4 )) // The dip switch on the left is active.
    {
        ledScanLeft( LED_INTERVAL_DELAY, 1 );
    }

    else if ( isSwitchActive( 5 )) // The second dip switch on the left  is active.
    {
        ledScanRight( LED_INTERVAL_DELAY, 1 );
    }
    else if ( isSwitchActive( 6 )) // The first dip switch on the right  is active.
    {
        ledScan( LED_INTERVAL_DELAY, 1, 1 );
    }
    else if ( isSwitchActive( 7 )) // The most right dip switch is active.
    {
        ledExpand( LED_INTERVAL_DELAY );
        slideOut( LED_INTERVAL_DELAY, 1 );
        slideScan( LED_INTERVAL_DELAY, 1 );
        ledBlink( LED_INTERVAL_DELAY, 1 );
        ledScanLeft( LED_INTERVAL_DELAY, 1 );
        ledScanRight( LED_INTERVAL_DELAY, 1 );
        ledScan( LED_INTERVAL_DELAY, 1, 0 );
        ledSlide( LED_INTERVAL_DELAY, 1 );
    }
    else // When no dip switch is activated.
    {
        PORTC = 0xFF;
    }
}