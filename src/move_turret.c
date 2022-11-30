
#include <starglider.h>

static t_pos choose_rota(t_turret *turret)
{
    t_pos ratio;

    ratio.x = atan2(turret->vect.y - turret->obj.position.y, turret->vect.z - turret->obj.position.z);
    ratio.y = atan2(turret->vect.x - turret->obj.position.x, turret->vect.z - turret->obj.position.z);
    //printf("%f\n", enemy->vect.z + 800);
    ratio.x = ratio.x + atan2(turret->vect.y - 40, (turret->vect.z + 800));
    ratio.y = ratio.y + atan2(turret->vect.x, (turret->vect.z + 800));
    ratio.z = 0;
    return (ratio);
}

void move_turret(t_turret     *turret,
                 t_pos        rota,
                 t_pos        rotation,
                 t_pos        posi)
{
    t_pos pos;
    t_pos campos;
    //t_pos posi;
    int compt;
    int compt2;

    campos.x = 0;
    campos.y = 40;
    campos.z = -800;
    if (turret->hp > 0)
    {
          compt = 0;
          compt2 = 0;
          pos.x = turret->obj.position.x;
          pos.y = turret->obj.position.y;
          pos.z = turret->obj.position.z;
          rota = choose_rota(turret);

          turret->obj.position = stdtruerotation(turret->obj.position, rota, pos);
          turret->vect = stdtruerotation(turret->vect, rota, pos);
          while (compt != turret->obj.nbr_subelems)
          {
              turret->obj.pos[compt2] = stdtruerotation(turret->obj.pos[compt2], rota, pos);
              turret->obj.pos[compt2 + 1] = stdtruerotation(turret->obj.pos[compt2 + 1], rota, pos);
              turret->obj.pos[compt2 + 2] = stdtruerotation(turret->obj.pos[compt2 + 2], rota, pos);
              compt = compt + 1;
              compt2 = compt2 + 3;
          }
          std_move(&turret->obj, rotation, posi);
          turret->vect = add_pos(turret->vect, posi);
          turret->vect = stdtruerotation(turret->vect, rotation, campos);
    }
}

