/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_xcavate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:28:49 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/25 14:25:36 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_seq	*find_latest(t_seq *block)
{
	if (!block)
		return (NULL);
	while (block->next)
		block = block->next;
	return (block);
}

bool	assign_inout(t_seq *block)
{
	int	istat;
	int	ostat;

	istat = open(block->in_file, O_RDONLY);
	if (istat < 0)
		perror("pipex");
	ostat = open((find_latest(block)->out_file), O_CREAT | O_WRONLY | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ostat < 0)
		perror("pipex");
	if (istat < 0 || ostat < 0)
		return (false);
	else
	{
		block->fd_in = 0;
		block->fd_out = istat;
		block = find_latest(block);
		block->fd_in = ostat;
		block->fd_out = 0;
		return (true);
	}
}

bool	assign_fds(t_seq *block, int size)
{
	int	piper[2];
	int	npipe;

	npipe = 0;
	block = block->next;
	while (npipe < size && block->next)
	{
		if (pipe(piper) < 0)
		{
			perror("pipex: pipe failed");
			return (false);
		}
		block->fd_in = piper[0];
		block->fd_out = piper[1];
		block = block->next;
		npipe++;
	}
	return (true);
}

char	**dirsect(char *env[])
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5) || ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	paths = ft_split(env[i], ':');
	return (paths);
}
