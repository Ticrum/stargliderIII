
#include <starglider.h>

void std_draw(t_bunny_pixelarray	*pix,
	      t_obj			*obj,
	      t_pos			rotation,
	      t_pos			posi)
{
  int compt;
  int compt2;
  t_pos pos[4];

  compt = 0;
  compt2 = 0;
  pos[3].x = 0;
  pos[3].y = 0;
  pos[3].z = -800;
  //write(1,"\n",1);
  while (compt != obj->nbr_subelems)
    {
      //write(1,"a",1);
      pos[0] = obj->pos[compt2];
      pos[1] = obj->pos[compt2 + 1];
      pos[2] = obj->pos[compt2 + 2];
      
      pos[0].x = pos[0].x + posi.x + obj->position.x;
      pos[0].y = pos[0].y + posi.y + obj->position.y;
      pos[0].z = pos[0].z + posi.z + obj->position.z;
      pos[1].x = pos[1].x + posi.x + obj->position.x;
      pos[1].y = pos[1].y + posi.y + obj->position.y;
      pos[1].z = pos[1].z + posi.z + obj->position.z;
      pos[2].x = pos[2].x + posi.x + obj->position.x;
      pos[2].y = pos[2].y + posi.y + obj->position.y;
      pos[2].z = pos[2].z + posi.z + obj->position.z;

      pos[0] = stdtruerotation(pos[0], rotation, pos[3]);
      pos[1] = stdtruerotation(pos[1], rotation, pos[3]);
      pos[2] = stdtruerotation(pos[2], rotation, pos[3]);

      std_set_triangle(pix, pos, &obj->color[compt].full, NULL, &compt, 0);
      compt = compt + 1;
      compt2 = compt2 + 3;
    }
}

