
#include <starglider.h>

t_sphere load_sphere(t_pos               pos,
                     int                 radius,
                     int                 res,
                     unsigned int        color)
{
    double angle;
    double angle2;
    t_sphere sphere;
    int compt[2];
    int tempres;

    sphere.pos = pos;
    sphere.radius = radius;
    sphere.res = res;
    sphere.color = color;
    if ((sphere.po = malloc(sizeof(t_pos *) * (res + 1))) == NULL)
        write(1, "malloc err", 10);
    compt[0] = 0;
    angle = -M_PI / 2;
    while (compt[0] < res + 1)//angle <= M_PI / 2)
    {
        tempres = res;
        //if (compt[0] < 10)
        //    tempres = res / 4;//compt[0] + 4;
        if ((sphere.po[compt[0]] = malloc(sizeof(t_pos) * (tempres * 2 + 1))) == NULL)
            write(1, "malloc err", 10);
        compt[1] = 0;
        angle2 = -M_PI;
        while (compt[1] < tempres * 2 + 1)//angle2 <= M_PI)
        {
	    //printf("%d %d\n", compt[0], compt[1]);
            sphere.po[compt[0]][compt[1]].x = pos.x + (radius * cos(angle) * cos(angle2));
            sphere.po[compt[0]][compt[1]].y = pos.y + (radius * cos(angle) * sin(angle2));
            sphere.po[compt[0]][compt[1]].z = pos.z + (radius * sin(angle));
            angle2 = angle2 + ((M_PI * 2.0) / ((float)tempres * 2.0));
            compt[1] = compt[1] + 1;
        }
        compt[0] = compt[0] + 1;
        angle = angle + (M_PI / (float)res);
    }
    //write(1,"pass",4);
    //printf("%p\n", sphere.po[0]);
    return (sphere);
}

