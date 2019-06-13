#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

int dpEditDistance(string str1, string str2)
{
    vector<vector<int>> editDistance(str2.size()+1, vector<int>(str1.size()+1, 0));
    for(int i=0; i<str1.size()+1; i++)
    {
        editDistance[0][i] = i;
    }
    for(int i=0; i<str2.size()+1; i++)
    {
        editDistance[i][0] = i;
    }
    for(int i=1; i<str2.size()+1; i++)
    {
        for(int j=1; j<str1.size()+1; j++)
        {
            int tempMin = min(editDistance[i-1][j]+1, editDistance[i][j-1]+1);
            editDistance[i][j] = min(tempMin, editDistance[i-1][j-1]+(str2[i]!=str1[j]));
        }
    }
    return editDistance[str2.size()][str1.size()];
}

int main(int argc, char const *argv[])
{
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't open";
        return 0;
    }
    string x,y;
    infile>>x>>y;
    infile.close();
    cout<<dpEditDistance(x, y);
    return 0;
}
