#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;

//TODO 添加旅行商问题的动态规划解法，需要集合的支持
class TravelingGraph
{
private:
    vector<vector<int>> graph;
public:
    TravelingGraph(){}
    TravelingGraph(vector<vector<int>> graph)
    {
        this->graph = graph;
    }
    int size()
    {
        graph.size();
    }
    int getDistance(int i, int j)
    {
        return graph[i][j];
    }
    TravelingGraph removeNode(int inx)
    {
        if(inx<0 || inx>=graph.size()) return TravelingGraph(graph);
        vector<vector<int>> temp = graph;
        for(int i=0; i<graph.size(); i++)
        {
            temp[i][inx] = INT32_MAX;
            temp[inx][i] = INT32_MAX;
        }
        return TravelingGraph(temp);
    }
};

vector<TravelingGraph> findSubsets(int index, TravelingGraph graph)
{
    if (index == graph.size())
        return vector<TravelingGraph>({graph});
    //find all subsets containing start node
    vector<TravelingGraph> subsets = findSubsets(index + 1, graph.removeNode(index));
    vector<TravelingGraph> temp = findSubsets(index + 1, graph);
    subsets.insert(subsets.end(), temp.begin(), temp.end());
    return subsets;
}

int dpSalesman(TravelingGraph graph)
{
    //choose 0 node to be the start
    int start = 0;
    //find all subsets containing start node
    vector<TravelingGraph> subSets = findSubsets(start+1, graph);
    vector<vector<int>> table(subSets.size(), vector<int>(graph.size(), 0));
    for(int i=0; i<subSets.size(); i++)
    {

    }
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> tempG;
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't exist"<<endl;
        return -1;
    }
    int n, dist;
    infile>>n;
    for(int i=0; i<n; i++)
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
    return 0;
}
