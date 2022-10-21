
#ifndef		STARGLIDER_H
#define		STARGLIDER_H

#include <stdbool.h>
#include <stdio.h>
#include <lapin.h>

typedef struct s_pos
{
  float x;
  float y;
  float z;
}t_pos;

typedef struct s_obj
{
  int nbr_subelems;
  t_pos position;
  t_pos rotation;
  t_pos zoom;
  //t_bunny_color color;
  t_bunny_picture *texture;
  t_bunny_position texture_position;
  t_pos         *pos;
  t_bunny_color *color;
  //struct s_obj *subelems[0];
}t_obj;

typedef struct s_data
{
  t_bunny_window *win;
  t_bunny_pixelarray *pix;
  t_obj obj[3];
  t_pos pos;
  t_pos rotation;
}t_data;

double std_abs(double				nbr);

void std_set_pixel(t_bunny_pixelarray		*px,
		   t_bunny_position		pos,
		   unsigned int			color);

void std_set_line(t_bunny_pixelarray		*px,
		  t_bunny_position		*pos,
		  unsigned int			*color);

void std_clear_pixelarray(t_bunny_pixelarray	*pix,
			  unsigned int		color);

void std_set_triangle(t_bunny_pixelarray	*pix,
		      t_pos			*pos,
		      unsigned int		*color,
		      t_bunny_position		*exept,
		      int			*empin,
		      int			recur);

t_bunny_position reduce_pos(t_bunny_position   	*pos,
			    t_bunny_pixelarray	*pix,
			    int			*place);

t_bunny_position find_pos(t_bunny_position	*pos,
			  t_bunny_pixelarray	*pix,
			  int			*in,
			  int			start,
			  int			end);

t_obj load_obj(char				*file,
	       int				nbr_obj,
	       t_pos				objpos);

void std_draw(t_bunny_pixelarray		*pix,
	      t_obj				*obj,
	      t_pos				rotation,
	      t_pos				posi);

t_pos stdtruerotation(t_pos			target,
		      t_pos			rotation,
		      t_pos			center);

t_pos stdrotation(t_pos				target,
		  t_pos				rotation);

t_bunny_position std_decal(t_bunny_pixelarray	*pix,
			   t_bunny_position	pos);

t_bunny_position std_perspective(float		x,
				 float		y,
				 float		z);

double	       	std_get_value(double		ratio,
			      double	       	min,
			      double		max);

double		std_get_ratio(double		max,
			      double		min,
			      double		curr);

t_pos		move_player(t_pos		pos,
			    t_pos		angle,
			    char		axe,
			    float		step);


#endif //	STARGLIDER_H
