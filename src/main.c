
#include <starglider.h>

static void respawn_present(t_data *data)
{
    int compt;

    compt = 0;
    while (compt < data->nbr_boss)
        {
            data->boss[compt].hp = data->boss[compt].maxhp;
            compt = compt + 1;
        }
}

static void player_movement(t_data  *data,
                            t_pos   *move,
                            t_pos   *rota)
{
    t_pos pos[2];
    int x;
    int y;
    unsigned int color;

    x = data->pix->clipable.buffer.width;
    y = data->pix->clipable.buffer.height;
    if (bunny_get_keyboard()[BKS_S] || (data->joy_mode == true && bunny_get_joy_axis()[0][1] > 50))
    {
        data->player.pos.z = data->player.pos.z + 5;
        move->z = 5;
    }
    if (bunny_get_keyboard()[BKS_Z] || (data->joy_mode == true && bunny_get_joy_axis()[0][1] < -50))
    {
        data->player.pos.z = data->player.pos.z - 13;
        move->z = -15;
    }
    if (bunny_get_keyboard()[BKS_D] || (data->joy_mode == true && bunny_get_joy_axis()[0][0] > 50))
    {
        data->player.pos.x = data->player.pos.x - 10;
        move->x = -7;
    }
    if (bunny_get_keyboard()[BKS_Q] || (data->joy_mode == true && bunny_get_joy_axis()[0][0] < -50))
    {
        data->player.pos.x = data->player.pos.x + 10;
        move->x = 7;
    }
    if (bunny_get_keyboard()[BKS_A] || ((data->joy_mode == true && bunny_get_joy_axis()[0][1] > 50) && (data->joy_mode == true && bunny_get_joy_button()[0][1] == true)))
    {
        data->player.pos.y = data->player.pos.y - 10;
        move->y = -7;
    }
    if (bunny_get_keyboard()[BKS_E] || ((data->joy_mode == true && bunny_get_joy_axis()[0][1] < -50) && (data->joy_mode == true && bunny_get_joy_button()[0][1] == true)))
    {
        data->player.pos.y = data->player.pos.y + 10;
        move->y = 7;
    }
    if (bunny_get_keyboard()[BKS_O] || (data->joy_mode == true && bunny_get_joy_axis()[1][1] < -50))
    {
        data->player.rotation.x = data->player.rotation.x + 0.025;
        rota->x = -0.025;
    }
    if (bunny_get_keyboard()[BKS_L] || (data->joy_mode == true && bunny_get_joy_axis()[1][1] > 50))
    {
        data->player.rotation.x = data->player.rotation.x - 0.025;
        rota->x = 0.025;
    }
    if (bunny_get_keyboard()[BKS_K] || ((data->joy_mode == true && bunny_get_joy_axis()[1][0] < -50) && (data->joy_mode == true && bunny_get_joy_button()[1][3] == false)))
    {
        data->player.rotation.y = data->player.rotation.y + 0.025;
        rota->y = 0.025;
    }
    if (bunny_get_keyboard()[BKS_M] || ((data->joy_mode == true && bunny_get_joy_axis()[1][0] > 50) && (data->joy_mode == true && bunny_get_joy_button()[1][3] == false)))
    {
        data->player.rotation.y = data->player.rotation.y - 0.025;
        rota->y = -0.025;
    }
    if (bunny_get_keyboard()[BKS_P] || ((data->joy_mode == true && bunny_get_joy_axis()[1][0] > 50) && (data->joy_mode == true && bunny_get_joy_button()[1][3] == true)))
    {
        data->player.rotation.z = data->player.rotation.z + 0.05;
        rota->z = -0.05;
    }
    if (bunny_get_keyboard()[BKS_I] || ((data->joy_mode == true && bunny_get_joy_axis()[1][0] < -50) && (data->joy_mode == true && bunny_get_joy_button()[1][3] == true)))
    {
        data->player.rotation.z = data->player.rotation.z - 0.05;
        rota->z = 0.05;
    }
    if ((bunny_get_keyboard()[BKS_LCONTROL] || (data->joy_mode == true && bunny_get_joy_button()[0][0] == true)) && data->player.energy > 0)
    {
        move->x = move->x * 3;
        move->y = move->y * 3;
        move->z = move->z * 3;
        rota->x = rota->x * 2;
        rota->y = rota->y * 2;
        rota->z = rota->z * 2;
        data->player.energy = data->player.energy - 2;
        pos[0].x = x * 0.5 + y * -0.081;
        pos[0].y = y * 0.68;//500;
        pos[0].z = -900;
        pos[1].x = x * 0.5 + y * -0.05;//445;
        pos[1].y = y * 0.63;// + 145;
        pos[1].z = -900;
        color = PURPLE;
        fire_beam(data->pix, data->zbuffer, pos, &color);
        pos[0].x = x * 0.5 + y * 0.081;
        pos[0].y = y * 0.68;//500;
        pos[0].z = -900;
        pos[1].x = x * 0.5 + y * 0.05;
        pos[1].y = y * 0.63;// + 145;
        pos[1].z = -900;
        fire_beam(data->pix, data->zbuffer, pos, &color);
    }
}

