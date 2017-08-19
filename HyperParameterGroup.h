#ifndef HYPERPARAMETERGROUP_H
#define HYPERPARAMETERGROUP_H

#include <vector>

namespace LNE
{
    const float WEIGHT_MAX_SHIFT = 0.1 ;
    const float WEIGHT_MIN_SHIFT = -0.1 ;
    const float NEW_WEIGHT_MAX = 1 ;
    const float NEW_WEIGHT_MIN = -1 ;
    const float WEIGHT_MAX = 5 ;
    const float WEIGHT_MIN = -5 ;
    const unsigned int MAX_LAYERS = 20 ;
    const unsigned int MIN_LAYERS = 2 ;
    const unsigned int MAX_NEURONS_IN_LAYER = 1000000 ;

    class HyperParameterGroup
    {
        public:
            HyperParameterGroup ( vector < unsigned int > & Sizes ) ;

            ~HyperParameterGroup ( ) ;

            HyperParameterGroup ( const HyperParameterGroup & other ) ;

            HyperParameterGroup & operator = ( const HyperParameterGroup & other ) ;



        private:
            float WeightMaxPositiveShift ;
            float WeightMaxNegativeShift ;
            vector < NeuralNetwork > Networks ;
    };

}

#endif // HYPERPARAMETERGROUP_H
