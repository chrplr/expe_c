#include "statistics.h"

void descriptive_stats(double vector[], unsigned int size, double *vmin, double *vmax, double *vmean, double *vstdev)
{
  assert(size > 0);

  double min = vector[0]; 
  double max = vector[0];
  double mean = 0.0;
  double sum = 0.0;
  double sumdev2 = 0.0;
  double stdev = 0.0;

  for (unsigned int i = 0; i < size; i++) sum += vector[i];
  mean = sum / size;

  for (unsigned int i = 0; i < size; i++) {
    double dev = (vector[i] - mean);
    sumdev2 += dev * dev;
    if (vector[i] < min)
      min = vector[i];
    if (vector[i] > max)
      max = vector[i];
  }
  stdev = sqrt(sumdev2 / size);

  *vmin = min;
  *vmax = max;
  *vmean = mean;
  *vstdev = stdev;
}
