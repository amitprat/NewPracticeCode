package programs.arrays;

import java.util.ArrayList;
import java.util.List;

public class FindDisjointContguousSubarrayWithMaxAbsDiff {
    public static void test() {
        FindDisjointContguousSubarrayWithMaxAbsDiff obj = new FindDisjointContguousSubarrayWithMaxAbsDiff();
        int[] arr = {2, -1, -2, 1, -4, 2, 8};

        var res = obj.findMaxDiff(arr);
        System.out.println(res);
    }

    private int findMaxDiff(int[] arr) {
        List<Integer> minArr = new ArrayList<>();
        int i = 0, j = 0;
        int sum = 0;
        while (j < arr.length) {
            sum += arr[j++];
            while (i < j && arr[i] >= 0) sum -= arr[i++];
            if (sum >= 0) {
                i = j;
                sum = 0;
            }
            minArr.add(sum);
        }

        i = arr.length-1;
        j = arr.length-1;
        sum = 0;
        List<Integer> maxArr = new ArrayList<>();
        while (j >= 0) {
            sum += arr[j--];
            while (i > j && arr[i] < 0) sum -= arr[i--];
            if (sum <= 0) {
                i = j;
                sum = 0;
            }
            maxArr.add(sum);
        }

        int mxDiff = Integer.MIN_VALUE;
        for (i = 0; i < arr.length; i++) {
            mxDiff = Math.max(mxDiff, maxArr.get(i) - minArr.get(i));
        }

        return mxDiff;
    }
}
