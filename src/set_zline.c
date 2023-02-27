
#include <starglider.h>

void std_set_zline(t_bunny_pixelarray	*px,
                   float                *zbuffer,
                   t_pos                *pos,
                   unsigned int		*color)
{
  float up;
  t_pos posi;
  double ratio;
  float ecartx;
  float ecarty;

  int *copy;
  int w;
  int h;
  int coord;

  ecartx = pos[1].x - pos[0].x;
  ecarty = pos[1].y - pos[0].y;
  ratio = 0;
  if (std_abs(ecartx) > std_abs(ecarty))
      up = 1.0 / (double)ecartx;
  else
      up = 1.0 / (double)ecarty;
  if (up < 0)
      up = -up;

  //up = 1 / (float)(sqrt((std_abs(pos[1].x - pos[0].x) * std_abs(pos[1].x - pos[0].x)) + (std_abs(pos[1].y - pos[0].y) * std_abs(pos[1].y - pos[0].y))) + 5);
  while (ratio <= 1 && ratio >= 0)
    {
      posi.x = std_get_value(ratio, pos[0].x, pos[1].x);
      posi.y = std_get_value(ratio, pos[0].y, pos[1].y);
      posi.z = std_get_value(ratio, pos[0].z, pos[1].z);
      
      w = px->clipable.buffer.width;
      h = px->clipable.buffer.height;
      copy = px->pixels;
      coord = (int)posi.x + (int)posi.y * w;
      if (posi.y > 0 && posi.y < h && posi.x < w && posi.x > 0)
      {
          if (posi.z < zbuffer[coord])
          {
              copy[coord] = color[0];
              zbuffer[coord] = posi.z;
          }
      }
      
      //std_set_zpixel(px, zbuffer, posi, color[0]);
      ratio = ratio + up;
    }
}

