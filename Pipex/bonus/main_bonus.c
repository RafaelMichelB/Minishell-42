/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:14:46 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:16:45 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		last;

	if (argc < 4)
		ft_exit(1);
	if (ft_strncmp(argv[1], "here_doc", 8) != 0
		&& access(argv[1], F_OK | R_OK) == -1)
		ft_exit(-1);
	last = check_last_arg(argv[argc - 1], envp);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (hdoc_main(last, argc, argv, envp));
	if (last == 0)
		return (no_file2_main(argc, argv, envp));
	return (pipex_main(argc, argv, envp));
}
