#include "../Header.h"

/*
You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists.

For example,
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]

The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.
*/

/*
There are k lists of sorted integers. Make a min heap of size k containing 1 element from each list. Keep track of min and max element and calculate the range.
In min heap, minimum element is at top. Delete the minimum element and another element instead of that from the same list to which minimum element belong. Repeat the process till any one of the k list gets empty.
Keep track of minimum range.

For eg.
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]

Min heap of size 3. containing 1 element of each list
Heap [0, 4, 5]
Range - 6

Remove 0 and add 9
Heap [4, 9, 5]
Range - 6

Remove 4 and add 10
Heap [5, 9, 10]
Range - 6

and so on....

Finally you will yield the result.
*/