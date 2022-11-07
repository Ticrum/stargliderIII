
#include <starglider.h>

static int hit_enemy(t_enemy   enemy)
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
/*
static int enemy_in(t_enemy             enemy,
                    t_bunny_pixelarray  *pix)
{
    return (1);
}
*/
void dmg_enemy(t_enemy              *enemy,
               int                  nbr)
{
    int compt;

    compt = 0;
    while (compt < nbr)
    {
        //if (enemy_in(enemy[compt], pix) == 1)
        //{
            //write(1,"a",1);
        if (hit_enemy(enemy[compt]) == 1 && enemy[compt].hp > 0)
            enemy[compt].hp = enemy[compt].hp - 1;
        //}
        compt = compt + 1;
    }
}

