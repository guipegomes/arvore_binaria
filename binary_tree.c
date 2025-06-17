#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

const char* skipSpaces(const char* str) {
  while (*str == ' ') str++;
  return str;
}

int verifyChar(const char** str, char comparison) {
  *str = skipSpaces(*str);
  if(**str != comparison) return 0;
  (*str)++;
  return 1;
}

int validateExpression(const char** str) {
  *str = skipSpaces(*str);
  if (**str == '\0') return 0;

  if (**str == ')') {
    return 1;
  }

  char c = **str;
  if (c == ',' || c == '(' || c == ')') return 0;
  (*str)++;

  if (!verifyChar(str, ',')) return 0;

  if (!verifyChar(str, '(')) return 0;

  if (!validateExpression(str)) return 0;

  if (!verifyChar(str, ')')) return 0;

  if (!verifyChar(str, ',')) return 0;

  if (!verifyChar(str, '(')) return 0;

  if (!validateExpression(str)) return 0;

  if (!verifyChar(str, ')')) return 0;

  return 1;
}

// socorro deus -- deve ter um jeito melhor de fazer isso...
t_node* readNode(const char* str, const char** next) {
  str = skipSpaces(str);
  if (*str == '\0' || *str == ')') {
    *next = str;
    return NULL;
  }

  char item = *str;
  str++;

  if (!verifyChar(&str, ',')) {
    *next = str;
    return NULL;
  }

  if (!verifyChar(&str, '(')) {
    *next = str;
    return NULL;
  }

  t_node* left = readNode(str, &str);

  if (!verifyChar(&str, ')')) {
    *next = str;
    return NULL;
  }

  if (!verifyChar(&str, ',')) {
    *next = str;
    return NULL;
  }

  if (!verifyChar(&str, '(')) {
    *next = str;
    return NULL;
  }

  t_node* right = readNode(str, &str);

  if (!verifyChar(&str, ')')) {
    *next = str;
    return NULL;
  }

  t_node* node = (t_node*)malloc(sizeof(t_node));
  node->item = item;
  node->left = left;
  node->right = right;

  *next = str;
  return node;
}

t_binary_tree* createTree(const char* str) {
  str = skipSpaces(str);
  if (*str != '(') return NULL;
  str++;

  const char* temp = str;
  if (!validateExpression(&temp)) {
    return NULL;
  }

  const char* next;
  t_node* root = readNode(str, &next);
  next = skipSpaces(next);

  if (*next != ')') {
    freeNode(root);
    return NULL;
  }

  t_binary_tree* tree = (t_binary_tree*)malloc(sizeof(t_binary_tree));
  tree->root = root;
  return tree;
}

void printPre(t_node* node) {
  if (node == NULL) return;
  printf("%c ", node->item);
  printPre(node->left);
  printPre(node->right);
}

void printIn(t_node* node) {
  if (node == NULL) return;
  printIn(node->left);
  printf("%c ", node->item);
  printIn(node->right);
}

void printPost(t_node* node) {
  if (node == NULL) return;
  printPost(node->left);
  printPost(node->right);
  printf("%c ", node->item);
}

void printTree(t_node* node, int level) {
  if (node == NULL) return;
  printTree(node->right, level + 1);
  for (int i = 0; i < level; i++) {
    printf("   ");
  }
  printf("%c\n", node->item);
  printTree(node->left, level + 1);
}

int getNodeHeight(t_node* node, char target) {
  if (node == NULL) return -1;

  if (node->item == target) {
    int left = node->left ? getNodeHeight(node->left, node->left->item) + 1 : 0;
    int right = node->right ? getNodeHeight(node->right, node->right->item) + 1 : 0;
    return (left > right ? left : right);
  }

  int leftSearch = getNodeHeight(node->left, target);
  if (leftSearch != -1) return leftSearch;

  return getNodeHeight(node->right, target);
}

void freeNode(t_node* node) {
  if (node == NULL) return;
  freeNode(node->left);
  freeNode(node->right);
  free(node);
}

void freeTree(t_binary_tree* tree) {
  if (tree == NULL) return;
  freeNode(tree->root);
  free(tree);
}