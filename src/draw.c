
#include <starglider.h>

void std_draw(t_bunny_pixelarray	*pix,
              float                     *zbuffer,
	      t_obj			*obj,
	      t_pos			rotation,
	      t_pos			posi)
{
  int compt;
  int compt2;
  t_pos pos[4];
  t_pos rotationmodif;

  compt = 0;
  compt2 = 0;
  pos[3].x = 0;
  pos[3].y = 40;
  pos[3].z = -800;
  //write(1,"\n",1);

  obj->position.x = obj->position.x + posi.x;
  obj->position.y = obj->position.y + posi.y;
  obj->position.z = obj->position.z + posi.z;
  obj->position = stdtruerotation(obj->position, rotation, pos[3]);

  while (compt != obj->nbr_subelems)
    {
        //write(1,"a",1);
        obj->pos[compt2].x = obj->pos[compt2].x + posi.x;
        obj->pos[compt2].y = obj->pos[compt2].y + posi.y;
        obj->pos[compt2].z = obj->pos[compt2].z + posi.z;
        obj->pos[compt2 + 1].x = obj->pos[compt2 + 1].x + posi.x;
        obj->pos[compt2 + 1].y = obj->pos[compt2 + 1].y + posi.y;
        obj->pos[compt2 + 1].z = obj->pos[compt2 + 1].z + posi.z;
        obj->pos[compt2 + 2].x = obj->pos[compt2 + 2].x + posi.x;
        obj->pos[compt2 + 2].y = obj->pos[compt2 + 2].y + posi.y;
        obj->pos[compt2 + 2].z = obj->pos[compt2 + 2].z + posi.z;
        pos[0] = obj->pos[compt2];
        pos[1] = obj->pos[compt2 + 1];
        pos[2] = obj->pos[compt2 + 2];
/*
        pos[0].x = pos[0].x + obj->position.x;
        pos[0].y = pos[0].y + obj->position.y;
        pos[0].z = pos[0].z + obj->position.z;
        pos[1].x = pos[1].x + obj->position.x;
        pos[1].y = pos[1].y + obj->position.y;
        pos[1].z = pos[1].z + obj->position.z;
        pos[2].x = pos[2].x + obj->position.x;
        pos[2].y = pos[2].y + obj->position.y;
        pos[2].z = pos[2].z + obj->position.z;
*/
        rotationmodif = rotation;
        //rotationmodif = compence_rotation(rotation);
        pos[0] = stdtruerotation(pos[0], rotationmodif, pos[3]);
        pos[1] = stdtruerotation(pos[1], rotationmodif, pos[3]);
        pos[2] = stdtruerotation(pos[2], rotationmodif, pos[3]);

        obj->pos[compt2] = pos[0];
        obj->pos[compt2 + 1] = pos[1];
        obj->pos[compt2 + 2] = pos[2];

        std_set_ztriangle(pix, zbuffer, pos, &obj->color[compt].full, NULL, &compt, 0);
        compt = compt + 1;
        compt2 = compt2 + 3;
    }
}

