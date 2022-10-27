
#include <starglider.h>

t_pos find_zpos(t_pos                   *pos,
                t_bunny_pixelarray	*pix,
                int			*in,
                int			start,
                int			end)
{
  t_pos po[2];
  t_pos posi[2];
  int dist[2];

  if (in[start] == 1)
    {
      posi[0] = pos[start];
      posi[1] = pos[end];
    }
  else
    {
      posi[0] = pos[end];
      posi[1] = pos[start];
    }
  po[0].x = 10000;
  po[0].y = 10000;
  if (posi[1].y <= 0)
  {
      po[0].x = std_get_value(std_get_ratio(posi[1].y, posi[0].y, 0), posi[0].x, posi[1].x);
      po[0].z = std_get_value(std_get_ratio(posi[1].y, posi[0].y, 0), posi[0].z, posi[1].z);
      po[0].y = 0;
  }
  if (posi[1].y >= pix->clipable.buffer.height)
  {
      po[0].x = std_get_value(std_get_ratio(posi[1].y, posi[0].y, pix->clipable.buffer.height), posi[0].x, posi[1].x);
      po[0].z = std_get_value(std_get_ratio(posi[1].y, posi[0].y, pix->clipable.buffer.height), posi[0].z, posi[1].z);
      po[0].y = pix->clipable.buffer.height;
  }
  po[1].x = 10000;
  po[1].y = 10000;
  if (posi[1].x <= 0)
  {
      po[1].y = std_get_value(std_get_ratio(posi[1].x, posi[0].x, 0), posi[0].y, posi[1].y);
      po[1].z = std_get_value(std_get_ratio(posi[1].x, posi[0].x, 0), posi[0].z, posi[1].z);
      po[1].x = 0;
  }
  if (posi[1].x >= pix->clipable.buffer.width)
  {
      po[1].y = std_get_value(std_get_ratio(posi[1].x, posi[0].x, pix->clipable.buffer.width), posi[0].y, posi[1].y);
      po[1].z = std_get_value(std_get_ratio(posi[1].x, posi[0].x, pix->clipable.buffer.width), posi[0].z, posi[1].z);
      po[1].x = pix->clipable.buffer.width;
  }
  dist[0] = (std_abs(po[0].x - posi[0].x) * std_abs(po[0].x - posi[0].x)) + (std_abs(po[0].y - posi[0].y) * std_abs(po[0].y - posi[0].y));
  dist[1] = (std_abs(po[1].x - posi[0].x) * std_abs(po[1].x - posi[0].x)) + (std_abs(po[1].y - posi[0].y) * std_abs(po[1].y - posi[0].y));
  if (dist[0] > dist[1])
    po[0] = po[1];
  return (po[0]);
}
