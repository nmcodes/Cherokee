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
 

QNode* newQNode( unsigned pageNumber );
Queue* createQueue( int numberOfFrames );
Hash* createHash( int capacity )
int AreAllFramesFull( Queue* queue )
int isQueueEmpty( Queue* queue )
void deQueue( Queue* queue )
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber )
void ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber )

#endif