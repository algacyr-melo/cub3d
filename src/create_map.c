/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:00:29 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/23 21:45:38 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	create_map(t_data *data)
{
	char *str;
	char *joker;
	//int i;
	int len;

	len = 0;
	//i = 0;
	str = NULL;
	joker = get_next_line(data->map.fd);
	while (1)
	{
		str = get_next_line(data->map.fd);
		if (str == NULL)
			break ;
		joker = ft_strjoin(joker, str);
		len++;
	}
	free(str);
	close(data->map.fd);
	to_matrix(data, joker);
}

void	to_matrix(t_data *data, char *joker)
{
	data->map.world_map = ft_split(joker, '\n');
	int i = 0;
	while(i != 12)
	{
		ft_printf("%s\n", data->map.world_map[i]); 
		i++;
	}

}

