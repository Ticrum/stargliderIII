
#include <starglider.h>

void dmg_player_proj(t_data  *data,
                     int     len)
{
    int compt;
    int compt2;

    compt2 = 0;
    while (compt2 < data->nbr_turret)
    {
        compt = 0;
        while (compt != len)
        {
            //printf("%f %f %f\n", data->enemy[compt].obj.position.x, data->enemy[compt].obj.position.y, data->enemy[compt].obj.position.z);
            if ((data->turret[compt2].proj[compt].pos.x > -60 && data->turret[compt2].proj[compt].pos.x < 60) &&
                (data->turret[compt2].proj[compt].pos.y > -20 && data->turret[compt2].proj[compt].pos.y < 100) &&
                (data->turret[compt2].proj[compt].pos.z > -860 && data->turret[compt2].proj[compt].pos.z < -740) &&
                data->turret[compt2].proj[compt].act == true)
            {
                data->player.hp = data->player.hp - data->turret[compt2].dmg;
                data->turret[compt2].proj[compt].act = false;
            }
            compt = compt + 1;
        }
        compt2 = compt2 + 1;
    }
}

