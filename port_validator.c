#include "port_validator.h"
#include <stddef.h>
/*
 * Temporary TDD stub:
 * This intentionally returns false for every input so that the first
 * test run exposes the missing behavior. Replace this body in the next step.
 */
bool is_valid_port_number(const char *input)
{
    unsigned int value = 0U;

    /* Reject a NULL pointer. */
    if (input == NULL) {
        return false;
    }

    /* Reject an empty string. */
    if (*input == '\0') {
        return false;
    }

    /* Check every character and convert it to a number. */
    while (*input != '\0') {

        /* Accept ASCII digits only. */
        if (*input < '0' || *input > '9') {
            return false;
        }

        unsigned int digit = (unsigned int)(*input - '0');

        /* Prevent overflow and reject values above 65535. */
        if (value > (65535U - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;

        ++input;
    }

    /* Valid port numbers are between 1 and 65535. */
    return (value >= 1U && value <= 65535U);
}
