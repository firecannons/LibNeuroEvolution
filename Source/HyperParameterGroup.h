/*
    Programmer: Lucas Winkelman
    File: HyperParameterGroup.h
    Date: 9/22/2017
    Purpose: HyperParameterGroup.h contains declarations for the
        HyperParameterGroup class in LibNeuroEvolution.
*/

#ifndef HYPERPARAMETERGROUP_H
#define HYPERPARAMETERGROUP_H

#include <vector>
#include <cmath>
#include "NeuralNetwork.h"
using namespace std ;

namespace LNE
{
    const float WEIGHT_SHIFT_RANGE_TOP_MAX = 0.5 ;
    const float WEIGHT_SHIFT_RANGE_TOP_MIN = -0.4 ;
    const float DEFAULT_WEIGHT_SHIFT_RANGE_TOP = 0.05 ;
    const float WEIGHT_SHIFT_RANGE_TOP_SHIFT_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_RANGE_TOP_NEW_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_RANGE_TOP_SHIFT_MIN = -0.1 ;
    const float WEIGHT_SHIFT_RANGE_TOP_SHIFT_MAX = 0.1 ;
    const float WEIGHT_SHIFT_RANGE_TOP_NEW_MIN = -0.4 ;
    const float WEIGHT_SHIFT_RANGE_TOP_NEW_MAX = 0.5 ;

    const float WEIGHT_SHIFT_RANGE_BOTTOM_MAX = 0.4 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_MIN = -0.5 ;
    const float DEFAULT_WEIGHT_SHIFT_RANGE_BOTTOM = -0.05 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_NEW_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MIN = -0.1 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MAX = 0.1 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MIN = -0.5 ;
    const float WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MAX = 0.4 ;

    const float NEW_WEIGHT_RANGE_TOP_MAX = 1 ;
    const float NEW_WEIGHT_RANGE_TOP_MIN = -0.9 ;
    const float DEFAULT_NEW_WEIGHT_RANGE_TOP = 0.5 ;
    const float NEW_WEIGHT_RANGE_TOP_SHIFT_CHANCE = 0.3 ;
    const float NEW_WEIGHT_RANGE_TOP_NEW_CHANCE = 0.3 ;
    const float NEW_WEIGHT_RANGE_TOP_SHIFT_MIN = -0.1 ;
    const float NEW_WEIGHT_RANGE_TOP_SHIFT_MAX = 0.1 ;
    const float NEW_WEIGHT_RANGE_TOP_NEW_MIN = -0.9 ;
    const float NEW_WEIGHT_RANGE_TOP_NEW_MAX = 1 ;

    const float NEW_WEIGHT_RANGE_BOTTOM_MAX = 0.9 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_MIN = -1 ;
    const float DEFAULT_NEW_WEIGHT_RANGE_BOTTOM = -0.5 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_SHIFT_CHANCE = 0.3 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_NEW_CHANCE = 0.3 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_SHIFT_MIN = -0.1 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_SHIFT_MAX = 0.1 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_NEW_MIN = -1 ;
    const float NEW_WEIGHT_RANGE_BOTTOM_NEW_MAX = 0.9 ;

    const float WEIGHT_SHIFT_CHANCE_MAX = 1 ;
    const float WEIGHT_SHIFT_CHANCE_MIN = 0 ;
    const float DEFAULT_WEIGHT_SHIFT_CHANCE = 0.5 ;
    const float WEIGHT_SHIFT_CHANCE_SHIFT_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_CHANCE_NEW_CHANCE = 0.3 ;
    const float WEIGHT_SHIFT_CHANCE_SHIFT_MIN = -0.1 ;
    const float WEIGHT_SHIFT_CHANCE_SHIFT_MAX = 0.1 ;
    const float WEIGHT_SHIFT_CHANCE_NEW_MIN = 0 ;
    const float WEIGHT_SHIFT_CHANCE_NEW_MAX = 1 ;

    const float WEIGHT_NEW_CHANCE_MAX = 1 ;
    const float WEIGHT_NEW_CHANCE_MIN = 0 ;
    const float DEFAULT_WEIGHT_NEW_CHANCE = 0.5 ;
    const float WEIGHT_NEW_CHANCE_SHIFT_CHANCE = 0.3 ;
    const float WEIGHT_NEW_CHANCE_NEW_CHANCE = 0.3 ;
    const float WEIGHT_NEW_CHANCE_SHIFT_MIN = -0.1 ;
    const float WEIGHT_NEW_CHANCE_SHIFT_MAX = 0.1 ;
    const float WEIGHT_NEW_CHANCE_NEW_MIN = 0 ;
    const float WEIGHT_NEW_CHANCE_NEW_MAX = 1 ;


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

            NeuralNetwork * GetBestNetwork ( ) const ;

            bool AreNetworksDoneRunning ( ) const ;

            NeuralNetwork * GetCurrentNetwork ( ) const ;

            void EndGeneration ( ) ;

            void Mutate ( ) ;

            void ResetIndexes ( ) ;

            void RandomizeValues ( ) ;



        private:
            unsigned int CurrentNetworkIndex ;
            float WeightShiftRangeTop ;
            float WeightShiftRangeBottom ;
            float NewWeightRangeTop ;
            float NewWeightRangeBottom ;
            float KillRatio ;
            float MutateRatio ;
            float WeightShiftChance ;
            float WeightNewChance ;
            unsigned int NumberNetworksPerGroup ;
            vector < NeuralNetwork * > Networks ;

            void MutateWeightNewChance ( ) ;
            void MutateWeightShiftChance ( ) ;
            void ResolveNewWeightRange ( ) ;
            void MutateNewWeightRangeTop ( ) ;
            void MutateNewWeightRangeBottom ( ) ;
            void ResolveWeightShiftRange ( ) ;
            void MutateWeightShiftRangeTop ( ) ;
            void MutateWeightShiftRangeBottom ( ) ;
            void MutateKillRatio ( ) ;
            void MutateMutateRatio ( ) ;
            void DeleteNetworks ( ) ;
            void CopyNetworks ( const vector < NeuralNetwork * > & SourceNetworks ) ;
            void KillNetworks ( ) ;
            void MutateNetworks ( ) ;

    };

}


#endif // HYPERPARAMETERGROUP_H
