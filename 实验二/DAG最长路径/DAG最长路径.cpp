#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;

vector<int> toplogicalSort(vector<vector<int>> graph)
{
    //show the state of all vertices
    vector<int> is_visited(graph.size(), 0);
    vector<int> sorted;
    stack<int> dfsStack;
    for(int i=0; i<graph.size(); i++)
    {
        if(is_visited[i]==0)
        {
            dfsStack.push(i);
            while(!dfsStack.empty())
            {
                int vertex = dfsStack.top();
                if(is_visited[vertex]==0)
                {
                    is_visited[vertex] = 1;
                    for (int j = 0; j < graph[vertex].size(); j++)
                    {
                        if (graph[vertex][j] > 0&&is_visited[j]!=2)
                        {
                            dfsStack.push(j);
                        }
                    }
                }else if(is_visited[vertex]==1)
                {
                    sorted.push_back(vertex);
                    is_visited[vertex]=2;
                    dfsStack.pop();
                }else
                {
                    dfsStack.pop();
                }
                
            }
        }
    }
    reverse(sorted.begin(), sorted.end());
    return sorted;
}

int dpLongestPathInDAG(vector<vector<int>> graph)
{
    //vector<int> indegree;
    set<int> vertices;
    //the length ending with vertex is initialized with 0
    vector<int> endLength(graph.size(), 0);
    vector<int> topSorted = toplogicalSort(graph);
    for(int i=0; i<topSorted.size(); i++)
    {
        int vertex = topSorted[i];
        for(int j=0; j<graph.size(); j++)
        {
            if(graph[j][vertex]>0 && graph[j][vertex]+endLength[j] > endLength[vertex])
            {
                endLength[vertex] = graph[j][vertex]+endLength[j];
            }
        }
    }
    int tempMax=0;
    for(int i=0; i<endLength.size(); i++)
    {
        if(tempMax < endLength[i])
        {
            tempMax = endLength[i];
        }
    }
    return tempMax;
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
    cout<<dpLongestPathInDAG(tempG);
    return 0;
}
