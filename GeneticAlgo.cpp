#include <vector>
#include <algorithm>
#include <cmath>
#include "GeneticAlgo.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
// int totalCities = 5;




double GeneticAlgo::calcDistance(const std::vector<double> &points, std::vector<std::vector<double>> input) {
    double sum = 0;

    for (int i = 0; i < points.size() - 1; i++) {
        sum += input[points[i]][points[i + 1]];
        check.push_back(input[points[i]][points[i + 1]]);
    }
    sum += input[points[points.size() - 1]][points[0]];
    check.push_back(input[points[points.size() - 1]][points[0]]);

    return sum;
}

void GeneticAlgo::swap(std::vector<double> &order, double indexA, double indexB) {
    int temp = order[indexA];
    order[indexA] = order[indexB];
    order[indexB] = temp;
}

void GeneticAlgo::calculateFitness() {

//    cout<<this->inputGraph[4][4];

    int currentRecord = INFINITY;
    for (int i = 0; i < population.size(); i++) {
        double d = calcDistance(population[i], inputGraph);
//        cout<<d;

        if (d < this->recordDistance) {
            this->recordDistance = d;
            bestEver = population[i];
            bestCheck = check;

        }

        if (d < currentRecord) {
            currentRecord = d;
//            currentBest = population[i];
        }
        // This fitness function has been edited from the original to improve performance
        fitness[i] = 1 / (pow(d, 8) + 1);

    }

}

void GeneticAlgo::normalizeFitness() {

    double sum = 0;
    //byc moze od iterowac ale sie zobaczy te fitnessy
    for (int i = 0; i < fitness.size(); i++) {
        sum += fitness[i];
    }
//    cout<<endl<<sum;
//    cout<<endl<<population.size();
    for (int i = 0; i < fitness.size(); i++) {
        fitness[i] = fitness[i] / sum;
    }

}

//wazna metoda
void GeneticAlgo::nextGeneration() {
    std::vector<std::vector<double>> newPopulation(population.size(), std::vector<double>(totalCities, 0));
    for (int i = 0; i < population.size(); i++) {

         std::vector<double> orderA = pickOne(population, fitness);
         std::vector<double> orderB = pickOne(population, fitness);
        std::vector<double> order = crossOver(orderA, orderB);
//cross albo pic
        mutate(order, 0.5);
        newPopulation[i] = order;

    }

    population = newPopulation;

}

std::vector<double>
GeneticAlgo::pickOne(std::vector<std::vector<double>> list,  std::vector<double> prob) {
    int index = 0;
    double r = rand() / static_cast<double>(RAND_MAX + 1);

    while (r > 0) {
        r = r - prob[index];
        index++;
    }
    index--;
    if(index<0)
        index=0;
    return list[index];
}

std::vector<double> GeneticAlgo::crossOver( std::vector<double> orderA,  std::vector<double> orderB) {
    int start = rand() % (orderA.size() -1) +1;
    int end = rand() % (orderA.size() - start ) + start + 1;

    //zeby z
    std::vector<double> newOrder(orderA.begin() + start+1, orderA.begin() + end);
    newOrder.insert(newOrder.begin(), 0); // Ensure 0 is at the beginning
    for (int i = 0; i < orderB.size(); i++) {
        const int city = orderB[i];
        if (find(newOrder.begin(), newOrder.end(), city) == newOrder.end()) {
            newOrder.push_back(city);
        }
    }
//    for (int i = 0; i < newOrder.size(); i++) {
//        cout<<newOrder[i]<<" ";
//    }
//    cout<<endl;
    return newOrder;
}

void GeneticAlgo::mutate(std::vector<double> &order, double mutationRate) {
    for (int i = 0; i < totalCities; i++) {
        const int indexA = rand() % order.size();
        const int indexB = (indexA + 1) % totalCities;
        if (static_cast<int>(rand()) / RAND_MAX < mutationRate && (indexA != 0 && indexB != 0)) {
            swap(order, indexA, indexB);
        }
    }
}

GeneticAlgo::GeneticAlgo(std::vector<std::vector<double>> input, int cities) {
    this->totalCities = cities;
//            cout<<input[0][0];
    this->inputGraph = input;

    std::vector<std::vector<double> > popul(
            cities,
            std::vector<double>(cities, 1.0));
    this->population = popul;


    std::vector<double> fit(cities, -1);
    this->fitness = fit;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++)
            this->population[i][j] = j;
        std::shuffle(this->population.at(i).begin() + 1, this->population.at(i).end(),
                     std::default_random_engine(seed));
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
//    for(int i=0;i<cities;i++){
//        for( int j=0;j<cities;j++)
//            cout<<population[i][j]<<" ";
//        cout<<endl;
//    }


}

GeneticAlgo::~GeneticAlgo() {

}



