
#include <starglider.h>

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

static void init_world(t_data *data)
{
    t_pos pos;
    int resox;
    int resoy;
    int compt;

    printf("loading world...\n");
    resox = 1280;//1280
    resoy = 720;//720
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
    data->foca = 1000 * ( 1.0 + (1.0 - ((resoy) / 1000.0)));
    data->win = bunny_start(resox, resoy, false, "Bunny");
    data->pix = bunny_new_pixelarray(resox, resoy);
    data->zbuffer = create_zbuffer(data->pix);
    data->obj[0] = load_obj("test_space.dab", 17, pos);
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    data->obj[1] = load_obj("test.dab", 3, pos);

    data->nbr_sphere = 17;
    compt = 0;
    while (compt < data->nbr_sphere)
    {
        pos.x = 0 + (rand() % 8000 - 4000);
        pos.y = 0 + (rand() % 8000 - 4000);
        pos.z = 600 + (rand() % 10000 - 5000);
        data->sphere[compt] = load_sphere(pos, rand() % 600 + 100, 15, rand());
        printf("%d / %d\r", compt + 1, data->nbr_sphere);
        compt = compt + 1;
    }
    /*
    pos.x = 0;
    pos.y = 0;
    pos.z = -7000;
    data->sphere[14] = load_sphere(pos, 1000, 12, YELLOW);//rand() % 300 + 50
    */
    pos.x = 0;
    pos.y = 30;
    pos.z = -300;
    data->obj[2] = load_obj("CPU.dab", 9, pos);
}

t_data init_game(void)
{
    t_data data;
    t_pos pos;
    int compt;

    srand(time(NULL));
    printf("Start loading...\n\n");
    init_world(&data);
    printf("\nDone\n\n");
    init_star(&data);
    data.nbr_enemy = 1;
    printf("loading enemy...\n");
    compt = 0;
    while (compt < data.nbr_enemy)
    {
        pos.x = 100 + (rand() % 2000 - 1000);//-10;
        pos.y = 50 + (rand() % 2000 - 1000);//20;
        pos.z = 0 + (rand() % 2000 - 1000);//-400;
        data.enemy[compt] = init_enemy("test_space.dab", 17, pos, 1, 100);
        printf("%d / %d\r", compt + 1, data.nbr_enemy);
        compt = compt + 1;
    }
    printf("\nDone\n\n");
    return (data);
}

