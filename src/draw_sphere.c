
#include <starglider.h>

static void decal_sphere(t_sphere   *sphere,
                         t_pos      rotation,
                         t_pos      posi)
{
    t_pos pos[4];
    int compt[2];

    compt[0] = 0;
    pos[3].x = 0;
    pos[3].y = 40;
    pos[3].z = -800;
    while (compt[0] < sphere->res + 1)
    {
        //color.full = RED;
        compt[1] = 0;
        while (compt[1] < (sphere->res * 2) + 1)
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
                 t_sphere               *sphere,
                 t_pos			rotation,
                 t_pos			posi)
{
    t_pos pos[3];
    t_bunny_color color;
    int compt[2];

    color.full = RED;
    compt[0] = 0;
    decal_sphere(sphere, rotation, posi);
    while (compt[0] < sphere->res)
    {
        compt[1] = 0;
        while (compt[1] < (sphere->res * 2))
        {
            //printf("display %d %d\n", compt[0], compt[1]);
            pos[0] = sphere->po[compt[0]][compt[1]];
            pos[1] = sphere->po[compt[0]][compt[1] + 1];
            pos[2] = sphere->po[compt[0] + 1][compt[1]];
            std_set_triangle(pix, pos, &color.full, NULL, NULL, 0);
            pos[0] = sphere->po[compt[0]][compt[1] + 1];
            pos[1] = sphere->po[compt[0] + 1][compt[1] + 1];
            pos[2] = sphere->po[compt[0] + 1][compt[1]];
            std_set_triangle(pix, pos, &color.full, NULL, NULL, 0);
            compt[1] = compt[1] + 1;
        }
        color.argb[RED_CMP] = color.argb[RED_CMP] - 200.0 / (float)sphere->res;
        compt[0] = compt[0] + 1;
    }
}

