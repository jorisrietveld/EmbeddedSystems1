/**
 * Author: Joris Rietveld <jorisrietveld@gmail.com>
 * Created: 12-09-2017 00:34
 * Licence: GPLv3 - General Public Licence version 3
 *
 * Experimental file to try using some object oriented design patterns
 * using plain C... Not because I am trying to create an more efficient
 * version of C++ or do I think this is way more elegant, just to learn
 * more about the inner workings of object oriented design.
 */
#include <stdio.h>

/***********************************************************************************************************************
 * Segment Display class.
 ***********************************************************************************************************************
 * To inherit from the sSegmentClass you have to create an constructor that
 * ties the classes methods to the function pointers.
 */
typedef struct sSegmentClass
{
    int (*write)(struct sSegmentClass *self, int * displayData );
    int (*getSegType)(struct sSegmentClass *self, char* segType );

    const char type[255];
} tSegmentClass;

/***********************************************************************************************************************
 * Decimal Segment Display "Class"
 ***********************************************************************************************************************
 */

/**
 * Write method for the Decimal se
 * @param decimalInstance
 * @param displayData
 * @return
 */
static int decimalWriteSeg (sSegmentClass *decimalInstance, int * displayData)
{
    printf ("This is an %s display that is about to write %s to the segment displays", decimalDisplay );
    return 0;
}

// Method for the decimal segment display 'class'. /////////////////////////////////////////////////////////////////////
static char * getSegType( sSegmentClass *decimalInstance, char* segType )
{
    return segType;
}

static int decimalDisplayInit (sSegmentClass *decimalInstance)
{
    decimalInstance->type = "decimal";
    decimalInstance->getSegType = &getSegType;
    decimalInstance->write = &decimalWriteSeg;
    return 0;
}

// Function for the HTTP 'class'.
static int hexadecimalWrite (sSegmentClass *hexadecimalInstance, char *fspec)
{
    printf ("Opening HTTP: %s\n", fspec);
    return 0;
}

static int hexadecimalInit (sSegmentClass *hexadecimalInstance)
{
    http->open = &httpOpen;
    return 0;
}
// Test program.
int main (void) {
    int status;
    tCommClass commTcp, commHttp;

    // Same 'base' class but initialised to different sub-classes.

    tcpInit (&commTcp);
    httpInit (&commHttp);

    // Called in exactly the same manner.

    status = (commTcp.open)(&commTcp, "bigiron.box.com:5000");
    status = (commHttp.open)(&commHttp, "http://www.microsoft.com");

    return 0;
}