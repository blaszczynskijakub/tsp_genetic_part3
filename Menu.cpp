#include "Menu.h"
#include <iostream>
#include <vector>
#include <string>

#include "DataGenerator.h"
#include "Data_parser.h"

void Menu::show_menu() {
    std::string choice_s;
    while (true) {
        std::cout << "Menu for the Traveling Salesman Problem solved with Simulated Annealing.\n";
        std::cout << "0 - Exit\n";
        std::cout << "1 - Load matrix from file\n";
        std::cout << "2 - Generate matrix\n";
        std::cout << "3 - Display the last loaded or generated matrix\n";
        std::cout << "4 - Run Genetic Algorithm on the last matrix\n";
        std::cout << "5 - Set stop criteria (number of iterations)\n";
        std::cout << "6 - Set temperature change coefficient\n";
        std::cout << "> ";

        std::cin >> choice_s;
        if (!is_digit(choice_s)) {
            std::cout << "Invalid input. Please enter a number.\n>";
            continue;
        }
        int choice = std::stoi(choice_s);

        switch (choice) {
            case 0: exit_program(); break;
            case 1: load_matrix_from_file(); break;
            case 2: generate_matrix(); break;
            case 3: display_matrix(); break;
            case 4: run_genetic_algorithm(); break;
            case 5: set_stop_criteria(); break;
            case 6: set_temperature_change_coefficient(); break;
            default: std::cout << "Invalid option.\n"; break;
        }
    }
}

void Menu::exit_program() {
    std::cout << "Exiting program.\n";
    exit(0);
}

void Menu::load_matrix_from_file() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    Data_parser parser(filename);
    if (parser.openFile()) {
        this->graph.setGraph(parser.readFile());
        this->double2DVector = convert_to_double_vector(this->graph.getGraph());
    } else {
        std::cout << "Failed to open file.\n";
    }
}

void Menu::generate_matrix() {
    int size;
    std::cout << "Enter matrix size: ";
    std::cin >> size;
    DataGenerator generator;
    this->graph.setGraph(generator.generate_data(size));
    this->double2DVector = convert_to_double_vector(this->graph.getGraph());
}

void Menu::display_matrix() {
    if (this->double2DVector.empty()) {
        std::cout << "Matrix is empty.\n";
        return;
    }
    for (const auto& row : this->double2DVector) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

void Menu::run_genetic_algorithm() {
    if (this->double2DVector.empty()) {
        std::cout << "Matrix is empty. Cannot run Genetic Algorithm.\n";
        return;
    }
    if (this->genPtr != nullptr) delete this->genPtr;
    this->genPtr = new GeneticAlgo(this->double2DVector, this->graph.getNumOfVertices(), 50, 0.90);
    algo_cycle(this->iterations, this->genPtr);
}

void Menu::set_stop_criteria() {
    std::cout << "Enter number of iterations: ";
    std::cin >> this->iterations;
}

void Menu::set_temperature_change_coefficient() {
    std::cout << "Enter temperature change coefficient: ";
    std::cin >> this->temperature_change_coefficient;
}

void Menu::algo_cycle(int iter, GeneticAlgo *genPtr){
    for (int i = 0; i < iter; i++) {

        genPtr->calculateFitness();
        genPtr->nextGeneration();
        std::cout << std::endl << genPtr->getRecordDistance() << std::endl;
    }
    std::cout << std::endl << genPtr->getRecordDistance() << std::endl;

}

bool Menu::is_digit(std::string input) {

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    return true;

}

std::vector<std::vector<double>> Menu::convert_to_double_vector(const std::vector<std::vector<int>>& intVector) {
    std::vector<std::vector<double>> doubleVector;
    for (const auto& row : intVector) {
        std::vector<double> doubleRow(row.begin(), row.end());
        doubleVector.push_back(doubleRow);
    }
    return doubleVector;
}
