/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 09-09-2017 05:26
 * Licence: GPLv3 - General Public Licence version 3
 */

#include "Switches.h"

#define LED_INTERVAL_DELAY 50

#ifndef SWITCH_PORTS
    #warning "SWITCH_PORTS was undifined, please configure what port your switches are connected to. using default PORTD"
    #define SWITCH_PORTS PIND
#endif
/**
 * Test if an certain switch is active by testing pins D input bit.
 * @param switchNumber The number of the D input port.
 * @return Is this switch activated?
 */
uint8_t isSwitchActive( uint8_t switchNumber )
{
    return !( SWITCH_PORTS & ( 1 << switchNumber ));
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
uint8_t readSwitches()
{
    if ( multipleSwitchesActive()) // To many switches SOS
    {
        return 0;
    }
    if ( isSwitchActive( 4 )) // Pulse count up reset at 9999
    {
        return 1;
    }
    else if ( isSwitchActive( 5 )) // Pulse count down reset at 0
    {
        return 2;
    }
    else if ( isSwitchActive( 6 )) // Pulse count up and down between 0 and 100.
    {
        return 3;
    }
    else if ( isSwitchActive( 7 )) // Pulse count up and down in different bases configurable using buttons.
    {
        return 4;
    }
    else // When no dip switch is activated.
    {
        return 0;
    }
}