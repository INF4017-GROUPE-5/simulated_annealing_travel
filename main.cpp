#include <iostream>
#include <cstdlib>
#include <cmath>

#include <list>
//#include <iterator>

#include <bits/stdc++.h>

using namespace std;

struct sPoint{
    int x;
    int y;
    int rootdist;
};

class Point{
public:
    int x;
    int y;
    int rootdist;

    void randGen(int pointsNumber){
        x = (int) (rand() % pointsNumber);
        y = (int) (rand() % pointsNumber);
        rootdist = (int) sqrt(x*x + y*y);
//        x = 1;
//        y = 2;
//        rootdist = (int) sqrt(x*x + y*y);
    }

    int distP(Point pB){
        int reslt = (int) sqrt(pow((pB.x - x),2) + pow((pB.y - y),2));
        return reslt;
    }

    void displayPoint(){
        printf("Salut, je suis le point (%d, %d). Ma distance à la racine du repère est %d\n", x, y, rootdist);
    }

};

struct PointComparator{
    bool operator()(const Point & point1, const Point & point2){
        return point1.rootdist < point2.rootdist;
    }
};

class PointsList{
    list<Point> pointsList;
//    Point* points;
    Point points[100];
    int pointsNumber = 100;

public:

    PointsList(int pointsNumber){
//        this->pointsNumber = pointsNumber;
//        Point pointsTable[pointsNumber];

//        for (int i = 0; i < pointsNumber; i++){
//            Point p;
//            p.randGen(pointsNumber);
//            pointsList.push_back(p);
//        }
//        pointsList.sort(PointComparator());


        for (int i = 0; i < pointsNumber; i++){
            Point p;
            p.randGen(pointsNumber);
            points[i] = p;
//            points[i] = listGet(i);
        }
        sort(points,points + 100, PointComparator());
        displayPoints();
//        points.displayPoint();
//        points = pointsTable;
    }

    void displayPoints(){
        for (int i = 0; i < pointsNumber; i++) {
            cout << i << " - " ;
            points[i].displayPoint();
        }
    }
    void displayPoints(int a){
        for(Point k: pointsList){
            k.displayPoint();
        }
    }

    Point listGet(int index){
        int i = 0;
        for (Point p: pointsList){
            if (i == index) return p;
            i++;
        }
    }

    int computeCost(){
        int cost = 0;
        for (int i = 1; i < pointsNumber; i++){
            cost += points[i-1].distP(points[i]);
//            cout << cost << endl ;
        }
        return cost;
    }

    Point get(int index){
        return points[index];
    }

    void set(int index, Point new_p){
        points[index] =  new_p;
    }

};

class Simulator{
public:
    float Temperature;

    Simulator(float tmp){
        Temperature = tmp;
    }


    int Simulated_annealing(list<Point> points){
    }
};



int main() {
    srand((unsigned) time(NULL));
    PointsList li = PointsList(100);
    li.displayPoints();
    cout << li.computeCost();
    cout << rand();
    cout << rand();
    cout << rand();
}
