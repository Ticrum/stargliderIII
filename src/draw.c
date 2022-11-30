
#include <starglider.h>

void std_draw(t_bunny_pixelarray	*pix,
              float                     *zbuffer,
	      t_obj			*obj,
              float                     foca)
{
  int compt;
  int compt2;
  t_pos pos[4];

  compt = 0;
  compt2 = 0;
  pos[3].x = 0;
  pos[3].y = 40;
  pos[3].z = -800;

  while (compt != obj->nbr_subelems)
    {
        pos[0] = obj->pos[compt2];
        pos[1] = obj->pos[compt2 + 1];
        pos[2] = obj->pos[compt2 + 2];
        std_set_ztriangle(pix, zbuffer, pos, &obj->color[compt].full, NULL, &compt, 0, foca);
        compt = compt + 1;
        compt2 = compt2 + 3;
    }
}

