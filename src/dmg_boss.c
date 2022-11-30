
#include <starglider.h>

static int hit_boss_beam(t_boss   boss)
{
    float hitsize;

    hitsize = 160;
    //printf("%f %f %f\n", enemy.obj.position.x, enemy.obj.position.y, enemy.obj.position.z);
    if ((boss.obj.position.x < hitsize && boss.obj.position.x > -hitsize) &&
        (boss.obj.position.y < hitsize && boss.obj.position.y > -hitsize) &&
        boss.obj.position.z > -800)
        return (1);
    return (0);
}

static int hit_boss_proj(t_boss   boss,
                         t_proj   *proj)
{
    float hitsize;
    int compt;

    hitsize = 180;
    compt = 0;
    while (compt < 50)
    {
        if (proj[compt].act == true)
            if ((boss.obj.position.x < hitsize + proj[compt].pos.x && boss.obj.position.x > -hitsize + proj[compt].pos.x) &&
                (boss.obj.position.y < hitsize + proj[compt].pos.y && boss.obj.position.y > -hitsize + proj[compt].pos.y) &&
                (boss.obj.position.z < hitsize + proj[compt].pos.z && boss.obj.position.z > -hitsize + proj[compt].pos.z))
            {
                proj[compt].act = false;
                return (1);
            }
        compt = compt + 1;
    }
    return (0);
}

/*
static int enemy_in(t_enemy             enemy,
                    t_bunny_pixelarray  *pix)
{
    return (1);
}
*/
void dmg_boss(t_boss              *boss,
              t_proj              *proj,
              int                 nbr,
              int                 mode,
              int                 *score)
{
    int compt;

    compt = 0;
    while (compt < nbr)
    {
        //if (enemy_in(enemy[compt], pix) == 1)
        //{
            //write(1,"a",1);
        if (boss[compt].hp > 0)
        {
            if (mode == true)
            {
                if (hit_boss_proj(boss[compt], proj) == 1 && boss[compt].hp > 0)
                    boss[compt].hp = boss[compt].hp - 4;
            }
            else
                if (hit_boss_beam(boss[compt]) == 1 && boss[compt].hp > 0)
                    boss[compt].hp = boss[compt].hp - 1;
            if (boss[compt].hp <= 0)
                *score = *score + 1000;
        }
        //}
        compt = compt + 1;
    }
}

