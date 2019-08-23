/////
///		Editor	rcrossp
///		Date	20180503
/////

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define N         5
#define LEFT     (i+N-1)%N
#define RIGHT    (i+1)%N
#define THINKING  0
#define HUNGRY    1
#define EATING    2

int state[N];
pthread_t tid[N];
pthread_mutex_t mutex;
pthread_mutex_t s[N];

void *philosopher(void *i);
void take_forks(int i);
void put_forks(int i);
void test(int i);

int main(){
	int i;
	
	for(i=0;i<N;i++)
		pthread_mutex_init(&s[i],NULL);
	pthread_mutex_init(&mutex,NULL);
	
	for(i=0;i<N;i++){
		int *temp=(int*)malloc(sizeof(int));
        *temp = i;
		pthread_create(&tid[i],NULL,philosopher,temp);
	}
	for(i=0;i<N;i++){
		pthread_join(tid[i],NULL);
	}
}
void *philosopher(void *i){
	int NUM=*(int *)i;
	while(1){
		//think();
		take_forks(NUM);
		//eat();
		sleep(rand()%5+1);
		put_forks(NUM);
	}
}
void take_forks(int i){
	pthread_mutex_lock(&mutex);
	state[i] = HUNGRY;
	printf("%d %d %d %d %d\n",state[0],state[1],state[2],state[3],state[4]);
	test(i);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&s[i]);
}
void put_forks(int i){
	pthread_mutex_lock(&mutex);
	if(state[i]==EATING){	
		state[i] = THINKING;
		printf("%d %d %d %d %d\n",state[0],state[1],state[2],state[3],state[4]);
	}	
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex);
}
void test(int i){
	if((state[i]==HUNGRY)&&(state[LEFT]!=EATING)&&(state[RIGHT]!=EATING)){
		state[i]=EATING;
		printf("%d %d %d %d %d\n",state[0],state[1],state[2],state[3],state[4]);
		pthread_mutex_unlock(&s[i]);
	}
}
