
#include <starglider.h>

t_bunny_position std_decal(t_bunny_pixelarray	*pix,
			   t_bunny_position	pos)
{
  pos.x = pos.x + (pix->clipable.buffer.width / 2);
  pos.y = pos.y + (pix->clipable.buffer.height / 2);
  return (pos);
}

