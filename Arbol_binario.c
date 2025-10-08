#include <stdio.h>
#include <stdlib.h>

/* Estructura del nodo del árbol */
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

/* Crear un nuevo nodo */
Node* create_node(int value) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Error de memoria\n");
        exit(EXIT_FAILURE);
    }
    n->value = value;
    n->left = n->right = NULL;
    return n;
}

/* Insertar un valor en el BST (recursivo).
   Si el valor ya existe, no lo inserta de nuevo. */
Node* insert(Node* root, int value) {
    if (root == NULL) return create_node(value);

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

/* Buscar un valor en el BST (retorna el nodo o NULL) */
Node* search(Node* root, int value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    if (value < root->value) return search(root->left, value);
    return search(root->right, value);
}

/* Recorridos clásicos */
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->value);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);
}

/* Liberar todo el árbol (postorder) */
void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* Ejemplo de uso */
int main(void) {
    Node *root = NULL;

    /* Insertamos valores de ejemplo */
    int values[] = {5, 3, 7, 2, 4, 6, 8};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i) {
        root = insert(root, values[i]);
    }

    printf("Inorder (orden ascendente): ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    /* Buscar ejemplo */
    int key = 4;
    Node *found = search(root, key);
    if (found) printf("Valor %d encontrado en el árbol.\n", key);
    else printf("Valor %d NO encontrado.\n", key);

    free_tree(root);
    return 0;
}
