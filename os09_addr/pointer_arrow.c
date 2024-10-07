typedef struct node {
  struct node * next;
  long x;
} node_t;
long chase(node_t * a) {
  long s = 0;
  for (node_t * p = a; p; p = p->next) {
    s += p->x;
  }
  return s;
}
