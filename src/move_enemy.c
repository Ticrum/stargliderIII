
#include <starglider.h>

static t_pos choose_rota(t_enemy *enemy)
{
    t_pos ratio;

    ratio.x = atan2(enemy->vect.y - enemy->obj.position.y, enemy->vect.z - enemy->obj.position.z);
    ratio.y = atan2(enemy->vect.x - enemy->obj.position.x, enemy->vect.z - enemy->obj.position.z);
    //printf("%f\n", enemy->vect.z + 800);
    ratio.x = ratio.x + atan2(enemy->vect.y - 40, (enemy->vect.z + 800));
    ratio.y = ratio.y + atan2(enemy->vect.x, (enemy->vect.z + 800));
/*
    if (ratio.x > 0)
        ratio.x = enemy->rota_speed.x;
    else if (ratio.y < 0)
        ratio.x = -enemy->rota_speed.x;
    else
        ratio.x = 0;
    if (ratio.y > 0)
        ratio.y = enemy->rota_speed.y;
    else if (ratio.y < 0)
        ratio.y = -enemy->rota_speed.y;
    else
        ratio.y = 0;
*/
    //ratio.x = 0;
    //ratio.y = 0;
    ratio.z = 0;//atan2(enemy->vect.y - enemy->obj.position.y, enemy->vect.x - enemy->obj.position.x);
    return (ratio);
}

void move_enemy(t_enemy     *enemy,
                t_pos       rota)
{
    t_pos pos;
    t_pos posi;
    int compt;
    int compt2;

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

          enemy->obj.position.x = enemy->obj.position.x + posi.x;
          enemy->obj.position.y = enemy->obj.position.y + posi.y;
          enemy->obj.position.z = enemy->obj.position.z + posi.z;
          enemy->obj.position = stdtruerotation(enemy->obj.position, rota, pos);
          enemy->vect.x = enemy->vect.x + posi.x;
          enemy->vect.y = enemy->vect.y + posi.y;
          enemy->vect.z = enemy->vect.z + posi.z;
          enemy->vect = stdtruerotation(enemy->vect, rota, pos);
          while (compt != enemy->obj.nbr_subelems)
          {
              enemy->obj.pos[compt2].x = enemy->obj.pos[compt2].x + posi.x;
              enemy->obj.pos[compt2].y = enemy->obj.pos[compt2].y + posi.y;
              enemy->obj.pos[compt2].z = enemy->obj.pos[compt2].z + posi.z;
              enemy->obj.pos[compt2 + 1].x = enemy->obj.pos[compt2 + 1].x + posi.x;
              enemy->obj.pos[compt2 + 1].y = enemy->obj.pos[compt2 + 1].y + posi.y;
              enemy->obj.pos[compt2 + 1].z = enemy->obj.pos[compt2 + 1].z + posi.z;
              enemy->obj.pos[compt2 + 2].x = enemy->obj.pos[compt2 + 2].x + posi.x;
              enemy->obj.pos[compt2 + 2].y = enemy->obj.pos[compt2 + 2].y + posi.y;
              enemy->obj.pos[compt2 + 2].z = enemy->obj.pos[compt2 + 2].z + posi.z;
              enemy->obj.pos[compt2] = stdtruerotation(enemy->obj.pos[compt2], rota, pos);
              enemy->obj.pos[compt2 + 1] = stdtruerotation(enemy->obj.pos[compt2 + 1], rota, pos);
              enemy->obj.pos[compt2 + 2] = stdtruerotation(enemy->obj.pos[compt2 + 2], rota, pos);
              compt = compt + 1;
              compt2 = compt2 + 3;
          }
    }
}

