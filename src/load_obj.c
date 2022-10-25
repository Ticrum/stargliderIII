
#include <starglider.h>

t_obj load_obj(char	*file,
	       int	nbr_obj,
	       t_pos	objpos)
{
  t_bunny_configuration *conf;
  t_obj newobj;
  int compt;
  int compt2;
  int i[12];

  if ((newobj.pos = malloc(sizeof(t_pos) * (nbr_obj * 3))) == NULL)
    return (newobj);
  if ((newobj.color = malloc(sizeof(unsigned int) * nbr_obj)) == NULL)
    return (newobj);
  newobj.nbr_subelems = nbr_obj;
  newobj.position = objpos;
  newobj.tposition = objpos;

  compt = 0;
  compt2 = 0;

  conf = bunny_open_configuration(file, NULL);
  while (compt < nbr_obj)
    {
      bunny_configuration_getf(conf, &i[0], "Mesh[%d].Color[0]", compt);
      bunny_configuration_getf(conf, &i[1], "Mesh[%d].Color[1]", compt);
      bunny_configuration_getf(conf, &i[2], "Mesh[%d].Color[2]", compt);
      bunny_configuration_getf(conf, &i[3], "Mesh[%d].Coord[0].Position[0]", compt);
      bunny_configuration_getf(conf, &i[4], "Mesh[%d].Coord[0].Position[1]", compt);
      bunny_configuration_getf(conf, &i[5], "Mesh[%d].Coord[0].Position[2]", compt);
      bunny_configuration_getf(conf, &i[6], "Mesh[%d].Coord[1].Position[0]", compt);
      bunny_configuration_getf(conf, &i[7], "Mesh[%d].Coord[1].Position[1]", compt);
      bunny_configuration_getf(conf, &i[8], "Mesh[%d].Coord[1].Position[2]", compt);
      bunny_configuration_getf(conf, &i[9], "Mesh[%d].Coord[2].Position[0]", compt);
      bunny_configuration_getf(conf, &i[10], "Mesh[%d].Coord[2].Position[1]", compt);
      bunny_configuration_getf(conf, &i[11], "Mesh[%d].Coord[2].Position[2]", compt);

      newobj.color[compt].argb[RED_CMP] = i[0];
      newobj.color[compt].argb[GREEN_CMP] = i[1];
      newobj.color[compt].argb[BLUE_CMP] = i[2];

      newobj.pos[compt2].x = i[3] + newobj.position.x;
      newobj.pos[compt2].y = i[4] + newobj.position.y;
      newobj.pos[compt2].z = i[5] + newobj.position.z;
      newobj.pos[compt2 + 1].x = i[6] + newobj.position.x;
      newobj.pos[compt2 + 1].y = i[7] + newobj.position.y;
      newobj.pos[compt2 + 1].z = i[8] + newobj.position.z;
      newobj.pos[compt2 + 2].x = i[9] + newobj.position.x;
      newobj.pos[compt2 + 2].y = i[10] + newobj.position.y;
      newobj.pos[compt2 + 2].z = i[11] + newobj.position.z;
      /*
      pos[0].x = i[3] + posi.x;
      pos[0].y = i[4] + posi.y;
      pos[0].z = i[5] + posi.z;
      pos[1].x = i[6] + posi.x;
      pos[1].y = i[7] + posi.y;
      pos[1].z = i[8] + posi.z;
      pos[2].x = i[9] + posi.x;
      pos[2].y = i[10] + posi.y;
      pos[2].z = i[11] + posi.z;
      */
      //color.argb[RED_CMP] = i[0];
      //color.argb[GREEN_CMP] = i[1];
      //color.argb[BLUE_CMP] = i[2];
      //color.full = GREEN;
      //std_set_triangle(pix, pos, &color.full);
      compt = compt + 1;
      compt2 = compt2 + 3;
    }
  bunny_delete_configuration(conf);

  return (newobj);
}


