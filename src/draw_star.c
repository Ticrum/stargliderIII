
#include <starglider.h>

void draw_star(t_bunny_pixelarray   *pix,
               t_star               *star,
               float                foca)
{
    int compt;
    t_bunny_position pos;

    compt = 0;
    while (compt < star->nbr_star)
    {
        pos = std_decal(pix, std_perspective(star->pos[compt].x, star->pos[compt].y, star->pos[compt].z, foca));//star->pos[compt]
        std_set_pixel(pix, pos, WHITE);
        compt = compt + 1;
    }
}

