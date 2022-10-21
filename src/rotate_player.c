
#include <starglider.h>

t_pos rotate_player(t_pos pos,
                    char axe,
                    float step)
{
    t_pos newpos;

    newpos = pos;
    newpos.x = newpos.y * sin(newpos.z) + newpos.x * cos(newpos.z);
    newpos.y = newpos.x * sin(newpos.z) + newpos.y * cos(newpos.z);
    newpos.z = newpos.y * sin(newpos.x) + newpos.x * cos(newpos.y);
    if (axe == 'x')
    {
        newpos.x = newpos.x + step * cos(pos.z);
        newpos.y = newpos.y + step * sin(pos.z);
        newpos.z = newpos.z + step * cos(pos.y);
    }
    if (axe == 'y')
    {
        newpos.x = newpos.x + step * sin(pos.z);
        newpos.y = newpos.y + step * cos(pos.z);
        newpos.z = newpos.z + step * sin(pos.x);
    }
    if (axe == 'z')
    {
        newpos.x = newpos.x + step * cos(pos.z);
        newpos.y = newpos.y + step * sin(pos.z);
        newpos.z = newpos.z + step * cos(pos.y);
    }


    return (newpos);
}
