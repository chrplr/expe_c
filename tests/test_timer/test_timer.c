/*
 *  wait several times for a fixed of time, and print the stats of the durations
 */

#include <stdio.h>
#include "precision_time.h"
#include "statistics.h"

#define WAITTIME 16.0
#define NREPETITIONS  5000


void test_delay(double target, unsigned int nrepetitions)
{
  double time1, time2;
  double results[nrepetitions];
  double diff = 0.0;

  for (int i = 0; i < nrepetitions; i++) {
    fprintf(stderr, "\r%d : %lf", i, diff);
    fflush(stdout);
    time1 = wall_clock_in_ms();
    delay_in_ms(target);
    time2 = wall_clock_in_ms();
    results[i] = diff = time2 - time1;
  }

  printf("\n");

  double min, max, mean, stdev;
  descriptive_stats(results, NREPETITIONS, &min, &max, &mean,& stdev);
  printf("mean=%.2lf SD=%lf min=%lf, max=%lf\n", mean, stdev, min, max);
}


int main()
{
  test_delay(WAITTIME, NREPETITIONS);
  return 0;
}
