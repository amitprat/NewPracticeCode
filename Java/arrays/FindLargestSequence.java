package programs.arrays;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class FindLargestSequence {
    public static void test() {
        FindLargestSequence obj = new FindLargestSequence();
        int[] arr = {1, 6, 10, 4, 7, 9, 5, 9, 11,13,12};

        int[] res = obj.findLargest(arr);
        System.out.println(Arrays.toString(res));
    }

    private int[] findLargest(int[] arr) {
        Map<Integer, Integer> map = new HashMap<>();
        int last = 0, first = 0;
        for (int i = 0; i < arr.length; i++) {
            int beg = arr[i], end = arr[i];
            if (map.containsKey(beg - 1)) beg = map.get(beg - 1);
            if (map.containsKey(end + 1)) end = map.get(end + 1);
            map.put(beg, end);
            map.put(end, beg);
            if (end - beg + 1 > last - first) {
                last = end;
                first = beg;
            }
        }
        int[] res = new int[last - first + 1];
        for (int i = first; i <= last; i++) res[i - first] = i;

        return res;
    }
}
