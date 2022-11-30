
#include <starglider.h>

void draw_sphere(t_bunny_pixelarray	*pix,
                 float                  *zbuffer,
                 t_sphere               *sphere,
                 float                  foca)
{
    t_pos pos[3];
    t_bunny_color color;
    int compt[2];
    int tempres;

    color.full = sphere->color;
    compt[0] = 0;
    while (compt[0] < sphere->res)
    {
        tempres = sphere->res;
        compt[1] = 0;
        while (compt[1] < (tempres * 2))
        {
            pos[0] = sphere->po[compt[0]][compt[1]];
            pos[1] = sphere->po[compt[0]][compt[1] + 1];
            pos[2] = sphere->po[compt[0] + 1][compt[1]];
            std_set_ztriangle(pix, zbuffer, pos, &color.full, NULL, NULL, 0, foca);
            pos[0] = sphere->po[compt[0]][compt[1] + 1];
            pos[1] = sphere->po[compt[0] + 1][compt[1] + 1];
            pos[2] = sphere->po[compt[0] + 1][compt[1]];
            std_set_ztriangle(pix, zbuffer, pos, &color.full, NULL, NULL, 0, foca);
            compt[1] = compt[1] + 1;
        }
        if (color.argb[RED_CMP] - 200.0 / (float)sphere->res >= 0)
            color.argb[RED_CMP] = color.argb[RED_CMP] - 200.0 / (float)sphere->res;
        if (color.argb[BLUE_CMP] - 200.0 / (float)sphere->res >= 0)
            color.argb[BLUE_CMP] = color.argb[BLUE_CMP] - 200.0 / (float)sphere->res;
        if (color.argb[GREEN_CMP] - 200.0 / (float)sphere->res >= 0)
            color.argb[GREEN_CMP] = color.argb[GREEN_CMP] - 200.0 / (float)sphere->res;
        compt[0] = compt[0] + 1;
    }
}

