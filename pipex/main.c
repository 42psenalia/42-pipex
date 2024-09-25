/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:39:51 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/25 14:27:23 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setblocks(t_seq **block, int size)
{
	t_seq	*temp;
	int		n;

	n = 0;
	while (n < size)
	{
		temp = malloc(sizeof(t_seq));
		if (!temp)
		{
			clearcache(block, (pid_t *)0);
			return ;
		}
		ft_bzero(temp, sizeof(t_seq));
		if (!*block)
			*block = temp;
		else
			find_latest(*block)->next = temp;
		printf("linked\n");
		n++;
	}
	return ;
}

static t_seq	*sequencer(t_seq *block, int argc, char *argv[])
{
	t_seq	*temp;
	int		size;
	int		n;

	size = argc - 1;
	n = 1;
	setblocks(&block, size);
	temp = block;
	block->in_file = ft_strdup(argv[n++]);
	block = block->next;
	while (block->next && n < size)
	{
		block->command = ft_strdup(argv[n]);
		block = block->next;
		n++;
	}
	block->out_file = ft_strdup(argv[size]);
	block = temp;
	return (block);
}

int	pipex(int argc, char *argv[], char *env[])
{
	pid_t	*pids;
	t_seq	*block;
	int		size;
	int		id;
	t_seq	*temp;

	block = NULL;
	block = sequencer(block, argc, argv);
	temp = block;
	// while (block)
	// {
	// 	printf("%s, %s, %s\n", \
	// 		block->in_file, block->command, block->out_file);
	// 	block = block->next;
	// }
	// block = temp;
	size = argc - 1;
	pids = (pid_t *)malloc(sizeof(pid_t) * (size - 1));
	if (!pids)
		return (1);
	if (!assign_inout(block))
	{
		close_fds(block);
		clearcache(&block, pids);
		return (2);
	}
	while (block)
	{
		printf("%s, %s, %s, %d, %d\n", \
			block->in_file, block->command, block->out_file, \
			block->fd_in, block->fd_out);
		block = block->next;
	}
	block = temp;
	id = -1;
	while (++id < size - 2)
		pids[id] = -1;
	forkexpress(block, pids, size - 2, env);
	close_fds(block);
	// endexpress(pids, size);
	clearcache(&block, pids);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	int		n;

	if (argc < 5)
		return (write (2, "Requires at least 'input', 'command1', \
				'command2', 'output' to function.\n", 71));
	else
	{
		n = pipex(argc, argv, env);
		if (n)
			return (errormsg(n));
		else
			return (n);
	}
}
