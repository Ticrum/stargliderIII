
#include <starglider.h>

static void init_proj(t_proj *proj)
{
    int compt;

    compt = 0;
    while (compt < 50)
    {
        proj[compt].act = false;
        proj[compt].pos.x = 9999;
        proj[compt].pos.y = 9999;
        proj[compt].pos.z = 9999;
        compt = compt + 1;
    }
}

t_turret init_turret(char   *file,
                     int    nbr_obj,
                     t_pos  objpos,
                     int    dmg,
                     int    hp,
                     int    rof)
{
    t_turret turret;

    turret.obj = load_obj(file, nbr_obj, objpos);
    turret.vect = turret.obj.position;
    turret.vect.z = turret.vect.z + 10;
    turret.dmg = dmg;
    turret.hp = hp;
    turret.maxhp = hp;
    turret.rota_speed.x = 0.03;
    turret.rota_speed.y = 0.03;
    turret.rota_speed.z = 0.03;
    turret.shot_compt = 0;
    turret.rof = rof;
    turret.rofc = 0;
    init_proj(turret.proj);
    return (turret);
}

