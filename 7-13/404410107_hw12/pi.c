#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <stdlib.h>
int global=0;
pthread_mutex_t mutex;
void throwPI(int* inp){
   	int i, count=0,N=*inp;
	struct drand48_data drand_buf;
	srand48_r(time(NULL),&drand_buf);
	double x, y,temp;
    
  	for(i = 0; i < N; ++i )
	{
        	drand48_r(&drand_buf, &temp);
		x = temp;
		drand48_r(&drand_buf, &temp);
		y = temp;
        	if( x*x + y*y <= 1 ) ++count;
    	}
	pthread_mutex_lock(&mutex);
	global += count;
	pthread_mutex_unlock(&mutex);
}
int main(int argc, char const *argv[]) {
        assert(argc == 3);
        char *temp = (char*)malloc(sizeof(char));
	int total = strtol(argv[1], &temp, 10);
	int num = strtol(argv[2], &temp, 10);
	pthread_t* id = (pthread_t*)malloc(sizeof(pthread_t) * num);
	int *th_nums = (int*)malloc(sizeof(int)* num);
	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);
	for(int i = 0; i < num; i++)
	{
		th_nums[i]=total / num +(i<total % num);
		pthread_create(id + i, NULL, (void *) throwPI, th_nums+i);
	}
	for(int i = 0; i < num; i++) pthread_join(id[i], NULL);
	printf("threads = %d \n",num);
	printf("%d = ",total);
	for(int i=0;i<num-1;i++)printf("%d + ",th_nums[i]);
	printf("%d\n",th_nums[num-1]);		
	printf("pi = %lf\n", global / (double)total * 4);	
	return 0;
}
