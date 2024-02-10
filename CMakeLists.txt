cmake_minimum_required(VERSION 3.24)
project(tsp_genetic_part3)

set(CMAKE_CXX_STANDARD 17)

add_executable(tsp_genetic_part3 main.cpp GeneticAlgo.h GeneticAlgo.cpp Data_parser.cpp DataGenerator.cpp FileReader.cpp Graph.cpp Menu.cpp OptionMenu.cpp Time_measure.cpp Write_to_csv.cpp )