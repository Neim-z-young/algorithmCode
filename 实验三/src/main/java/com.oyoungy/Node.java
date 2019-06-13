package com.oyoungy;

/**
 * 分支定界背包问题的树节点类
 */
class Node implements Comparable<Node>, Cloneable
{
    public double w;
    public double v;
    public double bound;
    public int level;
    public int[] selected;

    Node()
    {
        w=0;
        v=0;
        bound=0;
        level=0;
        selected = new int[1];
    }

    Node(double w, double v, double bound, int level, int n)
    {
        this.w = w;
        this.v = v;
        this.bound = bound;
        this.level = level;
        selected = new int[n];
    }

    @Override
    public int compareTo(Node o) {
        if(bound>o.bound) return 1;
        else if (bound<o.bound) return -1;
        return 0;
    }

    public Node clone()
    {
        Node node = new Node(this.w, this.v, this.bound, this.level, this.selected.length);
        node.selected = this.selected.clone();
        return node;
    }
}