static void draw_all_enemy(t_data *data)
{
    int compt;
    int compt2;

    compt = 0;
    while (compt < data->nbr_enemy)
    {
        draw_enemy(data->pix, data->zbuffer, &data->enemy[compt], data->foca);
        compt = compt + 1;
    }
    compt = 0;
    while (compt < data->nbr_turret)
    {
        draw_turret(data->pix, data->zbuffer, &data->turret[compt], data->foca);
        draw_proj(data->pix, data->turret[compt].proj, data->zbuffer, data->foca, 50);
        compt = compt + 1;
    }
    compt = 0;
    while (compt < data->nbr_boss)
    {
        draw_boss(data->pix, data->zbuffer, &data->boss[compt], data->foca);
        compt2 = 0;
        if (data->boss[compt].hp > 0)
            while (compt2 < data->boss[compt].nbr_turret)
                {
                    draw_turret(data->pix, data->zbuffer, &data->boss[compt].turret[compt2], data->foca);
                    draw_proj(data->pix, data->boss[compt].turret[compt2].proj, data->zbuffer, data->foca, 50);
                    compt2 = compt2 + 1;
                }
        compt = compt + 1;
    }
}

static void move_all_enemy(t_data *data)
{
    int compt;
    int compt2;

    compt = 0;
    while (compt < data->nbr_enemy)
    {
        move_enemy(&data->enemy[compt], data->rota, data->rota, data->move);
        compt = compt + 1;
    }
    compt = 0;
    while (compt < data->nbr_turret)
    {
        move_turret(&data->turret[compt], data->rota, data->rota, data->move);
        fire_turret_proj(&data->turret[compt]);
        move_proj(data->turret[compt].proj, 50, data->rota, data->move);
        compt = compt + 1;
    }
    compt = 0;
    while (compt < data->nbr_boss)
    {
        move_boss(&data->boss[compt], data->rota, data->rota, data->move);
        compt2 = 0;
        if (data->boss[compt].hp > 0)
            while (compt2 < data->boss[compt].nbr_turret)
                {
                    fire_turret_proj(&data->boss[compt].turret[compt2]);
                    move_proj(data->boss[compt].turret[compt2].proj, 50, data->rota, data->move);
                    compt2 = compt2 + 1;
                }
        compt = compt + 1;
    }
}

static void draw_all_sphere(t_data *data)
{
    int compt;

    compt = 0;
    while (compt < data->nbr_sphere)
    {
        t_bunny_position posi = std_perspective(data->sphere[compt].po[0][0].x, data->sphere[compt].po[0][0].y, data->sphere[compt].po[0][0].z, data->foca);
        if (posi.x > -1000 && posi.x < data->pix->clipable.buffer.width + 100 &&
            posi.y > -800 && posi.y < data->pix->clipable.buffer.height + 100)
            draw_sphere(data->pix, data->zbuffer, &data->sphere[compt], data->foca);
        compt = compt + 1;
    }
}

