#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semaphore.h"

#define SEM_FILE "./semfile"

int create_sem(int nsems)
{
	int semid = -1;
	int fd = -1;
	int key = -1;

	fd = open(SEM_FILE, O_RDWR |O_CREAT, 0664);
	if(-1 == fd)
	{
		perror("Error");
		exit(-1);
	}

	key = ftok(SEM_FILE, 'a');
	if(-1 == key)
	{
		perror("Error");
		exit(-1);
	}

	semid = semget(key, nsems, 0664 | IPC_CREAT);
	if(-1 == semid)
	{
		perror("Error");
		exit(-1);
	}

	return semid;
}

//信号量初始化
void init_sem(int semid, int semnum, int val)
{
	int ret = -1;
	//semnum是信号量编号，SETVAL设置信号量初始值cmd
	ret = semctl(semid, semnum, SETVAL, val);
	if(ret == -1)
	{
		perror("Error");
		exit(-1);
	}
}

//删除信号量
void del_sem(int semid, int nsems)
{
	int ret = -1;
	ret = semctl(semid, 0, IPC_RMID);
	if(ret == -1)
	{
		perror("Error");
		exit(-1);
	}
	remove(SEM_FILE);
}

//P操作
void p_sem(int semid, int semnum_buf[], int nsops)
{
	int i = 0;
	int ret = -1;
	struct sembuf sops[nsops]; 

	for(i = 0; i < nsops; i++)
	{
		sops[i].sem_num = semnum_buf[i];	//信号量编号
		sops[i].sem_op = -1;	//-1 P操作
		sops[i].sem_flg = SEM_UNDO;	//防止死锁
	}

	ret = semop(semid, sops, nsops);
	if(ret == -1)
	{
		perror("Error");
		exit(-1);
	}
}

//V操作
void v_sem(int semid, int semnum_buf[], int nsops)
{
	int i = 0;
	int ret = -1;
	struct sembuf sops[nsops]; 

	for(i = 0; i < nsops; i++)
	{
		sops[i].sem_num = semnum_buf[i];	//信号量编号
		sops[i].sem_op = 1;	//+1 V操作
		sops[i].sem_flg = SEM_UNDO;	//防止死锁
	}

	ret = semop(semid, sops, nsops);
	if(ret == -1)
	{
		perror("Error");
		exit(-1);
	}
}
