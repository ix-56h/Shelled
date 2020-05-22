/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:18:19 by mguerrea          #+#    #+#             */
/*   Updated: 2020/05/22 19:09:18 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

const char *g_sig_message[31] = {"Hangup: 1", "Interrupt: 2", "Quit: 3",
	"Illegal instruction: 4", "Trace/BPT trap: 5", "Abort trap: 6",
	"EMT trap: 7", "Floating point exception: 8", "Killed: 9", "Bus error: 10",
	"Segmentation fault: 11", "Bad system call: 12", "Broken pipe: 13",
	"Alarm clock: 14", "Terminated: 15", "Stack fault: 16", "SIGCHILD",
	"SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG",
	"Cputime limit exceeded: 24", "Filesize limit exceeded: 25",
	"Virtual timer expired: 26", "Profiling timer expired: 27", "SIGPROF",
	"SIGWINCH", "User defined signal 1: 30", "User defined signal 2: 31"};

void	signal_notif(t_job *job)
{
	int signal;

	if (!(WIFSTOPPED(job->list->status)) && WIFSIGNALED(job->list->status))
	{
	signal = WTERMSIG(job->list->status);
	ft_dprintf(2, "%d: Terminated by signal: %s.\n", job->pgid,
		g_sig_message[signal - 1]);
	}
}
