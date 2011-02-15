/*see LICENSES file for original credits*/

#ifndef QUEUE_H
#define QUEUE_H

#include"list.h"

typedef list* queue;

void clear_queue(queue* q);
bool empty_queue(const queue q);
item_type head_queue(const queue q);
queue init_queue(void);
item_type de_queue(queue* q);
void en_queue(queue* q, const item_type x, size_t n);

#endif /* QUEUE_H */


