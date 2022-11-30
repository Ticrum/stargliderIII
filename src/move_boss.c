
#include <starglider.h>

static t_pos choose_rota(t_boss *boss)
{
    t_pos ratio;

    ratio.x = (rand() % 10) / 80.0 - 0.05125;//atan2(enemy->vect.y - enemy->obj.position.y, enemy->vect.z - enemy->obj.position.z);
    ratio.y = (rand() % 10) / 80.0 - 0.05125;//atan2(enemy->vect.x - enemy->obj.position.x, enemy->vect.z - enemy->obj.position.z);
    //ratio.x = 0;//ratio.x + atan2(enemy->vect.y - 40, (enemy->vect.z + 800));
    //ratio.y = 0;//ratio.y + atan2(enemy->vect.x, (enemy->vect.z + 800));
    ratio.z = 0;
    return (ratio);
}

void move_boss(t_boss      *boss,
               t_pos       rota,
               t_pos	   rotation,
               t_pos	   posi2)
{
    t_pos pos;
    t_pos campos;
    t_pos posi;
    int compt;
    int compt2;

    campos.x = 0;
    campos.y = 40;
    campos.z = -800;
    if (boss->hp > 0)
    {
          compt = 0;
          compt2 = 0;
          pos.x = boss->obj.position.x;
          pos.y = boss->obj.position.y;
          pos.z = boss->obj.position.z;
          posi.x = boss->vect.x - boss->obj.position.x;
          posi.y = boss->vect.y - boss->obj.position.y;
          posi.z = boss->vect.z - boss->obj.position.z;
          rota = choose_rota(boss);
          boss->obj.position = add_pos(boss->obj.position, posi);
          boss->obj.position = stdtruerotation(boss->obj.position, rota, pos);
          boss->vect = add_pos(boss->vect, posi);
          boss->vect = stdtruerotation(boss->vect, rota, pos);
          while (compt != boss->obj.nbr_subelems)
          {
              boss->obj.pos[compt2] = add_pos(boss->obj.pos[compt2], posi);
              boss->obj.pos[compt2 + 1] = add_pos(boss->obj.pos[compt2 + 1], posi);
              boss->obj.pos[compt2 + 2] = add_pos(boss->obj.pos[compt2 + 2], posi);
              boss->obj.pos[compt2] = stdtruerotation(boss->obj.pos[compt2], rota, pos);
              boss->obj.pos[compt2 + 1] = stdtruerotation(boss->obj.pos[compt2 + 1], rota, pos);
              boss->obj.pos[compt2 + 2] = stdtruerotation(boss->obj.pos[compt2 + 2], rota, pos);
              compt = compt + 1;
              compt2 = compt2 + 3;
          }
          compt = 0;
          //rota.x = 0;
          //rota.y = 0;
          //rota.z = 0;
          posi.x = posi.x + posi2.x;
          posi.y = posi.y + posi2.y;
          posi.z = posi.z + posi2.z;
          while (compt < boss->nbr_turret)
          {
              
              boss->turret[compt].obj.position = stdtruerotation(boss->turret[compt].obj.position, rota, pos);
              boss->turret[compt].vect = stdtruerotation(boss->turret[compt].vect, rota, pos);
              compt2 = 0;
              while (compt2 < boss->turret[compt].obj.nbr_subelems * 3)
              {
                  boss->turret[compt].obj.pos[compt2] = stdtruerotation(boss->turret[compt].obj.pos[compt2], rota, pos);
                  boss->turret[compt].obj.pos[compt2 + 1] = stdtruerotation(boss->turret[compt].obj.pos[compt2 + 1], rota, pos);
                  boss->turret[compt].obj.pos[compt2 + 2] = stdtruerotation(boss->turret[compt].obj.pos[compt2 + 2], rota, pos);
                  compt2 = compt2 + 3;
              }
              
              move_turret(&boss->turret[compt], rota, rotation, posi);

              compt = compt + 1;
          }
          std_move(&boss->obj, rotation, posi2);
          boss->vect = add_pos(boss->vect, posi2);
          boss->vect = stdtruerotation(boss->vect, rotation, campos);
    }
}

