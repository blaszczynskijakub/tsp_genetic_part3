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
    GeneticAlgo * genPtr;
    std::vector<std::vector<double>> double2DVector;



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
                while(!double2DVector.empty())
                {
                    double2DVector.pop_back();
                }
                for (const auto& row : graph.getGraph()) {
                    std::vector<double> doubleRow(row.begin(), row.end());
                    double2DVector.push_back(doubleRow);
                }

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
                while(!double2DVector.empty())
                {
                    double2DVector.pop_back();
                }
                for (const auto& row : graph.getGraph()) {
                    std::vector<double> doubleRow(row.begin(), row.end());
                    double2DVector.push_back(doubleRow);
                }



        }
                break;
            case 3:

                graph.printGraph();
                break;
            case 4: {

                genPtr = new GeneticAlgo(double2DVector, graph.getNumOfVertices());
cout<< graph.getNumOfVertices();
                cout<< double2DVector.size();

                for(int i=0;i<1000;i++) {
                    genPtr->calculateFitness();
                    genPtr->normalizeFitness();
                    genPtr->nextGeneration();
//                    cout<<endl<<genPtr->recordDistance<< endl;
//                    for(int i=0;i<genPtr->bestEver.size();i++)
//                    {
//                        cout<<genPtr->population[24][i]<<" ";
//                    }
//                    cout<<endl;
                }
                cout<<endl<<genPtr->recordDistance<< endl;
                for(int i=0;i<genPtr->bestEver.size();i++)
                {
                    cout<<genPtr->bestEver[i]<<" ";
                }
                cout<<endl;
                delete genPtr;
//
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