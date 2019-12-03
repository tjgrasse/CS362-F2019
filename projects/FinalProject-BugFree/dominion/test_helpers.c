/*
 * Name:        test_helpers.c
 * Description: Contains the helper functions necessary to run the unit tests.
 */

#include <stdio.h>
#include <string.h>
#include "test_helpers.h"

/*
 * \name    - testAssert
 * \brief   - Processes assert like functionality without killing the program
 * \param   - const char* name - string to list when describing the function
 * \param   - int firstValue - first value of the comparison
 * \param   - int secondValue - second value of the comparison
 * \return  - 0 on successful comparison, -1 on error or invalid comparison
 */
int testAssert(const char* name, int firstValue, int secondValue)
{
    int retVal = -1;

    if (firstValue == secondValue)
    {
        printf("\t%s PASSED\n", name);
        retVal = 0;
    }
    else
    {
        printf("\t%s FAILED\n", name);
    }

    return retVal;
} 