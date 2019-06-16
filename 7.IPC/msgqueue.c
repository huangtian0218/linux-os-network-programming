#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define MSG_FILE "./msgfile"
#define MSG_SIZE 1024

static int msgid;

struct msgbuf
{
	long mtype;       
	char mtext[MSG_SIZE];
};

void signal_fun(int signo)
{
	//删除消息队列
	msgctl(msgid, IPC_RMID, NULL);
	exit(-1);
}

int create_msg_queue()
{
	int msgid = -1;	
	key_t key = -1;
	int fd = -1; 
	
	//创建一个消息队列专用文件
	fd = open(MSG_FILE, O_RDWR|O_CREAT, 0664);
	if(fd == -1)
	{
		perror("Error");
		return -1;
	}

	//利用已经存在的文件和8位整型数，创建key值
	key = ftok(MSG_FILE, 'a');
	if(key == -1)
	{
		perror("Error");
		return -1;
	}

	//利用key值创建或者获取消息队列
	msgid = msgget(key, 0664|IPC_CREAT);
	if(msgid == -1)
	{
		perror("Error");
		return -1;
	}

	return msgid;
}

int main(int argc, char *argv[])
{
	int ret = -1;
	long msgtype = -1;

	if(argc != 2)
	{
		printf("./a.out msgtype\n");
		return -1;
	}
	msgtype = atol(argv[1]);

	msgid = create_msg_queue();	
	if(msgid == -1)
	{
		perror("Error");
		return -1;
	}

	ret = fork();
	if(ret > 0)
	{
		//父进程捕获中断信号
		signal(SIGINT, signal_fun);

		struct msgbuf msgbuf;

		while(1)
		{
			memset(&msgbuf, 0, sizeof(msgbuf));

			//封装消息包
			//read(0, msgbuf.mtext, sizeof(msgbuf.mtext));
			printf("Please input msgtext: ");
			scanf("%s", msgbuf.mtext);
			printf("Please input msgtype: ");
			scanf("%ld", &msgbuf.mtype);

			//发送消息包
			msgsnd(msgid, &msgbuf, MSG_SIZE, 0);
		}
	}
	else if(ret == 0)
	{
		int ret = -1;
		struct msgbuf msgbuf;

		while(1)
		{
			memset(&msgbuf, 0, sizeof(msgbuf));
			ret = msgrcv(msgid, &msgbuf, MSG_SIZE, msgtype, 0);
			if(ret > 0)
			{
				printf("\nrecv a message from \033[40;31m\033[1m%ld", msgbuf.mtype);
				printf("\n\033[40;33m%s\033[0m\n", msgbuf.mtext);
			}
		}
	}

	return 0;
}
