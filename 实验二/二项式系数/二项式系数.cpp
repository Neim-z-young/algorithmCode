#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
using namespace std;

vector<vector<int>> dpBinomialCoeff(int n)
{
    vector<vector<int>> combination;
    //initial echelon matrix
    for(int i=0; i<n+1; i++)
    {
        vector<int> temp(i+1, 1);
        combination.push_back(temp);
    }
    //using recursion formula
    for(int i=0; i<n+1; i++)
    {
        for(int j=1; j<i; j++)
        {
            combination[i][j] = combination[i-1][j-1] + combination[i-1][j];
        }
    }
    return combination;
}

int main(int argc, char const *argv[])
{
    ofstream outfile("output.txt", ofstream::out);
    if(!outfile.is_open())
    {
        cout<<"file isn't open";
        return 0;
    }
    int n;
    cin>>n;
    vector<vector<int>> out = dpBinomialCoeff(n);
    for(int i=0; i<out.size(); i++)
    {
        for(int j=0; j<out[i].size(); j++)
        {
            outfile<<out[i][j]<<'\t';
        }
        outfile<<endl;
    }
    return 0;
}
