#include <stdio.h>
#include <stdalign.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "cubic_interp.h"


double get_dt(struct timeval start_time, struct timeval end_time)
{
  return ((double) (end_time.tv_usec - start_time.tv_usec) / 1000000 + (double) (end_time.tv_sec - start_time.tv_sec));
}


int main()
{
  size_t grid_x = 400;
  size_t grid_y = 400;

  srand(time(NULL));

  // Time data creation

  struct timeval start_time;
  struct timeval end_time;
  gettimeofday(&start_time, NULL);
  
  double *data = malloc(grid_x * grid_y * sizeof(double));
  
  for(size_t i = 0; i < grid_x * grid_y; i++)
  {
    data[i] = ((double) rand() / (double) RAND_MAX);
  }

  gettimeofday(&end_time, NULL);

  printf("Data creation time: %f seconds\n", get_dt(start_time, end_time));

  gettimeofday(&start_time, NULL);
  bicubic_interp *interp = bicubic_interp_init(data, grid_x, grid_y, -1, -1, 1, 1);
  gettimeofday(&end_time, NULL);
  printf("bicubic_interp_init execution time: %f seconds\n", get_dt(start_time, end_time));

  // Evaluate before freeing
  double accum_result = 0.0; // dummy variable so the compiler doesn't optimize away the bicubic_interp_eval loop
  size_t num_iterations = 0;
  gettimeofday(&start_time, NULL);
  for(double s = 0; s <= 100; s += 0.1)
  {
    for(double t = 0; t <= 100; t += 0.1)
    {
      const double result = bicubic_interp_eval(interp, s, t);
      accum_result += result;
      num_iterations++;
    }
  }
  gettimeofday(&end_time, NULL);

  printf("total result (dummy var): %f\n", accum_result);
  printf("num iterations: %lu\n", num_iterations);
  printf("Total bicubic_interp_eval time: %f\tAverage time for bicubic_interp_eval: %f\n", get_dt(start_time, end_time), get_dt(start_time, end_time) / num_iterations);




  bicubic_interp_free(interp);


  free(data);
  return 0;
}
