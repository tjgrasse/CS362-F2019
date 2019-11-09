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
 * \param   - enum assertType type - type of comparison used for the values
 * \return  - 0 on successful comparison, -1 on error or invalid comparison
 */
int testAssert(const char* name, int firstValue, int secondValue, enum assertType type)
{
    int retVal = -1;

    switch(type)
    {
        case GREATER_THAN:
        {
            printf("\t%s %d > %d\n", name, firstValue, secondValue);
            if (firstValue > secondValue)
            {
                retVal = 0;
            }
            break;
        }
        case GREATER_THAN_EQUAL:
        {
            printf("\t%s %d >= %d\n", name, firstValue, secondValue);
            if (firstValue >= secondValue)
            {
                retVal = 0;
            }
            break;
        }
        case EQUAL:
        {
            printf("\t%s %d == %d\n", name, firstValue, secondValue);
            if (firstValue == secondValue)
            {
                retVal = 0;
            }
            break;
        }
        case LESS_THAN:
        {
            printf("\t%s %d < %d\n", name, firstValue, secondValue);
            if (firstValue < secondValue)
            {
                retVal = 0;
            }
            break;
        }
        case LESS_THAN_EQUAL:
        {
            printf("\t%s %d <= %d\n", name, firstValue, secondValue);
            if (firstValue <= secondValue)
            {
                retVal = 0;
            }
            break;
        }
        default:
        {
            // Invalid value returning -1
        }
    }

    if (retVal == 0)
    {
        printf("\t\tPASSED\n");
    }
    else
    {
        printf("\t\tFAILED\n");
    }
    

    return retVal;
}