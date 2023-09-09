package programs.arrays;

public class MinimalDistance {
    /*
    public static void test() {
        List<String, List<Integer>> wordPositionMap = new ArrayList<>();
        wordPositionMap.put("job", Arrays.asList(5, 9, 17));
        wordPositionMap.put("in", Arrays.asList(4, 13, 18));
        wordPositionMap.put("google", Arrays.asList(8, 19, 21));

        System.out.println(getMinimalDistance(wordPositionMap));
    }

    private static boolean getMinimalDistance(Map<String, List<Integer>> wordPositionMap) {
        PriorityQueue<Triplet<Integer,Integer,Integer>> pq = new PriorityQueue<>((a, b) -> a.first - b.first);

        int[] elems = new int[wordPositionMap.size()];
        int index = 0;
        for(var entry : wordPositionMap.entrySet()) {
            if(!entry.getValue().isEmpty()) {
                pq.add(new Triplet<>(entry.getValue().get(0), index,0));
                elems[index] = entry.getValue().get(0);
            }
        }
        int minDist = Integer.MAX_VALUE;
        while(!pq.isEmpty()) {
            minDist = Math.min(minDist,distance(elems));
            var front = pq.poll();
            if(front.third < wordPositionMap.get(fr))
            elems
            minDist = Math.min(minDist,)
        }
    }
    */
}
