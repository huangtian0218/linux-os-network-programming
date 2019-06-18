#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include "semaphore.h"

#define NSEMS 1

static int semid;

void signal_fun(int signo)
{
	del_sem(semid, NSEMS);
	exit(-1);
}

int main()
{
	int ret = -1;
	int fd = -1;
	int i = 0;
	int semnum_buf[1] = {0};

	fd = open("./file", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if(fd == -1)
	{
		perror("Error");
		return -1;
	}

	semid = create_sem(NSEMS);
	for(i = 0; i < NSEMS; i++)
	{
		init_sem(semid, i, 1);
	}

	ret = fork();
	if(ret > 0)
	{
		signal(SIGINT, signal_fun);
		while(1)
		{
			semnum_buf[0] = 0;
			p_sem(semid, semnum_buf, 1);
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			semnum_buf[0] = 0;
			v_sem(semid, semnum_buf, 1);
		}
	}
	else if(ret == 0)
	{
		while(1)
		{
			semnum_buf[0] = 0;
			p_sem(semid, semnum_buf, 1);
			write(fd, "hhhhh ", 6);
			write(fd, "wwwww\n", 6);
			semnum_buf[0] = 0;
			v_sem(semid, semnum_buf, 1);
		}
	}

	return 0;
}
