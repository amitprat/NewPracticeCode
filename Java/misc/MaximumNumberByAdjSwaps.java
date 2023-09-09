package programs.misc;

/*
Given a array int a[]={2,5,1,9,3,7,2,8,9,3} and the no. of swap operations.We are allowed to do swap operations.
swap constraint: exchange only adjacent element.
Find the max number that can be formed using swap operations.


public static  int[] maximize(int arr[],int swapsAllowed);
 */

/*
https://www.careercup.com/question?id=5638261762424832

8
of 8 vote
By saying maximize, I assume elements in array are projected as digits in a single number. Now we want to maximize that number by shuffling.

1. Starting from first digit, check next n digits. Record the position of biggest one. Here n=swapsAllowed.
2. Bubble the biggest digit to the top. Reduce n by no. of swaps. Reset n to -> n=n-(distance of biggest digit from top)
3. Move to second digit, repeat #1 with new value of n.
4. Repeat 3 until n or no. of digits are exhausted.

Time needed - O(n2). Space O(1)

If extra memory is not a problem, we can parse all digits and keep them in a decreasing order along with their indeces, in a sorted map. In that case, time will come down to O(nlogn) -[O(nlogn) for sorting, and O(n) for processing], and space will go up by O(n).
 */
public class MaximumNumberByAdjSwaps {
}
