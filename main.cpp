#include <iostream>
#include <cstdlib>
#include <cmath>

#include <list>
//#include <iterator>

using namespace std;

class Point{
public:
    int x;
    int y;
    int rootdist;

    void randGen(){
        x = rand() % 101;
        y = rand() % 101;
        rootdist = (int) sqrt(x*x + y*y);
    }

    int distP(Point pB){
        return (int) sqrt(pow((pB.x - x),2) + pow((pB.y - y),2));
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
public:
    list<Point> pointsList;
    Point* points;

    PointsList(int pointsNumber){
        Point p[pointsNumber];
        for (int i = 0; i < pointsNumber; i++){
            Point p;
            p.randGen();
            pointsList.push_back(p);
        }
        pointsList.sort(PointComparator());

        for (int i = 0; i < pointsNumber; i++){
            p[i] = listGet(i);
        }
        points = p;
    }

    void displayPoints(){
        for (Point p : pointsList){
            p.displayPoint();
        }
    }

    Point listGet(int index){
        int i = 0;
        for (Point p: pointsList){
            if (i == index) return p;
            i++;
        }
    }

    Point get(int index){
        return points[index];
    }

    void set(int index, Point new_p){
        points[index] =  new_p;
    }

};

class Simulator{
    float Temperature;


    int Simulated_annealing(list<Point> points){
    }
};



int main() {
    srand((unsigned) time(NULL));
    PointsList li = PointsList(100);
    li.get(2).displayPoint();
    li.set(2, Point());
    li.get(2).displayPoint();
//    li.displayPoints();
//
//    li.get(2).displayPoint();

//    int* test1;
//    int test2[3];
//    test2[0] = 12;
//    test1 = test2;
//    cout << test1[0];

}
