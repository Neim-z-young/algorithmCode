package com.oyoungy;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

/**
 * 使用prime算法求最小生成树（MST）
 */
public class PrimeMST {

    public int[][] graph;
    public int length = 0;
    public ArrayList<Edge> edges;

    PrimeMST()
    {
        length = 0;
        edges = new ArrayList<>();
    }

    public int getLength() {
        return length;
    }

    public void loadGraph(String filename) throws IOException {
        int n=0;
        Path path = Paths.get(filename);
        List<String> lines = Files.readAllLines(path);
        n = lines.size();
        graph = new int[n][n];
        int i=0;
        for(String line:lines)
        {
            String[] strings = line.split("\\s+");
            for(int j=0; j<strings.length; j++)
                graph[i][j] = Integer.parseInt(strings[j]);
            i++;
        }
    }

    public void primeMST()
    {
        if(graph.length<=0) return;

        UnionFindSet set = new UnionFindSet(graph.length);
        PriorityQueue<Edge> queue = new PriorityQueue<>();
        //用第一个节点初始化树集合
        for(int i=0; i<graph.length; i++)
        {
            if(graph[0][i]>0)
            {
                queue.add(new Edge(0, i, graph[0][i]));
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
                for(int i=0; i<graph.length; i++)
                {
                    if(graph[v][i]>0)
                    {
                        queue.add(new Edge(v, i, graph[v][i]));
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        String string = "src/main/resources/MST.txt";
        PrimeMST mst = new PrimeMST();
        mst.loadGraph(string);
        mst.primeMST();
        System.out.println(mst.getLength());
    }
}
