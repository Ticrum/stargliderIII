
#include <starglider.h>

void std_set_z_speed_line(t_bunny_pixelarray	*px,
                          float                *zbuffer,
                          t_pos                *pos,
                          unsigned int		*color)
{
    //float up;
  t_pos posi;
  //double ratio;
  float compt;

  //ratio = 0;
  if (pos[0].x > pos[1].x)
  {
      posi = pos[0];
      pos[0] = pos[1];
      pos[1] = posi;
  }
  compt = pos[0].x;
  //up = 1 / (float)(sqrt((std_abs(pos[1].x - pos[0].x) * std_abs(pos[1].x - pos[0].x)) + (std_abs(pos[1].y - pos[0].y) * std_abs(pos[1].y - pos[0].y))) + 5);
  while (compt < pos[1].x)//ratio <= 1 && ratio >= 0)
    {
        posi.x = compt;//std_get_value(ratio, pos[0].x, pos[1].x);
        posi.y = pos[0].y;//std_get_value(ratio, pos[0].y, pos[1].y);
        posi.z = std_get_value(std_get_ratio(pos[1].x, pos[0].x, compt), pos[0].z, pos[1].z);
        std_set_zpixel(px, zbuffer, posi, color[0]);
        compt = compt + 1;
        //ratio = ratio + up;
    }
}

