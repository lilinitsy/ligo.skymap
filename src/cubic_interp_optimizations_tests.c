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


  // Evaluate before freeing

  bicubic_interp_free(interp);

  printf("bicubic_interp_init execution time: %f seconds\n", get_dt(start_time, end_time));


  free(data);
  return 0;
}
