
#include <starglider.h>

void draw_boss(t_bunny_pixelarray   *pix,
               float                *zbuffer,
               t_boss               *boss,
               float                foca)
{
    t_bunny_position poos[3];
    unsigned int color;

    if (boss->hp > 0)
    {
        std_draw(pix, zbuffer, &boss->obj, foca);
        poos[0] = std_decal(pix, std_perspective(boss->vect.x, boss->vect.y, boss->vect.z, foca));
        std_set_pixel(pix, poos[0], BLUE);

        poos[0] = std_decal(pix, std_perspective(boss->obj.position.x, boss->obj.position.y, boss->obj.position.z, foca));
        poos[1].x = poos[0].x - 100;
        poos[1].y = poos[0].y - 100;
        poos[2].y = poos[0].y - 100;
        color = RED;
        //poos[1].y = poos[1].y - 1;
        //poos[2].y = poos[1].y;
        poos[2].x = poos[0].x + 100;
        std_set_line(pix, &poos[1], &color);
        color = YELLOW;
        poos[2].x = std_get_value(std_get_ratio(boss->maxhp, 0, boss->hp), poos[0].x - 100, poos[0].x + 100);
        std_set_line(pix, &poos[1], &color);
    }
}

