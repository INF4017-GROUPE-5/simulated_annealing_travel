#include <iostream>
#include <cstdlib>
#include <cmath>

#include <list>
//#include <iterator>

#include <bits/stdc++.h>

using namespace std;

struct Neighbourhood{
    int _start;
    int _end;
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

public:
    int pointsNumber = 100;

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
    float temperature;
    PointsList pList;
    int nbNeighbourhood;
    list<Neighbourhood> neighbourhoods;

    Simulator( PointsList p){
        pList = p;
    }

    // Fonction de permutation de deux éléments aléatoirement choisis dans un espacé donné
    void neighbouringSwap(Neighbourhood nbh){
        int dif = nbh._end - nbh._start;
//        printf("range [%d,%d]\n", nbh._start, nbh._end);
//        cout << "this is dif " << dif << endl;
        int vrand = (int) rand() % (dif);
//        cout << "rand : " << vrand << endl;
        int source = vrand + nbh._start;
        vrand = (int) rand() % (dif);
//        cout << "rand : " << vrand << endl;
        int dest = vrand + nbh._start;

//        cout << "source : " << source << " dest : " << dest << endl;

        Point cache = pList.get(dest);
        pList.set(dest, pList.get(source));
        pList.set(source, cache);
    }

    Neighbourhood getRandomNeighbourhood(){
        int randomIndex = (int) rand() % nbNeighbourhood ;
        int i = 0;
        for (Neighbourhood nbh : neighbourhoods){
            if (i == randomIndex) return nbh;
            i++;
        }
    }

    // Géneration des voisinnages
    void generateNeighbourhoods(int sizeNeighbourhoods){
        int nb = 0;
        for (int i = 0; i < pList.pointsNumber; i += sizeNeighbourhoods){
            Neighbourhood nbh;
            nbh._start = i;
            nbh._end = i + sizeNeighbourhoods - 1;
            neighbourhoods.push_back(nbh);
            nb++;
        }
        nbNeighbourhood = nb;
    }

    int getCost(){
        return pList.computeCost();
    }

    int Simulated_annealing(float tmp){
        generateNeighbourhoods(10);
        temperature = tmp;
        int optValue = getCost();
        while( temperature > 0.1){
            Neighbourhood nbh = getRandomNeighbourhood();
            neighbouringSwap(nbh);
            int tester = getCost();
            if (tester < optValue) optValue = tester;
            temperature *= 0.9;
        }
        return optValue;
    }
};



int main() {
    float temp = 10.0;
    srand((unsigned) time(NULL));
    PointsList li = PointsList();
    cout << "Initial cost " << li.computeCost() << endl;
    Simulator simulator = Simulator(li);
    printf("Résultat optimisé : %d", simulator.Simulated_annealing(temp));
    return 0;
}
