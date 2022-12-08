
#include <starglider.h>

void draw_turret(t_bunny_pixelarray	*pix,
                 float                  *zbuffer,
                 t_turret		*turret,
                 float                  foca)
{
    t_bunny_position poos[3];

    if (turret->hp > 0)
    {
        std_draw(pix, zbuffer, &turret->obj, foca);
        poos[0] = std_decal(pix, std_perspective(turret->vect.x, turret->vect.y, turret->vect.z, foca));
        std_set_pixel(pix, poos[0], BLUE);
    }
}

