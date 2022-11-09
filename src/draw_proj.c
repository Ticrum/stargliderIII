
#include <starglider.h>

void draw_proj(t_bunny_pixelarray   *pix,
               t_proj               *proj,
               float                *zbuffer,
               t_pos                rota,
               t_pos                posi,
               float                foca,
               int                  len)
{
    t_pos pos;
    //t_pos posi;
    t_bunny_position poos2;
    t_pos poos;
    int compt;

    pos.x = 0;
    pos.y = 40;
    pos.z = -800;
    compt = 0;
    while (compt < len)
    {
        if (proj[compt].act == true)
        {
            proj[compt].pos.x = proj[compt].pos.x + posi.x;
            proj[compt].pos.y = proj[compt].pos.y + posi.y;
            proj[compt].pos.z = proj[compt].pos.z + posi.z;
            proj[compt].pos = stdtruerotation(proj[compt].pos, rota, pos);
            poos2 = std_decal(pix, std_perspective(proj[compt].pos.x, proj[compt].pos.y, proj[compt].pos.z, foca));
            poos.x = poos2.x;
            poos.y = poos2.y;
            poos.z = proj[compt].pos.z;
            std_set_zpixel(pix, zbuffer, poos, YELLOW);
            proj[compt].vect.x = proj[compt].vect.x + posi.x;
            proj[compt].vect.y = proj[compt].vect.y + posi.y;
            proj[compt].vect.z = proj[compt].vect.z + posi.z;
            proj[compt].vect = stdtruerotation(proj[compt].vect, rota, pos);
            poos2 = std_decal(pix, std_perspective(proj[compt].vect.x, proj[compt].vect.y, proj[compt].vect.z, foca));
            poos.x = poos2.x;
            poos.y = poos2.y;
            poos.z = proj[compt].pos.z;
            std_set_zpixel(pix, zbuffer, poos, RED);
            poos.x = poos.x + 1;
            std_set_zpixel(pix, zbuffer, poos, YELLOW);
            poos.x = poos.x - 2;
            //std_set_zpixel(pix, zbuffer, poos, YELLOW);
        }
        //else
            //write(1,"a",1);
        compt = compt + 1;
    }
}


