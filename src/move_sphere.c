
#include <starglider.h>

void move_sphere(t_sphere   *sphere,
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

    sphere->pos = add_pos(sphere->pos, posi);
    sphere->pos = stdtruerotation(sphere->pos, rotation, pos[3]);

    while (compt[0] < sphere->res + 1)
    {
        tempres = sphere->res;
        compt[1] = 0;
        while (compt[1] < (tempres * 2) + 1)
        {
            sphere->po[compt[0]][compt[1]] = add_pos(sphere->po[compt[0]][compt[1]], posi);
            sphere->po[compt[0]][compt[1]] = stdtruerotation(sphere->po[compt[0]][compt[1]], rotation, pos[3]);
            compt[1] = compt[1] + 1;
        }
        compt[0] = compt[0] + 1;
    }
}
