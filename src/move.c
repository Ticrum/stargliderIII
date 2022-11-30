
#include <starglider.h>

void std_move(t_obj			*obj,
	      t_pos			rotation,
	      t_pos			posi)
{
  int compt;
  int compt2;
  t_pos pos[4];

  compt = 0;
  compt2 = 0;
  pos[3].x = 0;
  pos[3].y = 40;
  pos[3].z = -800;

  obj->position = add_pos(obj->position, posi);
  obj->position = stdtruerotation(obj->position, rotation, pos[3]);

  while (compt != obj->nbr_subelems)
    {
        obj->pos[compt2] = add_pos(obj->pos[compt2], posi);
        obj->pos[compt2 + 1] = add_pos(obj->pos[compt2 + 1], posi);
        obj->pos[compt2 + 2] = add_pos(obj->pos[compt2 + 2], posi);
        pos[0] = obj->pos[compt2];
        pos[1] = obj->pos[compt2 + 1];
        pos[2] = obj->pos[compt2 + 2];
        obj->pos[compt2] = stdtruerotation(obj->pos[compt2], rotation, pos[3]);
        obj->pos[compt2 + 1] = stdtruerotation(obj->pos[compt2 + 1], rotation, pos[3]);
        obj->pos[compt2 + 2] = stdtruerotation(obj->pos[compt2 + 2], rotation, pos[3]);
        compt = compt + 1;
        compt2 = compt2 + 3;
    }
}

