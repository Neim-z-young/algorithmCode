#include<iostream>
#include<vector>
using namespace std;
void solveMatch(int n, int row, int col, vector<vector<int>>& arrange){
    if(n==2) {
        arrange[row][col] = row+1;
        arrange[row][col+1] = row+2;
        arrange[row+1][col] = row+2;
        arrange[row+1][col+1] = row+1;
        return;
    }
    solveMatch(n/2, row, col, arrange);
    solveMatch(n/2, row+n/2, col, arrange);
    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            arrange[row+i][col+n/2+j] = arrange[row+n/2+i][col+j];
            arrange[row+n/2+i][col+n/2+j] = arrange[row+i][col+j];
        }
    }
    return;
}
int main(int argc, char const *argv[])
{
    /* code */
    int n;
    cin>>n;
    vector<vector<int>> arrange(n, vector<int>(n,0));
    solveMatch(n, 0, 0, arrange);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<arrange[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
