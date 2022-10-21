
#include <starglider.h>

void std_set_pixel(t_bunny_pixelarray	*px,
		   t_bunny_position	pos,
		   unsigned int		color)
{
  int *copy;
  int w;
  int h;
  int coord;

  w = px->clipable.buffer.width;
  h = px->clipable.buffer.height;
  copy = px->pixels;
  coord = pos.x + pos.y * w;
  if (pos.y >= 0 && pos.y <= h && pos.x <= w && pos.x >= 0)
    copy[coord] = color;
}

