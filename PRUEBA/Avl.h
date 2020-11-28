#ifndef __AVL_H__
#define __AVL_H__

#include <functional>
#include <QTextStream>
#include <QListWidget>
#include<queue>
using std::function;
using std::max;
using namespace std;


template <typename T, typename R = T, T NONE = nullptr>
class Avl {
    struct Node {
        T element; Node* left; Node* right; int height;
        Node(T element) : element(element), left(nullptr), right(nullptr), height(0) {}
    };

    typedef function<R(T)>      lbdKey;
    typedef function<void(T)>   lbdProc;

    Node* root;
    int     len;
    lbdKey  key;

public:
    Avl(lbdKey key = [](T a) {return a; }) : key(key), root(nullptr), len(0) {}
    ~Avl() { destroy(root); }

    int     height() { return height(root); }
    int     size() { return len; }
    void    clear() { destroy(root); len = 0; }

    void    add(T elem,function<bool(T, T)>criterio) { add(root, elem,criterio); }
    void    inOrder_L(lbdProc proc) { inOrder_L(root, proc); }
    void inOrder(QListWidget* lista){inOrder(lista,this->root);}
    void inOrder_u(QListWidget *lista ){inOrder_u(lista,this->root);}

    T find(R attr) {
        Node*& node = find(root, attr);
        return node == nullptr ? NONE : node->element;
    }







private:
    void destroy(Node*& node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }
    int height(Node* node) {
        return node == nullptr ? -1 : node->height;
    }
    void add(Node*& node, T elem, function<bool(T, T)>criterio) {
            if (node == nullptr) {
                node = new Node(elem);
                ++len;
            } else {
                if (criterio(node->element,elem)) {
                    add(node->left, elem,criterio);
                } else {
                    add(node->right, elem,criterio);
                }
                balance(node); /* :O */
            }
        }
    Node*& greater(Node*& node) {
        return node->right != nullptr ? node : greater(node->right);
    }
    void inOrder_L(Node* node, lbdProc proc) {
        if (node != nullptr) {
         inOrder_L(node->left, proc);
         proc(node->element);
         inOrder_L(node->right, proc);
        }
    }

    void inOrder(QListWidget *lista ,Node* node) {

       if(node!=nullptr ) {

         inOrder(lista,node->left);

         lista->addItem(node->element->toString());

         inOrder(lista,node->right);
       }
        }
    void inOrder_u(QListWidget *lista ,Node* node) {

       if(node!=nullptr ) {

         inOrder(lista,node->left);

         lista->addItem(node->element->toString_u());

         inOrder(lista,node->right);
       }
        }

    Node*& find(Node*& node, R attr) {
        if (node == nullptr) {
            return dummynull;
        }
        else if (attr == key(node->element)) {
            return node;

        }
        else if (attr < key(node->element)) {
            return find(node->left, attr);
        }
        else {
            return find(node->right, attr);
        }
    }





    void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }
    void rotateLeft(Node*& node) { // X = node, Y = node->right
        Node* aux = node->right;
        node->right = aux->left;
        updateHeight(node);
        aux->left = node;
        updateHeight(aux);
        node = aux;
    }
    void rotateRight(Node*& node) { // Y = node, X = node->left
        Node* aux = node->left;
        node->left = aux->right;
        updateHeight(node);
        aux->right = node;
        updateHeight(aux);
        node = aux;
    }
    void balance(Node*& node) {
        int hl = height(node->left);
        int hr = height(node->right);

        if (hr - hl < -1) {
            hl = height(node->left->left);
            hr = height(node->left->right);
            if (hr > hl) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
        else if (hr - hl > 1) {
            hl = height(node->right->left);
            hr = height(node->right->right);
            if (hl > hr) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
        else {
            updateHeight(node);
        }
    }

    Node* dummynull = nullptr;
};

#endif
