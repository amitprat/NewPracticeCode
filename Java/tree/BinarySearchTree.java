package programs.tree;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Stack;

public class BinarySearchTree<T extends Comparable<T>> implements Iterable<T> {
    private Node<T> root = null;

    public static void test() throws Exception {
        BinarySearchTree<Integer> obj = new BinarySearchTree<Integer>();
        obj.insert(1);
        obj.insert(5);
        obj.insert(2);
        obj.insert(6);
        obj.insert(3);

        System.out.print("List: ");
        List<Integer> result = obj.inorder();
        for (Integer item : result) {
            System.out.print(item + " ");
        }
        System.out.println();

        obj.delete(1);
        obj.insert(2);
        obj.insert(8);
        obj.insert(100);
        obj.insert(-100);

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();

        obj.delete(100);
        try {
            obj.delete(200);
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();

        try {
            System.out.println("programs.tree.Node 1 found? " + obj.search(1));
        } catch (Exception e) {
            System.out.println(e);
        }
        System.out.println("programs.tree.Node 1 found? " + obj.search(8));

        System.out.print("List: ");
        for (Integer item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();
    }

    public Node<T> getNode() {
        return root;
    }

    @Override
    public Iterator<T> iterator() {
        return new BinarySearchTreeIterator<T>(root);
    }

    private boolean searchInternal(Node<T> cur, T val) throws Exception {
        if (cur == null) {
            throw new Exception("programs.tree.Node not found " + val.toString());
        }
        if (cur.val.compareTo(val) == 0) return true;
        if (val.compareTo(cur.val) < 0) return searchInternal(cur.left, val);
        return searchInternal(cur.right, val);
    }

    private Node insertInternal(Node<T> cur, T val) {

        if (cur == null) return new Node(val);
        if (val.compareTo(cur.val) < 0) cur.left = insertInternal(cur.left, val);
        else if (val.compareTo(cur.val) > 0) cur.right = insertInternal(cur.right, val);
        cur.sz++;
        return cur;
    }

    private void inorderInternal(Node cur, List result) {
        if (cur != null) {
            inorderInternal(cur.left, result);
            result.add(cur.val);
            inorderInternal(cur.right, result);
        }
    }

    private Node<T> deleteInternal(Node<T> cur, T val) throws Exception {
        if (cur == null) {
            throw new Exception(("programs.tree.Node not found while deleting " + val.toString()));
        }
        if (cur.val == val) cur = deleteCurrent(cur, val);
        else if (val.compareTo(cur.val) < 0) cur.left = deleteInternal(cur.left, val);
        else cur.right = deleteInternal(cur.right, val);
        cur.sz--;
        return cur;
    }

    private Node<T> deleteCurrent(Node<T> cur, T val) throws Exception {
        if (cur.left == null && cur.right == null) return null;
        if (cur.left == null || cur.right == null) {
            return cur.left != null ? cur.left : cur.right;
        }
        Node<T> successor = cur.right;
        while (successor.left != null) successor = successor.left;
        cur.val = successor.val;

        cur.right = deleteInternal(cur.right, successor.val);
        return cur;
    }

    void insert(T val) {
        if (root == null) root = new Node(val);
        insertInternal(root, val);
    }

    void delete(T val) throws Exception {
        if (root == null) {
            throw new Exception("Deletion Key not found " + val.toString());
        }
        root = deleteInternal(root, val);
    }

    boolean search(T val) throws Exception {
        if (root == null) {
            throw new Exception("Key not found " + val.toString());
        }
        return searchInternal(root, val);
    }

    List<T> inorder() {
        List<T> result = new ArrayList<>();
        inorderInternal(root, result);

        return result;
    }
}

class BinarySearchTreeIterator<T> implements Iterator<T> {
    private final Stack<Node<T>> stack = new Stack<Node<T>>();
    private Node<T> root;

    BinarySearchTreeIterator(Node<T> root) {
        this.root = root;
    }

    @Override
    public boolean hasNext() {
        return !stack.empty() || root != null;
    }

    @Override
    public T next() {
        if (root != null) {
            populateStack();
        }
        root = stack.pop();
        T val = root.val;
        root = root.right;
        return val;
    }

    private void populateStack() {
        while (root != null) {
            stack.push(root);
            root = root.left;
        }
    }
}
