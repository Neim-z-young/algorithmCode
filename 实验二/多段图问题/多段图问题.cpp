#include<iostream>
#include<vector>
#include<set>
#include<fstream>
using namespace std;

class MultiPartGraph
{
private:
    vector<vector<int>> graph;
    vector<vector<int>> levelSet;
public:
    MultiPartGraph(){}
    MultiPartGraph(vector<vector<int>> graph1)
    {
        graph = graph1;
        levelSet.push_back(vector<int>({0}));

        for(int i=getLevels(); ; i++){
            vector<int> presL = levelSet[i];
            set<int> level;
            vector<int> nexL;
            for(int j=0; j<presL.size(); j++)
            {
                vector<int> son = getSonsByIndex(presL[j]);
                for(int k=0; k<son.size(); k++)
                {
                    level.insert(son[k]);
                }
            }
            for(set<int>::iterator it = level.begin(); it!=level.end(); it++)
            {
                nexL.push_back(*it);
            }
            levelSet.push_back(nexL);
            if(nexL.size()==1) break;
        }
    }
    int getStart()
    {
        return 0;
    }
    int getEnd()
    {
        return graph.size();
    }
    vector<int> getSonsByIndex(int inx)
    {
        vector<int> nextSet;
        for(int i=0; i<graph[inx].size(); i++)
        {
            if(graph[inx][i]>0)
                nextSet.push_back(i);
        }
        return nextSet;
    }
    vector<int> getParentsByIndex(int inx)
    {
        vector<int> prevSet;
        for(int i=0; i<graph.size(); i++)
        {
            if(graph[i][inx]>0)
                prevSet.push_back(i);
        }
        return prevSet;
    }
    int getLevels()
    {
        return levelSet.size()-1;
    }
    vector<int> getPrevSet(int level)
    {
        if(level<=0)
            return levelSet[0];
        if(level>=levelSet.size())
            return levelSet[levelSet.size()-1];
        return levelSet[level-1];
    }
    int getDistance(int par, int son)
    {
        return graph[par][son];
    }
};
//向量中的每个点表示到终点的最短距离
vector<int> minDistance;

int dpMultiPartGraph(MultiPartGraph graph)
{
    int start = graph.getStart(), end = graph.getEnd();
    for(int i=start; i<end; i++)
    {
        minDistance.push_back(INT32_MAX);
    }
    minDistance.push_back(0);
    for(int level=graph.getLevels()+1; level>0; level--)
    {
        vector<int> son = graph.getPrevSet(level);
        for (int i = 0; i < son.size(); i++)
        {
            vector<int> parent = graph.getParentsByIndex(son[i]);
            for (int j = 0; j < parent.size(); j++)
            {
                if(minDistance[parent[j]]>minDistance[son[i]]+graph.getDistance(parent[j],son[i]))
                    minDistance[parent[j]] = minDistance[son[i]]+graph.getDistance(parent[j],son[i]);
            }
        }
    }
    return minDistance[start];
}

int main(int argc, char const *argv[])
{   
// 12
// 0   9   7   3   2   -1  -1  -1  -1  -1  -1  -1
// -1  0   -1  -1  -1  4   2   1   -1  -1  -1  -1
// -1  -1  0   -1  -1  2   7   -1  -1  -1  -1  -1
// -1  -1  -1  0   -1  -1  -1  11  -1  -1  -1  -1
// -1  -1  -1  -1  0   -1  11  8   -1  -1  -1  -1
// -1  -1  -1  -1  -1  0   -1  -1  6   5   -1  -1
// -1  -1  -1  -1  -1  -1  0   -1  4   3   -1  -1
// -1  -1  -1  -1  -1  -1  -1  0   -1  5   6   -1
// -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  4
// -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  2
// -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  5

    vector<vector<int>> tempG;
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't exist"<<endl;
        return -1;
    }
    int n, dist;
    infile>>n;
    for(int i=0; i<n-1; i++)
    {
        vector<int> temp;
        for(int j=0; j<n; j++)
        {
            if(infile.eof()) return 0;
            infile>>dist;
            temp.push_back(dist);
        }
        tempG.push_back(temp);
    }
    infile.close();
    MultiPartGraph graph(tempG);
    cout<<dpMultiPartGraph(graph)<<endl;
    return 0;
}
