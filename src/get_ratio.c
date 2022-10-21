
#include <starglider.h>

double std_get_ratio(double max,
		     double min,
		     double curr)
{
  return ((double)(curr - min) / (max - min));
}

