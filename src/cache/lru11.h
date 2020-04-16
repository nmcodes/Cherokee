/*
** lru11.h for Cherokee
**
** Made by NGALULA Jean-Paul
** Login   <ngalul_j@etna-alternance.net>
**
*/

#ifndef __LRU11_H__
#define __LRU11_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
    struct QNode *prev, *next;
    unsigned pageNumber;  
} QNode;
 
typedef struct Queue
{
    unsigned count;  
    unsigned numberOfFrames; 
    QNode *front, *rear;
} Queue;
 
typedef struct Hash
{
    int capacity; 
    QNode* *array;
} Hash;

QNode* newQNode( unsigned pageNumber );
Queue* createQueue( int numberOfFrames );
Hash* createHash( int capacity );
int AreAllFramesFull( Queue* queue );
int isQueueEmpty( Queue* queue );
void deQueue( Queue* queue );
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber );
void ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber );

#endif