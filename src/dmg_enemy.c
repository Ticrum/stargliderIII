
#include <starglider.h>

static int hit_enemy_beam(t_enemy   enemy)
{
    float hitsize;

    hitsize = 50;
    //printf("%f %f %f\n", enemy.obj.position.x, enemy.obj.position.y, enemy.obj.position.z);
    if ((enemy.obj.position.x < hitsize && enemy.obj.position.x > -hitsize) &&
        (enemy.obj.position.y < hitsize && enemy.obj.position.y > -hitsize) &&
        enemy.obj.position.z > -800)
        return (1);
    return (0);
}

static int hit_enemy_proj(t_enemy   enemy,
                          t_proj    *proj)
{
    float hitsize;
    int compt;

    hitsize = 80;
    compt = 0;
    while (compt < 50)
    {
        if (proj[compt].act == true)
            if ((enemy.obj.position.x < hitsize + proj[compt].pos.x && enemy.obj.position.x > -hitsize + proj[compt].pos.x) &&
                (enemy.obj.position.y < hitsize + proj[compt].pos.y && enemy.obj.position.y > -hitsize + proj[compt].pos.y) &&
                (enemy.obj.position.z < hitsize + proj[compt].pos.z && enemy.obj.position.z > -hitsize + proj[compt].pos.z))
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
void dmg_enemy(t_enemy              *enemy,
               t_proj               *proj,
               int                  nbr,
               int                  mode)
{
    int compt;

    compt = 0;
    while (compt < nbr)
    {
        //if (enemy_in(enemy[compt], pix) == 1)
        //{
            //write(1,"a",1);
        if (mode == true)
        {
            if (hit_enemy_proj(enemy[compt], proj) == 1 && enemy[compt].hp > 0)
                enemy[compt].hp = enemy[compt].hp - 7;
        }
        else
            if (hit_enemy_beam(enemy[compt]) == 1 && enemy[compt].hp > 0)
                enemy[compt].hp = enemy[compt].hp - 1;
        //}
        compt = compt + 1;
    }
}

