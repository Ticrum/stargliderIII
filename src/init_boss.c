
#include <starglider.h>

t_boss init_boss(char   *file,
                 int    nbr_obj,
                 t_pos  objpos,
                 int    dmg,
                 int    hp)
{
    t_boss boss;
    t_pos pos;
    int compt;

    boss.obj = load_obj(file, nbr_obj, objpos);
    boss.vect = boss.obj.position;
    boss.vect.z = boss.vect.z + 2;
    boss.dmg = dmg;
    boss.hp = 0;
    boss.maxhp = hp;
    boss.nbr_turret = 5;
    compt = 0;
    while (compt < boss.nbr_turret)
    {
        pos.x = boss.obj.position.x + compt * 200 - 400;//100 + (rand() % 3000 - 1500);//-10;
        pos.y = boss.obj.position.y + 50;//50 + (rand() % 3000 - 1500);//20;
        pos.z = boss.obj.position.z + 50;//0 + (rand() % 3000 - 1500);//-400;
        boss.turret[compt] = init_turret("turret.dab", 8, pos, 10, 100, 4);
        compt = compt + 1;
    }
    return (boss);
}

