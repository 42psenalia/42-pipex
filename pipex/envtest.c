/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenalia <psenalia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:51:00 by psenalia          #+#    #+#             */
/*   Updated: 2024/09/18 19:00:52 by psenalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	unsigned int	i;

	i = 0;
	if (argc < 1)
		return (0);
	while (env[i] && argv[i])
		printf("%s\n", env[i++]);
	return (0);
}
