
#include <starglider.h>

static void player_movement(t_data  *data,
                            t_pos   *move,
                            t_pos   *rota)
{
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
}

static t_bunny_response display(void *data2)
{
    t_data *data;

    data = (t_data *)data2;
    std_draw(data->pix, data->zbuffer, &data->obj[0], data->rota, data->move);
    move_enemy(&data->enemy[0], data->rota);
    move_enemy(&data->enemy[1], data->rota);
    move_enemy(&data->enemy[2], data->rota);
    dmg_player(data, 3);


    draw_sphere(data->pix, data->zbuffer, &data->sphere[0], data->rota, data->move);
    draw_sphere(data->pix, data->zbuffer, &data->sphere[1], data->rota, data->move);
    draw_sphere(data->pix, data->zbuffer, &data->sphere[2], data->rota, data->move);
    //draw_sphere(data->pix, data->zbuffer, &data->sphere[3], data->rota, data->move);

    draw_enemy(data->pix, data->zbuffer, &data->enemy[0], data->rota, data->move);
    draw_enemy(data->pix, data->zbuffer, &data->enemy[1], data->rota, data->move);
    draw_enemy(data->pix, data->zbuffer, &data->enemy[2], data->rota, data->move);

    data->obj[2].position.x = 0;//-data->pos.x;
    data->obj[2].position.y = 5;//300 * (1 - (data->pix->clipable.buffer.height / 1000.0)) + 5;//data->pix->clipable.buffer.height
                                                                                           //*
                                                                                           //0.1;//5;
    //printf("%f\n", data->obj[2].position.y);
    data->obj[2].position.z = -520;//data->pix->clipable.buffer.height * -0.520;//-550;
    data->rota.x = 0.5;
    data->rota.y = 0;
    data->rota.z = 0;//0.5;
    std_draw_static(data->pix, data->zbuffer, &data->obj[2], data->rota, data->obj[2].position);
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

  x = data->pix->clipable.buffer.width;
  y = data->pix->clipable.buffer.height;
  respawn_enemy(data->enemy, 3, &data->score);

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
      pos[0].x = x * 0.5;//500;
      pos[0].y = y * 0.5;//500;
      pos[0].z = 400;
      pos[1].x = x * 0.445;//445;
      pos[1].y = y * 0.645;
      pos[1].z = -800;
      color = PURPLE;
      fire_beam(data->pix, data->zbuffer, pos, &color);
      pos[1].x = x * 0.555;
      pos[1].y = y * 0.645;
      pos[1].z = -800;
      fire_beam(data->pix, data->zbuffer, pos, &color);
      dmg_enemy(data->pix, data->enemy, 3);
      data->player.energy = data->player.energy - 3;
  }
  if (data->player.energy < data->player.maxenergy)
      data->player.energy = data->player.energy + 1;

  return (GO_ON);
}

static t_bunny_response std_stop(t_bunny_event_state state,
				 t_bunny_keysym keycode,
				 void * data)
{
  (void)data;
  if (state == GO_UP)
    return (GO_ON);
  if (keycode == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int main(void)
{
  t_data data;
  //t_pos pos;

  data = init_game();
  //write(1,"a",1);
  bunny_set_loop_main_function(std_affiche);
  bunny_set_key_response(std_stop);
  bunny_set_display_function(display);
  bunny_loop(data.win, 60, (void *)&data);
  bunny_stop(data.win);
  printf("%d\n", data.score);
  return (0);
}

