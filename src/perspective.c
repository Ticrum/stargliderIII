
#include <starglider.h>

t_bunny_position std_perspective(float x,
				 float y,
				 float z)
{
  t_bunny_position pos;

  if (z < -999)
    z = -999;
  if (fabs(z) < 0.00001)
    return (std_perspective(x, y, z > 0 ? 0.0001 : -0.0001));
  if (z > 0.11)
    pos.x = x * (1000.0 / (z + 1000.0));
  else
    pos.x = x * (1000.0 / (z + 1000.0));
  if (z > 0.11)
    pos.y = y * (1000.0 / (z + 1000.0));
  else
    pos.y = y * (1000.0 / (z + 1000.0));
  return (pos);
}


