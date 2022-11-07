
#ifndef		STARGLIDER_H
#define		STARGLIDER_H

#include <stdbool.h>
#include <stdio.h>
#include <lapin.h>
#include <time.h>

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
    t_pos tposition;
    t_pos rotation;
    t_pos zoom;
    //t_bunny_color color;
    t_bunny_picture *texture;
    t_bunny_position texture_position;
    t_pos         *pos;
    t_bunny_color *color;
    //struct s_obj *subelems[0];
}t_obj;

typedef struct s_sphere
{
    t_pos pos;
    int radius;
    int res;
    t_pos **po;
    unsigned int color;
}t_sphere;

typedef struct s_enemy
{
    t_obj obj;
    t_pos vect;
    int dmg;
    int maxhp;
    int hp;
    t_pos speed;
    t_pos rota_speed;
}t_enemy;

typedef struct s_player
{
    t_pos pos;
    t_pos tpos;
    t_pos rotation;
    t_pos vect;
    int maxhp;
    int hp;
    int maxenergy;
    int energy;
}t_player;

typedef struct s_star
{
    t_pos *pos;
    int nbr_star;
}t_star;

typedef struct s_data
{
    t_bunny_window *win;
    t_bunny_pixelarray *pix;
    float *zbuffer;
    t_star star;
    t_obj obj[3];
    int nbr_obj;
    t_sphere sphere[50];
    int nbr_sphere;
    t_enemy enemy[200];
    int nbr_enemy;
    t_player player;
    int score;
    float foca;
    t_pos rota;
    t_pos move;
}t_data;

double std_abs(double				nbr);

void std_set_pixel(t_bunny_pixelarray		*px,
		   t_bunny_position		pos,
		   unsigned int			color);

void std_set_zpixel(t_bunny_pixelarray          *px,
                    float                       *zbuffer,
                    t_pos                       pos,
                    unsigned int                color);

void std_set_line(t_bunny_pixelarray		*px,
		  t_bunny_position		*pos,
		  unsigned int			*color);

void std_set_zline(t_bunny_pixelarray           *px,
                   float                        *zbuffer,
                   t_pos                        *pos,
                   unsigned int                 *color);

void std_set_z_speed_line(t_bunny_pixelarray	*px,
                          float                 *zbuffer,
                          t_pos                 *pos,
                          unsigned int		*color);

void std_clear_pixelarray(t_bunny_pixelarray	*pix,
			  unsigned int		color);

void std_set_triangle(t_bunny_pixelarray	*pix,
		      t_pos			*pos,
		      unsigned int		*color,
		      t_bunny_position		*exept,
		      int			*empin,
		      int			recur,
                      float                     foca);

void std_set_ztriangle(t_bunny_pixelarray	*pix,
                       float                    *zbuffer,
                       t_pos			*pos,
                       unsigned int		*color,
                       t_pos                    *exept,
                       int			*empin,
                       int			recur,
                       float                    foca);

t_pos           reduce_zpos(t_pos               *pos,
                            t_bunny_pixelarray	*pix,
                            int			*place);

t_bunny_position reduce_pos(t_bunny_position    *pos,
                            t_bunny_pixelarray	*pix,
                            int			*place);

t_pos           find_zpos(t_pos                 *pos,
                          t_bunny_pixelarray	*pix,
                          int			*in,
                          int			start,
                          int			end);

t_bunny_position find_pos(t_bunny_position       *pos,
                          t_bunny_pixelarray	*pix,
                          int			*in,
                          int			start,
                          int			end);

t_obj            load_obj(char          	*file,
                          int			nbr_obj,
                          t_pos			objpos);

void             std_draw(t_bunny_pixelarray	*pix,
                          float                 *zbuffer,
                          t_obj			*obj,
                          t_pos			rotation,
                          t_pos			posi,
                          float                 foca);

void std_draw_static(t_bunny_pixelarray         *pix,
                     float                      *zbuffer,
                     t_obj                      *obj,
                     t_pos                      rotation,
                     t_pos                      posi,
                     float                      foca);

t_pos stdtruerotation(t_pos			target,
		      t_pos			rotation,
		      t_pos			center);

t_pos stdrotation(t_pos				target,
		  t_pos				rotation);

t_bunny_position std_decal(t_bunny_pixelarray	*pix,
			   t_bunny_position	pos);

t_bunny_position std_perspective(float		x,
				 float		y,
				 float		z,
                                 float          foca);

double	       	std_get_value(double		ratio,
			      double	       	min,
			      double		max);

double		std_get_ratio(double		max,
			      double		min,
			      double		curr);

t_pos           rotate_player(t_pos             vect,
                              t_pos             rota);

void            fire_beam(t_bunny_pixelarray    *pix,
                          float                 *zbuffer,
                          t_pos                 *pos,
                          unsigned int          *color);

t_sphere        load_sphere(t_pos               pos,
                            int                 radius,
                            int                 res,
                            unsigned int        color);

void            draw_sphere(t_bunny_pixelarray	*pix,
                            float               *zbuffer,
                            t_sphere            *sphere,
                            t_pos		rotation,
                            t_pos		posi,
                            float               foca);

float           *create_zbuffer(t_bunny_pixelarray *pix);

void            clear_zbuffer(float                *zbuffer,
                              t_bunny_pixelarray   *pix);

t_enemy         init_enemy(char                 *file,
                           int                  nbr_obj,
                           t_pos                objpos,
                           int                  dmg,
                           int                  hp);

void            draw_enemy(t_bunny_pixelarray	*pix,
                           float                *zbuffer,
                           t_enemy              *enemy,
                           t_pos		rotation,
                           t_pos		posi,
                           float                foca);

void            dmg_enemy(t_enemy               *enemy,
                          int                   nbr);

void            move_enemy(t_enemy              *enemy,
                           t_pos                rota);

t_data          init_game(void);

void            dmg_player(t_data               *data,
                           int                  len);

void            display_hud(t_data              *data);

void            respawn_enemy(t_enemy           *enemy,
                              int               len,
                              int               *score);

void            draw_star(t_bunny_pixelarray    *pix,
                          t_star                *star,
                          float                 foca);

void            move_star(t_star                *star,
                          t_pos                 rota);

#endif //	STARGLIDER_H
