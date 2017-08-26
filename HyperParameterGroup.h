#ifndef HYPERPARAMETERGROUP_H
#define HYPERPARAMETERGROUP_H

#include <vector>
#include "LibNeuroEvolution.h"
#include "NeuralNetwork.h"
using namespace std ;

namespace LNE
{
    const float WEIGHT_SHIFT_MAX = 0.1 ;
    const float WEIGHT_SHIFT_MIN = -0.1 ;
    const float DEFAULT_WEIGHT_MAX_SHIFT = 0.05 ;
    const float DEFAULT_WEIGHT_MIN_SHIFT = -0.05 ;
    const float NEW_WEIGHT_MAX = 1 ;
    const float NEW_WEIGHT_MIN = -1 ;
    const float DEFAULT_NEW_WEIGHT_MAX = 0.5 ;
    const float DEFAULT_NEW_WEIGHT_MIN = -0.5 ;

    const float WEIGHT_SHIFT_CHANCE_MAX = 1 ;
    const float WEIGHT_SHIFT_CHANCE_MIN = 0 ;
    const float DEFAULT_WEIGHT_SHIFT_CHANCE = 0.3 ;
    const float WEIGHT_NEW_CHANCE_MAX = 1 ;
    const float WEIGHT_NEW_CHANCE_MIN = 0 ;
    const float DEFAULT_WEIGHT_NEW_CHANCE = 0.3 ;

    const float DEFAULT_KILL_RATIO = 0.5 ;
    const float KILL_RATIO_MAX = 1 ;
    const float KILL_RATIO_MIN = 0 ;
    const float KILL_RATIO_SHIFT_MAX = 0.2 ;
    const float KILL_RATIO_SHIFT_MIN = -0.2 ;
    const float KILL_RATIO_NEW_MAX = 1 ;
    const float KILL_RATIO_NEW_MIN = 0 ;
    const float KILL_RATIO_SHIFT_CHANCE = 0.3 ;
    const float KILL_RATIO_NEW_CHANCE = 0.3 ;

    const float DEFAULT_MUTATE_RATIO = 0.5 ;
    const float MUTATE_RATIO_MAX = 1 ;
    const float MUTATE_RATIO_MIN = 0 ;
    const float MUTATE_RATIO_SHIFT_MAX = 0.2 ;
    const float MUTATE_RATIO_SHIFT_MIN = -0.2 ;
    const float MUTATE_RATIO_NEW_MAX = 1 ;
    const float MUTATE_RATIO_NEW_MIN = 0 ;
    const float MUTATE_RATIO_SHIFT_CHANCE = 0.3 ;
    const float MUTATE_RATIO_NEW_CHANCE = 0.3 ;

    class HyperParameterGroup
    {
        public:
            HyperParameterGroup ( vector < unsigned int > & InSizes , unsigned int InNumberNetworksPerGroup ) ;

            ~HyperParameterGroup ( ) ;

            HyperParameterGroup ( const HyperParameterGroup & SourceGroup ) ;

            HyperParameterGroup & operator = ( const HyperParameterGroup & SourceGroup ) ;

            void ToNextNetwork ( ) ;

            unsigned int GetCurrentNetworkIndex ( ) const ;

            void SortNetworks ( ) ;

            float GetBestNetworkFitness ( ) const ;

            bool AreNetworksDoneRunning ( ) const ;

            NeuralNetwork * GetCurrentNetwork ( ) const ;

            void EndGeneration ( ) ;

            void Mutate ( ) ;



        private:
            unsigned int CurrentNetworkIndex ;
            float MaxWeightShift ;
            float MinWeightShift ;
            float NewWeightMax ;
            float NewWeightMin ;
            float KillRatio ;
            float MutateRatio ;
            float WeightShiftChance ;
            float WeightNewChance ;
            unsigned int NumberNetworksPerGroup ;
            vector < NeuralNetwork * > Networks ;

            void MutateKillRatio ( ) ;
            void MutateMutateRatio ( ) ;
            void DeleteNetworks ( ) ;
            void CopyNetworks ( vector < NeuralNetwork * > SourceNetworks ) ;
            void KillNetworks ( ) ;
            void MutateNetworks ( ) ;

    };

}

#endif // HYPERPARAMETERGROUP_H
