/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_xpunge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:43:35 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/25 13:50:12 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_seq *comms)
{
	while (comms)
	{
		if (comms->fd_in)
			close(comms->fd_in);
		if (comms->fd_out)
			close(comms->fd_out);
		comms = comms->next;
	}
	return ;
}

void	endexpress(pid_t *pids, int size)
{
	int		status;
	int		i;

	i = size - 3;
	status = 0;
	while (size > 0)
	{
		waitpid(pids[i], &status, 0);
		i--;
	}
	return ;
}

void	falseprotcl(char **protocol, char **pathmaps)
{
	int	i;

	i = 0;
	while (protocol[i])
		free(protocol[i++]);
	free(protocol);
	while (pathmaps[i])
		free(pathmaps[i++]);
	free(pathmaps);
	return ;
}

void	clearcache(t_seq **block, pid_t *pids)
{
	t_seq	*temp;

	if (block && *block)
	{
		while (*block)
		{
			temp = (*block)->next;
			if ((*block)->in_file)
				free((*block)->in_file);
			if ((*block)->command)
				free((*block)->command);
			if ((*block)->out_file)
				free((*block)->out_file);
			free(*block);
			*block = temp;
		}
		block = NULL;
	}
	if (pids)
		free(pids);
	return ;
}

int	errormsg(int n)
{
	if (n == 1)
		return (write(2, "Error: Failed to allocate memory\n", 34));
	if (n == 2)
		return (write(2, "Error: Failed to assign fd(s)\n", 31));
	else
		return (0);
}
