
#include <starglider.h>

static int hit_enemy(t_pos     pos,
                     t_pos     vect,
                     t_enemy   enemy)
{
    t_pos ratio;
    t_pos result;
    float max;
    float hitsize;

    hitsize = 30;
    //printf("%f %f %f\n", enemy.obj.position.x, enemy.obj.position.y, enemy.obj.position.z);
    /*
    pos.z = pos.z + 800;
    result.x = enemy.obj.position.x + pos.x;
    result.y = enemy.obj.position.y + pos.y;
    result.z = enemy.obj.position.z - pos.z;
    max = std_abs(result.x);
    if (std_abs(result.y) > max)
        max = std_abs(result.y);
    if (std_abs(result.z) > max)
        max = std_abs(result.z);
    ratio.x = max * vect.x;
    if (result.x < 0)
        ratio.x = -ratio.x;
    ratio.y = max * vect.y;
    if (result.y < 0)
        ratio.y = -ratio.y;
    ratio.z = max * vect.z;
    if (result.z < 0)
        ratio.z = -ratio.z;
    //result = (ratio.x + ratio.y + ratio.z) / 3.0;
    //printf("in %f %f %f / %f\n", ratio.x, ratio.y, ratio.z, result);
    printf("me %f %f %f / %f %f %f // %f %f %f\n", pos.x, pos.y, pos.z, result.x, result.y, result.z, vect.x, vect.y, vect.z);
    */
    if ((enemy.obj.position.x < hitsize && enemy.obj.position.x > -hitsize) &&
        (enemy.obj.position.y < hitsize && enemy.obj.position.y > -hitsize) &&
        enemy.obj.position.z > -800)
        return (1);
    return (0);
}

static int enemy_in(t_enemy             enemy,
                    t_bunny_pixelarray  *pix)
{
    return (1);
}

void dmg_enemy(t_bunny_pixelarray   *pix,
               t_pos                pos,
               t_pos                vect,
               t_enemy              *enemy,
               int                  nbr)
{
    int compt;

    compt = 0;
    while (compt < nbr)
    {
        if (enemy_in(enemy[compt], pix) == 1)
        {
            //write(1,"a",1);
            if (hit_enemy(pos, vect, enemy[compt]) == 1 && enemy[compt].hp > 0)
                enemy[compt].hp = enemy[compt].hp - 1;
        }
        compt = compt + 1;
    }
}

