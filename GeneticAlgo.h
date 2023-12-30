//
// Created by Jakub on 27.12.2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


class GeneticAlgo {

      int totalCities;
    std::vector<std::vector<double>> inputGraph;

     std::vector<std::vector<double>> population;
     std::vector<double> fitness;

    double calcDistance(const std::vector<double>& points, std::vector<std::vector<double>> );

    void swap(std::vector<double>& order, double indexA, double indexB);

    std::vector<double> pickOne(const std::vector<std::vector<double>>& list, const std::vector<double>& prob);

    std::vector<double> crossOver(const std::vector<double>& orderA, const std::vector<double>& orderB);

    void mutate(std::vector<double>& order, double mutationRate);

public:
    std::vector<double> check;
    std::vector<double> bestCheck;
    std::vector<double> bestEver;

    int recordDistance = INFINITY;

    GeneticAlgo(std::vector<std::vector<double>> , int);

    void calculateFitness();

    void nextGeneration();

    void normalizeFitness();

    void mutate(std::vector<double> &order, int mutationRate);
};


