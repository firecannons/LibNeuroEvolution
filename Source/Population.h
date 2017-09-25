/*
    Programmer: Lucas Winkelman
    File: Population.h
    Date: 9/19/2017
    Purpose: Population.h contains declarations for the Population class
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
            //     on given parameters.  InSizes should be an array with
            //     each element being the height of a layer in the neural
            //     network.
            // Pre: The minimum size for a neural network is two layers
            //     and each layer must have at least one neuron.
            //     InNumberGroups needs to be at least 10,
            //     InNumberNetworksPerGroup needs to be greater than 2,
            //     InGroupEvolutionGenerations needs to be greater than 1.
            Population( vector < unsigned int > InSizes ,
                unsigned int InNumberGroups ,
                unsigned int InNumberNetworksPerGroup ,
                unsigned int InGroupEvolutionGenerations ) ;
            
            // Desc: The Population destructor destroys a Population.
            ~ Population ( ) ;
            
            // Desc: The Population copy constructor constructs a Population
            //     based on another Population.
            Population( const Population & SourcePopulation ) ;
            
            // Desc: The = operator will make the destination Population
            //     equal to the source operator.
            Population & operator = ( const Population & SourcePopulation ) ;

			// Desc: The GetCurrentGeneration function returns the value of
			//     the CurrentGeneration variable.
            unsigned int GetCurrentGeneration ( ) const ;
            
            // Desc: The AreNetworksDoneRunning function returns the value
            //     of whether the networks in this Population have all been
            //     evaluated.  This should be in a guard statement of a loop
            //     with GetCurrentNetwork.
            bool AreNetworksDoneRunning ( ) const ;
            
            // Desc: The GetCurrentNetwork function will return the a pointer
            //     to the network in this Population who's turn it is to be
            //     evaluated.  This should be used in a loop for evaluating
            //     all the networks.
            NeuralNetwork * GetCurrentNetwork ( ) const ;
            
            // Desc: The ToNextNetwork function will move to the next network
            //      to be evaluated.
            void ToNextNetwork ( ) ;
            
            // Desc: The EndGeneration function will perform evolutionary
            //     computing on the networks and networks groups.  It will
            //     also prepare this Population for the next generation.
            void EndGeneration ( ) ;
            
            // Desc: The GetBestFitness function will get the best fitness
            //     value of all the fitness values of all the neural networks.
            float GetBestFitness ( ) ;
            
            // Desc: The GetBestNetwork function will the get the network with
            //     the highest fitness value of any network in any group of
            //     this Population.  This should be called after a call to
            //     EndGeneration and not during the fitness evaluation loop.
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
            void CopyGroups ( const vector < HyperParameterGroup * >
                & SourceGroups ) ;

    };

}




#endif // POPULATION_H
