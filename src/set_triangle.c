
#include <starglider.h>

static int triangle_in_screen(t_pos *pos)
{
  if (pos[0].z <= -999 || pos[1].z <= -999 || pos[2].z <= -999)
    return (0);
  return (1);
}

static int is_point_in_screen(t_bunny_position		*pos,
			      t_bunny_pixelarray	*pix)
{
  int compt;
  int w;
  int h;

  compt = 0;
  w = pix->clipable.buffer.width;
  h = pix->clipable.buffer.height;
  if (pos[0].y > 0 && pos[0].y < h && pos[0].x < w && pos[0].x > 0)
    compt = compt + 1;
  if (pos[1].y > 0 && pos[1].y < h && pos[1].x < w && pos[1].x > 0)
    compt = compt + 1;
  if (pos[2].y > 0 && pos[2].y < h && pos[2].x < w && pos[2].x > 0)
    compt = compt + 1;
  return (compt);
}

static void sort_pos(t_bunny_position *pos)
{
  t_bunny_position cash;

  if (pos[0].y > pos[1].y)
    {
      cash = pos[0];
      pos[0] = pos[1];
      pos[1] = cash;
    }
  if (pos[1].y > pos[2].y)
    {
      cash = pos[1];
      pos[1] = pos[2];
      pos[2] = cash;
    }
  if (pos[0].y > pos[1].y)
    {
      cash = pos[0];
      pos[0] = pos[1];
      pos[1] = cash;
    }
  if (pos[1].y > pos[2].y)
    {
      cash = pos[1];
      pos[1] = pos[2];
      pos[2] = cash;
    }
}

static void fill_triangle(t_bunny_pixelarray	*pix,
			  t_bunny_position    	*posi,
			  unsigned int		*color)
{
  t_bunny_position temppos[2];
  double compt[2];
  double ratio2[2];
  double up[2];

  sort_pos(posi);
  posi[3] = posi[2];
  posi[2].x = posi[0].x + ((posi[2].x - posi[0].x) * std_get_ratio(posi[2].y, posi[0].y, posi[1].y));
  posi[2].y = posi[1].y;
  compt[0] = posi[0].y;
  compt[1] = posi[3].y;
  up[0] = 1.0 / (posi[1].y - posi[0].y);
  up[1] = 1.0 / (posi[3].y - posi[1].y);
  ratio2[0] = 0;
  ratio2[1] = 0;
  while (compt[0] <= posi[1].y || compt[1] >= posi[1].y)
    {
      if (compt[0] <= posi[1].y)
	{
	  temppos[0].x = std_get_value(ratio2[0], posi[0].x, posi[1].x);
	  temppos[0].y = compt[0];
	  temppos[1].x = std_get_value(ratio2[0], posi[0].x, posi[2].x);
	  temppos[1].y = compt[0];
	  std_set_line(pix, temppos, color);
	}
      if (compt[1] >= posi[1].y)
	{
	  temppos[0].x = std_get_value(ratio2[1], posi[3].x, posi[1].x);
	  temppos[0].y = compt[1];
	  temppos[1].x = std_get_value(ratio2[1], posi[3].x, posi[2].x);
	  temppos[1].y = compt[1];
	  std_set_line(pix, temppos, color);
	}
      ratio2[0] = ratio2[0] + up[0];
      ratio2[1] = ratio2[1] + up[1];
      compt[0] = compt[0] + 1;
      compt[1] = compt[1] - 1;
    }
}

void std_set_triangle(t_bunny_pixelarray	*pix,
		      t_pos			*pos,
		      unsigned int		*color,
		      t_bunny_position		*exept,
		      int			*empin,
		      int			recur)
{
  t_bunny_position posi[5];
  //t_bunny_position recurpos[3];
  int emp[2];

  if (triangle_in_screen(pos) == 1)
    {
      posi[0] = std_decal(pix, std_perspective(pos[0].x, pos[0].y, pos[0].z));
      posi[1] = std_decal(pix, std_perspective(pos[1].x, pos[1].y, pos[1].z));
      posi[2] = std_decal(pix, std_perspective(pos[2].x, pos[2].y, pos[2].z));
      if (recur == 1)
	{
	  posi[empin[1]] = exept[1];
	  posi[empin[0]] = exept[0];
	}
      if (is_point_in_screen(posi, pix) != 0)
	{
	  //printf("1 %d %d 2 %d %d 3 %d %d\n", posi[0].x, posi[0].y, posi[1].x, posi[1].y, posi[2].x, posi[2].y);
	  if (is_point_in_screen(posi, pix) == 2)// && recur == 0)
	    {
	      posi[4] = reduce_pos(posi, pix, emp);
	      posi[3] = posi[emp[1]];
	      //printf("exept %d %d emp %d // exept %d %d emp %d\n", posi[3].x, posi[3].y, emp[0], posi[4].x, posi[4].y, emp[1]);
	      std_set_triangle(pix, pos, color, &posi[3], emp, 1);
	    }
	  else if (is_point_in_screen(posi, pix) != 3)
	    reduce_pos(posi, pix, emp);
	  //printf("print 1 %d %d 2 %d %d 3 %d %d\n", posi[0].x, posi[0].y, posi[1].x, posi[1].y, posi[2].x, posi[2].y);
	  posi[3] = posi[0];
	  std_set_line(pix, &posi[0], color);
	  std_set_line(pix, &posi[1], color);
	  std_set_line(pix, &posi[2], color);
	  fill_triangle(pix, posi, color);
	}
    }
}


