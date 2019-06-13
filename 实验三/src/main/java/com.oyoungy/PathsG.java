package com.oyoungy;

import java.util.ArrayList;
import java.util.zip.Adler32;


/**
 * dijkstra算法的路径类
 */
public class PathsG implements Comparable<PathsG>, Cloneable{
    private int start;
    private int end;
    private int distance;
    ArrayList<Edge> edges;

    PathsG(int start, int end, int distance)
    {
        this.start = start;
        this.end = end;
        this.distance = distance;
        edges = new ArrayList<>();
    }

    public void setStart(int start) {
        this.start = start;
    }

    public void setEnd(int end) {
        this.end = end;
    }

    public void setDistance(int distance) {
        this.distance = distance;
    }

    public int getStart() {
        return start;
    }

    public int getEnd() {
        return end;
    }

    public int getDistance() {
        return distance;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public void addEdge(Edge edge)
    {
        edges.add(edge);
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof PathsG)
        {
            PathsG pathsG = (PathsG)obj;
            if(start == pathsG.getStart() && end == pathsG.getEnd() && distance == pathsG.getDistance())
                return true;
        }
        return false;
    }

    @Override
    public int compareTo(PathsG o) {
        if(distance>o.getDistance()) return 1;
        else if (distance<o.getDistance()) return -1;
        return 0;
    }

    public PathsG clone() throws CloneNotSupportedException {
        PathsG temp = (PathsG)super.clone();
        temp.edges = (ArrayList<Edge>) edges.clone();
        return temp;
    }
}
