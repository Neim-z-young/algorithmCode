#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

#define _ROW_ 0
#define _COL_ 1
int dpChainMatrixMulti(vector<vector<int>> matrices)
{
    vector<vector<int>> table(matrices.size(), vector<int>(matrices.size(), 0));
    for(int m=1; m<matrices.size(); m++)
    {
        for(int j=m; j<matrices.size(); j++)
        {
            int tempMin=INT32_MAX;
            for(int k=j-m; k<j; k++)
            {
                tempMin = min(tempMin, 
                    table[j-m][k] + table[k+1][j] + 
                        matrices[j-m][_ROW_]*matrices[k][_COL_]*matrices[j][_COL_]);
            }
            table[j-m][j] = tempMin;
        }
    }
    return table[0][matrices.size()-1];
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> matrices;
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't exist"<<endl;
        return -1;
    }
    while(!infile.eof())
    {
        int row,col;
        infile>>row>>col;
        matrices.push_back({row, col});
    }
    infile.close();
    cout<<dpChainMatrixMulti(matrices);
    return 0;
}
