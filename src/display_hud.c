
#include <starglider.h>

void display_hud(t_data *data)
{
    t_bunny_position pos[2];
    unsigned int color;

    color = GREEN;
    pos[0].x = data->pix->clipable.buffer.width * 0.05;
    pos[0].y = data->pix->clipable.buffer.height * 0.05;
    pos[1].x = std_get_value(std_get_ratio(data->player.maxhp, 0, data->player.hp), data->pix->clipable.buffer.width * 0.05, data->pix->clipable.buffer.width * 0.4);
    pos[1].y = data->pix->clipable.buffer.height * 0.05;
    std_set_line(data->pix, pos, &color);

    color = BLUE;
    pos[0].x = data->pix->clipable.buffer.width * 0.05;
    pos[0].y = data->pix->clipable.buffer.height * 0.06;
    pos[1].x = std_get_value(std_get_ratio(data->player.maxenergy, 0, data->player.energy), data->pix->clipable.buffer.width * 0.05, data->pix->clipable.buffer.width * 0.4);
    pos[1].y = data->pix->clipable.buffer.height * 0.06;
    std_set_line(data->pix, pos, &color);

    color = YELLOW;
    pos[0].x = data->pix->clipable.buffer.width * 0.05;
    pos[0].y = data->pix->clipable.buffer.height * 0.07;
    pos[1].x = std_get_value(std_get_ratio(data->player.maxammo, 0, data->player.ammo), data->pix->clipable.buffer.width * 0.05, data->pix->clipable.buffer.width * 0.4);
    pos[1].y = data->pix->clipable.buffer.height * 0.07;
    std_set_line(data->pix, pos, &color);
}

