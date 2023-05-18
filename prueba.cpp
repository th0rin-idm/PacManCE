#include <iostream>
#include <vector>

struct Node {
    int value;
    std::vector<Node*> children;
    
    Node(int val) : value(val) {}
};

Node* createNode(int value) {
    Node* newNode = new Node(value);
    return newNode;
}

void createTree(std::vector<std::vector<int>>& matrix, Node* parent, int row, int col) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Check right neighbor
    if (col + 1 < cols) {
        int value = matrix[row][col + 1];
        Node* child = createNode(value);
        parent->children.push_back(child);
        createTree(matrix, child, row, col + 1);
    }
    
    // Check down neighbor
    if (row + 1 < rows) {
        int value = matrix[row + 1][col];
        Node* child = createNode(value);
        parent->children.push_back(child);
        createTree(matrix, child, row + 1, col);
    }
}

bool findPath(Node* node, int target, std::vector<int>& path) {
    path.push_back(node->value);
    
    if (node->value == target) {
        return true;
    }
    
    for (Node* child : node->children) {
        if (findPath(child, target, path)) {
            return true;
        }
    }
    
    path.pop_back();
    return false;
}

int main() {
    int rows, cols;
    std::cout << "Ingrese el número de filas: ";
    std::cin >> rows;
    std::cout << "Ingrese el número de columnas: ";
    std::cin >> cols;
    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    std::cout << "Ingrese los elementos de la matriz:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    Node* root = createNode(matrix[0][0]);
    createTree(matrix, root, 0, 0);
    
    int start, end;
    std::cout << "Ingrese el punto de inicio: ";
    std::cin >> start;
    std::cout << "Ingrese el punto de destino: ";
    std::cin >> end;
    
    std::vector<int> path;
    if (findPath(root, start, path)) {
        std::cout << "Camino encontrado: ";
        for (int value : path) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No se encontró un camino válido." << std::endl;
    }
    
    // Liberar memoria
    // ...
    
    return 0;
}
