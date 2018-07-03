/*
 * Queue.h
 *
 *  Created on: 23/06/2018
 *      Author: administrador
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef void *Type;
typedef struct strQueue *Queue;
typedef enum {falso, verdadero} Boolean;

Queue create_queue();
void destroy_queue(Queue);
void offer_queue(Queue, Type);
Type poll_queue(Queue);
Type peek_queue(Queue);
Boolean isEmpty_queue(Queue);
int size_queue(Queue);

#endif /* QUEUE_H_ */
