#include <stdio.h>  

#include<pthread.h>  

#include<semaphore.h>  

#include <unistd.h>  

int chairs_count;  

sem_t customers;  

sem_t barber;  

sem_t mutex;  

  void *Barber() {  

    while(1)  

    {  

        	sem_wait(&customers);  

        	printf("\nBarber: Woke up.");  

      	sem_post(&barber); 

printf("\nBarber: Cutting hair.");  

        	sleep(4);  

printf("\nBarber: Finished cutting hair.");  

  	sem_post(&mutex);  

        	printf("\nBarber: Going to sleep.");  

    }  

}  

void *Customer(void *num)  

{  

    int number = *(int*)num;  

  sem_wait(&mutex);  

   if(chairs_count > 0)  

    {  

 printf("\nCustomer %d: Sitting in chair. Chairs Available: %d", number, chairs_count);  

 chairs_count--;  

 	     sleep(2);  

  	  printf("\nCustomer %d: Woke up the barber.", number);  

        	sem_post(&customers);  

sem_wait(&barber);  

      	  printf("\nCustomer %d: Getting my hair cut.", number);  

       	sleep(2);  

  	sem_post(&mutex);  

printf("\nCustomer %d: Leaving shop.", number);  

    }  

    else  {  

     sem_post(&mutex);  

        printf("\nCustomer %d: No chairs available. Leaving shop.", number);  

    }  

}  

int main() {  

    int i;  

    pthread_t barber_t, customer_t[20];  

    int num[20];  

    printf("\nEnter number of chairs: ");  

    scanf("%d", &chairs_count);  

 sem_init(&customers, 0, 0);  

    sem_init(&barber, 0, 0);  

    sem_init(&mutex, 0, 1);  

 pthread_create(&barber_t, NULL, Barber, NULL);  

  for(i = 0; i < 20; i++) {  

        num[i] = i;  

        pthread_create(&customer_t[i], NULL, Customer, (void *)&num[i]);  

    }  

  pthread_join(barber_t, NULL);  

    for(i = 0; i < 20; i++){  

        pthread_join(customer_t[i], NULL);  

    }  

 return 0;  

} 
