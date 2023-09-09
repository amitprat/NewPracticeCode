#include "../header.h"

class AddTwoLinkedLists {
    struct Node {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        Node *root1 = new Node(9);
        root1->next = new Node(1);
        root1->next->next = new Node(2);
        root1->next->next->next = new Node(3);
        root1->next->next->next->next = new Node(8);
        root1->next->next->next->next->next = new Node(9);

        Node *root2 = new Node(9);
        root2->next = new Node(8);
        root2->next->next = new Node(1);
        root2->next->next->next = new Node(8);
        root2->next->next->next->next = new Node(7);

        AddTwoLinkedLists obj;
        Node *root = obj.addLists(root1, root2);
        cout << "First list: " << root1 << endl;
        cout << "Second list: " << root2 << endl;
        cout << "Sum list: " << root << endl;
    }

    Node *addLists(Node *root1, Node *root2) {
        int l1 = length(root1);
        int l2 = length(root2);

        if (l1 < l2)
            root1 = padList(root1, l2 - l1);
        else if (l2 < l1)
            root2 = padList(root2, l1 - l2);

        int carry = 0;
        Node *root = addListsInternal(root1, root2, carry);
        if (carry) {
            Node *next = root;
            root = new Node(carry);
            root->next = next;
        }

        return root;
    }

    Node *addListsInternal(Node *root1, Node *root2, int &carry) {
        if (!root1 && !root2)
            return nullptr;

        Node *next = addListsInternal(root1->next, root2->next, carry);

        int sum = root1->val + root2->val + carry;
        Node *root = new Node(sum % 10);
        carry = sum / 10;

        root->next = next;

        return root;
    }

    int length(Node *root) {
        int l = 0;
        while (root) {
            l++;
            root = root->next;
        }

        return l;
    }

    Node *padList(Node *root, int diff) {
        while (diff) {
            Node *next = root;
            root = new Node(0);
            root->next = next;
            diff--;
        }

        return root;
    }

    friend std::ostream &operator<<(std::ostream &out, Node *root) {
        while (root) {
            out << root->val << " ";
            root = root->next;
        }

        return out;
    }
};