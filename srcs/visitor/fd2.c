/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:35:19 by akeiflin          #+#    #+#             */
/*   Updated: 2020/02/02 23:57:12 by akeiflin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int				save_and_restore_fd(int action)
{
    static int  fds[3] = {-1};

    if (action == 0)                                //Save stdin/out/err
    {
        fds[STDIN_FILENO] = dup(STDIN_FILENO);
        fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
        fds[STDERR_FILENO] = dup(STDERR_FILENO);
    }
    else if (action == 1)                           //Restore stdin/out/err
    {
        dup2(fds[STDIN_FILENO], STDIN_FILENO);
        close(fds[STDIN_FILENO]);
        dup2(fds[STDOUT_FILENO], STDOUT_FILENO);
        close(fds[STDOUT_FILENO]);
        dup2(fds[STDERR_FILENO], STDERR_FILENO);
        close(fds[STDERR_FILENO]);
    }
    return (1);
}