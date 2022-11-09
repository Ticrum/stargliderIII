
#include <starglider.h>

static void free_obj(t_data data)
{
    int compt;

    compt = 0;
    while (compt < data.nbr_obj)
    {
        free(data.obj[compt].pos);
        compt = compt + 1;
    }
}

void free_game(t_data data)
{
    free(data.zbuffer);
    bunny_delete_clipable(&data.pix->clipable);
    //free_obj(data);
}

