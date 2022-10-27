
#include <starglider.h>

void std_set_zline(t_bunny_pixelarray	*px,
                   float                *zbuffer,
                   t_pos                *pos,
                   unsigned int		*color)
{
  float up;
  t_pos posi;
  double ratio;

  ratio = 0;
  up = 1 / (float)(sqrt((std_abs(pos[1].x - pos[0].x) * std_abs(pos[1].x - pos[0].x)) + (std_abs(pos[1].y - pos[0].y) * std_abs(pos[1].y - pos[0].y))) + 5);
  while (ratio <= 1 && ratio >= 0)
    {
      posi.x = std_get_value(ratio, pos[0].x, pos[1].x);
      posi.y = std_get_value(ratio, pos[0].y, pos[1].y);
      posi.z = std_get_value(ratio, pos[0].z, pos[1].z);
      std_set_zpixel(px, zbuffer, posi, color[0]);
      ratio = ratio + up;
    }
}

