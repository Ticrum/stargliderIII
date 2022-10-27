
#include <starglider.h>

t_pos reduce_zpos(t_pos                 *pos,
                  t_bunny_pixelarray	*pix,
                  int			*place)
{
  t_pos po;
  t_pos save;

  int in[3];
  int w;
  int h;

  in[0] = 0;
  in[1] = 0;
  in[2] = 0;
  w = pix->clipable.buffer.width;
  h = pix->clipable.buffer.height;
  if (pos[0].y > 0 && pos[0].y < h && pos[0].x < w && pos[0].x > 0)
    in[0] = 1;
  if (pos[1].y > 0 && pos[1].y < h && pos[1].x < w && pos[1].x > 0)
    in[1] = 1;
  if (pos[2].y > 0 && pos[2].y < h && pos[2].x < w && pos[2].x > 0)
    in[2] = 1;

  if ((in[0] == 0 && in[1] == 1) || (in[0] == 1 && in[1] == 0))
    {
      po = find_zpos(pos, pix, in, 0, 1);
      if (in[0] == 0)
	{
	  save = pos[0];
	  place[1] = 0;
	  place[0] = 1;
	  pos[0] = po;
	  in[0] = 1;
	}
      else
	{
	  save = pos[1];
	  place[1] = 1;
	  place[0] = 0;
	  pos[1] = po;
	  in[1] = 1;
	}
    }
  else if ((in[1] == 0 && in[2] == 1) || (in[1] == 1 && in[2] == 0))
    {
      po = find_zpos(pos, pix, in, 1, 2);
      if (in[1] == 0)
	{
	  save = pos[1];
	  place[1] = 1;
	  place[0] = 2;
	  pos[1] = po;
	  in[1] = 1;
	}
      else
	{
	  save = pos[2];
	  place[1] = 2;
	  place[0] = 1;
	  pos[2] = po;
	  in[2] = 1;
	}
    }
  else if ((in[2] == 0 && in[0] == 1) || (in[2] == 1 && in[0] == 0))
    {
      po = find_zpos(pos, pix, in, 2, 0);
      if (in[2] == 0)
	{
	  save = pos[2];
	  place[1] = 2;
	  place[0] = 0;
	  pos[2] = po;
	  in[2] = 1;
	}
      else
	{
	  save = pos[0];
	  place[1] = 0;
	  place[0] = 2;
	  pos[0] = po;
	  in[0] = 1;
	}
    }
  return (save);
}


