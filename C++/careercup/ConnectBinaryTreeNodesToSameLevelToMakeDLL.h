#include "../header.h"

class ConnectBinaryTreeNodesToSameLevelToMakeDLL {
    using Node = Tree::Node;

   public:
    static void test() {
        Node *root = new Node(10);
        root->left = new Node(8);
        root->right = new Node(2);
        root->left->left = new Node(3);
        root->right->right = new Node(4);

        ConnectBinaryTreeNodesToSameLevelToMakeDLL obj;
        obj.printLevelOrder(root, cout);

        // auto head = obj.connectNodesUsingLevelOrder(root);
        // auto head = obj.connectNodesWithoutExtraSpace(root);
        obj.connectNodesUsingRecursionForCompleteBinaryTree(root);

        obj.printDLL(root, cout);
    }

   private:
    void printLevelOrder(Node *root, ostream &out) {
        if (!root)
            return;

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            while (levelSize--) {
                auto front = q.front();
                q.pop();

                out << front->val << " ";

                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            out << '\n';
        }
        out << '\n';
    }

    Node *connectNodesUsingLevelOrder(Node *root) {
        if (!root)
            return root;

        queue<Node *> q;
        q.push(root);

        Node *head = nullptr;
        Node *prev = nullptr;

        while (!q.empty()) {
            int levelSize = q.size();

            while (levelSize--) {
                auto front = q.front();
                q.pop();

                if (!prev)
                    prev = head = front;
                else {
                    prev->next = front;
                    prev = front;
                }

                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
        }

        return head;
    }

    void printDLL(Node *root, ostream &out) {
        while (root) {
            out << root->val << " ";
            root = root->next;
        }
        out << endl;
    }

   private:
    Node *connectNodesWithoutExtraSpace(Node *root) {
        if (!root)
            return root;

        Node *nextLevelLeftMostNode = root;

        while (nextLevelLeftMostNode) {
            Node *current = nextLevelLeftMostNode;
            Node *currentPrev = nullptr;

            Node *nextLevelPrev = nullptr;
            Node *nextLevelLeftMost = nullptr;

            while (current) {
                // connect nodes at next level
                if (current->left) {
                    if (!nextLevelPrev)
                        nextLevelLeftMost = current->left;
                    else
                        nextLevelPrev->next = current->left;

                    current->left->prev = nextLevelPrev;
                    nextLevelPrev = current->left;
                }
                if (current->right) {
                    if (!nextLevelPrev)
                        nextLevelLeftMost = current->right;
                    else
                        nextLevelPrev->next = current->right;

                    current->right->prev = nextLevelPrev;
                    nextLevelPrev = current->right;
                }

                currentPrev = current;
                current = current->next;
            }

            // connect prevLevel last node to next level left most node.
            if (currentPrev)
                currentPrev->next = nextLevelLeftMost;
            if (nextLevelLeftMost)
                nextLevelLeftMost->prev = currentPrev;

            nextLevelLeftMostNode = nextLevelLeftMost;
        }

        return root;
    }

    Node *findNextNode(Node *curr) {
        while (curr) {
            if (curr->left)
                return curr->left;
            if (curr->right)
                return curr->right;

            curr = curr->next;
        }

        return nullptr;
    }

   private:
    // This only connects nodes at same level
    void connectNodesUsingRecursionForCompleteBinaryTree(Node *root) {
        if (!root)
            return;

        if (root->left) {
            root->left->next = root->right;
            if (root->right)
                root->right->prev = root->left;
        }
        if (root->right) {
            root->right->next = root->next ? root->next->left : nullptr;
            if (root->right->next)
                root->right->next->prev = root->right;
        }

        connectNodesUsingRecursionForCompleteBinaryTree(root->left);
        connectNodesUsingRecursionForCompleteBinaryTree(root->right);
    }
};