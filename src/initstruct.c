/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   InitMap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:54:27 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:59:31 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

t_textures		init_textures(t_sdl sdl)
{
	t_textures	textures;

	textures.icon = SDL_LoadBMP(ICON_SURFACE);
//	textures.floor = ft_load_image(FLOOR_TEXT, sdl.renderer);
	textures.north = ft_load_image(NORTH_TEXT, sdl.renderer);
	textures.south = ft_load_image(SOUTH_TEXT, sdl.renderer);
	textures.east = ft_load_image(EAST_TEXT, sdl.renderer);
	textures.west = ft_load_image(WEST_TEXT, sdl.renderer);
//	SDL_QueryTexture(textures.floor, NULL, NULL, &textures.floorwh.x,
//			&textures.floorwh.y);
	SDL_QueryTexture(textures.north, NULL, NULL, &textures.northwh.x,
			&textures.northwh.y);
	SDL_QueryTexture(textures.south, NULL, NULL, &textures.southwh.x,
			&textures.southwh.y);
	SDL_QueryTexture(textures.east, NULL, NULL, &textures.eastwh.x,
			&textures.eastwh.y);
	SDL_QueryTexture(textures.west, NULL, NULL, &textures.westwh.x,
			&textures.westwh.y);
	return (textures);
}

t_vector		init_plane(double angle)
{
	t_vector	plane;
	double		angle2;

	angle2 = angle - M_PI_2;
	plane = init_vector(cos(angle2), -1 * sin(angle2));
	return (plane);
}

t_begin			init_begin(char *str)
{
	t_begin		begin;

	if ((sdl_init(&begin.sdl.window, &begin.sdl.renderer, WIN_W, WIN_H) <= 0))
	{
		begin.err = 0;
		return (begin);
	}
	begin.angle = M_PI;
	begin.dir = init_vector(cos(begin.angle), -1 * sin(begin.angle));
	begin.plane = init_plane(begin.angle);
	begin.sidedist = init_vector(0, 0);
	begin.textures = init_textures(begin.sdl);
	if (begin.textures.north == 0)
	{
		sdl_free_all(2, &begin);
		begin.err = 0;
		return (begin);
	}
	begin.worldmap = init_map(str, &begin.mapsize);
	if (begin.worldmap == NULL)
	{
		ft_putstr("Erreur Map\n");
		sdl_free_all(2, &begin);
		begin.err = 0;
		return (begin);
	}
	begin.pos = init_vector(begin.mapsize.posx, begin.mapsize.posy);
	begin.err = 1;
	return (begin);
}

t_refresh		init_refresh(t_begin *begin, int x)
{
	t_refresh	refresh;

	refresh.xpos = x;
	refresh.map = init_config((int)begin->pos.x, (int)begin->pos.y);
	refresh.hit = 0;
	refresh.camerax = (double)(2 * (double)((double)x / WIN_W)) - 1;
	refresh.raydirx = begin->dir.x + begin->plane.x * refresh.camerax;
	refresh.raydiry = begin->dir.y + begin->plane.y * refresh.camerax;
	refresh.deltadist.x = fabs(1 / refresh.raydirx);
	refresh.deltadist.y = fabs(1 / refresh.raydiry);
	return (refresh);
}
