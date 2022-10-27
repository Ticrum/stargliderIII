
#include <starglider.h>

void std_set_zpixel(t_bunny_pixelarray	*px,
                    float               *zbuffer,
                    t_pos               pos,
                    unsigned int	color)
{
  int *copy;
  int w;
  int h;
  int coord;

  w = px->clipable.buffer.width;
  h = px->clipable.buffer.height;
  copy = px->pixels;
  coord = (int)pos.x + (int)pos.y * w;
  if (pos.y > 0 && pos.y < h && pos.x < w && pos.x > 0)
  {
      if (pos.z < zbuffer[coord])
      {
          copy[coord] = color;
          zbuffer[coord] = pos.z;
      }
  }
}

