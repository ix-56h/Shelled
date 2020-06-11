/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:18:19 by mguerrea          #+#    #+#             */
/*   Updated: 2020/06/11 19:12:58 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "ligne.h"

const char *g_sig_message[31] = {"Hangup: 1", "Interrupt: 2", "Quit: 3",
	"Illegal instruction: 4", "Trace/BPT trap: 5", "Abort trap: 6",
	"EMT trap: 7", "Floating point exception: 8", "Killed: 9", "Bus error: 10",
	"Segmentation fault: 11", "Bad system call: 12", "Broken pipe: 13",
	"Alarm clock: 14", "Terminated: 15", "Stack fault: 16", "SIGCHILD",
	"SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG",
	"Cputime limit exceeded: 24", "Filesize limit exceeded: 25",
	"Virtual timer expired: 26", "Profiling timer expired: 27", "SIGPROF",
	"SIGWINCH", "User defined signal 1: 30", "User defined signal 2: 31"};

void	child_handler(int useless, siginfo_t *info, void *context)
{
	int		signal;
	t_job	*job;

	(void)useless;
	(void)context;
	signal = WTERMSIG(info->si_status);
	job = g_job_head;
	while (job && job->pgid != info->si_pid)
		job = job->next;
	if ((info->si_code == CLD_DUMPED || info->si_code == CLD_KILLED)
		&& signal > 0 && signal < 32 && job)
	{
		if (signal == SIGKILL)
			job->is_notified = 0;
		else if (signal == SIGINT)
			ft_dprintf(2, "\n");
		else if (signal != SIGPIPE)
		{
			job->is_notified = 1;
			ft_dprintf(2, "%s\n", g_sig_message[signal - 1]);
		}
	}
}

void	set_up_sigchld(void)
{
	struct sigaction act;

	act.sa_sigaction = child_handler;
	act.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, 0);
}

void	sighup_handler(int sig)
{
	(void)sig;
	g_ready_exit = 1;
	clean_before_exit();
	exit(SIGHUP);
}

void	set_up_signals(void)
{
	int					j;
	struct sigaction	act;

	j = 1;
	while (j < 31)
	{
		signal(j, SIG_IGN);
		j++;
	}
	signal(SIGINT, ctrl_c_line_handler);
	signal(SIGHUP, sighup_handler);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = child_handler;
	act.sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
	sigaction(SIGCHLD, &act, 0);
}

void	restore_signals(void)
{
	int j;

	j = 1;
	while (j < 31)
	{
		signal(j, SIG_DFL);
		j++;
	}
}
