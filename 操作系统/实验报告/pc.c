#define __LIBRARY__
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
	
#define BUFFER_SIZE 10	/* 缓冲区数量 */
#define NUM 25			/* 产品总数 */

#define __NR_sem_open 87
#define __NR_sem_wait 88
#define __NR_sem_post 89
#define __NR_sem_unlink 90
#define __NR_shmget 91
#define __NR_shmat 92

typedef void sem_t;  /* 下面用到sem_t*的，其实质都是指针，故在此将sem_t*类型定义为void*类型，
						就不用在此重新定义sem_t的结构体，因此也方便了对结构体的管理：如果在
						此重新定义此结构体，内核中也已经定义了此结构体，如需对其修改，则同时
						需要修改此处和内存处两处的结构体 */
_syscall2(int, shmget, int, key, int, size)
_syscall2(int, shmat, int, shmid, const void*, shmaddr)
_syscall2(int, sem_open, const char*, name, unsigned int, value)
_syscall1(int, sem_wait, sem_t *, sem)
_syscall1(int, sem_post, sem_t *, sem)
_syscall1(int, sem_unlink, const char *, name)

int main()
{	
	/* 注意: 在应用程序中不能使用断点等调试功能 */
	int i, j;
	int consumeNum = 0; /* 消费者消费的产品号 */
	int produceNum = 0; /* 生产者生产的产品号 */
	int consume_pos = 0; /* 消费者从共享缓冲区中取出产品消费的位置 */
	int produce_pos = 0; /* 生产者生产产品向共享缓冲区放入的位置 */
	int shmid;
	int *p;
	sem_t *empty, *full, *mutex;
	FILE *fp = NULL;
	pid_t producer_pid, consumer_pid;
	
	/* 创建empty、full、mutex三个信号量 */
	empty = (sem_t*)sem_open("empty", BUFFER_SIZE);
	full  = (sem_t*)sem_open("full", 0);
	mutex = (sem_t*)sem_open("mutex", 1);
	/* 创建生产者进程 */
	if( !fork() )
	{
		producer_pid = getpid();
		printf("producer pid=%d create success!\n", producer_pid);
		shmid = shmget(0, 4096);
		p = (int*)shmat(shmid, NULL);
		for( i = 0 ; i < NUM; i++)
		{
			sem_wait(empty);
			sem_wait(mutex);
			produceNum = i;

			*(p + produce_pos) = produceNum;
			
			/* 输出生产产品的信息 */
			printf("Producer pid=%d : %02d at %d\n", producer_pid, produceNum, produce_pos); 
			fflush(stdout);
			
			/* 生产者的游标向后移动一个位置 */
			produce_pos = (produce_pos + 1) % BUFFER_SIZE;
			
			sem_post(mutex);
			sem_post(full);
			
			sleep(2);
		}
		exit(0);
	}
	
	/* 创建消费者进程 */
	if( !fork() )
	{
		consumer_pid = getpid();
		printf("\t\t\tconsumer pid=%d create success!\n", consumer_pid);
		shmid = shmget(0, 4096);
		p = (int*)shmat(shmid, NULL);
		for( j = 0; j < NUM; j++ ) 
		{
			sem_wait(full);
			sem_wait(mutex);
			
			consumeNum = *(p + consume_pos);
			
			/* 输出消费产品的信息 */
			printf("\t\t\tConsumer pid=%d: %02d at %d\n", consumer_pid, consumeNum, consume_pos);
			fflush(stdout);
			
			/* 消费者的游标向后移动一个位置 */
			consume_pos = (consume_pos + 1) % BUFFER_SIZE;
	
			sem_post(mutex);
			sem_post(empty);
			
			if(j<4)	sleep(8);
			else sleep(1);
		}
		exit(0);
	}

	waitpid(producer_pid, NULL, 0);	/* 等待生产者进程结束 */
	waitpid(consumer_pid, NULL, 0);	/* 等待消费者进程结束 */
	
	/* 关闭所有信号量 */
	sem_unlink("empty");
	sem_unlink("full");
	sem_unlink("mutex");
	
	/* 关闭文件 */
	fclose(fp);
	
	return 0;
}
