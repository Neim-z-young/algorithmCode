package com.oyoungy;

import java.io.IOException;
import java.util.PriorityQueue;

/**
 * 使用kruskal算法求最小生成树（MST）
 */
public class KruskalMST extends PrimeMST{
    public void kruskalMST()
    {
        if(graph.length<=0) return;

        UnionFindSet set = new UnionFindSet(graph.length);
        PriorityQueue<Edge> queue = new PriorityQueue<>();
        //按边的权值排序
        for(int i=0; i<graph.length; i++)
        {
            for(int j=0 ;j<graph.length; j++)
            {
                if(graph[i][j]>0)
                {
                    queue.add(new Edge(i, j, graph[i][j]));
                }
            }
        }
        while (!queue.isEmpty())
        {
            Edge edge = queue.poll();
            int u = edge.getU(), v = edge.getV();
            if(set.findSet(u)!=set.findSet(v))
            {
                set.unionSet(u, v);
                length+=edge.getWeight();
                edges.add(edge);
            }
        }
    }
    public static void main(String[] args) throws IOException {
        String string = "src/main/resources/MST.txt";
        KruskalMST mst = new KruskalMST();
        mst.loadGraph(string);
        mst.kruskalMST();
        System.out.println(mst.getLength());
    }
}
