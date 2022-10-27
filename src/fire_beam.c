
#include <starglider.h>

void fire_beam(t_bunny_pixelarray   *pix,
               float                *zbuffer,
               t_pos                *pos,
               unsigned int         *color)
{
    std_set_zline(pix, zbuffer, pos, color);
}

