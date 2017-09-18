#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "HyperParameterGroup.h"
using namespace std ;

namespace LNE
{
    const float POPULATION_KILL_AMOUNT = 0.1 ;
    const float POPULATION_MUTATE_AMOUNT = 0.1 ;


    class Population
    {
        public:
            Population( vector < unsigned int > InSizes , unsigned int InNumberGroups ,
                       unsigned int InNumberNetworksPerGroup , unsigned int InGroupEvolutionGenerations ) ;

            ~ Population ( ) ;

            Population( const Population & SourcePopulation ) ;

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
