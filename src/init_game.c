
#include <starglider.h>

static void init_world(t_data *data)
{
    t_pos pos;
    int resox;
    int resoy;

    resox = 1000;
    resoy = 1000;
    pos.x = 0;//-10;
    pos.y = 0;//20;
    pos.z = 1;//-400;

    data->player.hp = 100;
    data->player.maxhp = 100;
    data->player.energy = 100;
    data->player.maxenergy = 100;

    data->player.pos.z = 1;
    data->player.pos.y = 0;
    data->player.pos.x = 0;
    data->player.tpos = data->player.pos;
    data->player.rotation.x = 0;
    data->player.rotation.y = 0;
    data->player.rotation.z = 0;
    data->player.vect = pos;

    data->score = 0;
    data->win = bunny_start(resox, resoy, false, "Bunny");
    data->pix = bunny_new_pixelarray(resox, resoy);
    data->zbuffer = create_zbuffer(data->pix);
    data->obj[0] = load_obj("test_space.dab", 17, pos);
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    data->obj[1] = load_obj("test.dab", 3, pos);
    pos.x = 0;
    pos.y = 400;
    pos.z = 0;
    data->sphere[0] = load_sphere(pos, 300, 8);
    pos.x = 1000;
    pos.y = 600;
    pos.z = 1000;
    data->sphere[1] = load_sphere(pos, 400, 10);
    pos.x = -1000;
    pos.y = 200;
    pos.z = 600;
    data->sphere[2] = load_sphere(pos, 200, 6);
    pos.x = 0;
    pos.y = 0;
    pos.z = 3500;
    data->sphere[3] = load_sphere(pos, 3500, 10);
    pos.x = 0;
    pos.y = 30;
    pos.z = -300;
    data->obj[2] = load_obj("CPU.dab", 9, pos);
}

t_data init_game(void)
{
    t_data data;
    t_pos pos;

    init_world(&data);
    pos.x = 100;//-10;
    pos.y = 50;//20;
    pos.z = 0;//-400;
    data.enemy[0] = init_enemy("test_space.dab", 17, pos, 1, 100);
    pos.x = 250;//-10;
    pos.y = 150;//20;
    pos.z = 0;//-400;
    data.enemy[1] = init_enemy("test_space.dab", 17, pos, 1, 100);
    pos.x = 400;//-10;
    pos.y = -50;//20;
    pos.z = 0;//-400;
    data.enemy[2] = init_enemy("test_space.dab", 17, pos, 1, 100);
    return (data);
}

