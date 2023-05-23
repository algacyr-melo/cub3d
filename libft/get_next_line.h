/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psydenst <psydenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:49:37 by psydenst          #+#    #+#             */
/*   Updated: 2023/05/23 17:41:34 by psydenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFFER_SIZE 100
# include <unistd.h>
# include <stdlib.h>

char	*ft_strjoin_cp(char *s1, char *s2);
char	*ft_strchr_cp(char *s, int c);
size_t	ft_strlen_cp(char *s);
char	*get_next_line(int fd);
char	*ft_read_and_save(char *save, int fd);
char	*ft_save_rest(char *save);
char	*get_line(char *save);

#endif
