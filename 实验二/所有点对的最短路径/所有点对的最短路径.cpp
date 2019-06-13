#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
using namespace std;

void dpShortestPath(vector<vector<int>> &graph)
{
    //i is mid node
    for(int i=0; i<graph.size(); i++)
    {
        for(int j=0; j<graph.size(); j++)
        {
            if(j!=i)
            {
                for(int k=0; k<graph.size(); k++)
                {
                    //avoid overflow
                    graph[j][k] = min(graph[j][k], (graph[j][i]+graph[i][k])>=0?(graph[j][i]+graph[i][k]):INT32_MAX);
                }
            }
        }
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
    dpShortestPath(tempG);
    ofstream outfile("output.txt", ofstream::out);
    if(!outfile.is_open())
    {
        cout<<"outfile isn't exist"<<endl;
        return -1;
    }
    for(int i=0; i<tempG.size(); i++)
    {
        for(int j=0; j<tempG[i].size(); j++)
        {
            outfile<<tempG[i][j]<<' ';
        }
        outfile<<endl;
    }
    return 0;
}
