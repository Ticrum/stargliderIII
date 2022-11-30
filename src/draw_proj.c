
#include <starglider.h>

void draw_proj(t_bunny_pixelarray   *pix,
               t_proj               *proj,
               float                *zbuffer,
               float                foca,
               int                  len)
{
    t_bunny_position poos2;
    t_pos poos;
    int compt;

    compt = 0;
    while (compt < len)
    {
        if (proj[compt].act == true)
        {
            //proj[compt].pos = add_pos(proj[compt].pos, posi);
            //proj[compt].pos = stdtruerotation(proj[compt].pos, rota, pos);
            poos2 = std_decal(pix, std_perspective(proj[compt].pos.x, proj[compt].pos.y, proj[compt].pos.z, foca));
            poos.x = poos2.x;
            poos.y = poos2.y;
            poos.z = proj[compt].pos.z;
            std_set_zpixel(pix, zbuffer, poos, YELLOW);
            //proj[compt].vect = add_pos(proj[compt].vect, posi);
            //proj[compt].vect = stdtruerotation(proj[compt].vect, rota, pos);
            poos2 = std_decal(pix, std_perspective(proj[compt].vect.x, proj[compt].vect.y, proj[compt].vect.z, foca));
            poos.x = poos2.x;
            poos.y = poos2.y;
            poos.z = proj[compt].pos.z;
            std_set_zpixel(pix, zbuffer, poos, RED);
            poos.x = poos.x + 1;
            std_set_zpixel(pix, zbuffer, poos, YELLOW);
            poos.x = poos.x - 2;
        }
        compt = compt + 1;
    }
}


