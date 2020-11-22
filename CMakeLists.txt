cmake_minimum_required(VERSION 3.10)
project(MVP_DataAnalyzer)

set(CMAKE_CXX_STANDARD 98)

add_executable(MVP_DataAnalyzer main.cpp iCommand.cpp iCommand.h dnaSequence.cpp nucleotide.cpp indexed_dna_sequence.h indexed_dna_sequence.cpp command_controller.h command_controller.cpp lastReference.cpp lastReference.h)