
#include <starglider.h>

void dmg_player(t_data  *data,
                int     len)
{
    int compt;

    compt = 0;
    while (compt != len)
    {
        //printf("%f %f %f\n", data->enemy[compt].obj.position.x, data->enemy[compt].obj.position.y, data->enemy[compt].obj.position.z);
        if ((data->enemy[compt].obj.position.x > -60 && data->enemy[compt].obj.position.x < 60) &&
            (data->enemy[compt].obj.position.y > -20 && data->enemy[compt].obj.position.y < 100) &&
            (data->enemy[compt].obj.position.z > -860 && data->enemy[compt].obj.position.z < -740))
            data->player.hp = data->player.hp - 1;
        compt = compt + 1;
    }
}

