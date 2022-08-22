/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:33:24 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/08/22 14:35:18 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCE_H 
#define PARCE_H
 
#include"../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

int     ft_str_cub(char *s1,char *s2);
char    *file_existed(int ac, char **av);
void    parce(int ac, char **av);
char	*get_next_line(int fd);
char    *read_file(int fd);
void    check_file(char *file);
int     check_texture(char **file);
void    free_tab2(char **ptr);
int     ft_error(char *msg, void *ptr);
int     check_map(char **s_file, char *file);
#endif