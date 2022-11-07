
#include <starglider.h>

void move_star(t_star   *star,
               t_pos    rota)
{
    int compt;
    t_pos pos;

    pos.x = 0;
    pos.y = 40;
    pos.z = -800;

    compt = 0;
    while (compt < star->nbr_star)
    {
        star->pos[compt] = stdtruerotation(star->pos[compt], rota, pos);
        compt = compt + 1;
    }
}
