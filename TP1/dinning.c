#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//mutex 
pthread_mutex_t lock[5];

//thread 
void *thr(void *arg)
{
	int left, right;

	int i= (int)arg;

	// The first four take the left hand
	if (i < 4)
	{
		left = i;
		if (i == 0)
		{
			right = 4;
		}
		else{
			right = i - 1;
		}
	}

	//The fifth one takes the right lock
	if (i == 4)
	{
		left = i-1;
		right = i;
	}
	while (1)
	{

		//Apply for the lock on the left
		pthread_mutex_lock(&lock[left]);

		//Apply for the lock on the right
		if ((pthread_mutex_trylock(&lock[right])) != 0)
		{
			pthread_mutex_unlock(&lock[left]);
			printf(" ==thread  %d ==  Application failed\n", i);
			continue;
		}

		//Both sides successfully applied
		printf("==thread  %d == succesful\n", i);

		//Release the lock
		pthread_mutex_unlock(&lock[left]);
		pthread_mutex_unlock(&lock[right]);

		sleep(1);
	}
}

int main()
{
	//initialization
	for (int i; i < 5; i++)
	{
		pthread_mutex_init(& [i], NULL);
	}

	//Create thread
	pthread_t dit[5];
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&dit[i], NULL, thr, (void *)i);
	}

	//Recycle thread
	for (int i = 0; i < 5; i++)
	{
		pthread_join(dit[i], NULL);
	}
	//Destruction
	pthread_exit(NULL);

	return 0;
}