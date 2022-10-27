
#include <starglider.h>

t_enemy init_enemy(char *file,
                   int nbr_obj,
                   t_pos objpos,
                   int dmg,
                   int hp)
{
    t_enemy enemy;

    enemy.obj = load_obj(file, nbr_obj, objpos);
    enemy.vect = enemy.obj.position;
    enemy.vect.z = enemy.vect.z + 2;
    enemy.dmg = dmg;
    enemy.hp = hp;
    enemy.speed.x = 10;
    enemy.speed.y = 10;
    enemy.speed.z = 10;
    enemy.rota_speed.x = 0.03;
    enemy.rota_speed.y = 0.03;
    enemy.rota_speed.z = 0.03;
    return (enemy);
}

