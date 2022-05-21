#ifndef DZ2_3_TREE_H
#define DZ2_3_TREE_H

#include <iostream>
#include <string.h>
#include <iomanip>

enum term_type_t {
    OPERATION,
    VALUE,
};

struct node_t {
    char *term;
    term_type_t type;
    node_t *left;
    node_t *right;
};

char *findNextOperation(char *str, int len);
bool inBrackets(char *str, int len);
void parseString(char *str, size_t len, node_t **node_out);
void preorder(const node_t *root);
void inorder(const node_t *root);
void postorder(const node_t *root);
void print(node_t *p, int indent = 20);
void deleteTree(node_t *root);
void printTree(node_t *root);

#endif //DZ2_3_TREE_H
