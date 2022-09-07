#include "tree.h"

char *findNextOperation(char *str, int len) {
    char *op = NULL;
    int priority = 100;
    int brackets = 0;
    for (int i = 0; i < len; i++) {
        char simbol = str[i];
        if (simbol == '(') { brackets++; }
        if (simbol == ')') { brackets--; }
        if (brackets == 0) {
            int p = priority;
            switch (simbol) {
                case '+':
                case '-':
                    p = 1;
                    break;
                case '*':
                case '/':
                    p = 2;
                    break;
            }
            if (p < priority) {
                priority = p;
                op = str + i;
            }
        }
    }
    return op;
}

bool inBrackets(char *str, int len) {
    bool result = false;
    if (str[0] == '(') {
        result = true;
        int brackets = 1;
        for (int i = 1; (i < len - 2) && result; i++) {
            if (str[i] == '(') { brackets++; }
            if (str[i] == ')') { brackets--; }
            if (brackets == 0) {
                result = false;
            }
        }
    }
    return result;
}

void parseString(char *str, size_t len, node_t **node_out) {
    int first = 0;
    int last = len - 1;
    node_t *new_node = new node_t;
    while (inBrackets(str + first, last - first + 1)) {
        first++;
        last--;
    }
    char *op = findNextOperation(str + first, last - first);
    if (op == NULL) {
        new_node->type = VALUE;
        int size = last - first + 1;
        new_node->term = new char[size + 1];
        strncpy(new_node->term, str + first, size);
        new_node->term[size] = 0;
        new_node->left = new_node->right = NULL;
    } else {
        new_node->type = OPERATION;
        new_node->term = new char[2];
        new_node->term[0] = *op;
        new_node->term[1] = 0;
        int index = op - str;
        parseString(str + first, index - first, &new_node->left);
        parseString(op + 1, last - index, &new_node->right);
    }
    *node_out = new_node;
}

void preorder(const node_t *root) {
    std::cout << root->term << " ";
    if (root->left) preorder(root->left);
    if (root->right) preorder(root->right);
}

void inorder(const node_t *root) {
    if (root->left) inorder(root->left);
    std::cout << root->term << " ";
    if (root->right) inorder(root->right);
}

void postorder(const node_t *root) {
    if (root->left) postorder(root->left);
    if (root->right) postorder(root->right);
    std::cout << root->term << " ";
}

void print(node_t *p, int indent) {
    if (p) {
        std::cout << std::setw(indent) << p->term << std::endl;
        if (p->left)
            print(p->left, indent - 4);
        if (p->right)
            print(p->right, indent + 4);
    }
}

void deleteTree(node_t *root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void printTree(node_t *root) {
    std::cout << "Tree:" << std::endl;
    print(root);
    std::cout << "Pre-order:" << std::endl;
    preorder(root);
    std::cout << std::endl << "Post-order:" << std::endl;
    postorder(root);
    std::cout << std::endl << "In-order: " << std::endl;
    inorder(root);
    std::cout << std::endl;
}

//AAA