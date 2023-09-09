#pragma once
#include "../Header.h"

namespace bsttodll {
template <class T>
class BST {
   public:
    class Node {
       public:
        T val;
        Node *left, *right;
        Node(T val) : val(val), left(nullptr), right(nullptr) {}
    };
    Node* root = nullptr;

   public:
    void insert(T val) {
        root = insert(root, val);
    }
    string to_string() {
        stringstream ss;
        inorder(root, ss);
        return ss.str();
    }
    Node* getRoot() {
        return root;
    }

   private:
    Node* insert(Node* cur, T val) {
        if (!cur) return new Node(val);
        if (val < cur->val)
            cur->left = insert(cur->left, val);
        else
            cur->right = insert(cur->right, val);
        return cur;
    }
    void inorder(Node* cur, stringstream& ss) {
        if (cur) {
            inorder(cur->left, ss);
            ss << cur->val << " ";
            inorder(cur->right, ss);
        }
    }
};
class BSTToDll {
   public:
    static void test() {
        BSTToDll obj;
        BST<int> bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(20);
        bst.insert(30);
        cout << bst.to_string() << endl;

        BST<int>::Node* head = nullptr;
        obj.covertBSTToDLL(bst.getRoot(), head);
        while (head) {
            cout << head->val << " ";
            head = head->right;
        }
    }

   private:
    void covertBSTToDLL(BST<int>::Node* root, BST<int>::Node*& head) {
        if (!root) return;
        static BST<int>::Node* prev = nullptr;
        covertBSTToDLL(root->left, head);
        if (!prev)
            head = root;
        else
            prev->right = root;
        root->left = prev;
        prev = root;
        covertBSTToDLL(root->right, head);
    }

   private:
    Node* bToDLL(Node* root) {
        Node* next = nullptr;
        return bToDLL(root, next);
    }

    Node* bToDLL(Node* root, Node*& next) {
        if (!root) return root;

        bToDLL(root->right, next);

        root->right = next;
        if (next) next->left = root;
        next = root;

        bToDLL(root->left, next);

        return next;
    }
};
}  // namespace bsttodll