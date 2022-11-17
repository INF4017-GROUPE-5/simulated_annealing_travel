#include <iostream>
#include <cstdlib>
#include <cmath>

#include <list>
//#include <iterator>

#include <bits/stdc++.h>

using namespace std;

struct neighbouring

class Point{
public:
    int x;
    int y;
    int rootdist;

    void randGen(int pointsNumber){
        x = (int) (rand() % pointsNumber);
        y = (int) (rand() % pointsNumber);
        rootdist = (int) sqrt(x*x + y*y);
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
    Point points[100];
    int pointsNumber = 100;

public:

    PointsList(){

        for (int i = 0; i < pointsNumber; i++){
            Point p;
            p.randGen(pointsNumber);
            points[i] = p;
        }
        sort(points,points + 100, PointComparator());
//        displayPoints();
    }

    void displayPoints(){
        for (int i = 0; i < pointsNumber; i++) {
            cout << i << " - " ;
            points[i].displayPoint();
        }
    }

    int computeCost(){
        int cost = 0;
        for (int i = 1; i < pointsNumber; i++){
            cost += points[i-1].distP(points[i]);
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
    PointsList pList;

    Simulator(float tmp, PointsList p){
        pList = p;
        Temperature = tmp;
    }

    // Fonction de permutation de deux éléments aléatoirement choisis dans un espacé donné
    void neighbouringSwap(int _begin, int _end){
        int source = (int) (rand() % (_end - _begin)) + _end;
        int dest = (int) (rand() % (_end - _begin)) + _end;

        Point cache = pList.get(dest);
        pList.set(dest, pList.get(source));
        pList.set(source, cache);
    }

    int getCost(){
        return pList.computeCost();
    }

    int Simulated_annealing(){
        neighbouringSwap(1, 10);
        return 1;
    }
};



int main() {
    float temp = 400.0;
    srand((unsigned) time(NULL));
    PointsList li = PointsList();
    Simulator simulator = Simulator(temp, li);

    return 0;
}