static void move_all_sphere(t_data *data)
{
    int compt;

    compt = 0;
    while (compt < data->nbr_sphere)
    {
        move_sphere(&data->sphere[compt], data->rota, data->move);
        //draw_sphere(data->pix, data->zbuffer, &data->sphere[compt], data->foca);
        compt = compt + 1;
    }
    //draw_sphere(data->pix, data->zbuffer, &data->sphere[14], data->rota, data->move);
}

static t_bunny_response display(void *data2)
{
    t_data *data;
    double fps;

    data = (t_data *)data2;
    draw_star(data->pix, &data->star, data->foca);
    std_draw(data->pix, data->zbuffer, &data->obj[0], data->foca);

    draw_all_sphere(data);
    draw_all_enemy(data);

    draw_proj(data->pix, data->player.proj, data->zbuffer, data->foca, 50);

    data->obj[2].position.x = 0;//-data->pos.x;
    data->obj[2].position.y = 5;//300 * (1 - (data->p    //printf("%f\n", data->obj[2].position.y);
    data->obj[2].position.z = -520;//data->pix->clipable.buffer.height * -0.520;//-550;
    data->rota.x = 0.5;
    data->rota.y = 0;
    data->rota.z = 0;//0.5;
    std_draw_static(data->pix, data->zbuffer, &data->obj[2], data->rota, data->obj[2].position, data->foca);
    display_hud(data);
    bunny_blit(&data->win->buffer, &data->pix->clipable, NULL);
    bunny_display(data->win);

    fps = 1.0 / ((double)(clock() - data->time) / CLOCKS_PER_SEC);
    data->fps = data->fps + fps;
    data->compt = data->compt + 1;
    if (data->compt % 2 == 0)
        printf("FPS = %f Avr = %f\r",fps, data->fps / data->compt);
return (GO_ON);
}

static t_bunny_response loop(void *data2)
{
  t_data *data;
  t_pos pos[2];
  unsigned int color;
  int x;
  int y;

  data = (t_data *)data2;
  data->time = clock();
  std_clear_pixelarray(data->pix, BLACK);
  //write(1,"a",1);
  if (data->player.hp > 0)
      {
          x = data->pix->clipable.buffer.width;
          y = data->pix->clipable.buffer.height;
          respawn_enemy(data->enemy, data->nbr_enemy, &data->score);

          //if (data->player.hp < 0)
          //    return (EXIT_ON_SUCCESS);
          data->move.x = 0;
          data->move.y = 0;
          data->move.z = 0;
          data->rota.x = 0;
          data->rota.y = 0;
          data->rota.z = 0;
          clear_zbuffer(data->zbuffer, data->pix);

          player_movement(data, &data->move, &data->rota);

          if ((bunny_get_keyboard()[BKS_SPACE] || (data->joy_mode == true && bunny_get_joy_button()[1][0] == true)) && data->player.energy > 0)
              {
                  if (data->mode == false)
                      {
                          pos[0].x = x * 0.5;//500;
                          pos[0].y = y * 0.5;//500;
                          pos[0].z = 400;
                          pos[1].x = x * 0.5 + y * -0.15;//445;
                          pos[1].y = y * 0.645;// + 145;
                          pos[1].z = -800;
                          color = PURPLE;
                          fire_beam(data->pix, data->zbuffer, pos, &color);
                          pos[1].x = x * 0.5 + y * 0.15;
                          pos[1].y = y * 0.645;// + 145;
                          pos[1].z = -800;
                          fire_beam(data->pix, data->zbuffer, pos, &color);
                          data->player.energy = data->player.energy - 3;
                      }
                  else if (data->player.ammo > 0 && data->player.r == false)
                      {
                          fire_proj(&data->player);
                          data->player.ammo = data->player.ammo - 2;
                      }
                  dmg_enemy(data->enemy, data->player.proj, data->nbr_enemy, data->mode);
                  dmg_boss(data->boss, data->player.proj, data->nbr_boss, data->mode, &data->score);
              }
          if (bunny_get_keyboard()[BKS_UP])
              data->foca = data->foca + 5;
          if (bunny_get_keyboard()[BKS_DOWN])
              data->foca = data->foca - 5;

          if (bunny_get_keyboard()[BKS_LEFT] && bunny_get_keyboard()[BKS_T] && bunny_get_keyboard()[BKS_B])
              respawn_present(data);
          if (data->player.energy < data->player.maxenergy)
              data->player.energy = data->player.energy + 1;

          if (data->player.ammo <= 0)
              data->player.r = true;
          if (data->player.ammo < data->player.maxammo && data->player.r == true)
              data->player.ammo = data->player.ammo + 1;
          if (data->player.ammo >= data->player.maxammo)
              data->player.r = false;

          move_star(&data->star, data->rota);
          std_move(&data->obj[0], data->rota, data->move);

          dmg_player(data, data->nbr_enemy);
          dmg_player_proj(data, 50);

          move_all_sphere(data);
          move_all_enemy(data);

          move_proj(data->player.proj, 50, data->rota, data->move);
      }
  return (GO_ON);
}

