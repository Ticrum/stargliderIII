
#include <starglider.h>

void move_proj(t_proj   *proj,
               int      len,
               t_pos    rota,
               t_pos    posi2)
{
    //t_pos pos;
    t_pos posi;
    t_pos pos;
    int compt;

    pos.x = 0;
    pos.y = 40;
    pos.z = -800;
    compt = 0;
    while (compt < len)
    {
        if (proj[compt].act == true)
        {
            //pos = proj[compt].pos;
            posi.x = proj[compt].vect.x - proj[compt].pos.x;
            posi.y = proj[compt].vect.y - proj[compt].pos.y;
            posi.z = proj[compt].vect.z - proj[compt].pos.z;
            proj[compt].pos = add_pos(proj[compt].pos, posi);
            proj[compt].vect = add_pos(proj[compt].vect, posi);
            proj[compt].pos = add_pos(proj[compt].pos, posi2);
            proj[compt].pos = stdtruerotation(proj[compt].pos, rota, pos);
            proj[compt].vect = add_pos(proj[compt].vect, posi2);
            proj[compt].vect = stdtruerotation(proj[compt].vect, rota, pos);
        }
        compt = compt + 1;
    }
}

