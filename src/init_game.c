
#include <starglider.h>

static void init_proj(t_data *data)
{
    int compt;

    data->player.shot_compt = 0;
    compt = 0;
    while (compt < 50)
    {
        data->player.proj[compt].act = false;
        compt = compt + 1;
    }
}

static void init_star(t_data *data)
{
    int compt;

    data->star.nbr_star = 600;
    if ((data->star.pos = malloc(sizeof(t_pos) * data->star.nbr_star)) == NULL)
        write(1, "malloc err init_star", 20);
    compt = 0;
    while (compt < data->star.nbr_star)
    {
        data->star.pos[compt].x = (rand() % 1000 - 500) * 100;
        data->star.pos[compt].y = (rand() % 1000 - 500) * 100;
        data->star.pos[compt].z = -800 + (rand() % 1000 - 500) * 100;
        compt = compt + 1;
    }
}

static void init_stats(t_data *data)
{
    data->compt = 0;
    data->fps = 0;

    data->player.hp = 1000;
    data->player.maxhp = 1000;
    data->player.energy = 100;
    data->player.maxenergy = 100;
    data->player.maxammo = 180;
    data->player.ammo = 180;
    data->player.r = false;

    data->player.pos.z = 1;
    data->player.pos.y = 0;
    data->player.pos.x = 0;
    data->player.vect = data->player.pos;
    data->player.tpos = data->player.pos;
    data->player.rotation.x = 0;
    data->player.rotation.y = 0;
    data->player.rotation.z = 0;

    data->mode = 0;
    data->score = 0;
    data->foca = 1000 * ( 1.0 + (1.0 - ((data->resoy) / 1000.0)));
    data->pix = bunny_new_pixelarray(data->resox, data->resoy);
    data->zbuffer = create_zbuffer(data->pix);

    //data->j0 = bunny_get_joy_info(0);
    //data->j1 = bunny_get_joy_info(1);
    if (bunny_get_joy_info(0)->connected == true) //|| data->j1->connected == true)
        data->joy_mode = true;
    else
        data->joy_mode = false;

}

static void init_world(t_data *data)
{
    t_pos pos;
    int compt;

    printf("loading world...\n");
    pos.x = 0;//-10;
    pos.y = 0;//20;
    pos.z = 1;//-400;

    data->obj[0] = load_obj("test_space.dab", 17, pos);
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    data->obj[1] = load_obj("test.dab", 3, pos);

    init_proj(data);
    data->nbr_sphere = 50;
    compt = 0;
    while (compt < data->nbr_sphere)
    {
        pos.x = 0 + (rand() % 20000 - 10000);
        pos.y = 0 + (rand() % 20000 - 10000);
        pos.z = 600 + (rand() % 26000 - 13000);
        data->sphere[compt] = load_sphere(pos, rand() % 600 + 100, 15, rand());
        printf("%d / %d\r", compt + 1, data->nbr_sphere);
        compt = compt + 1;
    }

    pos.x = 0;
    pos.y = 30;
    pos.z = -300;
    data->obj[2] = load_obj("CPU.dab", 9, pos);
}

t_data init_game(t_data *data)
{
    //t_data data;
    t_pos pos;
    int compt;

    srand(time(NULL));
    printf("Start loading...\n\n");
    init_stats(data);
    init_world(data);
    printf("\nDone\n\n");
    init_star(data);
    printf("loading enemy...\n");
    data->nbr_enemy = 5;
    compt = 0;
    while (compt < data->nbr_enemy)
    {
        pos.x = 100 + (rand() % 2000 - 1000);//-10;
        pos.y = 50 + (rand() % 2000 - 1000);//20;
        pos.z = 0 + (rand() % 2000 - 1000);//-400;
        data->enemy[compt] = init_enemy("test_space.dab", 17, pos, 10, 100);
        printf("%d / %d\r", compt + 1, data->nbr_enemy + data->nbr_turret);
        compt = compt + 1;
    }

    data->nbr_turret = 2;
    compt = 0;
    while (compt < data->nbr_turret)
    {
        pos.x = 100 + (rand() % 3000 - 1500);//-10;
        pos.y = 50 + (rand() % 3000 - 1500);//20;
        pos.z = 0 + (rand() % 3000 - 1500);//-400;
        data->turret[compt] = init_turret("turret.dab", 8, pos, 5, 100, 2);
        printf("%d / %d\r", compt + 1 + data->nbr_enemy, data->nbr_enemy + data->nbr_turret);
        compt = compt + 1;
    }

    data->nbr_boss = 3;
    compt = 0;
    while (compt < data->nbr_boss)
    {
        pos.x = 100 + (rand() % 5000 - 2500);//-10;
        pos.y = 50 + (rand() % 5000 - 2500);//20;
        pos.z = 0 + (rand() % 5000 - 2500);//-400;
        data->boss[compt] = init_boss("boss.dab", 17, pos, 8, 2000);
        //printf("%d / %d\r", compt + 1 + data.nbr_enemy, data.nbr_enemy + data.nbr_turret);
        compt = compt + 1;
    }

    printf("\nDone\n\n");
    return (*data);
}

