#ifndef HYPERPARAMETERGROUP_H
#define HYPERPARAMETERGROUP_H

#include <vector>
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
    const float WEIGHT_MAX = 5 ;
    const float WEIGHT_MIN = -5 ;
    const unsigned int MAX_LAYERS = 50 ;
    const unsigned int MIN_LAYERS = 2 ;
    const unsigned int MAX_NEURONS_IN_LAYER = 1000000 ;
    const float KILL_RATIO_MAX = 1 ;
    const float KILL_RATIO_MIN = 0 ;
    const float MUTATE_RATIO_MAX = 1 ;
    const float MUTATE_RATIO_MIN = 0 ;
    const float DEFAULT_KILL_RATIO = 0.5 ;
    const float DEFAULT_MUTATE_RATIO = 0.5 ;


    class HyperParameterGroup
    {
        public:
            HyperParameterGroup ( vector < unsigned int > & InSizes , unsigned int InNumberNetworksPerGroup ) ;

            ~HyperParameterGroup ( ) ;

            HyperParameterGroup ( const HyperParameterGroup & other ) ;

            HyperParameterGroup & operator = ( const HyperParameterGroup & other ) ;
            
            void ToNextNetwork ( ) ;
            
            unsigned int GetCurrentNetworkIndex ( ) const ;



        private:
            float CurrentNetworkIndex ;
            float MaxWeightShift ;
            float MinWeightShift ;
            float NewWeightMax ;
            float NewWeightMin ;
            float KillRatio ;
            float MutateRatio ;
            unsigned int NumberNetworks ;
            vector < NeuralNetwork * > Networks ;
            
            DeleteNetworks ( ) ;
            CopyNetworks ( vector < NeuralNetwork * > Networks ) ;
            
    };

}

#endif // HYPERPARAMETERGROUP_H
