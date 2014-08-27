/*
*	 ������ʵ�ֶ��̵߳Ŀ���
* 	���߳̽��о��ȵĵ���
* 	pthread_cond_signal �Ե����̷߳���
* 	pthread_cond_broadcast �Զ���̹߳㲥����
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/* ����3���߳�tid	*/
pthread_t t1,t2,t3;

/* �̻߳�����	*/
pthread_mutex_t m;

/*	�߳�������		*/
pthread_cond_t c;

int val = 0;

/* �߳�t1�Ĵ�����	*/
void *r1(void *d)
{
	int a = 0;
	while(1)	//�������߳�
	{
		pthread_mutex_lock(&m);	// �������
		pthread_cond_wait(&c,&m);
		a++;
		val++;
		printf("�߳�---1!----%d\n", a);
		pthread_mutex_unlock(&m);	// �������
		if(a == 10)
			break;
	}
	return;
}

/* �߳�t2�Ĵ�����	*/
void *r2(void *d)
{
	int a = 0;
	while(1)	//�������߳�
	{
		pthread_mutex_lock(&m);	// �������
		pthread_cond_wait(&c,&m);
		a++;
		val++;
		printf("�߳�----2!--%d\n", a);
		pthread_mutex_unlock(&m);	// �������
		if (a == 10)
			break;
	}
	return;
}

/* �߳�t3�Ĵ�����	*/
void *r3(void *d)
{
	int a = 0;
	while(1)	//�������߳�
	{
		pthread_mutex_lock(&m);	// �������
		pthread_cond_wait(&c,&m);
		a++;
		val++;
		printf("�߳�-----3--%d!\n", a);
		pthread_mutex_unlock(&m);	// �������
		if(a == 10) 
			break;
	}
	return;

}

main()
{
	// ��ʼ�����������ȳ�ʼ��������ͷ�
	pthread_mutex_init(&m,0);

	// ��ʼ��������
	pthread_cond_init(&c,0);
	
	/* ����3���߳�	*/
	pthread_create(&t1,0,r1,0);
	pthread_create(&t2,0,r2,0);
	pthread_create(&t3,0,r3,0);

	int i = 1;
	while(i<=10)
	{
		//����3�����߳�
		sleep(1);

		// ����������
		//pthread_cond_signal(&c);
		pthread_mutex_lock(&m);	// �������
		pthread_cond_broadcast(&c);
		pthread_mutex_unlock(&m);	// �������
		i++;

	}
	
	/* ���̵߳ȴ�3�����߳̽���	*/
	pthread_join(t1,(void **)0);
	pthread_join(t2,(void **)0);
	pthread_join(t3,(void **)0);

	printf("all thread is over\n");
	printf("val is %d\n", val);
	// �ͷ�������
	pthread_cond_destroy(&c);

	// �ͷŻ�����
	pthread_mutex_destroy(&m);

}
