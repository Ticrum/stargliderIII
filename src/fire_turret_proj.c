
#include <starglider.h>

void fire_turret_proj(t_turret *turret)
{
    t_pos pos;

    //srand(clock());
    //pos = turret->vect;
    //pos.y = 40;
    if (turret->rofc == turret->rof)
    {
        pos.x = turret->vect.x + (turret->vect.x - turret->obj.position.x) * 4;
        pos.y = turret->vect.y + (turret->vect.y - turret->obj.position.y) * 4;
        pos.z = turret->vect.z + (turret->vect.z - turret->obj.position.z) * 4;
        turret->proj[turret->shot_compt].pos = turret->obj.position;
        //pos.z = pos.z ;
        //pos.y = pos.y + ((rand() % 10 - 5) / 5.0);
        //pos.x = pos.x + ((rand() % 10 - 5) / 5.0);
        turret->proj[turret->shot_compt].vect = pos;//turret->vect;
        turret->proj[turret->shot_compt].act = true;
        turret->shot_compt = turret->shot_compt + 1;
        if (turret->shot_compt == 50)
            turret->shot_compt = 0;
        turret->rofc = 0;
    }
    else
        turret->rofc = turret->rofc + 1;
}

