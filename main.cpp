#include <iostream>
#include <cstdlib>
#include <cmath>

#include <list>

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

//    Génération aléatoire des coordonnées des points (entre 0 et 99)
    void randGen(int pointsNumber){
        x = (int) (rand() % pointsNumber);
        y = (int) (rand() % pointsNumber);
        rootdist = (int) sqrt(x*x + y*y);
    }
//    Calcul de la distance entre l'instance courante de la classe et un autre point pris en paramètre
    int distP(Point pB){
        int reslt = (int) sqrt(pow((pB.x - x),2) + pow((pB.y - y),2));
        return reslt;
    }
//    Affichage des coordonnées d'un point
    void displayPoint(){
        printf("(%d, %d) ", x, y);
    }

};

//Operateur de comparaison utilisé pour faire le tri du tableau des points
struct PointComparator{
    bool operator()(const Point & point1, const Point & point2){
        return point1.rootdist < point2.rootdist;
    }
};

//Classe contenant une permutation de points
class PointsList{
    Point points[100]; // Ensemble de points de travail

public:
    int pointsNumber = 100;

    PointsList(){

        for (int i = 0; i < pointsNumber; i++){
            Point p;
            p.randGen(pointsNumber); // affectation aléatoire des valeurs des coordonnées des points
            points[i] = p; // ajout du point crée aléatoirement à l'ensemble de travail
        }

        // Tri des points générés aléatoirement sur la base de la distance à l'origine du repère : Point (0,0)
        sort(points,points + 100, PointComparator());
    }

//    Affichage du chemin courant
    void displayPath(){
        for (int i = 0; i < pointsNumber; i++) {
            points[i].displayPoint();
        }
    }

//    Calcul de la longeur du chemin courant
    int computeCost(){
        int cost = 0;
        // On calcule la distance entre les points deux à deux
        for (int i = 1; i < pointsNumber; i++){
            cost += points[i-1].distP(points[i]); // distance entre le point i-1 et le point i
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

// classe containant l'implementation de l'algorithme de simulated annealing
class Simulator{
public:
    float temperature;
    PointsList pList; // L'ensemble des points sur lequel on travaille
    int nbNeighbourhood;  // Nombre de voisinnages de points utilisées
    list<Neighbourhood> neighbourhoods;  // Ensemble des voisinnages de points

    // On initialise le constructeur en lui passant la liste des points qui aura été générée en amont
    Simulator( PointsList p){
        pList = p;
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

    // Fonction permettant de recevoir un voisinage aléatoire parmi ceux qui ont été crée avec la fonction generateNeighbourhoods
    Neighbourhood getRandomNeighbourhood(){
        int randomIndex = (int) rand() % nbNeighbourhood ;
        int i = 0;
        for (Neighbourhood nbh : neighbourhoods){
            if (i == randomIndex) return nbh;  // on retourne le voisinnage numero i
            i++;
        }
    }

    // Fonction de permutation de deux éléments aléatoirement choisis dans l'espace de points
    void neighbouringSwap(Neighbourhood nbh){
        // Détermination de la position des points du voisinnage nbh à permuter
        int dif = nbh._end - nbh._start;
        int vrand = (int) rand() % (dif);
        int source = vrand + nbh._start;
        vrand = (int) rand() % (dif);
        int dest = vrand + nbh._start;

        Point cache = pList.get(dest);
        pList.set(dest, pList.get(source));
        pList.set(source, cache);
    }

    // Récupération du cout de l'ensemble courant
    int getCost(){
        return pList.computeCost();
    }
    // Implementation de l'algorithme de recuit simulé
    int Simulated_annealing(float tmp){
        generateNeighbourhoods(10); // On génère 10 voisinnages dans l'ensemble initialement trié
        temperature = tmp; // On définit la température avec laquelle on va dérouler l'algorithme
        int optValue = getCost();  // On évalue le cout de la configuration initiale
        while( temperature > 0.1 ){
            Neighbourhood nbh = getRandomNeighbourhood(); // On choisi aléatoirement un voisinnage parmi ceux générés
            neighbouringSwap(nbh); // On fait la permutation de deux points pris aléatoirement dans le voisinnage

            cout << "\ncurrent permutation" << endl;
            pList.displayPath();  // On affiche la permutation courante

            // On prend le cout de l'itération courante et s'il est meilleur, on le sauvegarde
            int tester = getCost();
            if (tester < optValue) optValue = tester;
            temperature *= 0.9;
        }
        return optValue;
    }

    void displayResult(){
        cout << "\n>>>> Chemin final" << endl;
        pList.displayPath();
    }
};



int main() {
    srand((unsigned) time(NULL));


    float temp = 40.0; // définition de la température
    PointsList li = PointsList(); // cration aléatoire de la première configuration

    cout << "Initial cost " << li.computeCost() << endl;

    Simulator simulator = Simulator(li); // L'objet simulator lance l'implementation de l'algorithme

    cout << "Initial path " << endl;
    simulator.pList.displayPath();

    printf("\n \nRésultat optimisé : %d\n", simulator.Simulated_annealing(temp));
    simulator.displayResult();

    return 0;
}
