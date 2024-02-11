#ifndef PEA_PROJEKT_1_MENU_H
#define PEA_PROJEKT_1_MENU_H

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "DataGenerator.h"
#include "GeneticAlgo.h"

class Menu {

public:
    Menu() = default;
    void show_menu();

private:
    std::vector<std::vector<double>> double2DVector = {};
    int iterations =1000;
    double temperature_change_coefficient = 0.8;
    Graph graph = Graph(std::vector<std::vector<int>>() );
    GeneticAlgo* genPtr = nullptr;



    bool is_digit(std::string input);


    void algo_cycle(int iter , GeneticAlgo *genPtr );

    void set_stop_criteria();

    void run_genetic_algorithm();

    void display_matrix();

    void generate_matrix();

    void load_matrix_from_file();

    void exit_program();

    void set_temperature_change_coefficient();

    std::vector<std::vector<double>> convert_to_double_vector(const std::vector<std::vector<int>> &intVector);
};

#endif //PEA_PROJEKT_1_MENU_H