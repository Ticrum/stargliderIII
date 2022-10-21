
#include <starglider.h>

double  std_get_value(double	ratio,
		      double	min,
		      double	max)
{
  return ((double)min + (ratio * (max - min)));
}

