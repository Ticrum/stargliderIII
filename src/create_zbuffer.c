
#include <starglider.h>

float *create_zbuffer(t_bunny_pixelarray *pix)
{
    float *zbuffer;
    int compt;

    if ((zbuffer = malloc(sizeof(float) * (pix->clipable.buffer.width * pix->clipable.buffer.height))) == NULL)
        return (NULL);
    compt = 0;
    while (compt < pix->clipable.buffer.width * pix->clipable.buffer.height)
    {
        zbuffer[compt] = -100000;
        compt = compt + 1;
    }
    return (zbuffer);
}

