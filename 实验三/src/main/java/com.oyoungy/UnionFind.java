package com.oyoungy;

public interface UnionFind {
    public boolean makeSet(int ele);
    public int findSet(int ele);
    public boolean unionSet(int ele1, int ele2);
}
