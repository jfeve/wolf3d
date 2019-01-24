/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 19:16:46 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 19:38:21 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

int				sdl_init(SDL_Window **window, SDL_Renderer **renderer, int w,
		int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	*window = SDL_CreateWindow("Raycaster", 100, 100, w, h,
			SDL_WINDOW_ALWAYS_ON_TOP);
	if (window == 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (sdl_free_all(0, NULL));
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	return (1);
}

t_config		init_config(int x, int y)
{
	t_config	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_vector		init_vector(double x, double y)
{
	t_vector	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void			init_side_dist(t_begin **begin, t_refresh refresh, t_vector
		*step)
{
	if (refresh.raydirx < 0)
	{
		step->x = -1;
		(*begin)->sidedist.x = ((*begin)->pos.x - refresh.map.x) *
			refresh.deltadist.x;
	}
	else
	{
		step->x = 1;
		(*begin)->sidedist.x = (refresh.map.x + 1.0 - (*begin)->pos.x) *
			refresh.deltadist.x;
	}
	if (refresh.raydiry < 0)
	{
		step->y = -1;
		(*begin)->sidedist.y = ((*begin)->pos.y - refresh.map.y) *
			refresh.deltadist.y;
	}
	else
	{
		step->y = 1;
		(*begin)->sidedist.y = (refresh.map.y + 1.0 - (*begin)->pos.y) *
			refresh.deltadist.y;
	}
}
