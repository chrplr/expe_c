/* Basic functions to handle time */

#include "precision_time.h"

double wall_clock_in_ms()
{
        struct timespec time;
        if (clock_gettime(CLOCK_REALTIME, &time) == -1)
                return 0.0;
        return (double)(time.tv_sec) * 1E3 + time.tv_nsec / 1E6;
}

void delay_in_ms(double millisec)
{
        struct timespec interval;
        interval.tv_sec = (time_t) (millisec / 1E3);
        interval.tv_nsec = (long)((millisec * 1E6)) % 1000000000;
        clock_nanosleep(CLOCK_REALTIME, 0, &interval, NULL);
}
