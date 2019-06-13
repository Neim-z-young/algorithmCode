#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<fstream>

#define __AXIS__ 0
#define _X_ 0
#define _Y_ 1
using namespace std;
struct Point{
    int x[2];
    Point(){
        x[_X_]=0;
        x[_Y_]=0;
    }
    Point(int x, int y){
        this->x[_X_]=x;
        this->x[_Y_]=y;
    }
    bool operator <(const Point& p1){
        return this->x[__AXIS__]<p1.x[__AXIS__];
    }
    double distance(Point p){
        return sqrt(double(this->x[_X_]-p.x[_X_])*(this->x[_X_]-p.x[_X_])+(this->x[_Y_]-p.x[_Y_])*(this->x[_Y_]-p.x[_Y_]));
    }
};

vector<Point> closestPoints(vector<Point>& points, int low, int high){
    if(high-low+1==2)
        return vector<Point>({points[low], points[high]});
    sort(
        points.begin(), points.end(), 
        [](const Point &p1, const Point &p2) -> bool {return p1.x[_X_]<p2.x[_X_];}
    );
    int mid = low+(high+1-low)/2;
    vector<Point> tmp1 = closestPoints(points, low, mid);
    vector<Point> tmp2 = closestPoints(points, mid, high);
    double dist1 = tmp1[0].distance(tmp1[1]);
    double dist2 = tmp2[0].distance(tmp2[1]);
    int minDist = dist1>dist2?dist2:dist1;
    int tmpMin = ceil(minDist);
    vector<Point> minP = dist1>dist2?tmp2:tmp1;
    //expand
    int tlow = mid, thigh = mid;
    while(tmpMin>abs(points[mid].x[_X_]-points[tlow].x[_X_]) && tlow>low) tlow--;
    while(tmpMin>abs(points[thigh].x[_X_]-points[mid].x[_X_]) && thigh<high) thigh++;
    sort(
        points.begin(), points.end(), 
        [](const Point &p1, const Point &p2) -> bool {return p1.x[_Y_]<p2.x[_Y_];}
    );
    for(int i=tlow; i<thigh; i++){
        for(int j=i+1; j<=thigh; j++){
            if(points[j].x[_Y_]-points[i].x[_Y_] >= tmpMin) break;
            else{
                double tmpdist = points[j].distance(points[i]);
                if(tmpdist<minDist){
                    minDist = tmpdist;
                    tmpMin = ceil(tmpdist);
                    minP = vector<Point>({points[i], points[j]});
                }
            }
        }
    }
    return minP;
}

int main(int argc, char const *argv[])
{
    vector<Point> points;
    int n=4;
    // for(int i=1; i<=n; i++){
    //     points.push_back(Point(i, i));
    //     points.push_back(Point(i, 2*i));
    //     points.push_back(Point(i, 3*i));
    // }

    srand((int)time(0));

    ifstream infile("最近点对.txt");
    if(!infile.is_open()) return 0;
    while(!infile.eof()){
        Point tmp;
        infile>>tmp.x[0]>>tmp.x[1];
        points.push_back(tmp);
    }

    // for(int i=1; i<=2*n; i++){
    //     Point tmp = Point(rand()%20, rand()%20);
    //     cout<<"点"<<i<<": "<<tmp.x[0]<<" "<<tmp.x[1]<<endl;
    //     points.push_back(tmp);
    // }

    vector<Point> ans = closestPoints(points, 0, points.size()-1);
    cout<<"点："<<ans[0].x[0]<<" "<<ans[0].x[1]<<endl;
    cout<<"点："<<ans[1].x[0]<<" "<<ans[1].x[1]<<endl;
    cout<<"距离"<<ans[0].distance(ans[1]);
    return 0;
}
