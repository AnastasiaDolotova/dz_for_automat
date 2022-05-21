/* Для заданного арифметического выражения построить дерево арифметического разбора,
 * написать алгоритм подсчета арифметического выражения,
 * организовав ввод переменных с клавиатуры и с помощью датчика случайных чисел в соответствии с заданным вариантом.
 * Вывести дерево и результат расчета на экран. Провести тестирование программы.
 * (6-3*(z+4)+2)*(5-k) */

#include "tree.h"
#include <conio.h>
#include <stdlib.h>

void deleteSpaces(char *string) {
    char *ptr = string;
    while ((ptr = strstr(ptr, " ")) != NULL)
        strcpy(ptr, ptr + 1);
    ptr = string;
    if (string[0] == ' ')
        strcpy(ptr, ptr + 1);
    if (string[strlen(string) - 1] == ' ')
        string[strlen(string) - 1] = '\0';
}

double solve(char op, double a, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/': {
            if (abs(b) < 0.000001) {
                std::cout << "Error: zero division!" << std::endl;
                return 0;
            }
            return a / b;
        }
        default:
            break;
    }
    return 0;
}

double evaluate(node_t *root, double x, double y) {
    if (root == NULL) {
        return 0;
    }
    if (root->type == VALUE) {
        if (strstr(root->term, "x")) {
            return x;
        }
        if (strstr(root->term, "y")) {
            return y;
        }
        return atof(root->term);
    }
    return solve(root->term[0], evaluate(root->left, x, y), evaluate(root->right, x, y));
}

int main() {
    std::cout << "Choose action:" << std::endl;
    std::cout << "1 - input expression" << std::endl;
    std::cout << "2 - solve (6-3*(x+4)+2)*(5-y)" << std::endl;
    int key;
    std::cin >> key;
    node_t *root = NULL;
    while (key != 4) {
        switch (key) {
            case 1: {
                if (root) deleteTree(root);
                system("cls");
                std::cout << "Input expression f(x, y): ";
                char *string = new char[100];
                std::cin.ignore();
                gets(string);
                deleteSpaces(string);
                parseString(string, strlen(string), &root);
                printTree(root);
                double x, y;
                std::cout << "Input x, y: ";
                std::cin >> x;
                std::cin.ignore();
                std::cin >> y;
                double res = evaluate(root, x, y);
                std::cout << "f(x, y) = " << res << std::endl;
                delete[] string;
                break;
            }
            case 2: {
                if (root) deleteTree(root);
                system("cls");
                char *string = "((6-3*(x+4))+2)*(5-y)";
                parseString(string, strlen(string), &root);
                std::cout << "f(x, y) = (6 - 3 * (x + 4) + 2) * (5 - y)" << std::endl;
                printTree(root);
                double x, y;
                std::cout << "Input x, y: ";
                std::cin >> x;
                std::cin.ignore();
                std::cin >> y;
                double res = evaluate(root, x, y);
                std::cout << "f(x, y) = " << res << std::endl;
                break;
            }
            case 3: {
                system("cls");
                printTree(root);
                break;
            }
        }
        getch();
        system("cls");
        std::cout << "Choose action:" << std::endl;
        std::cout << "1 - input expression" << std::endl;
        std::cout << "2 - solve (6-3*(x+4)+2)*(5-y)" << std::endl;
        std::cout << "3 - info" << std::endl;
        std::cout << "4 - exit" << std::endl;
        std::cin >> key;
    }
    deleteTree(root);
    return 0;
}
