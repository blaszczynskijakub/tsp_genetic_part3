#include <vector>
#include <algorithm>
#include <cmath>
#include "GeneticAlgo.h"
#include <iostream>
#include <chrono>
#include <random>
#include <map>


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



    int currentRecord = INFINITY;
    for (int i = 0; i < (population.size()-population_number); i++) {
//        cout<<123<<endl;

        double d = calcDistance(population[i+population_number], inputGraph);
//        int index=0;
//        while(  index<sorted_distances.size()) {
//            if(d<sorted_distances[index])
//            {
//                index++;
//                break;
//            }
//            index++;
//        }
//        index--;



//        sorted_distances.insert(sorted_distances.begin()+index,d);
//        sorted_population.insert(sorted_population.begin()+index, i);

            double key = d;
            std::vector<double> value = population[i];
        if(populationDictionary.find(key) == populationDictionary.end()) {
            populationDictionary[key] = value;
        }

//
        if (d < this->recordDistance) {
            this->recordDistance = d;
            bestEver = population[i];

        }


        // This fitness function has been edited from the original to improve performance
//        fitness[i] = 1 / (pow(d,8) + 1);
//        cout<<fitness[i];
//        cout<<recordDistance<<endl;


    }
//    while(sorted_population.size()!=population_number) {
//      //  population.erase(population.begin() + sorted_population.back());
//        sorted_population.pop_back();
//        sorted_distances.pop_back();
//    }

    while(population.size()!=population_number)
    {
        population.pop_back();
    }
//    cout<<89;
//    auto index = --populationDictionary.end();
    while(populationDictionary.size()>population_number)
    {
        populationDictionary.erase(prev(populationDictionary.end()));
//        --index;
    }
//cout<<89;

//    cout<<endl;
//    cout<<endl;
//    cout<<endl;
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
//        cout<<fitness[i]<<endl;
//        cout<<calcDistance(population[i],inputGraph)<<endl<<endl;

    }


}

//wazna metoda
void GeneticAlgo::nextGeneration() {

    int loop_end = int(population_number*crossRate)-1;
    auto it = populationDictionary.begin();

    for (int i = 0; i < int(loop_end/2); i++) {

        std::vector<double> first =  it->second;
        advance(it,1);
        std::vector<double> second =  it->second;

        std::vector<double> order = crossOver(first,second);
        std::vector<double> orderSecond = crossOver(second,first);
//czy mutate na pewno dziala na pamieci a nie na kopii

//wydluza
        mutate(order, 0.1);
        mutate(orderSecond, 0.1);

population.push_back(order);
population.push_back(orderSecond);
//sorted_population.push_back(-9);
//sorted_distances.push_back(INT_MAX);
    }



}

std::vector<double>
GeneticAlgo::pickOne(std::vector<std::vector<double>> list,  std::vector<double> prob, bool biggest) {
//    double r = rand() / static_cast<double>(RAND_MAX + 1);
    double maxx = INT_MIN;
    double second_maxx = INT_MIN;
    int maxx_index;
    int second_maxx_index;
    for(int i=0;i<prob.size();i++)
    {
        if(prob[i]>maxx)
        {
            maxx_index = i;
            maxx = prob[i];
        }
        if(prob[i]>second_maxx && prob[i]<maxx)
        {
            second_maxx_index = i;
            second_maxx=prob[i];
        }
    }
//    cout<<index<<endl;
if(biggest==1)
    return list[maxx_index];
else
{
    return list[second_maxx_index];
}
}
// miszanie jest dobre tyle ze bez pomysli fitness zle dziala, dobre rozwiazania nie sa faworyzowane
std::vector<double> GeneticAlgo::crossOver( std::vector<double> orderA,  std::vector<double> orderB) {
    int start = rand() % (orderA.size() -1) ;
    int end = rand() % (orderA.size() - start ) + start ;
    //zeby z
    std::vector<double> newOrder(orderA.begin() + start, orderA.begin() + end);
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
//tp jest podejrzane wartp rozpatrzec
void GeneticAlgo::mutate(std::vector<double> &order, double mutationRate) {
    for (int i = 0; i < totalCities; i++) {
        const int indexA = rand() % order.size();
        const int indexB = rand() % order.size();
        if (static_cast<int>(rand()) / RAND_MAX < mutationRate && (indexA != 0 && indexB != 0) &&(indexA != indexB) ) {
            swap(order, indexA, indexB);
        }
    }
}

GeneticAlgo::GeneticAlgo(std::vector<std::vector<double>> input, int cities, int population_nr, double crossRateInput) {
    population_number = population_nr;
    std::vector<double> sorPopu(population_nr, -3);
    std::vector<double> sorDist(population_nr, INT_MAX);
    sorted_distances = sorDist;
    sorted_population = sorPopu;
    this->crossRate = crossRateInput;
    this->totalCities = cities;
//            cout<<input[0][0];
    this->inputGraph = input;

    std::vector<std::vector<double> > popul(
            population_nr,
            std::vector<double>(cities, 1.0));
    this->population = popul;


    std::vector<double> fit(population_nr, -1);
    this->fitness = fit;






    int min = INT_MAX;
    int min_vertex = 0;
    //wygenerowane sciezka bedzie miec taka dlugosc jak liczba wierzcholkow w macierzy wejsciowej
    vector<double> path;
    path.push_back(0);
    int cur_vertex = 0;

    for (int i = 0; i <cities - 1; i++) {
        for (int j = 0; j < cities; j++) {
            if (input[cur_vertex][j] < min && std::find(path.begin(), path.end(), j) == path.end()) {
                min_vertex = j;
                min = input[cur_vertex][j];


            }
        }
        cur_vertex = min_vertex;
        path.push_back(min_vertex);
        min = INT_MAX;
    }

    for(int i=0; i<population_nr;i++)
    {
        population[i]=path;
    }







    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < population_nr; i++) {
//        for (int j = 0; j < cities; j++)
//            this->population[i][j] = j;
        std::shuffle(this->population.at(i).begin() + 1, this->population.at(i).end(),
                     std::default_random_engine(seed));
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    for (int i = 0; i < population.size(); i++) {
        double d = calcDistance(population[i], inputGraph);

        double key = d;
        std::vector<double> value = population[i];
        if(populationDictionary.find(key) == populationDictionary.end()) {
            populationDictionary[key] = value;
        }

    }


//    cout<<calcDistance(population[0], input)<<endl;
//    cout<<calcDistance(path, input)<<endl;
//    for(int i=0;i<cities;i++){
//        for( int j=0;j<cities;j++)
//            cout<<population[i][j]<<" ";
//        cout<<endl;
//    }


}

GeneticAlgo::~GeneticAlgo() {

}



