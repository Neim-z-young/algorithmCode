#pragma comment(linker, "/STACK:100000000")
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<string>
using namespace std;

/*
* 使用快排思想
*/
int doPartition(vector<int>& array, int low, int high){
    int cur = low;
    while(low<high){
        while(array[cur]<array[high]&&low<high) high--;
        while(array[cur]>=array[low]&&low<high) low++;
        int tmp = array[low];
        array[low] = array[high];
        array[high] = tmp;
        high--;
    }
    int tmp = array[low];
    array[low] = array[cur];
    array[cur] = tmp;
    return low;
}

int findKthSmallestWithQuickSort(vector<int>& array, int k, int low, int high){
    if(k>(high-low+1))
        return -1;
    int index = doPartition(array, low, high);
    if(index-low == k-1)
        return array[index];
    else if(index-low > k-1)
        return findKthSmallestWithQuickSort(array, k, low, index-1);
    else
        return findKthSmallestWithQuickSort(array, low+k-1-index, index+1, high);
}

int findKthSmallestWithQuickSort(vector<int> array, int k){
    return findKthSmallestWithQuickSort(array, k, 0, array.size()-1);
}

/*
* PPT算法,保证了最坏情况下的速度
*/
int findKthSmallest(vector<int> array, int k){
    int size = array.size();
    if(k>size) return -1;
    if(size<75) {
        sort(array.begin(), array.end());
        return array[k-1];
    }
    vector<int> medium;
    int step = 15;
    for(int i=0; i<size; i+=step){
        vector<int> tmp;
        for(int j=i; j<i+step&&j<size; j++){
            tmp.push_back(array[j]);
        }
        if(tmp.size()) medium.push_back(findKthSmallest(tmp, 1+tmp.size()/2));
    }
    int x = findKthSmallest(medium, 1+medium.size()/2);
    medium.~vector();
    vector<int> S1, S2;
    for(int i=0; i<size; i++){
        if(array[i]<=x) S1.push_back(array[i]);
        else S2.push_back(array[i]);
    }
    array.~vector();
    if(k<=S1.size()) return findKthSmallest(S1, k);
    else return findKthSmallest(S2, k-S1.size());
}

/*
* 优化版
*/
int findKthSmallest(vector<int>& array, int k, int low, int high){
    if(k>high-low+1) return -1;
    if(high-low+1<75) {
        sort(array.begin()+low, array.begin()+high+1);
        return array[low+k-1];
    }
    vector<int> medium;
    int step = 15;
    for(int i=low; i<=high; i+=step){
        int len = high-i+1>step?step:high-i+1;
        medium.push_back(findKthSmallest(array, 1+len/2, i, len+i-1));
    }
    int x = findKthSmallest(medium, 1+medium.size()/2, 0, medium.size()-1);
    medium.~vector();

    vector<int> S1, S2;
    for(int i=low; i<=high; i++){
       if(array[i]<=x) S1.push_back(array[i]);
       else S2.push_back(array[i]);
    }
    array.~vector();
    if(k<=S1.size())
        return findKthSmallest(S1, k, 0, S1.size()-1);
    else
        return findKthSmallest(S2, k-S1.size(), 0, S2.size()-1);
}

int findKthSmallestOpt(vector<int> array, int k){
    return findKthSmallest(array, k, 0, array.size()-1);
}

/*
* 使用内置排序
*/
int findKthSmallestBySort(vector<int> array, int k){
    if(k>array.size()) return -1;
    sort(array.begin(), array.end());
    return array[k-1];
}


static int n;
static int k;

/*
* 算法测试
*/
void test(string s, bool worst, int m){
    vector<int> array;
    srand(int(time(0)));
    cout<<s<<endl;
    for(int i=0; i<n; i++){
        array.push_back(worst?n-i:rand());
    }

    clock_t start, end;
    double deltaTime;

    cout<<"快排思想："<<findKthSmallestWithQuickSort(array, k)<<endl;
    start = clock();
    for(int i=0; i<m; i++){
        findKthSmallestWithQuickSort(array, k);
    }
    end = clock();
    deltaTime = (end-start)/CLOCKS_PER_SEC;
    cout<<"平均用时: "<<deltaTime/m<<endl;
    
    cout<<"改进快排："<<findKthSmallest(array, k)<<endl;
    start = clock();
    for(int i=0; i<m; i++){
        findKthSmallest(array, k);
    }
    end = clock();
    deltaTime = (end-start)/CLOCKS_PER_SEC;
    cout<<"平均用时: "<<deltaTime/m<<endl;

    cout<<"优化："<<findKthSmallestOpt(array, k)<<endl;
    start = clock();
    for(int i=0; i<m; i++){
        findKthSmallestOpt(array, k);
    }
    end = clock();
    deltaTime = (end-start)/CLOCKS_PER_SEC;
    cout<<"平均用时: "<<deltaTime/m<<endl;

    cout<<"直接排序："<<findKthSmallestBySort(array, k)<<endl;
    start = clock();
    for(int i=0; i<m; i++){
        findKthSmallestBySort(array, k);
    }
    end = clock();
    deltaTime = (end-start)/CLOCKS_PER_SEC;
    cout<<"平均用时: "<<deltaTime/m<<endl;

    return;
}

int main(int argc, char const *argv[])
{
    
    cout<<"总数：";
    cin>>n;
    cout<<"kth: ";
    cin>>k;
    //test("最坏情况", true, 1);
    cout<<endl;
    test("平均情况", false, 2);
    return 0;
}
