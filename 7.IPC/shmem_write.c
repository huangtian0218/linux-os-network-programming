#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define SHM_FILE "./shm_file"
#define SHM_SIZE 4096

static int shmid = -1;
static void *shmaddr = NULL;

void create_shmem()
{
	int fd = -1;
	int ret = -1;
	key_t key = -1;

	fd = open(SHM_FILE, O_RDWR | O_CREAT, 0664);
	if(fd == -1)
	{
		perror("Error");
		exit(-1);
	}

	key = ftok(SHM_FILE, 'b');
	if(key == -1)
	{
		perror("Error");
		exit(-1);
	}

	//创建共享内存
	shmid = shmget(key, SHM_SIZE, 0664 | IPC_CREAT);
	if(shmid == -1)	
	{
		perror("Error");
		exit(-1);
	}
}

void signal_fun(int signo)
{
	//取消映射共享内存
	shmdt(shmaddr);
	//删除共享内存
	shmctl(shmid, IPC_RMID, NULL);
	
	remove(SHM_FILE);

	exit(-1);
}

int main()
{
	char buf[1024] = "12lkj4l2k3459nlks901jlkjl";

	//捕获中断信号
	signal(SIGINT, signal_fun);

	create_shmem();	

	//映射共享内存
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (void *)-1)
	{
		perror("shmat fail");
		return -1;
	}

	while(1)
	{
		memmove(shmaddr, buf, sizeof(buf));
		sleep(1);
	}

	return 0;
}
