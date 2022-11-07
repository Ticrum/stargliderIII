
#include <starglider.h>

static int triangle_in_screen(t_pos *pos)
{
    //printf("%f %f %f\n", pos[0].z, pos[1].z, pos[2].z);
  if (pos[0].z >= 6500 && pos[1].z >= 6500 && pos[2].z >= 6500)
    return (0);
  return (1);
}

static int is_point_in_screen(t_pos                     *pos,
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

static void sort_pos(t_pos *pos)
{
  t_pos cash;

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
                          float                 *zbuffer,
			  t_pos                 *posi,
			  unsigned int		*color)
{
  t_pos temppos[2];
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
          temppos[0].z = std_get_value(ratio2[0], posi[0].z, posi[1].z);
	  temppos[0].y = compt[0];
	  temppos[1].x = std_get_value(ratio2[0], posi[0].x, posi[2].x);
          temppos[1].z = std_get_value(ratio2[0], posi[0].z, posi[2].z);
	  temppos[1].y = compt[0];
	  std_set_z_speed_line(pix, zbuffer, temppos, color);
	}
      if (compt[1] >= posi[1].y)
	{
	  temppos[0].x = std_get_value(ratio2[1], posi[3].x, posi[1].x);
          temppos[0].z = std_get_value(ratio2[1], posi[3].z, posi[1].z);
	  temppos[0].y = compt[1];
	  temppos[1].x = std_get_value(ratio2[1], posi[3].x, posi[2].x);
          temppos[0].z = std_get_value(ratio2[1], posi[3].z, posi[2].z);
	  temppos[1].y = compt[1];
	  std_set_z_speed_line(pix, zbuffer, temppos, color);
	}
      ratio2[0] = ratio2[0] + up[0];
      ratio2[1] = ratio2[1] + up[1];
      compt[0] = compt[0] + 1;
      compt[1] = compt[1] - 1;
    }
}

void std_set_ztriangle(t_bunny_pixelarray	*pix,
                       float                    *zbuffer,
                       t_pos			*pos,
                       unsigned int		*color,
                       t_pos                    *exept,
                       int			*empin,
                       int			recur,
                       float                    foca)
{
  t_bunny_position posi[5];
  t_pos po[5];
  //t_bunny_position recurpos[3];
  int emp[2];
  int inscreen;

  if (triangle_in_screen(pos) == 1)
    {
        posi[0] = std_decal(pix, std_perspective(pos[0].x, pos[0].y, pos[0].z, foca));
        posi[1] = std_decal(pix, std_perspective(pos[1].x, pos[1].y, pos[1].z, foca));
        posi[2] = std_decal(pix, std_perspective(pos[2].x, pos[2].y, pos[2].z, foca));
        po[0].x = posi[0].x;
        po[0].y = posi[0].y;
        po[0].z = pos[0].z;
        po[1].x = posi[1].x;
        po[1].y = posi[1].y;
        po[1].z = pos[1].z;
        po[2].x = posi[2].x;
        po[2].y = posi[2].y;
        po[2].z = pos[2].z;
        if (recur == 1)
	{
            po[empin[1]] = exept[1];
            po[empin[0]] = exept[0];
	}
        inscreen = is_point_in_screen(po, pix);
        if (inscreen != 0)
	{
            //printf("1 %d %d 2 %d %d 3 %d %d\n", posi[0].x, posi[0].y,
            //posi[1].x, posi[1].y, posi[2].x, posi[2].y);

            if (inscreen == 2)// && recur == 0)
	    {
                po[4] = reduce_zpos(po, pix, emp);
                po[3] = po[emp[1]];
                //printf("exept %d %d emp %d // exept %d %d emp %d\n", posi[3].x, posi[3].y, emp[0], posi[4].x, posi[4].y, emp[1]);
                std_set_ztriangle(pix, zbuffer, pos, color, &po[3], emp, 1, foca);
	    }
            else if (inscreen != 3)
                reduce_zpos(po, pix, emp);

            if (inscreen != 3)
            {
                if (po[2].x > pix->clipable.buffer.width * 1.700)
                    po[2].x = pix->clipable.buffer.width * 1.700;
                else if (po[2].x < pix->clipable.buffer.width * -1.700)
                    po[2].x = pix->clipable.buffer.width * -1.700;
                if (po[2].y > pix->clipable.buffer.height * 1.700)
                    po[2].y = pix->clipable.buffer.height * 1.700;
                else if (po[2].y < pix->clipable.buffer.height * -1.700)
                    po[2].y = pix->clipable.buffer.height * -1.700;
                if (po[1].x > pix->clipable.buffer.width * 1.700)
                    po[1].x = pix->clipable.buffer.width * 1.700;
                else if (po[1].x < pix->clipable.buffer.width * -1.700)
                    po[1].x = pix->clipable.buffer.width * -1.700;
                if (po[1].y > pix->clipable.buffer.height * 1.700)
                    po[1].y = pix->clipable.buffer.height * 1.700;
                else if (po[1].y < pix->clipable.buffer.height * -1.700)
                    po[1].y = pix->clipable.buffer.height * -1.700;
                if (po[0].x > pix->clipable.buffer.width * 1.700)
                    po[0].x = pix->clipable.buffer.width * 1.700;
                else if (po[0].x < pix->clipable.buffer.width * -1.700)
                    po[0].x = pix->clipable.buffer.width * -1.700;
                if (po[0].y > pix->clipable.buffer.height * 1.700)
                    po[0].y = pix->clipable.buffer.height * 1.700;
                else if (po[0].y < pix->clipable.buffer.height * -1.700)
                    po[0].y = pix->clipable.buffer.height * -1.700;
                //printf("print 1 %f %f 2 %f %f 3 %f %f\n", po[0].x, po[0].y, po[1].x, po[1].y, po[2].x, po[2].y);
            }

            po[3] = po[0];
            std_set_zline(pix, zbuffer, &po[0], color);
            std_set_zline(pix, zbuffer, &po[1], color);
            std_set_zline(pix, zbuffer, &po[2], color);
            fill_triangle(pix, zbuffer, po, color);
	}
    }
}


