#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class AVL_Tree {

private:

    struct Book {

        Book(int label, string author, string title, int year, int copyCount) {
            this->label = label;
            this->author = author;
            this->title = title;
            this->year = year;
            this->copyCount = copyCount;

            this->height = 0;
            this->left = nullptr;
            this->right = nullptr;
        }

        int label;
        string author;
        string title;
        int year;
        int copyCount;

        int height;
        Book* left;
        Book* right;
    };

public:

    AVL_Tree(): root(nullptr) {}

    Book* root;

    void insert(int label, string author, string title, int year, int copyCount) {
        Book aBook(label, author, title, year, copyCount);
        root = insert(root, aBook);
    }

    void remove(int label) {
        root = remove(root, label);
    }

    void showBookList() {
        vector <Book> array;
        inorderTraversal(root, array);
        sort(array.begin(), array.end(), [](Book& a, Book& b)->bool {return a.year < b.year;});
        for (auto& el : array) {
            cout << el.label << " " << el.author << " " << el.title << " " << el.year << " " << el.copyCount << endl;
        }
    }

private:

    Book* leftRotate(Book* el) {
        Book* p = el->right;
        el->right = p->left;
        p->left = el;
        fixHeight(el);
        fixHeight(p);
        return p;
    }

    Book* rightRotate(Book* el) {
        Book* p = el->left;
        el->left = p->right;
        p->right = el;
        fixHeight(el);
        fixHeight(p);
        return p;
    }

    int getHeight(Book* el) {
        return (el != nullptr ? el->height : -1);
    }

    void fixHeight(Book* el) {
        int lh = getHeight(el->left);
        int rh = getHeight(el->right);
        el->height = max(lh, rh) + 1;
    }

    int balanceFactor(Book* el) {
        return getHeight(el->left) - getHeight(el->right);
    }

    Book* balance(Book* el) {
        fixHeight(el);

        if (balanceFactor(el) == -2) {      // do left rotate
            if (balanceFactor(el->right) > 0) {     // do BIG left rotate
                el->right = rightRotate(el->right);
            }
            return leftRotate(el);
        }

        if (balanceFactor(el) == 2) {       // do right rotate
            if (balanceFactor(el->left) < 0) {      // do BIG right rotate
                el->left = leftRotate(el->left);
            }
            return rightRotate(el);
        }

        return el;
    }

    Book* insert(Book* el, Book& aBook) {
        if (el == nullptr) {
            return new Book(aBook);
        }
        if (aBook.label < el->label) {
            el->left = insert(el->left, aBook);
        }
        else {
            el->right = insert(el->right, aBook);
        }
        return balance(el);
    }

    void inorderTraversal(Book* el, vector <Book>& array) {
        if (el != nullptr) {
            inorderTraversal(el->left, array);
            array.push_back(*el);
            inorderTraversal(el->right, array);
        }
    }

    //Removing an element (Eto pizdec)
    Book* findMin(Book* el) {
        return (el->left != nullptr ? findMin(el->left) : el);
    }

    Book* removeMin(Book* el) {
        if (el->left == nullptr) {
            return el->right;
        }
        el->left = removeMin(el->left);
        return balance(el);
    }

    Book* remove(Book* el, int label) {
        if (label < el->label) {
            el->left = remove(el->left, label);
        }
        else if (label > el->label) {
            el->right = remove(el->right, label);
        }
        else {
            Book* left = el->left;
            Book* right = el->right;
            delete el;
            if (right == nullptr) {
                return left;
            }
            Book* minEl = findMin(right);
            minEl->right = removeMin(right);
            minEl->left = left;
            return balance(minEl);
        }
        return balance(el);
    }

    static bool compareByYear(const Book &a, const Book &b) {
        return a.year < b.year;
    }
};

int main() {
    AVL_Tree library;

    while (true) {
        int request;
        cin >> request;

        if (request == 0) { //exit loop
            break;
        }
        else if (request == 1) { //insert element
            int label; string author; string title; int year; int copyCount;
            cin >> label >> author >> title >> year >> copyCount;
            library.insert(label, author, title, year, copyCount);
        }
        else if (request == 2) { //remove element
            int label;
            cin >> label;
            library.remove(label);
        }
        else if (request == 3) { //book list
            library.showBookList();
        }
        else {
            continue;
        }
    }

    return 0;
}
