package programs.arrays;

import org.jetbrains.annotations.NotNull;

import java.util.Stack;

public class AreaUnderHistogram {
    public static void test() {
        int[] hist = {6, 2, 5, 4, 5, 1, 6};
        var res = areaUnderHist(hist);
        System.out.println("Area under histogram = " + res);

        var trappedWater = trappedRainWater(hist);
        System.out.println("Trapped water = " + trappedWater);

        int[][] matrix = {
                {1, 2, -1, -4, -20},
                {-8, -3, 4, 2, 1},
                {3, 8, 10, 1, 3},
                {-4, -1, 1, 7, -6}
        };

        var largestRect = largestRectangleSum(matrix);
        System.out.println("Largest rectangle = " + largestRect);

        int[][] binaryRectangle = {
                {0, 1, 1, 0},
                {1, 1, 1, 1},
                {1, 1, 1, 1},
                {1, 1, 0, 0},
        };

        var largestRectangle = largestBinaryRectangle(binaryRectangle);
        System.out.println("Largest binary rectangle = " + largestRectangle);
    }

    static int areaUnderHist(int[] hist) {
        Stack<Integer> st = new Stack<>();
        int mxArea = 0;
        int i = 0;
        while (i < hist.length) {
            if (st.empty() || hist[i] >= hist[st.peek()]) {
                st.push(i++);
            } else {
                int height = hist[st.pop()];
                int width = st.empty() ? i : i - st.peek() - 1;
                //System.out.printf("Height = %d, Width = %d\n", height, width);

                mxArea = Math.max(mxArea, height * width);
            }
        }

        while (!st.empty()) {
            int height = hist[st.pop()];
            int width = st.empty() ? i : i - st.peek() - 1;
            //System.out.printf("Height = %d, Width = %d\n", height, width);

            mxArea = Math.max(mxArea, height * width);
        }

        return mxArea;
    }

    static int trappedRainWater(int[] hist) {
        int l = 0, r = hist.length - 1;
        int edgeLevel = 0;
        int water = 0;
        while (l < r) {
            int currentLevel = hist[l] < hist[r] ? hist[l++] : hist[r--];
            edgeLevel = Math.max(edgeLevel, currentLevel);

            water += edgeLevel - currentLevel;
        }

        return water;
    }

    static int largestRectangleSum(int[][] matrix) {
        int mxRectSum = 0;
        for (int top = 0; top < matrix.length; top++) {
            int[] tmp = new int[matrix[top].length];
            for (int bottom = top; bottom < matrix.length; bottom++) {
                for (int j = 0; j < matrix[bottom].length; j++) {
                    tmp[j] += matrix[bottom][j];
                }
                //System.out.println(Arrays.toString(tmp));
                mxRectSum = Math.max(mxRectSum, kadane(tmp));
            }
        }

        return mxRectSum;
    }

    static int kadane(int @NotNull [] arr) {
        int sum = 0;
        int curSum = 0;
        for (int i = 0; i < arr.length; i++) {
            curSum += arr[i];
            sum = Math.max(sum, curSum);
            if (curSum < 0) curSum = 0;
        }

        return sum;
    }

    static int largestBinaryRectangle(int[][] matrix) {
        int mxRectangle = 0;
        for (int r = 0; r < matrix.length; r++) {
            if (r != 0) {
                for (int c = 0; c < matrix[r].length; c++) {
                    if (matrix[r][c] == 1) matrix[r][c] += matrix[r - 1][c];
                }
            }
            mxRectangle = Math.max(mxRectangle, areaUnderHist(matrix[r]));
        }

        return mxRectangle;
    }
}
