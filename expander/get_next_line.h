/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:04:32 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/25 12:03:24 by tomoki-kouk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TEMP_BUF_SIZE 32
# define END -2

char	*ft_strdup_extra(char *s);
char	*exted_buf(char *s, int k);
int		ft_getchar(int fd);
char	*get_next_line(int fd);
#endif