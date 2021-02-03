#include "utils.h"
#include <inttypes.h>
#include <time.h>

uint64_t timestamp_us()
{
    struct timespec tms;

    if (clock_gettime(CLOCK_REALTIME, &tms)) {
        return 0;
    }

    uint64_t us = tms.tv_sec * 1000000;
    us += (tms.tv_nsec / 1000);

    return us;
}
