/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:33 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:57 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "./libft/libft.h"

/*-----------------------------------------------------------------------------
 *				Essentials
 *---------------------------------------------------------------------------*/

int		pipex(int argc, char *argv[], char *env[]);
bool	assign_fds(t_seq *block, int size);
bool	assign_inout(t_seq *block);
void	close_fds(t_seq *comms);
char	**logistics(char *protocolm, char *env[]);
void	forkexpress(t_seq *block, pid_t *pids, int commcount, char *env[]);
void	subexpress(t_seq *comms, char *env[], int pno);
void	endexpress(pid_t *pids, int size);
// bool	reprise(int *ideal, t_stack *a);

/*-----------------------------------------------------------------------------
 *				Utilities
 *---------------------------------------------------------------------------*/

t_seq	*find_latest(t_seq *block);
char	**dirsect(char *env[]);
int		errormsg(int n);
void	falseprotcl(char **protocol, char **pathmaps);
void	clearcache(t_seq **block, pid_t *pids);
// void	preset(int *sorted, t_stack **stack, int size);
// void	freestack(t_stack **stack);

#endif
