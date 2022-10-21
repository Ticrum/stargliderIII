
#include <starglider.h>

t_pos move_player(t_pos pos,
		  t_pos angle,
		  char axe,
		  float step)
{
  t_pos newpos;
  t_pos target;
  t_pos old_point;

  /*
  if (axe == 'z')
    {
      newpos.z = pos.z + step * cos(angle.y);
      newpos.x = pos.x + step * sin(-angle.y);
      newpos.y = pos.y + step * sin(angle.z);
    }
  */
  newpos = pos;
  if (axe == 'x')
    newpos.x = newpos.x + step;
  else if (axe == 'y')
    newpos.y = newpos.y + step;
  else if (axe == 'z')
    newpos.z = newpos.z + step;
  //if (cos(angle.x) > 0.0 || cos(angle.y) < 0.0)
  //  angle.x = -angle.x;
  printf("%f %f %f\n", angle.x, angle.y, angle.z);
  angle.y = -angle.y;
  angle.x = -angle.x;
  /*
  target = newpos;
  old_point = target;
  target.x = old_point.x * cos(angle.z) + old_point.y * -sin(angle.z);
  target.y = old_point.x * sin(angle.z) + old_point.y * cos(angle.z);
  target.z = old_point.z;

  old_point = target;
  target.x = old_point.x * cos(angle.y) + old_point.z * sin(angle.y);
  target.z = old_point.x * -sin(angle.y) + old_point.z * cos(angle.y);
  target.y = old_point.y;

  old_point = target;
  target.y = old_point.y * cos(angle.x) + old_point.z * -sin(angle.x);
  target.z = old_point.y * sin(angle.x) + old_point.z * cos(angle.x);
  target.x = old_point.x;
  */
  newpos = stdtruerotation(newpos, angle, pos);
  return (newpos);
}



