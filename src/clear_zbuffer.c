
#include <starglider.h>

void clear_zbuffer(float                *zbuffer,
                   t_bunny_pixelarray   *pix)
{
    int compt;

    compt = 0;
    while (compt < pix->clipable.buffer.width * pix->clipable.buffer.height)
    {
        zbuffer[compt] = 100000;
        compt = compt + 1;
    }
}

