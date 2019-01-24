/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf3d.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 18:47:23 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 19:59:42 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/libft.h"
# include <SDL2/SDL.h>
# include <stdio.h>
# include <math.h>

# define WIN_W 1920
# define WIN_H 1080
# define RENDERER_ERR 1
# define ICON_SURFACE "textures/icon.bmp"
# define FLOOR_TEXT "textures/floor.bmp"
# define NORTH_TEXT "textures/text1.bmp"
# define SOUTH_TEXT "textures/text2.bmp"
# define EAST_TEXT "textures/text3.bmp"
# define WEST_TEXT "textures/text4.bmp"

typedef struct		s_config
{
	int				x;
	int				y;
}					t_config;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					t_sdl;

typedef struct		s_map
{
	int				x;
	int				y;
	int				posx;
	int				posy;
}					t_map;

typedef struct		s_input
{
	SDL_bool		key[SDL_NUM_SCANCODES];
	SDL_bool		quit;
	int				x;
	int				y;
	int				xrel;
	int				yrel;
	int				xwheel;
	int				ywheel;
	SDL_bool		mouse[6];
}					t_input;

typedef struct		s_textures
{
	SDL_Surface		*icon;
	SDL_Texture		*floor;
	SDL_Texture		*north;
	SDL_Texture		*east;
	SDL_Texture		*south;
	SDL_Texture		*west;
	t_config		floorwh;
	t_config		northwh;
	t_config		southwh;
	t_config		eastwh;
	t_config		westwh;
}					t_textures;

typedef struct		s_begin
{
	int				err;
	int				**worldmap;
	t_input			in;
	double			angle;
	t_sdl			sdl;
	t_map			mapsize;
	SDL_Color		color;
	SDL_Event		event;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		sidedist;
	t_textures		textures;
}					t_begin;

typedef	struct		s_refresh
{
	int				side;
	int				xpos;
	int				drawstart;
	int				drawend;
	int				lineheight;
	int				hit;
	double			darkness;
	double			camerax;
	double			raydirx;
	double			raydiry;
	t_vector		deltadist;
	t_config		map;
	t_config		oldmap;
}					t_refresh;



int					draw_nstext(t_begin **begin, t_refresh *refresh, double
		perpwalldist);
int					draw_ewtext(t_begin **begin, t_refresh *refresh, double
		perpwalldist);
SDL_Texture			*ft_load_image(const char *file, SDL_Renderer *renderer);
SDL_Surface			*load_bmp(const char *file, Uint32 format);


void				update_event(t_input *in);
void				run_event(t_begin *begin, t_input *in);


t_vector			init_plane(double angle);
t_begin				init_begin(char *str);
t_refresh			init_refresh(t_begin *begin, int x);
void				init_side_dist(t_begin **begin, t_refresh refresh,
		t_vector *step);
t_config			init_config(int x, int y);
t_vector			init_vector(double x, double y);
int					sdl_init(SDL_Window **window, SDL_Renderer **renderer,
		int w, int h);
int					**init_map(char *file, t_map *mapsize);


int					usage(void);
int					sdl_free_all(int flag, t_begin *begin);
#endif
