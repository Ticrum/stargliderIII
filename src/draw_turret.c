
#include <starglider.h>

void draw_turret(t_bunny_pixelarray	*pix,
                 float                  *zbuffer,
                 t_turret		*turret,
                 float                  foca)
{
    t_bunny_position poos[3];
    unsigned int color;

    if (turret->hp > 0)
    {
        std_draw(pix, zbuffer, &turret->obj, foca);
        poos[0] = std_decal(pix, std_perspective(turret->vect.x, turret->vect.y, turret->vect.z, foca));
        std_set_pixel(pix, poos[0], BLUE);

        /*
        poos[0] = std_decal(pix, std_perspective(turret->obj.position.x, turret->obj.position.y, turret->obj.position.z, foca));
        color = RED;
        poos[1].x = poos[0].x - 100;
        poos[1].y = poos[0].y - 50;
        poos[2].x = std_get_value(std_get_ratio(turret->maxhp, 0, turret->hp), poos[0].x - 100, poos[0].x + 100);
        poos[2].y = poos[0].y - 50;
        std_set_line(pix, &poos[1], &color);
        */
    }
}

