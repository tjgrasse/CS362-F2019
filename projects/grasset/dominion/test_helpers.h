#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

// enum of different comparisons that can be done against the values in the 
// assert function
enum assertType 
{
    GREATER_THAN,
    GREATER_THAN_EQUAL,
    EQUAL,
    LESS_THAN,
    LESS_THAN_EQUAL
};

int testAssert(const char* name, int firstValue, int secondValue);

#endif 
