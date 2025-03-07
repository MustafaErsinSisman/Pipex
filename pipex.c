/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:48 by musisman          #+#    #+#             */
/*   Updated: 2025/03/07 12:51:48 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void file_control(int *fd_infile, int *fd_outfile)
{
        // dosya varken izileri değiştirirsem ne olur F_OK R_OK nasıl çalışıyor doğru mu access ne döndürüyor vs incele bu methodu else komutları gereksiz gibi izinleri farklı şekilde kontrol etmen gerekebilir
        if (access("infile", F_OK) != 0)
        {
                *fd_infile = open("infile", O_CREAT | O_RDONLY, 0644);
                if (*fd_infile == -1)
                        perror("open error");
        }
        else
        {
                *fd_infile = open("infile", O_RDONLY);
                if (access("infile", R_OK) != 0)
                        perror("infile has not read permision!");
        }
        if (access("outfile", F_OK) != 0)
        {
                *fd_outfile = open("outfile", O_CREAT | O_WRONLY, 0644);
                if (*fd_outfile == -1)
                        perror("open error");
        }
        else
        {
                *fd_outfile = open("outfile", O_WRONLY);
                if (access("outfile", W_OK) != 0)
                        perror("outfile has not read permision!");
        }
}

void file_error(int *fd_infile, int *fd_outfile)
{
        if (*fd_infile != -1 && close(*fd_infile) == -1)
                perror("infile close error! ");
        if (*fd_outfile  != -1 &&  close(*fd_outfile) == -1)
                perror("outfile close error! ");
}

int main(int ac, char **av)
{
        if (ac == 5)
        {
                int fd_infile;
                int fd_outfile;

                file_control(&fd_infile, &fd_outfile);
                int i = 0;
                while (av[1][i])
                {
                        // """"" eğer argüman olarak tek sayıda tırnak gönderirsem >  açılıyor çift sayıda tırnak gönderirsem de ne varsa  onu yazıyor orada "32""32" 3232 mesela neden?
                        ft_printf("%c ", av[1][i++]);
                }
                ft_printf("\n%d %d\n", fd_infile,  fd_outfile);
                file_error(&fd_infile, &fd_outfile);
        }
        else
                ft_printf("there is no 5 argument\n");
        return (0);
}