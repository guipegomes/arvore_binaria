#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

int main() {
  t_binary_tree *tree = NULL;
  char command[16];
  int loop = 1;

  while (loop) {
    printf("> ");
    scanf("%s", command);

    // Converte para usar no switch
    int cmd = -1;
    if (strcmp(command, "create") == 0) cmd = 1;
    else if (strcmp(command, "pre") == 0) cmd = 2;
    else if (strcmp(command, "in") == 0) cmd = 3;
    else if (strcmp(command, "post") == 0) cmd = 4;
    else if (strcmp(command, "print") == 0) cmd = 5;
    else if (strcmp(command, "height") == 0) cmd = 6;
    else if (strcmp(command, "exit") == 0) cmd = 0;
    else cmd = -1;

    switch (cmd) {
      case 1: { // create
        char expr[1000];
        scanf(" %[^\n]", expr);

        if (tree != NULL) {
          freeTree(tree);
          tree = NULL;
        }

        tree = createTree(expr); 
        if (tree == NULL || tree->root == NULL) {
          printf("invalid\n");
          if (tree) {
            freeTree(tree);
            tree = NULL;
          }
        }
        break;
      }

      case 2: { // pre
        if (tree) {
          printPre(tree->root);
          printf("\n");
        }
        else {
          printf("Crie uma árvore primeiro.\n");
        }
        break;
      }

      case 3: { // in
        if (tree) {
          printIn(tree->root);
          printf("\n");
        }
        else {
          printf("Crie uma árvore primeiro.\n");
        }
        break;
      }

      case 4: { // post
        if (tree) {
          printPost(tree->root);
          printf("\n");
        }
        else {
          printf("Crie uma árvore primeiro.\n");
        }
        break;
      }

      case 5: { // print
        if (tree) {
          printTree(tree->root, 0);
        }
        else {
          printf("Crie uma árvore primeiro.\n");
        }
        break;
      }

      case 6: { // height
        char target;
        scanf(" %c", &target);

        if (tree) {
          int h = getNodeHeight(tree->root, target);
          if (h == -1) {
            printf("node not found\n");
          } else {
            printf("%d\n", h);
          }
        }
        else {
          printf("Crie uma árvore primeiro.\n");
        }
        break;
      }

      case 0: // exit
        loop = 0;
        break;

      default:
        printf("Comando não existe\n");
        break;
    }
  }

  if (tree) {
    freeTree(tree);
  }

  return 0;
}
