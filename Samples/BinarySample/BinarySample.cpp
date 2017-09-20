/*
	Programmer: Lucas Winkelman
	File: BinarySample.cpp
	Date: 9/19/2017
	Purpose: BinarySample is an example usage of the LibNeuroEvolution library.
		  It will first evolve networks to flip an input between 0 and 1.  Then it
		  will let the user input a 1 or 0 and flip it.
*/

// Necessary included library for BinarySample
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "LibNeuroEvolution.h"
using namespace LNE ;
using namespace std ;

// Number of HyperParameterGroups we will have in our Population
const unsigned int NUMBER_GROUPS = 40 ;

// Number of networks in the HyperParameterGroup
const unsigned int NUMBER_NETWORKS = 30 ;

// Number of generations per evolution of HyperParameterGroups
//     in our Population
const unsigned int GROUP_EVOLUTION_GENERATIONS = 5 ;

// Number when entered will quit the program
const unsigned int QUIT_PROGRAM_NUMBER = 2 ;

// Accuracy to acheive before training ends
const float STOP_TRAIN_ACCURACY = -0.001 ;


int main ( )
{
		// Randomize RNG
    srand ( time ( NULL ) ) ;
		
		// Each element in Sizes will represent the size of a layer
		//     in the network.  Our network will have only an input layer
		//     and an output layer.  The input layer will be size 2 and the output
		//     layer will be size 1.
    vector < unsigned int > Sizes ;
    Sizes . push_back ( 2 ) ;
    Sizes . push_back ( 1 ) ;
		
		// Create a Population which contains HyperParameterGroups and networks
    Population MyPop ( Sizes , NUMBER_GROUPS , NUMBER_NETWORKS ,
		    GROUP_EVOLUTION_GENERATIONS ) ;
		
		// *** Evolve networks ***
		
    unsigned int GenerationIterator = 0 ;
		// Check to see if the best fitness of any network is good enough to quit
		//     evolution
    while ( MyPop . GetBestFitness ( ) < STOP_TRAIN_ACCURACY )
    {
        cout << "Generation: " << MyPop . GetCurrentGeneration ( ) <<
            "  Best Fitness: " << MyPop . GetBestFitness ( ) << endl ;
						
				// Check to see if we have evaluated all the networks
        while ( MyPop . AreNetworksDoneRunning ( ) == false )
        {
            float Output = 0 ;
            float Cost = 0 ;
						
						// Get the current network from the MyPop
            NeuralNetwork * CurrentNetwork = MyPop . GetCurrentNetwork ( ) ;
						
						// Input a 0 in position 0 and a 1 in position 1 in the input
						//     layer. The 1 is just for bias in the neural network.
            CurrentNetwork -> SetInput ( 0 , 0 ) ;
            CurrentNetwork -> SetInput ( 1 , 1 ) ;
						
						// Run the inputs through the network to the output layer
            CurrentNetwork -> Pump ( ) ;
						
						// Get output in position 0
            Output = CurrentNetwork -> GetOutput ( 0 ) ;
						
						// Compare Output with 1 and calculate cost
            Cost = Cost - abs ( Output - 1 ) ;
						
						// Input a 1 into position 0 and a 1 into position 1 for bias.
            CurrentNetwork -> SetInput ( 0 , 1 ) ;
            CurrentNetwork -> SetInput ( 1 , 1 ) ;
            CurrentNetwork -> Pump ( ) ;
            Output = CurrentNetwork -> GetOutput ( 0 ) ;
						
						// Compare output with 0
            Cost = Cost - abs ( Output - 0 ) ;
						
						// Set the fitness value for this network
            CurrentNetwork -> SetFitness ( Cost ) ;
						
						// MyPop will move to the next network
            MyPop . ToNextNetwork ( ) ;
        }
				
				// Move to next generation
        MyPop . EndGeneration ( ) ;
				
        GenerationIterator = GenerationIterator + 1 ;
    }

		// *** Now User Input ***
		
		// Get the network with greatest fitness
    NeuralNetwork * BestNetwork = MyPop . GetBestNetwork ( ) ;
		
    unsigned int Input = 0 ;
    while ( Input != 2 )
    {
				// Output prompt
        cout << "Input a 0 or 1 and it will flip it to the opposite or input a 2 to quit the program: " ;
        cin >> Input ;
        if ( Input == 0 || Input == 1 )
        {
            float Output = 0 ;
						
						// Same process as before
            BestNetwork -> SetInput ( 0 , Input ) ;
            BestNetwork -> SetInput ( 1 , 1 ) ;
            BestNetwork -> Pump ( ) ;
            Output = BestNetwork -> GetOutput ( 0 ) ;
            cout << "Output: " << Output << endl ;
        }
    }

    return 0 ;
}
