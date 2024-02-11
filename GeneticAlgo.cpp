#include <vector>
#include <algorithm>
#include <cmath>
#include "GeneticAlgo.h"
#include <chrono>
#include <random>
#include <map>


using namespace std;


double GeneticAlgo::calcDistance(const std::vector<double> &points, std::vector<std::vector<double>> input) {
    double sum = 0;
    for (int i = 0; i < points.size() - 1; i++) {
        sum += input[points[i]][points[i + 1]];
    }

    sum += input[points[points.size() - 1]][points[0]];

    return sum;
}

void GeneticAlgo::swap(std::vector<double> &order, double indexA, double indexB) {
    int temp = order[indexA];
    order[indexA] = order[indexB];
    order[indexB] = temp;
}

void GeneticAlgo::calculateFitness() {


    for (int i = 0; i < (population.size() - population_number); i++) {

        double d = calcDistance(population[i + population_number], inputGraph);


        double key = d;

        std::vector<double> value = population[i + population_number];
        if (populationDictionary.find(key) == populationDictionary.end()) {
            populationDictionary[key] = value;
        }

//
        if (d < this->recordDistance) {
            this->recordDistance = d;
            bestEver = population[i + population_number];
        }
    }


    while (population.size() > population_number) {
        population.pop_back();
    }


    while (populationDictionary.size() > population_number) {
        populationDictionary.erase(prev(populationDictionary.end()));
    }

}


void GeneticAlgo::nextGeneration() {

    int loop_end = int(population_number * crossRate) - 1;

    for (int i = 0; i < int(loop_end / 2); i++) {
        auto it = populationDictionary.begin();

        std::vector<double> first = it->second;

        advance(it, i);
        std::vector<double> second = it->second;

        std::vector<double> order = crossOver(first, second);
        std::vector<double> orderSecond = crossOver(second, first);


        auto randMut = populationDictionary.begin();
        int indexToMut = ((std::rand()) % (populationDictionary.size() - 2) + 1);

        advance(randMut, indexToMut);
        mutate(randMut->second, 0.3);
        std::vector<double> mutatedPath = randMut->second;
        int mutDist = calcDistance(mutatedPath, inputGraph);
        if (populationDictionary.find(mutDist) == populationDictionary.end()) {
            populationDictionary.erase(randMut);

        }
        populationDictionary[mutDist] = mutatedPath;


        population.push_back(order);
        population.push_back(orderSecond);

    }


}


std::vector<double> GeneticAlgo::crossOver(std::vector<double> orderA, std::vector<double> orderB) {
    int start = rand() % (orderA.size() - 2) + 1;
    int end = rand() % (orderA.size() - start) + start;
    std::vector<double> newOrder(orderA.begin() + start, orderA.begin() + end);
    newOrder.insert(newOrder.begin(), 0);
    for (int i = 0; i < orderB.size(); i++) {
        const int city = orderB[i];
        if (find(newOrder.begin(), newOrder.end(), city) == newOrder.end()) {
            newOrder.push_back(city);
        }
    }

    return newOrder;
}

void GeneticAlgo::mutate(std::vector<double> &order, double mutationRate) {
    for (int i = 0; i < totalCities; i++) {
        const int indexA = rand() % order.size();
        const int indexB = rand() % order.size();
        if (static_cast<int>(rand()) / RAND_MAX < mutationRate && (indexA != 0 && indexB != 0) && (indexA != indexB)) {
            swap(order, indexA, indexB);
        }
    }
}

void GeneticAlgo::initializeMembers(int population_nr, double crossRateInput, int cities, const std::vector<std::vector<double>>& input) {
    population_number = population_nr;
    crossRate = crossRateInput;
    totalCities = cities;
    inputGraph = input;

    sorted_distances = std::vector<double>(population_nr, INT_MAX);
    sorted_population = std::vector<double>(population_nr, -3);
    population = std::vector<std::vector<double>>(population_nr, std::vector<double>(cities, 1.0));
    fitness = std::vector<double>(population_nr, -1);
}

std::vector<double> GeneticAlgo::generateInitialPath() {
    std::vector<double> path;
    path.push_back(0);
    int min = INT_MAX, min_vertex = 0, cur_vertex = 0;

    for (int i = 0; i < totalCities - 1; ++i) {
        for (int j = 0; j < totalCities; ++j) {
            if (inputGraph[cur_vertex][j] < min && std::find(path.begin(), path.end(), j) == path.end()) {
                min = inputGraph[cur_vertex][j];
                min_vertex = j;
            }
        }
        path.push_back(min_vertex);
        cur_vertex = min_vertex;
        min = INT_MAX;
    }
    return path;
}

void GeneticAlgo::shufflePopulation(unsigned& seed) {
    for (auto& individual : population) {
        std::shuffle(individual.begin() + 1, individual.end(), std::default_random_engine(seed));
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
}

void GeneticAlgo::calculateInitialDistances() {
    for (const auto& path : population) {
        double distance = calcDistance(path, inputGraph);
        if (populationDictionary.find(distance) == populationDictionary.end()) {
            populationDictionary[distance] = path;
        }
    }
}


GeneticAlgo::GeneticAlgo(std::vector<std::vector<double>> input, int cities, int population_nr, double crossRateInput) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    initializeMembers(population_nr, crossRateInput, cities, input);
    auto initialPath = generateInitialPath();
    for (auto& individual : population) {
        individual = initialPath;
    }
    shufflePopulation(seed);
    calculateInitialDistances();
}

GeneticAlgo::~GeneticAlgo() {

}



int GeneticAlgo::getRecordDistance() const {
    return recordDistance;
}



