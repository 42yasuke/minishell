/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:44:36 by jose              #+#    #+#             */
/*   Updated: 2023/05/25 07:05:40 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
	//char *arg[2] = {"cat", NULL};
	pid_t pid = fork();
	
	if (pid == 0) {
		// Processus fils
		raise(SIGKILL);
	} else if (pid > 0) {
		// Processus parent
		int status;
		wait(&status);
		
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);
			printf("Code de sortie : %d\n", exit_status);
		} else if (WIFSIGNALED(status)) {
			int term_signal = WTERMSIG(status);
			printf("Terminé avec un signal : %d\n", term_signal + 128);
		}
	} else {
		// Erreur lors de la création du processus fils
		perror("fork");
		exit(1);
	}
	
	return 0;
}
