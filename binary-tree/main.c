#include <stdio.h>
#include <stdlib.h>

enum TCompare {
    LESS_THAN = -1,
    GREATER_THAN = 1,
    EQUALS = 0
} typedef Compare;

enum TBalanceFactor {
    UNBALANCED_RIGHT = 1,
    SLIGHTLY_UNBALANCED_RIGHT,
    BALANCED,
    SLIGHTLY_UNBALANCED_LEFT,
    UNBALANCED_LEFT
};

struct TNode {
    int value;
    struct TNode * right;
    struct TNode * left;
} typedef Node;

struct TAvlTree {
    struct TNode * root;
} typedef AvlTree;

Node * createNode(int valueOfNode) {
    Node * node = (Node *)malloc(sizeof(Node));
    node->value = valueOfNode;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AvlTree * createTree() {
    AvlTree * avlTree = (AvlTree *)malloc(sizeof(AvlTree));
    avlTree->root = NULL;
    return avlTree;
}

int compareValues(int valueOne, int valueTwo) {
    if(valueOne < valueTwo) return LESS_THAN;
    if(valueOne > valueTwo) return GREATER_THAN;
    return EQUALS;
}

int max(int valueOne, int valueTwo) {
    return valueOne > valueTwo ? valueOne : valueTwo;
}

Node * rotationLL(Node * node) {
    Node * tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    return tmp;
}

Node * rotationRR(Node * node) {
    Node * tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    return tmp;
}

Node * rotationLR(Node * node) {
    node->left = rotationRR(node->left);
    return rotationLL(node);
}

Node * rotationRL(Node * node) {
    node->right = rotationLL(node->right);
    return rotationRR(node);
}

Node * insertNode(Node * node, int element) {
    if(node == NULL) {
        return createNode(element);
    } else if(compareValues(element, node->value) == LESS_THAN) {
        node->left = insertNode(node->left, element);
    } else if(compareValues(element, node->value) == GREATER_THAN) {
        node->right = insertNode(node->right, element);
    } else {
        return node;
    }

    int balanceFactor = getBalanceFactor(node);

    if(balanceFactor == UNBALANCED_LEFT) {
        if(compareValues(element, node->left->value) == LESS_THAN) {
            node = rotationLL(node);
        } else {
            return rotationLR(node);
        }
    }

    if(balanceFactor == UNBALANCED_RIGHT) {
        if(compareValues(element, node->right->value) == GREATER_THAN) {
            node = rotationRR(node);
        } else {
            return rotationRL(node);
        }
    }

    return node;
}

void insert(AvlTree * avlTree, int element) {
    avlTree->root = insertNode(avlTree->root, element);
}


int getNodeHeight(Node * node) {
    if(node == NULL) return -1;
    return max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

int getBalanceFactor(Node * node) {
    int heightDifference = getNodeHeight(node->left) - getNodeHeight(node->right);

    switch(heightDifference) {
        case -2:
            return UNBALANCED_RIGHT;
        case -1:
            return SLIGHTLY_UNBALANCED_RIGHT;
        case 1:
            return SLIGHTLY_UNBALANCED_LEFT;
        case 2:
            return UNBALANCED_LEFT;
        default:
            return BALANCED;
    }
}

void menu(int option, AvlTree * avlTree) {
    int valueOfNode;

    switch(option) {
        case 0:
            printf("\nEncerrando programa!\n");
        break;
        case 1:
            printf("\nDigite o valor do no que deseja inserir: ");
            scanf("%d", &valueOfNode);

            insert(avlTree, valueOfNode);
        break;
        default:
            printf("\nOpcao invalida!\n");
        break;
    }

    printf("\n");
}

int main()
{
    int option;
    AvlTree * avlTree = createTree();

    do {
        printf("0 - Encerrar o programa\n1 - Inserir no na arvore\n\n");
        scanf("%d", &option);

        menu(option, avlTree);
    } while(option != 0);
}