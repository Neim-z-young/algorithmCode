#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

#define _WEIGHT_ 0
#define _VALUE_ 1
int dpKnapsack(vector<vector<int>> terms, int W)
{
    vector<vector<int>> kanpsack(terms.size()+1, vector<int>(W+1, 0));
    for(int i=1; i<terms.size()+1; i++)
    {
        for(int j=1; j<W+1; j++)
        {
            int tempWeight = j-terms[i-1][_WEIGHT_];
            int tempComp = 0;
            if(tempWeight>=0)
            {
                tempComp = kanpsack[i-1][tempWeight]+terms[i-1][_VALUE_];
            }
            kanpsack[i][j] = max(tempComp, kanpsack[i-1][j]);
        }
    }
    return kanpsack[terms.size()][W];
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> terms;
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't exist"<<endl;
        return -1;
    }
    int W;
    infile>>W;
    while(!infile.eof())
    {
        int weight,value;
        infile>>weight>>value;
        terms.push_back({weight, value});
    }
    infile.close();
    cout<<dpKnapsack(terms, W);
    return 0;
}
