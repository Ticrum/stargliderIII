
#include <starglider.h>

void draw_enemy(t_bunny_pixelarray	*pix,
                float                   *zbuffer,
                t_enemy			*enemy,
                t_pos			rotation,
                t_pos			posi)
{
    t_pos pos;
    t_bunny_position poos[3];
    unsigned int color;

    pos.x = 0;
    pos.y = 40;
    pos.z = -800;
    if (enemy->hp > 0)
    {
        std_draw(pix, zbuffer, &enemy->obj, rotation, posi);
        enemy->vect.x = enemy->vect.x + posi.x;
        enemy->vect.y = enemy->vect.y + posi.y;
        enemy->vect.z = enemy->vect.z + posi.z;
        enemy->vect = stdtruerotation(enemy->vect, rotation, pos);
        poos[0] = std_decal(pix, std_perspective(enemy->vect.x, enemy->vect.y, enemy->vect.z));
        //printf("%d %d\n", poos.x, poos.y);
        std_set_pixel(pix, poos[0], BLUE);

        poos[0] = std_decal(pix, std_perspective(enemy->obj.position.x, enemy->obj.position.y, enemy->obj.position.z));
        color = RED;
        poos[1].x = poos[0].x - 100;
        poos[1].y = poos[0].y - 50;
        poos[2].x = std_get_value(std_get_ratio(enemy->maxhp, 0, enemy->hp), poos[0].x - 100, poos[0].x + 100);
        poos[2].y = poos[0].y - 50;
        std_set_line(pix, &poos[1], &color);

    }
}

