package com.oyoungy;

import javax.print.DocPrintJob;
import java.io.IOException;
import java.util.ArrayList;
import java.util.PriorityQueue;

/**
 * 采用dijkstra算法求定起点到其余点的最短距离，复用了primeMST类的部分功能
 */
public class Dijkstra extends PrimeMST {

    private int[] distance;
    private ArrayList<PathsG> pathsGS;

    Dijkstra() {
        distance = new int[1];
        pathsGS = new ArrayList<>();
    }

    public int[] getDistance() {
        return distance;
    }

    public void dijkstra(int source) throws CloneNotSupportedException {
        if (graph.length <= 0 || source >= graph.length) return;

        UnionFindSet set = new UnionFindSet(graph.length);
        PriorityQueue<PathsG> queue = new PriorityQueue<>();
        distance = new int[graph.length];
        for (int i = 0; i < distance.length; i++) {
            distance[i] = Integer.MAX_VALUE / 2;
        }
        distance[source] = 0;
        for (int i = 0; i < graph.length; i++) {
            queue.add(new PathsG(source, i, distance[i]));
        }
        int start, end;
        //从源节点的邻居节点开始查找
        PathsG p = queue.poll();
        start = p.getStart();
        end = p.getEnd();
        set.unionSet(start, end);
        pathsGS.add(p);
        for (int i = 0; i < graph.length; i++) {
            if (graph[end][i] > 0) {
                if (distance[i] > distance[end] + graph[end][i]) {
                    distance[i] = distance[end] + graph[end][i];
                    PathsG pa = p.clone();
                    pa.setEnd(i);
                    pa.setDistance(distance[i]);
                    pa.addEdge(new Edge(end, i, graph[end][i]));
                    queue.add(pa);
                }
            }
        }


        while (!queue.isEmpty()) {
            PathsG paths = queue.poll();
            start = paths.getStart();
            end = paths.getEnd();
            if (set.findSet(start) != set.findSet(end)) {
                set.unionSet(start, end);
                pathsGS.add(paths);
                for (int i = 0; i < graph.length; i++) {
                    if (graph[end][i] > 0) {
                        if (distance[i] > distance[end] + graph[end][i]) {
                            distance[i] = distance[end] + graph[end][i];
                            PathsG pa = paths.clone();
                            pa.setEnd(i);
                            pa.setDistance(distance[i]);
                            pa.addEdge(new Edge(end, i, graph[end][i]));
                            queue.add(pa);
                        }
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        String string = "src/main/resources/MST.txt";
        Dijkstra sssp = new Dijkstra();
        sssp.loadGraph(string);
        try {
            sssp.dijkstra(0);
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        System.out.println("OK");
    }
}
