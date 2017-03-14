
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#define BUFFER_SIZE 10
typedef struct {
   char type; 
   int amount; 
   char unit; 
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t se;
void produce(item *i) {
   while ((first + 1) % BUFFER_SIZE == last) {    
   }
	sem_wait(&se);
   	memcpy(&buffer[first], i,sizeof(item));
 	first = (first + 1) % BUFFER_SIZE;
	sem_post(&se);
}
item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) {      
    } 
	sem_wait(&se);
    	memcpy(i, &buffer[last], sizeof(item));
   	last = (last + 1) % BUFFER_SIZE;
    	return i;
	sem_post(&se);
}
void first_last() {
	printf("First = %d  Last = %d\n",first,last);
}
void *produce_thread(void *param){
	item item_1;
	item item_2;
	item item_3;
	item_1.type = '1';
	item_1.amount = 0;
	item_1.unit ='1';
	item_2.type = '0';
	item_2.amount = 1;
	item_2.unit ='0';
	printf("The item 1 is :\n type:%c\n amount:%d\n unit:%c\n",item_1.type,item_1.amount,item_1.unit);
	produce(&item_1);
	first_last();
	printf("The item 2 is :\n type:%c\n amount:%d\n unit:%c\n",item_2.type,item_2.amount,item_2.unit);
	produce(&item_2);
	first_last();
	printf("The item 3 is :\n type:%c\n amount:%d\n unit:%c\n",item_3.type,item_3.amount,item_3.unit);
	produce(&item_3);
	first_last();
}
void *consume_thread(void *param) {
	item *consumed= consume();
   	printf("\n-First consuming:\n type: %c\n amount: %d\n unit: %c\n",consumed->type, consumed->amount, consumed->unit);
	first_last();
	printf("\n-Second consuming:\n type: %c\n amount: %d\n unit: %c\n",consumed->type, consumed->amount, consumed->unit);
	first_last()`;
}
int main() {
	sem_init(&se, 0, 1);
	pthread_t tid_1, tid_2;
	pthread_create(
		&tid_1,
		NULL,
		produce_thread,
		NULL);
	pthread_join(tid_1, NULL);
	pthread_create(
		&tid_2,
		NULL,
		consume_thread,
		NULL);
	pthread_join(tid_2, NULL);
	sem_destroy(&se);
}	
