/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 17:39:10 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 17:13:11 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

int				set_draw(t_begin **begin, t_refresh *refresh, t_vector step)
{
	double		perpwalldist;
	int			err;

	if (refresh->side == 0)
		perpwalldist = (refresh->map.x - (*begin)->pos.x + (1 - step.x) / 2) /
			refresh->raydirx;
	else
		perpwalldist = (refresh->map.y - (*begin)->pos.y + (1 - step.y) / 2) /
			refresh->raydiry;
	refresh->lineheight = (int)((1 * WIN_H) / perpwalldist);
	refresh->drawstart = -refresh->lineheight / 2 + WIN_H / 2;
	if (refresh->drawstart < 0)
		refresh->drawstart = 0;
	refresh->drawend = refresh->lineheight / 2 + WIN_H / 2;
	if (refresh->drawend > WIN_H)
		refresh->drawend = WIN_H;
	if (refresh->side == 1)
		err = draw_nstext(begin, refresh, perpwalldist);
	else
		err = draw_ewtext(begin, refresh, perpwalldist);
	if (err == 0)
		return (0);
	if (SDL_SetRenderDrawColor((*begin)->sdl.renderer, 96, 96, 96, 255) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	if (SDL_RenderDrawLine((*begin)->sdl.renderer, refresh->xpos,
				refresh->drawend, refresh->xpos, WIN_H) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	return (1);
}

void			set_hit(t_begin **begin, t_refresh *refresh, t_vector step)
{
	while (refresh->hit == 0)
	{
		if ((*begin)->sidedist.x < (*begin)->sidedist.y)
		{
			(*begin)->sidedist.x += refresh->deltadist.x;
			refresh->map.x += step.x;
			refresh->side = 0;
		}
		else
		{
			(*begin)->sidedist.y += refresh->deltadist.y;
			refresh->map.y += step.y;
			refresh->side = 1;
		}
		if ((*begin)->worldmap[refresh->map.y][refresh->map.x] > 0)
		{
			refresh->hit = 1;
			break ;
		}
		else if (refresh->map.x == 0 || refresh->map.x == (*begin)->mapsize.x)
		{
			refresh->hit = 1;
			break ;
		}
		else if (refresh->map.y == 0 || refresh->map.y == (*begin)->mapsize.y)
		{
			refresh->hit = 1;
			break ;
		}
	}
	if (set_draw(begin, refresh, step) == 0)
	{
		(*begin)->err = 0;
		return ;
	}
}

int				refresh_view(t_begin *begin)
{
	int			x;
	t_vector	step;
	t_refresh	refresh;

	x = 0;
	if (SDL_SetRenderDrawColor(begin->sdl.renderer, 0, 0, 0, 255) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	if (SDL_RenderClear(begin->sdl.renderer) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	while (x < WIN_W)
	{
		refresh = init_refresh(begin, x);
		init_side_dist(&begin, refresh, &step);
		set_hit(&begin, &refresh, step);
		if (begin->err == 0)
		{
			return (0);
		}
		x++;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	t_begin		begin;
	t_input		in;

	ft_memset(&in, 0, sizeof(t_input));
	if (argc != 2)
		return (usage());
	begin = init_begin(argv[1]);
	if (begin.sdl.renderer == 0)
		return (sdl_free_all(1, &begin));
	else if (begin.err == 0)
		return (0);
	SDL_SetWindowIcon(begin.sdl.window, begin.textures.icon);
	SDL_FreeSurface(begin.textures.icon);
	if (refresh_view(&begin) == 0)
		return (sdl_free_all(2, &begin));
	SDL_RenderPresent(begin.sdl.renderer);
	while (!in.quit)
	{
		update_event(&in);
		run_event(&begin, &in);
		if (refresh_view(&begin) == 0)
			return (sdl_free_all(2, &begin));
		SDL_RenderPresent(begin.sdl.renderer);
	}
	return (sdl_free_all(2, &begin));
}
