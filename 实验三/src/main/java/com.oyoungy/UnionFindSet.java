package com.oyoungy;

/**
 * 并查集，使用数组实现的简单类型
 */
public class UnionFindSet implements UnionFind{

    private int[] elementSet;
    private int[] rank;

    UnionFindSet(){
        elementSet = new int[1];
        rank = new int[1];
    }

    UnionFindSet(int n){
        elementSet = new int[n];
        rank = new int[n];
        for(int i=0 ;i<n ;i++)
        {
            makeSet(i);
        }
    }

    public boolean makeSet(int ele){
        if(ele<elementSet.length)
        {
            elementSet[ele] = ele;
            rank[ele] = 0;
            return true;
        }
        return false;
    }


    public int findSet(int ele){
        if(ele < elementSet.length)
        {
            if(elementSet[ele]==ele)
            {
                return ele;
            }
            else return findSet(elementSet[ele]);
        }
        return -1;
    }

    public boolean unionSet(int ele1, int ele2){
        if(ele1<elementSet.length && ele2<elementSet.length)
        {
            int par1, par2;
            par1 = findSet(ele1);
            par2 = findSet(ele2);
            if(par1==par2)
            {
                return true;
            }
            else
            {
                if(rank[ele1]>rank[ele2])
                {
                    elementSet[par1] = par2;
                    rank[par1] = rank[par2] + 1;
                }
                else
                {
                    elementSet[par2] = par1;
                    rank[par2] = rank[par1] + 1;
                }
                return true;
            }
        }
        return false;
    }
}
