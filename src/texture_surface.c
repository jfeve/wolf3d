/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   texture_surface.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/22 17:57:04 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:35:56 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

SDL_Rect		init_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

SDL_Rect		find_rect(t_config cardinalwh, double wallx, t_refresh *fresh)
{
	SDL_Rect	rect;
	int			texx;
	int			tmp;

	texx = (int)(wallx * cardinalwh.x);
	if (fresh->side == 1 && fresh->raydiry < 0)
		texx = cardinalwh.x - texx - 1;
	if (fresh->side == 0 && fresh->raydirx > 0)
		texx = cardinalwh.x - texx - 1;
	rect = init_rect(texx, 0, 1, cardinalwh.y);
	tmp = fresh->drawstart * 256 - WIN_H * 128 + fresh->lineheight * 128;
	rect.y = ((tmp * cardinalwh.y) / fresh->lineheight) / 256;
	return (rect);
}

int				draw_nstext(t_begin **begin, t_refresh *fresh, double perp)
{
	double		wallx;
	SDL_Rect	dst;
	SDL_Rect	rect;

	dst = init_rect(fresh->xpos, fresh->drawstart, 1, fresh->lineheight);
	wallx = (*begin)->pos.x + perp * fresh->raydirx;
	wallx -= floor(wallx);
	if ((*begin)->pos.y < fresh->map.y)
	{
		rect = find_rect((*begin)->textures.northwh, wallx, fresh);
		if (SDL_RenderCopy((*begin)->sdl.renderer, (*begin)->textures.north,
				&rect, &dst) != 0)
		{
			dprintf(1, "1\t");
			ft_putstr("Erreur SDL_Init: ");
			ft_putstr(SDL_GetError());
			return (0);
		}
	}
	if ((*begin)->pos.y > fresh->map.y)
	{
		rect = find_rect((*begin)->textures.southwh, wallx, fresh);
		if (SDL_RenderCopy((*begin)->sdl.renderer, (*begin)->textures.south, &rect,
				&dst) != 0)
		{
			dprintf(1, "1\t");
			ft_putstr("Erreur SDL_Init: ");
			ft_putstr(SDL_GetError());
			return (0);
		}
	}
	if (SDL_SetRenderDrawColor((*begin)->sdl.renderer, 193, 191, 177, 255) != 0)
	{
			dprintf(1, "1\t");
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	if (SDL_RenderDrawLine((*begin)->sdl.renderer, fresh->xpos, 0, fresh->xpos,
			fresh->drawstart) != 0)
	{
			dprintf(1, "1\t");
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	return (1);
}

int				draw_ewtext(t_begin **begin, t_refresh *fresh, double perp)
{
	double		wallx;
	SDL_Rect	dst;
	SDL_Rect	rect;

	dst = init_rect(fresh->xpos, fresh->drawstart, 1, fresh->lineheight);
	wallx = (*begin)->pos.y + perp * fresh->raydiry;
	wallx -= floor(wallx);
	if ((*begin)->pos.x < fresh->map.x)
	{
		rect = find_rect((*begin)->textures.westwh, wallx, fresh);
		if (SDL_RenderCopy((*begin)->sdl.renderer, (*begin)->textures.west, &rect,
				&dst) != 0)
		{
			ft_putstr("Erreur SDL_Init: ");
			ft_putstr(SDL_GetError());
			return (0);
		}
	}
	if ((*begin)->pos.x > fresh->map.x)
	{
		rect = find_rect((*begin)->textures.eastwh, wallx, fresh);
		if (SDL_RenderCopy((*begin)->sdl.renderer, (*begin)->textures.east, &rect,
				&dst) != 0)
		{
			ft_putstr("Erreur SDL_Init: ");
			ft_putstr(SDL_GetError());
			return (0);
		}
	}
	if (SDL_SetRenderDrawColor((*begin)->sdl.renderer, 193, 191, 177, 255) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	if (SDL_RenderDrawLine((*begin)->sdl.renderer, fresh->xpos, 0, fresh->xpos,
			fresh->drawstart) != 0)
	{
		ft_putstr("Erreur SDL_Init: ");
		ft_putstr(SDL_GetError());
		return (0);
	}
	return (1);
}
