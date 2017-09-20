/*
    Programmer: Lucas Winkelman
    File: Population.h
    Date: 9/19/2017
    Purpose: Population.h contains definitions for the Population class
        in LibNeuroEvolution.
*/

#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "HyperParameterGroup.h"
using namespace std ;

namespace LNE
{
        // Coefficient of the worst HyperParameterGroups to kill each generation
        //     they are regenerated.
    const float POPULATION_KILL_AMOUNT = 0.1 ;
		
        // Coefficient of the worst HyperParameterGroups to mutate each generation
        //     they are regenerated.
    const float POPULATION_MUTATE_AMOUNT = 0.1 ;


    class Population
    {
        public:
            // Desc: The Population constructor creates a Population based
            //     on given parameters.
            // Pre: InSizes must be of least size 2 (there must be two or
            //     more layers in the network).  Each element must be
            //     greater than 0.
            // Post: A Population class based on the given parameters is
            //     constructed.
            Population( vector < unsigned int > InSizes ,
                unsigned int InNumberGroups ,
                unsigned int InNumberNetworksPerGroup ,
                unsigned int InGroupEvolutionGenerations ) ;
            
            // Desc: The Population destructor destroys a Population
            // Pre: The Population must exist.
            // Post: The Population is destroyed.
            ~ Population ( ) ;
            
            // Desc: The Population copy constructor constructs a Population
            //     based on another Population.
            // Pre: The source Population must exist.
            // Post: The a new Population is constructed.
            Population( const Population & SourcePopulation ) ;
            
            // Desc: The = operator will make the destination Population
            //     equal to the source operator.
            // Pre: The source population must exist.
            // Post: The destination Population will have be equal
            //     to the source Population.
            Population & operator = ( const Population & SourcePopulation ) ;

            unsigned int GetCurrentGeneration ( ) const ;

            bool AreNetworksDoneRunning ( ) const ;

            NeuralNetwork * GetCurrentNetwork ( ) const ;

            void ToNextNetwork ( ) ;

            void EndGeneration ( ) ;

            float GetBestFitness ( ) ;

            NeuralNetwork * GetBestNetwork ( ) const ;





        private:
            vector < HyperParameterGroup * > Groups ;
            unsigned int CurrentGroupIndex ;
            unsigned int CurrentGeneration ;
            unsigned int NumberGroups ;
            unsigned int NumberNetworksPerGroup ;
            unsigned int GroupEvolutionGenerations ;


            void Evolve ( ) ;
            void SortGroups ( ) ;
            void KillGroups ( ) ;
            void MutateGroups ( ) ;
            void EvolveGroups ( ) ;
            void EvolveNetworks ( ) ;
            void ResetIndexes ( ) ;
            void DeleteGroups ( ) ;
            void CopyGroups ( const vector < HyperParameterGroup * > & SourceGroups ) ;

    };

}




#endif // POPULATION_H
