
#include <starglider.h>

static t_pos choose_rota(t_enemy *enemy)
{
    t_pos ratio;

    ratio.x = atan2(enemy->vect.y - enemy->obj.position.y, enemy->vect.z - enemy->obj.position.z);
    ratio.y = atan2(enemy->vect.x - enemy->obj.position.x, enemy->vect.z - enemy->obj.position.z);
    ratio.x = ratio.x + atan2(enemy->vect.y - 40, (enemy->vect.z + 800));
    ratio.y = ratio.y + atan2(enemy->vect.x, (enemy->vect.z + 800));
    ratio.z = 0;
    return (ratio);
}

void move_enemy(t_enemy     *enemy,
                t_pos       rota,
                t_pos	    rotation,
                t_pos	    posi2)
{
    t_pos pos;
    t_pos campos;
    t_pos posi;
    int compt;
    int compt2;

    campos.x = 0;
    campos.y = 40;
    campos.z = -800;
    if (enemy->hp > 0)
    {
          compt = 0;
          compt2 = 0;
          pos.x = enemy->obj.position.x;
          pos.y = enemy->obj.position.y;
          pos.z = enemy->obj.position.z;
          posi.x = enemy->vect.x - enemy->obj.position.x;
          posi.y = enemy->vect.y - enemy->obj.position.y;
          posi.z = enemy->vect.z - enemy->obj.position.z;
          rota = choose_rota(enemy);
          enemy->obj.position = add_pos(enemy->obj.position, posi);
          enemy->obj.position = stdtruerotation(enemy->obj.position, rota, pos);
          enemy->vect = add_pos(enemy->vect, posi);
          enemy->vect = stdtruerotation(enemy->vect, rota, pos);
          while (compt != enemy->obj.nbr_subelems)
          {
              enemy->obj.pos[compt2] = add_pos(enemy->obj.pos[compt2], posi);
              enemy->obj.pos[compt2 + 1] = add_pos(enemy->obj.pos[compt2 + 1], posi);
              enemy->obj.pos[compt2 + 2] = add_pos(enemy->obj.pos[compt2 + 2], posi);
              enemy->obj.pos[compt2] = stdtruerotation(enemy->obj.pos[compt2], rota, pos);
              enemy->obj.pos[compt2 + 1] = stdtruerotation(enemy->obj.pos[compt2 + 1], rota, pos);
              enemy->obj.pos[compt2 + 2] = stdtruerotation(enemy->obj.pos[compt2 + 2], rota, pos);
              compt = compt + 1;
              compt2 = compt2 + 3;
          }
          std_move(&enemy->obj, rotation, posi2);
          enemy->vect = add_pos(enemy->vect, posi2);
          enemy->vect = stdtruerotation(enemy->vect, rotation, campos);
    }
}

