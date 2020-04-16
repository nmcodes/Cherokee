/*
** lru11.c for Cherokee
**
** Made by NGALULA Jean-Paul
** Login   <ngalul_j@etna-alternance.net>
**
*/

#include "lru11.h"
 
QNode* newQNode( unsigned pageNumber )
{
    QNode* temp = (QNode *)malloc( sizeof( QNode ) );
    temp->pageNumber = pageNumber;
    temp->prev = temp->next = NULL;
    return temp;
}
 
Queue* createQueue( int numberOfFrames )
{
    Queue* queue = (Queue *)malloc( sizeof( Queue ) ); 
    queue->count = 0;
    queue->front = queue->rear = NULL;
    queue->numberOfFrames = numberOfFrames;
 
    return queue;
}
 

Hash* createHash( int capacity )
{
    Hash* hash = (Hash *) malloc( sizeof( Hash ) );
    hash->capacity = capacity;
    hash->array = (QNode **) malloc( hash->capacity * sizeof( QNode* ) );
    int i;
    for( i = 0; i < hash->capacity; ++i )
        hash->array[i] = NULL;
 
    return hash;
}
 
int AreAllFramesFull( Queue* queue )
{
    return queue->count == queue->numberOfFrames;
}
 

int isQueueEmpty( Queue* queue )
{
    return queue->rear == NULL;
}
 
void deQueue( Queue* queue )
{
    if( isQueueEmpty( queue ) )
        return;
 
    if (queue->front == queue->rear)
        queue->front = NULL;
 
    QNode* temp = queue->rear;
    queue->rear = queue->rear->prev;
 
    if (queue->rear)
        queue->rear->next = NULL;
 
    free( temp );

    queue->count--;
}
 
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber )
{

    if ( AreAllFramesFull ( queue ) )
    {
        hash->array[ queue->rear->pageNumber ] = NULL;
        deQueue( queue );
    }
 
    QNode* temp = newQNode( pageNumber );
    temp->next = queue->front;
 
    if ( isQueueEmpty( queue ) )
        queue->rear = queue->front = temp;
    else 
    {
        queue->front->prev = temp;
        queue->front = temp;
    }
 
    hash->array[ pageNumber ] = temp;
 
 
    queue->count++;
}
 

void ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber )
{
    QNode* reqPage = hash->array[ pageNumber ];
 
    if ( reqPage == NULL )
        Enqueue( queue, hash, pageNumber );
 
    else if (reqPage != queue->front)
    {
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
           reqPage->next->prev = reqPage->prev;
         if (reqPage == queue->rear)
        {
           queue->rear = reqPage->prev;
           queue->rear->next = NULL;
        }
        reqPage->next = queue->front;
        reqPage->prev = NULL;
        reqPage->next->prev = reqPage;
 
        queue->front = reqPage;
    }
}
 

int main(int argc, char *argv[])
{
    Queue* q = createQueue( 4 );        
    Hash* hash = createHash( 10 );
    ReferencePage( q, hash, 1);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 3);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 5);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 4);
    printf ("%d ", q->front->pageNumber);
    printf ("%d ", q->front->next->pageNumber);
    printf ("%d ", q->front->next->next->pageNumber);
    printf ("%d ", q->front->next->next->next->pageNumber);

    if (argc > 2) {
        fprintf(stderr, "usage: shmdemo [data_to_write]\n");
        exit(1);
    }

    /* make the key: */
    if ((key = ftok("lru11.c", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

	printf ("\nkey : %d \n", key);

    /* connect to (and possibly create) the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    if (argc == 2) {
        printf("writing to segment: \"%s\"\n", argv[1]);
        strncpy(data, argv[1], SHM_SIZE);
    } else
        printf("segment contains: \"%s\"\n", data);

    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
 
    return 0;
}
