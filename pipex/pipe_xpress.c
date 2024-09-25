/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_xpress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:43:14 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/25 17:51:59 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	dup_fds(t_seq *comms, int no)
{
	printf("duping\n");
	if (no == 0)
	{
		if (dup2(comms->fd_in, STDIN_FILENO) < 0)
			return (false);
		close(comms->fd_in);
		close(comms->fd_out);
	}
	else
	{
		if (dup2(comms->fd_out, STDOUT_FILENO) < 0)
			return (false);
		close(comms->fd_in);
		close(comms->fd_out);
	}
	// if (dup2(comms->next->fd_in, STDIN_FILENO) < 0 || \
	// 	dup2(comms->fd_out, STDOUT_FILENO) < 0)
	// 	return (false);
	// close(comms->next->fd_in);
	// close(comms->fd_out);
	return (true);
}

char	**logistics(char *protocolm, char *env[])
{
	char	**pathsect;
	char	**remapped;
	char	*decipher;
	int		i;

	printf("logistics in\n");
	pathsect = dirsect(env);
	if (!pathsect)
		return (NULL);
	i = 0;
	while (pathsect[i])
	{
		printf("%s\n", pathsect[i]);
		i++;
	}
	remapped = (char **)malloc(sizeof(char *) * i);
	if (!remapped)
		return (NULL);
	i = 0;
	while (pathsect[i])
	{
		decipher = ft_strjoin(pathsect[i], "/");
		remapped[i] = ft_strjoin(decipher, protocolm);
		free(decipher);
		free(pathsect[i]);
		i++;
	}
	remapped[i] = NULL;
	printf("found %d path arrays\nlogistics out\n", i);
	free(pathsect);
	return (remapped);
}

static int	chkprotcl(char **pathmap, char **protocol)
{
	int	i;

	i = 0;
	while (pathmap[i])
	{
		if (!access(pathmap[i], X_OK))
			break ;
		i++;
	}
	if (pathmap[i] == NULL)
	{
		ft_putstr_fd("pipex: command not found ", 2);
		ft_putstr_fd(protocol[0], 2);
		ft_putstr_fd("\n", 2);
		falseprotcl(protocol, pathmap);
		return (-1);
	}
	return (i);
}

void	subexpress(t_seq *comms, char *env[], int pno)
{
	char		**protocol;
	char		**pathmaps;
	int			i;

	protocol = ft_split(comms->command, 32);
	if (!protocol)
		return ;
	printf("got protocol %s\n", protocol[0]);
	if (!dup_fds(comms, pno))
		return (perror("pipex dup failed:"));
	// close_fds(comms);
	pathmaps = logistics(protocol[0], env);
	if (!pathmaps)
		return ;
	i = chkprotcl(pathmaps, protocol);
	if (i < 0)
		return ;
	printf("found access path @ #%d\n", i + 1);
	if (execve(pathmaps[i], protocol, env) < 0)
	{
		falseprotcl(protocol, pathmaps);
		perror("pipex");
	}
	printf("end subexpress\n");
	return ;
}

void	forkexpress(t_seq *block, pid_t *pids, int commcount, char *env[])
{
	int		i;
	t_seq	*start;

	i = 0;
	start = block;
	if (!block->command)
		block = block->next;
	if (!assign_fds(block, commcount))
		return (perror("pipex"));
	while (block && i < commcount)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return ;
		else if (pids[i] == 0)
		{
			printf("subexpress child %d->%d\n", i, pids[i]);
			subexpress(block, env, i);
		}
		else
		{
			printf("forked parent %d->%d\n", i, pids[i]);
			endexpress(pids, commcount + 2);
		}
		printf("%d & %d\n", pids[0], pids[1]);
		block = block->next;
		i++;
	}
	block = start;
	return ;
}
