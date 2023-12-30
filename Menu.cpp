#include "Menu.h"
#include "GeneticAlgo.h"
#include "Data_parser.h"
#include "Brute_force.h"

void Menu::show_menu() {
    using namespace std;
    std::vector<std::vector<int>> init_vector;
    std::vector<int> path;

    DataGenerator generator;
    Graph graph(init_vector);

    std::string fromFile;
    std::string choice_s;

    double stop = 5;

    while (true) {
        std::cout
                << "Problem komiwojazera rozwiazywany metoda symulowanego wyrzazania.\nAutor: Jakub Blaszczynski #263966\n\n";
        std::cout << "0 - Wyjdz z programu\n";
        std::cout << "1 - Wczytaj macierz z pliku\n";
        std::cout << "2 - Wygeneruj macierz\n";
        std::cout << "3 - Wyswietl ostatnio wczytana z pliku lub wygenerowana macierz\n";
        std::cout << "4 - Uruchom symulowane wyrzazanie dla ostatnio wczytanej lub wygenerowanej macierzy i wyswietl wyniki\n";
        std::cout << "5 - Podaj kryterium stopu\n";
        std::cout << "6 - Ustaw wspolczynnik zmian temperatury\n";


        std::cout << ">";

        std::cin >> choice_s;
        while (!is_digit(choice_s)) {
            std::cout << "Podany ciag znakow nie jest liczba!\nWpisz liczbe\n>";
            std::cin >> choice_s;
        }
        int choice = std::stoi(choice_s);
        double a =0.8;



        switch (choice) {
            case 0:
                exit(0);
            case 1: {
                std::cout << "Podaj nazwe pliku do wczytania\n>";
                std::cin >> choice_s;
                Data_parser dataParser(choice_s);
                dataParser.openFile();
                graph.setGraph(dataParser.readFile());

                std::vector<std::vector<double>> double2DVector;
                for (const auto& row : graph.getGraph()) {
                    std::vector<double> doubleRow(row.begin(), row.end());
                    double2DVector.push_back(doubleRow);
                }
                GeneticAlgo geneticAlgo(double2DVector, 5);

//                graph.readGraph(choice_s);
            }

                break;
            case 2:{
                std::cout << "Podaj wielkosc macierzy (rozmiar MAX_CITIES)\n>";
                std::cin >> choice_s;
                while (!is_digit(choice_s)) {
                    std::cout << "Podany ciag znakow nie jest liczba!\nWpisz liczbe\n>";
                    std::cin >> choice_s;
                }
                graph.setGraph(generator.generate_data(atoi(choice_s.c_str())));
                std::vector<std::vector<double>> double2DVector;
                for (const auto& row : graph.getGraph()) {
                    std::vector<double> doubleRow(row.begin(), row.end());
                    double2DVector.push_back(doubleRow);
                }
                GeneticAlgo geneticAlgo(double2DVector, 5);
        }
                break;
            case 3:

                graph.printGraph();
                break;
            case 4: {
                std::vector<std::vector<double>> double2DVector;
                for (const auto& row : graph.getGraph()) {
                    std::vector<double> doubleRow(row.begin(), row.end());
                    double2DVector.push_back(doubleRow);
                }
                GeneticAlgo geneticAlgo(double2DVector, 5);
                for(int i=0;i<100;i++) {
                    geneticAlgo.calculateFitness();
                    geneticAlgo.normalizeFitness();
                    geneticAlgo.nextGeneration();

                }
                cout<<endl<<geneticAlgo.recordDistance<< endl;
                for(int i=0;i<geneticAlgo.bestEver.size();i++)
                {
                    cout<<geneticAlgo.bestEver[i]<<" ";
                }
                cout<<endl;
//                for(int i=0;i<geneticAlgo.bestEver.size();i++)
//                {
//                    cout<<geneticAlgo.bestCheck[i]<<" ";
//                }
//                cout<<endl;

//                SimulatedAnnealing simulatedAnnealing(graph.getGraph());

//                for(int h=0;h<10;h++) {

//                    graph.setGraph(generator.generate_data(choice_ss));




                    int sV, e, t, iE;
//                    std::cout << "Podaj startowy wierzcholek \n";
//                    cin >> sV;
//                    std::cout << "Podaj alfe \n";
//                    cin >> a;
//                    std::cout << "Podaj liczbe epok \n";
//                    cin >> e;
//                    std::cout << "Podaj liczbe iteracji w epoce \n";
//                    cin >> iE;
//                    std::cout << "Podaj startowa temperature \n";
//                    cin >> t;
//                simulatedAnnealing.startAlgorithm(sV, a, e, iE, t);





//                    simulatedAnnealing.showPath(0);
//                cout<<endl<<simulatedAnnealing.getFinalCost()<<endl;
//                    simulatedAnnealing.setTemperature(simulatedAnnealing.calculateTemperature());

                    auto start = std::chrono::high_resolution_clock::now();
//                simulatedAnnealing.startAlgorithm(0, 0.99, 1000, 100000, 1000000, 120 );
//                auto end = std::chrono::high_resolution_clock::now();
//                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//
//
//                cout<<endl<<simulatedAnnealing.getFinalCost()<<endl;
//                for(int i=0;i<graph.getNumOfVertices()+1;i++)
//                    cout<<simulatedAnnealing.getGlobalPath()->at(i)<<"->";
//
//                    cout<<endl<<duration.count()<<endl;
//                    cout<<simulatedAnnealing.getTemperature()<<endl;

//                }
            }

                break;
            case 5: {
                Brute_force bruteForce(graph.getGraph());
                bruteForce.perform_brute_force();
                cout<<bruteForce.get_lowest_path()<<endl;
                cout<<bruteForce.get_lowest_cost()<<endl;
            }

                break;
            case 6: {
                cin>>a;
            }


                break;
            default:
                std::cout << "Program nie zawiera funkcji dla podanej liczby!\n";
                break;
        }
    }

}

bool Menu::is_digit(std::string input) {

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    return true;

}