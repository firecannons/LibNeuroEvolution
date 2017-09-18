#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "LibNeuroEvolution.h"
using namespace LNE ;

using namespace std ;

const unsigned int NUMBER_GROUPS = 40 ;
const unsigned int NUMBER_NETWORKS = 30 ;
const unsigned int GROUP_EVOLUTION_GENERATIONS = 5 ;
const unsigned int QUIT_PROGRAM_NUMBER = 2 ;
const float STOP_TRAIN_ACCURACY = -0.001 ;

int main ( )
{
    srand ( time ( NULL ) ) ;
    vector < unsigned int > Sizes ;
    Sizes . push_back ( 2 ) ;
    Sizes . push_back ( 1 ) ;

    Population MyPop ( Sizes , NUMBER_GROUPS , NUMBER_NETWORKS , GROUP_EVOLUTION_GENERATIONS ) ;
    unsigned int GenerationIterator = 0 ;
    while ( MyPop . GetBestFitness ( ) < STOP_TRAIN_ACCURACY )
    {
        cout << "Generation: " << MyPop . GetCurrentGeneration ( ) <<
            "  Best Fitness: " << MyPop . GetBestFitness ( ) << endl ;
        unsigned int NetworkIterator = 0 ;
        while ( MyPop . AreNetworksDoneRunning ( ) == false )
        {
            float Output = 0 ;
            float Cost = 0 ;
            NeuralNetwork * CurrentNetwork = MyPop . GetCurrentNetwork ( ) ;

            CurrentNetwork -> SetInput ( 0 , 0 ) ;
            CurrentNetwork -> SetInput ( 1 , 1 ) ;
            CurrentNetwork -> Pump ( ) ;
            Output = CurrentNetwork -> GetOutput ( 0 ) ;
            Cost = Cost - abs ( Output - 1 ) ;

            CurrentNetwork -> SetInput ( 0 , 1 ) ;
            CurrentNetwork -> SetInput ( 1 , 1 ) ;
            CurrentNetwork -> Pump ( ) ;
            Output = CurrentNetwork -> GetOutput ( 0 ) ;
            Cost = Cost - abs ( Output - 0 ) ;

            CurrentNetwork -> SetFitness ( Cost ) ;

            MyPop . ToNextNetwork ( ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
        MyPop . EndGeneration ( ) ;
        GenerationIterator = GenerationIterator + 1 ;
    }

    NeuralNetwork * BestNetwork = MyPop . GetBestNetwork ( ) ;
    unsigned int Input = 0 ;
    while ( Input != 2 )
    {
        cout << "Input a 0 or 1 and it will flip it to the opposite or input a 2 to quit the program: " ;
        cin >> Input ;
        if ( Input == 0 || Input == 1 )
        {
            float Output = 0 ;
            BestNetwork -> SetInput ( 0 , Input ) ;
            BestNetwork -> SetInput ( 1 , 1 ) ;
            BestNetwork -> Pump ( ) ;
            Output = BestNetwork -> GetOutput ( 0 ) ;
            cout << "Output: " << Output << endl ;
        }
    }

    return 0 ;
}
