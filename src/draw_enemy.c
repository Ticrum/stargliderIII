
#include <starglider.h>

void draw_enemy(t_bunny_pixelarray	*pix,
                float                   *zbuffer,
                t_enemy			*enemy,
                float                   foca)
{
    t_bunny_position poos[3];
    unsigned int color;

    if (enemy->hp > 0)
    {
        std_draw(pix, zbuffer, &enemy->obj, foca);
        poos[0] = std_decal(pix, std_perspective(enemy->vect.x, enemy->vect.y, enemy->vect.z, foca));
        std_set_pixel(pix, poos[0], BLUE);

        poos[0] = std_decal(pix, std_perspective(enemy->obj.position.x, enemy->obj.position.y, enemy->obj.position.z, foca));
        color = RED;
        poos[1].x = poos[0].x - 100;
        poos[1].y = poos[0].y - 50;
        poos[2].x = std_get_value(std_get_ratio(enemy->maxhp, 0, enemy->hp), poos[0].x - 100, poos[0].x + 100);
        poos[2].y = poos[0].y - 50;
        std_set_line(pix, &poos[1], &color);

    }
}

