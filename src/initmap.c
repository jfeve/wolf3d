/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   initmap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/12 18:37:26 by jfeve        #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:55:52 by jfeve       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../incs/wolf3d.h"

int			get_line_col(int fd, t_map **mapsize)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) == -1)
	{
		ft_putstr("read() failed\n");
		if ((close(fd)) == -1)
			ft_putstr("close() failed\n");
		return (-1);
	}
	(*mapsize)->x = ft_atoi(line);
	(*mapsize)->y = ft_atoi(line + ft_countdigits((*mapsize)->x) + 1);
	ft_strdel(&line);
	if ((ret = get_next_line(fd, &line)) == -1)
	{
		ft_putstr("read() failed\n");
		if ((close(fd)) == -1)
			ft_putstr("close() failed\n");
		return (-1);
	}
	(*mapsize)->posx = ft_atoi(line);
	(*mapsize)->posy = ft_atoi(line + ft_countdigits((*mapsize)->posx) + 1);
	ft_strdel(&line);
	return (0);
}

int			fill_lines(int ***map, char **str, t_map *mapsize, int i)
{
	int j;

	j = 0;
	if (!((*map)[i] = malloc(sizeof(int) * mapsize->x)))
	{
		while (i >= 0)
		{
			free((*map)[i]);
			i--;
		}
		free(*map);
	}
	while (j < mapsize->x)
	{
		(*map)[i][j] = ft_atoi(str[j]);
		j++;
	}
	return (j);
}

int			**malloc_lines(int fd, t_map *mapsize, int **map)
{
	char	**str;
	int		ret;
	char	*line;
	int		i;
	int		j;

	i = 0;
	while ((ret = get_next_line(fd, &line)) && i < mapsize->y)
	{
		j = 0;
		if (!(str = ft_strsplit(line, ' ')))
		{
			free(map);
			if ((close(fd)) == -1)
				ft_putstr("close() failed\n");
			return (NULL);
		}
		j = fill_lines(&map, str, mapsize, i);
		i++;
		while (j >= 0)
			free(str[j--]);
		free(str);
		ft_strdel(&line);
	}
	return (map);
}

int			**init_map(char *file, t_map *mapsize)
{
	int		**map;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("open() failed\n");
		return (NULL);
	}
	if ((get_line_col(fd, &mapsize)) == -1)
		return (NULL);
	if (!(map = malloc(sizeof(int*) * mapsize->y)))
	{
		if ((close(fd)) == -1)
			ft_putstr("close() failed\n");
		return (NULL);
	}
	map = malloc_lines(fd, mapsize, map);
	if ((close(fd)) == -1)
		ft_putstr("close() failed\n");
	if (map[mapsize->posy][mapsize->posy] != 0)
	{
		mapsize->posx = 22;
		mapsize->posy = 12;
	}
	return (map);
}
