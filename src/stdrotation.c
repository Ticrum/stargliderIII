
#include <starglider.h>

t_pos stdrotation(t_pos target,
		  t_pos rotation)
{
  t_pos old_point;

  old_point = target;

  target.x = old_point.x * cos(rotation.z) + old_point.y * -sin(rotation.z);
  target.y = old_point.x * sin(rotation.z) + old_point.y * cos(rotation.z);
  target.z = old_point.z;

  old_point = target;
  target.x = old_point.x * cos(rotation.y) + old_point.z * sin(rotation.y);
  target.z = old_point.x * -sin(rotation.y) + old_point.z * cos(rotation.y);
  target.y = old_point.y;

  old_point = target;
  target.y = old_point.y * cos(rotation.x) + old_point.z * -sin(rotation.x);
  target.z = old_point.y * sin(rotation.x) + old_point.z * cos(rotation.x);
  target.x = old_point.x;
  return (target);
}


