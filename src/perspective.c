
#include <starglider.h>

t_bunny_position std_perspective(float x,
				 float y,
				 float z,
                                 float foca)
{
  t_bunny_position pos;

  if (z < -foca + 1)
    z = -foca + 1;
  if (fabs(z) < 0.00001)
      return (std_perspective(x, y, z > 0 ? 0.0001 : -0.0001, foca));
  if (z > 0.11)
    pos.x = x * (foca / (z + foca));
  else
    pos.x = x * (foca / (z + foca));
  if (z > 0.11)
    pos.y = y * (foca / (z + foca));
  else
    pos.y = y * (foca / (z + foca));
  return (pos);
}


