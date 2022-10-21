
#include <starglider.h>

t_pos stdtruerotation(t_pos target,
		      t_pos rotation,
		      t_pos center)
{
  target.x = target.x - center.x;
  target.y = target.y - center.y;
  target.z = target.z - center.z;

  target = stdrotation(target, rotation);

  target.x = target.x + center.x;
  target.y = target.y + center.y;
  target.z = target.z + center.z;
  return (target);
}
