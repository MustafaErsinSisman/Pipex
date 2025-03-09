/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:44:30 by musisman          #+#    #+#             */
/*   Updated: 2025/03/08 16:44:30 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
{
        *fd_infile = open(av[1], O_RDONLY, 0644);
        if (*fd_infile == -1)
        {
                ft_putstr_fd(av[1], 2);
                perror(" file not found");
        }
        *fd_outfile = open(av[ac - 1], O_CREAT | O_TRUNC |O_WRONLY, 0644);
        if (*fd_outfile == -1)
        {
                ft_putstr_fd(av[ac - 1], 2);
                perror(" file not found");
        }
}

int main(int ac, char **av)
{
        if (ac == 5)
        {
                int fd_infile;
                int fd_outfile;

                file_control(&fd_infile, &fd_outfile, ac, av);
                
                // dup2(fd_infile, fd_outfile);
                

                // ft_putstr_fd("bu2312 \n", fd_outfile);
                // ft_putstr_fd("belki 31231 kine\n", fd_outfile);
                // close(fd_infile);
                // close(fd_outfile);

                
        }
        else
                ft_printf("there is no 5 argument\n");
        return (0);
}