static t_bunny_response std_stop(t_bunny_event_state state,
				 t_bunny_keysym      keycode,
				 void                *data2)
{
  t_data *data;

  data = (t_data *)data2;
  if (state == GO_UP)
    return (GO_ON);
  if (keycode == BKS_R)
      data->player.r = true;
  if (keycode == BKS_F)
  {
      if (data->mode == false)
          data->mode = true;
      else
          data->mode = false;
      //printf("%d\n", data->mode);
  }
  if (keycode == BKS_N)
      {
          printf("\nscore : %d\n", data->score);
          init_game(data);
      }
  if (keycode == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

static t_bunny_response joy_con(t_bunny_event_state state,
                                int                 joyid,
                                const t_bunny_joystick *joyinfo,
                                void                *data2)
{
    t_data *data;

    data = (t_data *)data2;
    (void)state;
    (void)joyid;
    (void)joyinfo;
    (void)data;
    return (GO_ON);
}

static t_bunny_response joy_axe(int                 joyid,
                                t_bunny_axis        axis,
                                float               value,
                                void                *data2)
{
    (void)joyid;
    (void)axis;
    (void)value;
    (void)data2;
    return (GO_ON);
}

static t_bunny_response joy(t_bunny_event_state state,
                            int                 joyif,
                            int                 button,
                            void                *data2)
{
  t_data *data;

  data = (t_data *)data2;
  //write(1,"but\n",4);
  if (state == GO_UP)
    return (GO_ON);
  if (button == 2 && joyif == 1)
      data->player.r = true;
  if (button == 1 && joyif == 1)
  {
      if (data->mode == false)
          data->mode = true;
      else
          data->mode = false;
      //printf("%d\n", data->mode);
  }
  if (button == 3 && joyif == 0)
      {
          printf("\nscore : %d\n", data->score);
          init_game(data);
      }
  return (GO_ON);
}

int main(void)
{
    //printf("%zu\n", sizeof(t_data));
    //return (0);
    t_data data;

    data.resox = 1280;//1280
    data.resoy = 720;//720
    data.win = bunny_start(data.resox, data.resoy, false, "Bunny");
    init_game(&data);
    printf("Game started\n");
    bunny_set_loop_main_function(loop);
    bunny_set_key_response(std_stop);
    if (data.joy_mode == true)
        {
            bunny_set_joy_connect_response(joy_con);
            bunny_set_joy_button_response(joy);
            bunny_set_joy_axis_response(joy_axe);
            write(1,"yes\n",4);
        }
    bunny_set_display_function(display);
    bunny_loop(data.win, 60, (void *)&data);
    bunny_stop(data.win);
    printf("\nscore : %d\n", data.score);
    free_game(data);
    return (0);
}

