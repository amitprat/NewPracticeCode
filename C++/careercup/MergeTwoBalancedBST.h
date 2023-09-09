#include "../header.h"

/*
https://careercup.com/question?id=5261732222074880

how to merge two binary search tree into balanced binary search tree.. Let there be m elements in first tree and n elements in the other tree.
Your merge function should take O(m+n) time with in constant space.

This can be done in 3 steps:
1. covert the BSTs to sorted linked list (this can be done in place with O(m+n) time)
2. Merge this two sorted linked lists to a single list (this can be done in place with O(m+n) time)
3. Convert sorted linked list to balanced BST (this can be done in place with O(m+n) time)
*/
class MergeTwoBalancedBST {
   private:
    Node *mergeBst(Node *root1, Node *root2) {
        LinkedListNode *head1, head2;

        head1 = inorder(root1, head1);
        head2 = inorder(root2, head2);

        LinkedListNode *head = mergeLinkedList(head1, head2);

        Node *root = convertSortedListToBst(head);
    }

    LinkedListNode *inorder(Node *root, LinkedListNode *head) {
        if (!root) return head;

        inorder(root->left, head);
        if (!head)
            head = new Node(root->val);
        else {
            head->next = new Node(root->val);
            head = head->next;
        }
        inorder(root->right, head);
    }

    LinkedListNode *mergeLinkedList(LinkedListNode *head1, LinkedListNode *head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        if (head1->val <= head2->val) {
            head1->next = mergeLinkedList(head1->next, head2);
            return head1;
        } else {
            head2->next = mergeLinkedList(head1, head2->next);
            return head2;
        }
    }

   private:
    Node *convertSortedListToBst(LinkedListNode *head) {
        if (!head) return nullptr;
        auto mid = findMid(head, first, second);
        Node *root = new Node(mid->val);
        root->left = convertSortedListToBst(first);
        root->right = convertSortedListToBst(second);

        return root;
    }

    Node *findMid(LinkedListNode *head, Node *&first, Node *&second) {
        if (!head) return nullptr;
        if (!head->next) return head;

        first = head;
        second = head->next;
        Node *mid;

        while (second && second->next) {
            mid = first;
            first = first->next;
            second = second->next->next;
        }

        mid = mid->next;
        mid->next = nullptr;
        second = first->next;

        return mid;
    }

   private:
    Node *convertSortedListToBstOptimized(LinkedListNode *head) {
        int n = size(head);

        return convertSortedListToBstOptimized(head, n);
    }

    Node *convertSortedListToBstOptimized(LinkedListNode *&head, int n) {
        if (n == 0) return nullptr;

        auto left = convertSortedListToBstOptimized(head, n / 2);

        Node *root = new Node(head->val);
        head = head->next;

        root->left = left;

        root->right = convertSortedListToBstOptimized(head, n - n / 2 - 1);

        return root;
    }
};