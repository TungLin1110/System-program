#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
const double _eps = 0.00000000001;
long long total, threads, count;
pthread_mutex_t mutex;

void* thread( void ){
	unsigned int t = time(NULL);
	double x, y, z;
	long long times = total / threads, count_ = 0;
	do{
		x = rand_r( &t ) / (RAND_MAX + 1.);
		y = rand_r( &t ) / (RAND_MAX + 1.);
		z = x * x + y * y;
		if( z < 1 + _eps ) ++count_;
	}while( --times );

	
	pthread_mutex_lock( &mutex );
	count += count_;
	pthread_mutex_unlock( &mutex );
	

	pthread_exit( 0 );
}
int main(int argc, char* argv[]){
	//IO
	if( argc != 3 ){
		fprintf( stderr, "Wrong Input.\n" );
		exit( -1 );
	}
	total = atol( argv[1] ), threads = atol( argv[2] ), count = 0;
	if( threads > 100 ){
		fprintf( stderr, "Sorry but I have only 100 capacity for threads.\n" );
		exit( -1 );
	}

	pthread_t tid[100];
	long long i;
	pthread_mutex_init( &mutex, NULL );
	for( i = 0; i < threads; ++i ) pthread_create( tid + i, NULL, (void *) thread, NULL );
	for( i = 0; i < threads; ++i ) pthread_join( tid[i], NULL);

	fprintf( stderr, "pi = %.8lf\n", 4. * count / total );
	return 0;
}
