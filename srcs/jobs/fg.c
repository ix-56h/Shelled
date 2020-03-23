/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:10:01 by mguerrea          #+#    #+#             */
/*   Updated: 2020/03/23 15:07:46 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "job.h"
#include "builtins.h"

// static void put_job_in_foreground (job *j, int cont)
// {
//   /* Put the job into the foreground.  */
//   tcsetpgrp (0, j->pgid);


//   /* Send the job a continue signal, if necessary.  */
//   if (cont)
//     {
//       restore_term(1);
//       if (kill (- j->pgid, SIGCONT) < 0)
//         perror ("kill (SIGCONT)");
//     }


//   /* Wait for it to report.  */
//   wait_for_job (j);

//   /* Put the shell back in the foreground.  */
//   tcsetpgrp (shell_terminal, shell_pgid);

//   /* Restore the shell’s terminal modes.  */
// 	restore_term(2);
// }
