#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct _node {
  char item;
  struct _node* left;
  struct _node* right;
} t_node;

typedef struct {
  t_node* root;
} t_binary_tree;

t_binary_tree* createTree(const char* str);
void printPre(t_node* node);
void printIn(t_node* node);
void printPost(t_node* node);
void printTree(t_node* node, int level);
int getNodeHeight(t_node* node, char target);
void freeTree(t_binary_tree* tree);
void freeNode(t_node* node);

#endif
