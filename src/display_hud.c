
#include <starglider.h>

void display_hud(t_data *data)
{
    t_bunny_position pos[2];
    unsigned int color;

    color = GREEN;
    pos[0].x = 50;
    pos[0].y = 50;
    pos[1].x = std_get_value(std_get_ratio(data->player.maxhp, 0, data->player.hp), 50, 200);
    pos[1].y = 50;
    std_set_line(data->pix, pos, &color);

    color = BLUE;
    pos[0].x = 50;
    pos[0].y = 60;
    pos[1].x = std_get_value(std_get_ratio(data->player.maxenergy, 0, data->player.energy), 50, 200);
    pos[1].y = 60;
    std_set_line(data->pix, pos, &color);
}

