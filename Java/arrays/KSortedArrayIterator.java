package programs.arrays;

import java.util.*;

public class KSortedArrayIterator implements Iterable {
    private final List<List<Integer>> arrays;

    public KSortedArrayIterator(List<List<Integer>> arrays) {
        this.arrays = arrays;
    }

    public static void test() {
        List<List<Integer>> arrays = new ArrayList<>();
        arrays.add(Arrays.asList(1, 5, 7));
        arrays.add(Arrays.asList(2, 3, 10));
        arrays.add(Arrays.asList(4, 6, 9));
        KSortedArrayIterator obj = new KSortedArrayIterator(arrays);
        for (var item : obj) {
            System.out.print(item + " ");
        }
        System.out.println();
    }

    @Override
    public Iterator iterator() {
        return new PriorityQueueIterator(arrays);
    }

    class SortedArrayIterator implements Iterator<Integer> {
        private final List<List<Integer>> arrays;
        private final List<Position> pointers;
        private int pos = -1;

        SortedArrayIterator(List<List<Integer>> arrays) {
            this.arrays = arrays;
            this.pointers = new ArrayList<>();

            init();
        }

        @Override
        public boolean hasNext() {
            pos = getNextSmallest();
            return pos != -1;
        }

        @Override
        public Integer next() {
            return moveNext();
        }

        private void init() {
            for (int i = 0; i < arrays.size(); i++) {
                pointers.add(new Position(i, 0));
            }
        }

        private int getNextSmallest() {
            for (int i = 0; i < pointers.size(); i++) {
                if (pos == -1 && arrays.get(i).size() > 0) pos = i;
                else if (less(i, pos)) pos = i;
            }
            if (!moreElements()) reset();
            return pos;
        }

        private boolean moreElements() {
            return pointers.get(pos).arrIndex < arrays.get(pointers.get(pos).arrNumber).size();
        }

        private void reset() {
            pos = -1;
        }

        private boolean less(int ptrIndex, int mnPos) {
            var p = pointers.get(ptrIndex);
            return p.arrIndex < arrays.get(p.arrNumber).size() &&
                    arrays.get(p.arrNumber).get(p.arrIndex) < getValue(mnPos);
        }

        private int getValue(int index) {
            var mnPtr = pointers.get(index);
            var mnItem = (mnPtr.arrIndex < arrays.get(mnPtr.arrNumber).size()) ?
                    arrays.get(mnPtr.arrNumber).get(mnPtr.arrIndex) :
                    Integer.MAX_VALUE;
            return mnItem;
        }

        private Integer moveNext() {
            var p = pointers.get(pos);
            var ret = arrays.get(p.arrNumber).get(p.arrIndex);
            p.arrIndex++;
            return ret;
        }

        class Position {
            int arrNumber = -1;
            int arrIndex = -1;

            Position(int num, int idx) {
                this.arrNumber = num;
                this.arrIndex = idx;
            }
        }
    }

    class PriorityQueueIterator implements Iterator<Integer> {
        private final PriorityQueue<Integer> pq;

        PriorityQueueIterator(List<List<Integer>> arrays) {
            pq = new PriorityQueue<>();
            for (var arr : arrays) {
                for (var item : arr) {
                    pq.add(item);
                }
            }
        }

        @Override
        public boolean hasNext() {
            return !pq.isEmpty();
        }

        @Override
        public Integer next() {
            return pq.poll();
        }
    }
}
