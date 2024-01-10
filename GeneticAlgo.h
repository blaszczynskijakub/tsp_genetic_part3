//
// Created by Jakub on 27.12.2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>


class GeneticAlgo {
public:
    GeneticAlgo(std::vector<std::vector<double>> input, int cities, int population_nr);

    GeneticAlgo(std::vector<std::vector<double>> input, int cities, int population_nr, double crossRate);

    ~GeneticAlgo();

private:
    int totalCities;
    std::vector<std::vector<double>> inputGraph;

     std::vector<double> fitness;

    double calcDistance(const std::vector<double>& points, std::vector<std::vector<double>> );

    void swap(std::vector<double>& order, double indexA, double indexB);



    void mutate(std::vector<double>& order, double mutationRate);

public:
    std::map<double, std::vector<double>> populationDictionary;

    std::vector<double> sorted_population;
    std::vector<double> sorted_distances;
int population_number;
    std::vector<std::vector<double>> population;
    double crossRate;
    std::vector<double> check;
    std::vector<double> bestCheck;
    std::vector<double> bestEver;

    int recordDistance = INFINITY;

    GeneticAlgo(std::vector<std::vector<double>> , int);

    void calculateFitness();

    void nextGeneration();

    void normalizeFitness();

    void mutate(std::vector<double> &order, int mutationRate);

    std::vector<double> pickOne(std::vector<std::vector<double>> list, std::vector<double> prob);

    std::vector<double> crossOver(std::vector<double> orderA, std::vector<double> orderB);

    std::vector<double> pickOne(std::vector<std::vector<double>> list, std::vector<double> prob, bool biggest);
};


