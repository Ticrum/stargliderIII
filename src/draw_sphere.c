
#include <starglider.h>

static void decal_sphere(t_sphere   *sphere,
                         t_pos      rotation,
                         t_pos      posi)
{
    t_pos pos[4];
    int compt[2];
    int tempres;

    compt[0] = 0;
    pos[3].x = 0;
    pos[3].y = 40;
    pos[3].z = -800;

    sphere->pos.x = sphere->pos.x + posi.x;
    sphere->pos.y = sphere->pos.y + posi.y;
    sphere->pos.z = sphere->pos.z + posi.z;
    sphere->pos = stdtruerotation(sphere->pos, rotation, pos[3]);

    while (compt[0] < sphere->res + 1)
    {
        tempres = sphere->res;
        //if (compt[0] < 10)
        //    tempres = sphere->res / 4;//compt[0OB] + 4;
        //color.full = RED;
        compt[1] = 0;
        while (compt[1] < (tempres * 2) + 1)
        {
            sphere->po[compt[0]][compt[1]].x = sphere->po[compt[0]][compt[1]].x + posi.x;
            sphere->po[compt[0]][compt[1]].y = sphere->po[compt[0]][compt[1]].y + posi.y;
            sphere->po[compt[0]][compt[1]].z = sphere->po[compt[0]][compt[1]].z + posi.z;
            sphere->po[compt[0]][compt[1]] = stdtruerotation(sphere->po[compt[0]][compt[1]], rotation, pos[3]);
            compt[1] = compt[1] + 1;
        }
        compt[0] = compt[0] + 1;
    }
}

void draw_sphere(t_bunny_pixelarray	*pix,
                 float                  *zbuffer,
                 t_sphere               *sphere,
                 t_pos			rotation,
                 t_pos			posi,
                 float                  foca)
{
    t_pos pos[3];
    t_bunny_color color;
    int compt[2];
    int tempres;

    color.full = sphere->color;
    compt[0] = 0;
    decal_sphere(sphere, rotation, posi);
    while (compt[0] < sphere->res)
    {
        tempres = sphere->res;
        //if (compt[0] < sphere->res / 2)
        //    tempres = sphere->res / 4;//compt[0] + 4;
        compt[1] = 0;
        while (compt[1] < (tempres * 2))
        {
            //printf("display %d %d\n", compt[0], compt[1]);
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

