import java.util.*;

class freckles {
    static class mstEdge implements Comparable<mstEdge> {
        double distance;
        int src;
        int dest;

        public mstEdge(double distance, int src, int dest) {
            this.distance = distance;
            this.src = src;
            this.dest = dest;
        }

        @Override
        public int compareTo(mstEdge other) {
            return Double.compare(this.distance, other.distance);
        }
    }

    static List<mstEdge> kruskal(List<Pair<Double, Double>> points) {
        PriorityQueue<mstEdge> q = new PriorityQueue<>();
        int vertices = points.size();
        List<Set<Integer>> vertSets = new ArrayList<>(vertices);
        Map<Integer, Integer> setLoc = new HashMap<>();
        List<mstEdge> mst = new ArrayList<>();
        mstEdge temp;
        int index1, index2;

        // create a list of sets with one vertex per set
        for (int i = 0; i < vertices; i++) {
            Set<Integer> set = new HashSet<>();
            set.add(i);
            vertSets.add(set);
            setLoc.put(i, i);
        }

        // calculate and push all edges into the queue
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                double distance = Math.sqrt(Math.pow(points.get(j).getKey() - points.get(i).getKey(), 2) +
                        Math.pow(points.get(j).getValue() - points.get(i).getValue(), 2));
                temp = new mstEdge(distance, j, i);
                q.add(temp);
            }
        }

        // starting at the shortest edge distance, if edge is across different sets, combine them
        // also add edge to mst, when mst is complete return it
        while (mst.size() != vertices - 1) {
            temp = q.poll();
            index1 = setLoc.get(temp.src);
            index2 = setLoc.get(temp.dest);
            if (index1 != index2) {
                mst.add(temp);
                Set<Integer> set2 = vertSets.get(index2);
                for (int i : set2) {
                    vertSets.get(index1).add(i);
                    setLoc.put(i, index1);
                }
            }
        }

        return mst;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int cases = scanner.nextInt();
        for (int i = 0; i < cases; i++) {
            List<mstEdge> mst;
            List<Pair<Double, Double>> points = new ArrayList<>();
            double total = 0.0;

            int numPoints = scanner.nextInt();

            for (int j = 0; j < numPoints; j++) {
                double src = scanner.nextDouble();
                double dest = scanner.nextDouble();
                points.add(new Pair<>(src, dest));
            }

            mst = kruskal(points);

            for (mstEdge element : mst) {
                total += element.distance;
            }

            System.out.printf("%.2f%n", total);
        }
    }
}

class Pair<K, V> {
    private K key;
    private V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }
}