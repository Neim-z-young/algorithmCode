package com.oyoungy;


/**
 * 图的边数据类型
 */
public class Edge implements Comparable<Edge>{

    private int u;
    private int v;
    private int weight;

    Edge(int u, int v, int weight)
    {
        this.u = u;
        this.v = v;
        this.weight = weight;
    }

    public int getU() {
        return u;
    }

    public int getV() {
        return v;
    }

    public int getWeight() {
        return weight;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Edge)
        {
            Edge temp = (Edge)obj;
            if(temp.getU()==u && temp.getV()==v && temp.getWeight()==weight) return true;
            else if(temp.getU()==v && temp.getV()==u && temp.getWeight()==weight) return true;
        }
        return false;
    }

    @Override
    public int compareTo(Edge o) {
        if(this.weight < o.weight) return -1;
        else if(this.weight > o.weight) return 1;
        return 0;
    }
}