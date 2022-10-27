
#include <starglider.h>

void draw_enemy(t_bunny_pixelarray	*pix,
                float                   *zbuffer,
                t_enemy			*enemy,
                t_pos			rotation,
                t_pos			posi)
{
    t_pos pos;
    t_bunny_position poos;

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
        poos = std_decal(pix, std_perspective(enemy->vect.x, enemy->vect.y, enemy->vect.z));
        //printf("%d %d\n", poos.x, poos.y);
        std_set_pixel(pix, poos, BLUE);
    }
}

