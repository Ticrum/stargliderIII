
#include <starglider.h>

static t_bunny_response std_affiche(void *data2)
{
  t_data *data;
  unsigned int i;
  t_pos po[5];
  t_bunny_position pos[2];
  t_pos rota;
  t_pos move;
  unsigned int color;

  //t_bunny_position posi[2];

  data = (t_data *)data2;
  std_clear_pixelarray(data->pix, BLACK);
  i = RED;

  move.x = 0;
  move.y = 0;
  move.z = 0;
  rota.x = 0;
  rota.y = 0;
  rota.z = 0;

  if (bunny_get_keyboard()[BKS_S])
  {
      data->pos.z = data->pos.z + 10;//move_player(data->pos, data->rotation,
                                     //'z', 10);
      move.z = 10;
  }
  if (bunny_get_keyboard()[BKS_Z])
  {
      data->pos.z = data->pos.z - 10;//move_player(data->pos, data->rotation,
                                     //'z', -10);
      move.z = -10;
  }
  if (bunny_get_keyboard()[BKS_D])
  {
      data->pos.x = data->pos.x - 4;//move_player(data->pos, data->rotation,
                                    //'x', -4);
      move.x = -4;
  }
  if (bunny_get_keyboard()[BKS_Q])
  {
      data->pos.x = data->pos.x + 4;//move_player(data->pos, data->rotation,
                                    //'x', 4);
      move.x = 4;
  }
  if (bunny_get_keyboard()[BKS_A])
  {
      data->pos.y = data->pos.y - 10;//move_player(data->pos, data->rotation,
                                     //'y', -10);
      move.y = -10;
  }
  if (bunny_get_keyboard()[BKS_E])
  {
      data->pos.y = data->pos.y + 10;//move_player(data->pos, data->rotation,
                                     //'y', 10);
      move.y = 10;
  }
  //std_set_pixel(data->pix, std_decal(data->pix, std_perspective(data->pos.x, data->pos.y, data->pos.z)), BLUE);
  if (bunny_get_keyboard()[BKS_UP])
  {
      data->rotation.x = data->rotation.x + 0.03;//rotate_player(data->rotation,
                                                 //'x', 0.05);//
      rota.x = -0.05;
  }
  if (bunny_get_keyboard()[BKS_DOWN])
  {
      data->rotation.x = data->rotation.x - 0.03;//rotate_player(data->rotation,
                                                 //'x', -0.05);//
      rota.x = 0.05;
  }
  if (bunny_get_keyboard()[BKS_LEFT])
  {
      data->rotation.y = data->rotation.y + 0.03;//rotate_player(data->rotation,
                                                 //'y', 0.05);//
      rota.y = 0.05;
  }
  if (bunny_get_keyboard()[BKS_RIGHT])
  {
      data->rotation.y = data->rotation.y - 0.03;//rotate_player(data->rotation,
                                                 //'y', -0.05);//
      rota.y = -0.05;
  }
  if (bunny_get_keyboard()[BKS_P])
  {
      data->rotation.z = data->rotation.z + 0.03;//rotate_player(data->rotation,
                                                 //'y', 0.05);//
      rota.z = 0.05;
  }
  if (bunny_get_keyboard()[BKS_O])
  {
      data->rotation.z = data->rotation.z - 0.03;//rotate_player(data->rotation,
                                                 //'y', -0.05);//
      rota.z = -0.05;
  }

  if (bunny_get_keyboard()[BKS_SPACE])
  {
      pos[0].x = 500;
      pos[0].y = 500;
      pos[1].x = 445;
      pos[1].y = 725;
      color = RED;
      fire_beam(data->pix, pos, &color);
      pos[1].x = 555;
      pos[1].y = 725;
      fire_beam(data->pix, pos, &color);
  }

  std_draw(data->pix, &data->obj[0], rota, move);
  std_draw(data->pix, &data->obj[1], rota, move);

  data->obj[2].position.x = 0;//-data->pos.x;
  data->obj[2].position.y = 5;//-data->pos.y + 0;
  data->obj[2].position.z = -550;//-data->pos.z - 200;
  draw_sphere(data->pix, &data->sphere[0], rota, move);
  draw_sphere(data->pix, &data->sphere[1], rota, move);
  draw_sphere(data->pix, &data->sphere[2], rota, move);

  rota.x = 0.5;
  rota.y = 0;
  rota.z = 0;//0.5;
  std_draw_static(data->pix, &data->obj[2], rota, data->obj[2].position);
  /*
  posi[0].x = -800;
  posi[0].y = -100;
  posi[1].x = 200;
  posi[1].y = 200;
  std_set_line(data2->pix, posi, &i);
  */
  //printf("%f %f %f\n", data->rotation.x / M_PI * 180.0, data->rotation.y / M_PI * 180.0, data->rotation.z / M_PI * 180.0);
  bunny_blit(&data->win->buffer, &data->pix->clipable, NULL);
  bunny_display(data->win);
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
  t_pos pos;

  pos.x = 0;//-10;
  pos.y = 0;//20;
  pos.z = 0;//-400;

  data.pos.z = 1;
  data.pos.y = 0;
  data.pos.x = 0;
  data.tpos = data.pos;
  data.rotation.x = 0;
  data.rotation.y = 0;
  data.rotation.z = 0;
  data.win = bunny_start(1000, 1000, false, "Bunny");
  data.pix = bunny_new_pixelarray(1000, 1000);
  data.obj[0] = load_obj("test_space.dab", 17, pos);
  pos.x = 0;
  pos.y = 0;
  pos.z = 0;
  data.obj[1] = load_obj("test.dab", 3, pos);
  pos.x = 0;
  pos.y = 400;
  pos.z = 0;
  data.sphere[0] = load_sphere(pos, 300, 20);
  pos.x = 1000;
  pos.y = 600;
  pos.z = 1000;
  data.sphere[1] = load_sphere(pos, 400, 20);
  pos.x = -1000;
  pos.y = 200;
  pos.z = 600;
  data.sphere[2] = load_sphere(pos, 200, 15);
  pos.x = 0;
  pos.y = 30;
  pos.z = -300;
  data.obj[2] = load_obj("CPU.dab", 9, pos);

  //write(1,"a",1);
  bunny_set_loop_main_function(std_affiche);
  bunny_set_key_response(std_stop);
  bunny_loop(data.win, 60, (void *)&data);
  bunny_stop(data.win);
  return (0);
}

