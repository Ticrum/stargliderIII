
#include <starglider.h>

static t_pos choose_rota(t_enemy *enemy)
{
    t_pos ratio;
    float goal;

    ratio.x = enemy->vect.x / enemy->obj.position.x;
    ratio.y = enemy->vect.y / enemy->obj.position.y;
    ratio.z = enemy->vect.z / enemy->obj.position.z;
    goal = (ratio.x + ratio.y + ratio.z) / 3.0;
    if (ratio.x > goal)//enemy->vect.x > enemy->obj.position.x)
        ratio.x = -enemy->rota_speed.x;
    else
        ratio.x = enemy->rota_speed.x;
    if (ratio.y > goal)//enemy->vect.y > enemy->obj.position.y)
        ratio.y = -enemy->rota_speed.y;
    else
        ratio.y = enemy->rota_speed.y;
    //if (enemy->vect.z > enemy->obj.position.z)
    //    ratio.z = -enemy->rota_speed.z;
    //else
    //    ratio.z = enemy->rota_speed.z;
    ratio.x = atan2(enemy->vect.y, enemy->vect.x);
    ratio.y = 0;//atan2(enemy->obj.position.x, enemy->obj.position.z);
    //ratio.y = 0;
    ratio.z = 0;
    return (ratio);
}

void move_enemy(t_enemy     *enemy,
                t_pos       rota,
                t_pos       cpos)
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

