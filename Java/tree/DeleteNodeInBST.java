package programs.tree;

import programs.types.Triplet;

public class DeleteNodeInBST {
    public static void test() {
        DeleteNodeInBST obj = new DeleteNodeInBST();
        Node<Integer> root = new Node(5);
        root.left = new Node(3);
        root.right = new Node(8);
        root.left.left = new Node(2);
        root.left.left.left = new Node(1);
        root.left.right = new Node(4);
        root.right.right = new Node(9);
        root.right.left = new Node(7);

        System.out.println("Is BST = " + obj.isBST(root));

        obj.inorder(root);

        root = obj.deleteNode(root, root.left.left.left);

        obj.inorder(root);

        root = obj.deleteNode(root, root);

        obj.inorder(root);

        PredSuc preSuc = obj.new PredSuc();
        int val = 7;
        obj.findPredSuc(root, val, preSuc);
        System.out.println("Result for " + val + " = " + preSuc);

        val = 8;
        preSuc = obj.new PredSuc();
        obj.findPredSuc(root, val, preSuc);
        System.out.println("Result for " + val + " = " + preSuc);

        val = 9;
        preSuc = obj.new PredSuc();
        obj.findPredSuc(root, val, preSuc);
        System.out.println("Result for " + val + " = " + preSuc);

        val = 10;
        preSuc = obj.new PredSuc();
        obj.findPredSuc(root, val, preSuc);
        System.out.println("Result for " + val + " = " + preSuc);

        System.out.println("LCA = " + obj.lca(root, root.left, root.right));
        System.out.println("LCA = " + obj.lca1(root, root.left, root.right));

        System.out.println("LCA = " + obj.lca(root, root.left, root.left.right));
        System.out.println("LCA = " + obj.lca1(root, root.left, root.left.right));

        System.out.println("LCA = " + obj.lca(root, root.left.right, root.right.right));
        System.out.println("LCA = " + obj.lca1(root, root.left.right, root.right.right));

        System.out.println("LCA = " + obj.lca(root, root.right.right, new Node(10)));
        System.out.println("LCA = " + obj.lca1(root, root.right.right, new Node(10)));

        PredSuc res = obj.new PredSuc();
        obj.successor(root, 8, res);
        System.out.println("Successor = " + res);

        res = obj.new PredSuc();
        obj.successor(root, 9, res);
        System.out.println("Successor = " + res);
    }

    class PredSuc {
        Node<Integer> pre = null;
        Node<Integer> suc = null;

        @Override
        public String toString() {
            return "{Predecessor=" + val(pre) + ",Successor=" + val(suc) + "}";
        }

        int val(Node<Integer> cur) {
            return cur == null ? -1 : cur.val;
        }
    }

    void findPredSuc(Node<Integer> cur, int val, PredSuc res) {
        if (cur == null) return;
        if (val < cur.val) {
            res.suc = cur;
            findPredSuc(cur.left, val, res);
        } else if (val > cur.val) {
            res.pre = cur;
            findPredSuc(cur.right, val, res);
        } else {
            var tmp = cur.left;
            while (tmp != null && tmp.right != null) tmp = tmp.right;
            if (tmp != null) res.pre = tmp;

            tmp = cur.right;
            while (tmp != null && tmp.left != null) tmp = tmp.left;
            if (tmp != null) res.suc = tmp;
        }
    }

    void inorder(Node<Integer> cur) {
        System.out.println("Inorder : ");
        inorderInternal(cur);
        System.out.println();
    }

    void inorderInternal(Node<Integer> cur) {
        if (cur != null) {
            inorderInternal(cur.left);
            System.out.print(cur.val + " ");
            inorderInternal(cur.right);
        }
    }

    Node deleteNode(Node<Integer> cur, Node<Integer> target) {
        if (cur == null) return cur;
        if (target.val < cur.val) cur.left = deleteNode(cur.left, target);
        else if (target.val > cur.val) cur.right = deleteNode(cur.right, target);
        else {
            if (cur.left == null || cur.right == null) {
                return cur.left != null ? cur.left : cur.right;
            }
            var suc = successor(cur.right);
            cur.val = suc.val;
            cur.right = deleteNode(cur.right, suc);
        }
        return cur;
    }

    Node<Integer> successor(Node<Integer> cur) {
        while (cur.left != null) cur = cur.left;
        return cur;
    }

    boolean isBST(Node cur) {
        return isBST(cur, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    boolean isBST(Node<Integer> cur, int mn, int mx) {
        if (cur == null) return true;
        if (cur.val < mn || cur.val > mx) return false;

        return isBST(cur.left, mn, cur.val) || isBST(cur.right, cur.val, mx);
    }

    Node<Integer> lca(Node<Integer> cur, Node<Integer> node1, Node<Integer> node2) {
        if (cur == null) return null;
        if (node1.val < cur.val && node2.val < cur.val) return lca(cur.left, node1, node2);
        else if (node1.val > cur.val && node2.val > cur.val) return lca(cur.right, node1, node2);
        else {
            return cur;
        }
    }

    Triplet<Boolean, Boolean, Node<Integer>> lca1(Node<Integer> cur, Node<Integer> node1, Node<Integer> node2) {
        if (cur == null) return new Triplet<>(false, false, null);

        var res = new Triplet<Boolean, Boolean, Node<Integer>>(false, false, null);
        if (cur == node1) res.first = true;
        if (cur == node2) res.second = true;

        var left = lca1(cur.left, node1, node2);
        if (left.third != null) return left;
        var right = lca1(cur.right, node1, node2);
        if (right.third != null) return right;

        if (left.first || right.first) res.first = true;
        if (left.second || right.second) res.second = true;
        if (res.first && res.second) res.third = cur;
        return res;
    }

    void successor(Node<Integer> cur, int val, PredSuc res) {
        if (cur == null) return;
        if (val < cur.val) {
            res.suc = cur;
            successor(cur.left, val, res);
        } else if (val > cur.val) {
            successor(cur.right, val, res);
        } else {
            if (cur.right != null) {
                var tmp = cur.right;
                while (tmp.left != null) tmp = tmp.left;
                res.suc = tmp;
            }
        }
    }
}
