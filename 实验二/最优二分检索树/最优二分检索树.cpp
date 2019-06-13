#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

double dpOptimalBinaryTree(vector<double> proba)
{
    vector<vector<double>> table(proba.size()+1, vector<double>(proba.size()+1, 0));
    for(int i=0; i<proba.size(); i++)
    {
        table[i][i+1] = proba[i];
    }
    for(int i=2; i<table.size(); i++)
    {
        for(int j=i; j<table.size(); j++)
        {
            double sumProba=0;
            for (int m = j-i; m<j; m++)
            {
                sumProba += proba[m];
            }
            double tempMin = DBL_MAX;
            for(int k=j-i; k<j; k++)
            {
                tempMin = min(tempMin, table[j-i][k] + table[k+1][j]);
            }
            table[j-i][j] = tempMin + sumProba;
        }
    }
    return table[0][proba.size()];
}

int main(int argc, char const *argv[])
{
    vector<double> probabilities;
    ifstream infile("input.txt", ifstream::in);
    if(!infile.is_open())
    {
        cout<<"file isn't exist"<<endl;
        return -1;
    }
    while(!infile.eof())
    {
        double prob;
        infile>>prob;
        probabilities.push_back(prob);
    }
    infile.close();
    cout<<dpOptimalBinaryTree(probabilities);
    return 0;
}
