#pragma once
#include "Header.h"

class LinkNodesAtSameLevelInBinaryTreeToDLL
{
private:
    template <class T>
    class Node {
    public:
        T val;
        Node* left, * right;
        Node* prev, * next;
        Node() {}
        Node(T val) :val(val), left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {}
        string to_string() {
            return std::to_string(val);
        }
    };
public:
    static void test() {
        LinkNodesAtSameLevelInBinaryTreeToDLL obj;

        Node<int>* root = new Node<int>(1);
        root->left = new Node<int>(2);
        root->right = new Node<int>(3);
        root->left->left = new Node<int>(4);
        root->left->right = new Node<int>(5);
        root->right->left = new Node<int>(6);
        root->right->right = new Node<int>(7);
        root->left->left->left = new Node<int>(8);
        root->left->left->right = new Node<int>(9);
        root->left->right->left = new Node<int>(10);
        root->left->right->right = new Node<int>(11);
        root->right->left->left = new Node<int>(12);
        root->right->left->right = new Node<int>(13);
        root->right->right->left = new Node<int>(14);
        root->right->right->left = new Node<int>(15);

        Node<int>* node = obj.binaryTreeToDll2(root);
        while (node) {
            cout << node->val << " ";
            node = node->next;
        }
        cout << endl;
    }
private:
    Node<int>* binaryTreeToDll1(Node<int>* root) {
        Node<int>* prev = nullptr;
        queue<Node<int>*> q;
        q.push(root);

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            cur->prev = prev;
            if (prev) prev->next = cur;
            prev = cur;

            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        return root;
    }

    Node<int>* binaryTreeToDll2(Node<int>* root) {
        Node<int>* last = root;
        Node<int>* cur = root;

        while (cur) {
            if (cur->left) {
                last->next = cur->left;
                cur->left->prev = last;
                last = cur->left;
            }
            if (cur->right) {
                last->next = cur->right;
                cur->right->prev = last;
                last = cur->right;
            }

            cur = cur->next;
        }

        return root;
    }
};