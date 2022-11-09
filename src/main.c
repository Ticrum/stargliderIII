
#include <starglider.h>

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
    if (bunny_get_keyboard()[BKS_S])
    {
        data->player.pos.z = data->player.pos.z + 5;
        move->z = 5;
    }
    if (bunny_get_keyboard()[BKS_Z])
    {
        data->player.pos.z = data->player.pos.z - 13;
        move->z = -15;
    }
    if (bunny_get_keyboard()[BKS_D])
    {
        data->player.pos.x = data->player.pos.x - 10;
        move->x = -7;
    }
    if (bunny_get_keyboard()[BKS_Q])
    {
        data->player.pos.x = data->player.pos.x + 10;
        move->x = 7;
    }
    if (bunny_get_keyboard()[BKS_A])
    {
        data->player.pos.y = data->player.pos.y - 10;
        move->y = -7;
    }
    if (bunny_get_keyboard()[BKS_E])
    {
        data->player.pos.y = data->player.pos.y + 10;
        move->y = 7;
    }
    if (bunny_get_keyboard()[BKS_O])
    {
        data->player.rotation.x = data->player.rotation.x + 0.025;
        rota->x = -0.025;
    }
    if (bunny_get_keyboard()[BKS_L])
    {
        data->player.rotation.x = data->player.rotation.x - 0.025;
        rota->x = 0.025;
    }
    if (bunny_get_keyboard()[BKS_K])
    {
        data->player.rotation.y = data->player.rotation.y + 0.025;
        rota->y = 0.025;
    }
    if (bunny_get_keyboard()[BKS_M])
    {
        data->player.rotation.y = data->player.rotation.y - 0.025;
        rota->y = -0.025;
    }
    if (bunny_get_keyboard()[BKS_P])
    {
        data->player.rotation.z = data->player.rotation.z + 0.05;
        rota->z = -0.05;
    }
    if (bunny_get_keyboard()[BKS_I])
    {
        data->player.rotation.z = data->player.rotation.z - 0.05;
        rota->z = 0.05;
    }
    if (bunny_get_keyboard()[BKS_LCONTROL] && data->player.energy > 0)
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

static void all_enemy(t_data *data)
{
    int compt;

    compt = 0;
    while (compt < data->nbr_enemy)
    {
        move_enemy(&data->enemy[compt], data->rota);
        draw_enemy(data->pix, data->zbuffer, &data->enemy[compt], data->rota, data->move, data->foca);
        compt = compt + 1;
    }
    compt = 0;
    while (compt < data->nbr_turret)
    {
        move_turret(&data->turret[compt], data->rota);
        draw_turret(data->pix, data->zbuffer, &data->turret[compt], data->rota, data->move, data->foca);
        fire_turret_proj(&data->turret[compt]);
        move_proj(data->turret[compt].proj, 50);
        draw_proj(data->pix, data->turret[compt].proj, data->zbuffer, data->rota, data->move, data->foca, 50);
        compt = compt + 1;
    }
}

static void all_sphere(t_data *data)
{
    int compt;

    compt = 0;
    while (compt < data->nbr_sphere)
    {
        draw_sphere(data->pix, data->zbuffer, &data->sphere[compt], data->rota, data->move, data->foca);
        compt = compt + 1;
    }
    //draw_sphere(data->pix, data->zbuffer, &data->sphere[14], data->rota, data->move);
}

static t_bunny_response display(void *data2)
{
    t_data *data;

    data = (t_data *)data2;
    draw_star(data->pix, &data->star, data->foca);
    move_star(&data->star, data->rota);
    std_draw(data->pix, data->zbuffer, &data->obj[0], data->rota, data->move, data->foca);

    dmg_player(data, data->nbr_enemy);
    dmg_player_proj(data, 50);

    all_sphere(data);
    all_enemy(data);

    move_proj(data->player.proj, 50);
    draw_proj(data->pix, data->player.proj, data->zbuffer, data->rota, data->move, data->foca, 50);

    data->obj[2].position.x = 0;//-data->pos.x;
    data->obj[2].position.y = 5;//300 * (1 - (data->p    //printf("%f\n", data->obj[2].position.y);
    data->obj[2].position.z = -520;//data->pix->clipable.buffer.height * -0.520;//-550;
    data->rota.x = 0.5;
    data->rota.y = 0;
    data->rota.z = 0;//0.5;
    std_draw_static(data->pix, data->zbuffer, &data->obj[2], data->rota, data->obj[2].position, data->foca);
    //printf("%f %f %f\n", data->rotation.x / M_PI * 180.0, data->rotation.y /
    //M_PI * 180.0, data->rotation.z / M_PI * 180.0);
    display_hud(data);
    bunny_blit(&data->win->buffer, &data->pix->clipable, NULL);
    bunny_display(data->win);
    return (GO_ON);
}

static t_bunny_response std_affiche(void *data2)
{
  t_data *data;
  t_pos pos[2];
  unsigned int color;
  int x;
  int y;

  data = (t_data *)data2;
  std_clear_pixelarray(data->pix, BLACK);
  //write(1,"a",1);
  x = data->pix->clipable.buffer.width;
  y = data->pix->clipable.buffer.height;
  respawn_enemy(data->enemy, data->nbr_enemy, &data->score);

  if (data->player.hp < 0)
      return (EXIT_ON_SUCCESS);
  data->move.x = 0;
  data->move.y = 0;
  data->move.z = 0;
  data->rota.x = 0;
  data->rota.y = 0;
  data->rota.z = 0;
  clear_zbuffer(data->zbuffer, data->pix);

  player_movement(data, &data->move, &data->rota);

  if (bunny_get_keyboard()[BKS_SPACE] && data->player.energy > 0)
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
  }
  if (bunny_get_keyboard()[BKS_UP])
      data->foca = data->foca + 5;
  if (bunny_get_keyboard()[BKS_DOWN])
      data->foca = data->foca - 5;

  if (data->player.energy < data->player.maxenergy)
      data->player.energy = data->player.energy + 1;

  if (data->player.ammo <= 0)
      data->player.r = true;
  if (data->player.ammo < data->player.maxammo && data->player.r == true)
      data->player.ammo = data->player.ammo + 1;
  if (data->player.ammo >= data->player.maxammo)
      data->player.r = false;

  return (GO_ON);
}

static t_bunny_response std_stop(t_bunny_event_state state,
				 t_bunny_keysym keycode,
				 void * data2)
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
  if (keycode == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int main(void)
{
    printf("%zu\n", sizeof(t_data));
    //return (0);
  t_data data;

  data = init_game();
  printf("Game started\n");
  bunny_set_loop_main_function(std_affiche);
  bunny_set_key_response(std_stop);
  bunny_set_display_function(display);
  bunny_loop(data.win, 60, (void *)&data);
  bunny_stop(data.win);
  printf("%d\n", data.score);
  free_game(data);
  return (0);
}

