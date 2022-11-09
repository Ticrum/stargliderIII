
#include <starglider.h>

void fire_proj(t_player *player)
{
    t_pos pos;

    //srand(clock());
    pos.x = 0;
    pos.y = 40;
    pos.z = -800;
    player->proj[player->shot_compt].pos = pos;
    pos.z = -700;
    pos.y = pos.y + ((rand() % 10 - 5) / 5.0);
    pos.x = pos.x + ((rand() % 10 - 5) / 5.0);
    player->proj[player->shot_compt].vect = pos;
    player->proj[player->shot_compt].act = true;
    player->shot_compt = player->shot_compt + 1;
    if (player->shot_compt == 50)
        player->shot_compt = 0;
}

