
#include <starglider.h>

void move_proj(t_proj   *proj,
               int      len)
{
    t_pos pos;
    t_pos posi;
    int compt;

    compt = 0;
    while (compt < len)
    {
        if (proj[compt].act == true)
        {
            pos = proj[compt].pos;
            posi.x = proj[compt].vect.x - proj[compt].pos.x;
            posi.y = proj[compt].vect.y - proj[compt].pos.y;
            posi.z = proj[compt].vect.z - proj[compt].pos.z;
            proj[compt].pos.x = proj[compt].pos.x + posi.x;
            proj[compt].pos.y = proj[compt].pos.y + posi.y;
            proj[compt].pos.z = proj[compt].pos.z + posi.z;
            proj[compt].vect.x = proj[compt].vect.x + posi.x;
            proj[compt].vect.y = proj[compt].vect.y + posi.y;
            proj[compt].vect.z = proj[compt].vect.z + posi.z;
        }
        compt = compt + 1;
    }
}

