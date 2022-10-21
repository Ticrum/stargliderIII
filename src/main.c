
#include <starglider.h>

static t_bunny_response std_affiche(void *data2)
{
  t_data *data;
  unsigned int i;
  t_pos po[5];
  t_pos rota;

  //t_bunny_position posi[2];

  data = (t_data *)data2;
  std_clear_pixelarray(data->pix, BLACK);
  i = RED;

  if (bunny_get_keyboard()[BKS_S])
    data->pos = move_player(data->pos, data->rotation, 'z', 10);//data->pos.z + 10;
  if (bunny_get_keyboard()[BKS_Z])
    data->pos = move_player(data->pos, data->rotation, 'z', -10);//data->pos.z - 10;
  if (bunny_get_keyboard()[BKS_D])
    data->pos = move_player(data->pos, data->rotation, 'x', -4);//data->pos.x - 4;
  if (bunny_get_keyboard()[BKS_Q])
    data->pos = move_player(data->pos, data->rotation, 'x', 4);//data->pos.x + 4;
  if (bunny_get_keyboard()[BKS_A])
    data->pos = move_player(data->pos, data->rotation, 'y', -10);//data->pos.y - 10;
  if (bunny_get_keyboard()[BKS_E])
    data->pos = move_player(data->pos, data->rotation, 'y', 10);//data->pos.y + 10;

  //std_set_pixel(data->pix, std_decal(data->pix, std_perspective(data->pos.x, data->pos.y, data->pos.z)), BLUE);
  if (bunny_get_keyboard()[BKS_UP])
      data->rotation.x = data->rotation.x + 0.05;//rotate_player(data->rotation, 'x', 0.05);//
  if (bunny_get_keyboard()[BKS_DOWN])
      data->rotation.x = data->rotation.x - 0.05;//rotate_player(data->rotation, 'x', -0.05);//
  if (bunny_get_keyboard()[BKS_LEFT])
      data->rotation.y = data->rotation.y + 0.05;//rotate_player(data->rotation, 'y', 0.05);//
  if (bunny_get_keyboard()[BKS_RIGHT])
      data->rotation.y = data->rotation.y - 0.05;//rotate_player(data->rotation, 'y', -0.05);//

  std_draw(data->pix, &data->obj[0], data->rotation, data->pos);
  std_draw(data->pix, &data->obj[1], data->rotation, data->pos);

  data->obj[2].position.x = -data->pos.x;
  data->obj[2].position.y = -data->pos.y + 0;
  data->obj[2].position.z = -data->pos.z + 100;
  rota.x = 0.5;
  rota.y = 1.5;
  rota.z = 0.5;
  std_draw(data->pix, &data->obj[2], rota, data->obj[2].position);
  /*
  posi[0].x = -800;
  posi[0].y = -100;
  posi[1].x = 200;
  posi[1].y = 200;
  std_set_line(data2->pix, posi, &i);
  */
  po[0].x = data->pos.x + 0;
  po[0].y = data->pos.y + 0;
  po[0].z = data->pos.z + 100;
  po[1].x = data->pos.x + 0;
  po[1].y = data->pos.y + 0;
  po[1].z = data->pos.z + 100;
  po[2].x = data->pos.x + 0;
  po[2].y = data->pos.y + 0;
  po[2].z = data->pos.z + 100;
  po[3].z = data->rotation.x;
  po[3].y = 0;
  po[3].x = 0;
  printf("%f %f %f\n", data->pos.x, data->pos.y, data->pos.z);
  po[4].y = 0;
  po[4].x = 0;
  po[4].z = 0;

  po[0] = stdtruerotation(po[0], data->rotation, po[2]);
  po[1] = stdtruerotation(po[1], data->rotation, po[2]);
  po[2] = stdtruerotation(po[2], data->rotation, po[2]);
  std_set_triangle(data->pix, po, &i, NULL, NULL, 0);
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
  pos.y = 0;
  pos.z = 0;
  data.obj[2] = load_obj("CPU.dab", 9, pos);

  //write(1,"a",1);
  bunny_set_loop_main_function(std_affiche);
  bunny_set_key_response(std_stop);
  bunny_loop(data.win, 60, (void *)&data);
  bunny_stop(data.win);
  return (0);
}

