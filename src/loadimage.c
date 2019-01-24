/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loadim.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 18:32:56 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/22 18:02:52 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

SDL_Surface		*load_bmp(const char *file, Uint32 format)
{
	SDL_Surface	*tmp;
	SDL_Surface	*s;

	tmp = SDL_LoadBMP(file);
	if (tmp == NULL)
		return (NULL);
	s = SDL_ConvertSurfaceFormat(tmp, format, 0);
	SDL_FreeSurface(tmp);
	if (s == NULL)
		return (NULL);
	return (s);
}

SDL_Texture		*ft_load_image(const char *file, SDL_Renderer *renderer)
{
	SDL_Surface	*tmp;
	SDL_Texture	*texture;

	tmp = load_bmp(file, SDL_PIXELFORMAT_RGBA8888);
	if (tmp == NULL)
	{
		dprintf(1, "Erreur SDL_LoadBMP: %s", SDL_GetError());
		return (NULL);
	}
	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	if (texture == NULL)
	{
		dprintf(1, "Erreur SDL_TextureFromSurface: %s", SDL_GetError());
		return (NULL);
	}
	return (texture);
}
