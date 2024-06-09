#include <iostream>
#include <algorithm>

using namespace std;

class AVL_Tree {

private:

    struct Node {
        Node(int value_): value(value_), height(0), left(nullptr), right(nullptr) {}
        int value;
        int height;
        Node* left;
        Node* right;
    };

public:

    AVL_Tree(): root(nullptr) {}

    Node* root;

    void insert(int value) {
        root = insert(root, value);
    }

    void preorderTraversal(Node* el) {
        if (el != nullptr) {
            if (balanceFactor(el) == 0) {
                cout << el->value << " ";
            }
            preorderTraversal(el->left);
            preorderTraversal(el->right);
        }
    }

private:

    Node* leftRotate(Node* el) {
        Node* p = el->right;
        el->right = p->left;
        p->left = el;
        fixHeight(el);
        fixHeight(p);
        return p;
    }

    Node* rightRotate(Node* el) {
        Node* p = el->left;
        el->left = p->right;
        p->right = el;
        fixHeight(el);
        fixHeight(p);
        return p;
    }

    int getHeight(Node* el) {
        return (el != nullptr ? el->height : -1);
    }

    void fixHeight(Node* el) {
        int lh = getHeight(el->left);
        int rh = getHeight(el->right);
        el->height = max(lh, rh) + 1;
    }

    int balanceFactor(Node* el) {
        return getHeight(el->left) - getHeight(el->right);
    }

    Node* balance(Node* el) {
        fixHeight(el);

        if (balanceFactor(el) == -2) {
            if (balanceFactor(el->right) > 0) {
                el->right = rightRotate(el->right);
            }
            return leftRotate(el);
        }

        if (balanceFactor(el) == 2) {
            if (balanceFactor(el->left) < 0) {
                el->left = leftRotate(el->left);
            }
            return rightRotate(el);
        }

        return el;
    }

    Node* insert(Node* el, int value) {
        if (el == nullptr) {
            return new Node(value);
        }
        if (value < el->value) {
            el->left = insert(el->left, value);
        }
        else {
            el->right = insert(el->right, value);
        }
        return balance(el);
    }
};

int main() {
    int n;
    cin >> n;
    AVL_Tree tree;
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    tree.preorderTraversal(tree.root);

    return 0;
}
