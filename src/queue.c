#include "queue.h"

#include <stdlib.h>


queue_t* create_queue() {
  queue_t* queue = malloc(sizeof(queue_t));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void free_queue(queue_t* queue) {
  while (!queue_is_empty(queue)) {
    node_t* node = dequeue(queue);
    free_node(node);
  }
  free(queue);
}

void enqueue(queue_t* queue, int x, int y, lawn_matrix_t* lawn_matrix) {
  node_t* node = create_node(x, y, lawn_matrix);
  if (queue_is_empty(queue)) {
    queue->front = node;
    queue->rear = node;
  } else {
    queue->rear->next = node;
    queue->rear = node;
  }
}

node_t* dequeue(queue_t* queue) {
  node_t* node = queue->front;
  queue->front = queue->front->next;
  return node;
}

bool queue_is_empty(queue_t* queue) { return queue->front == NULL; }


node_t* create_node(int x, int y, lawn_matrix_t* lawn_matrix) {
  node_t* node = malloc(sizeof(node_t));
  node->x = x;
  node->y = y;
  node->lawn_matrix = lawn_matrix;
  node->next = NULL;
  return node;
}

void free_node(node_t* node) {
  free_lawn_matrix(node->lawn_matrix);
  free(node);
}
