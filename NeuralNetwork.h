#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"

namespace LNE
{
    const unsigned int MAX_LAYERS = 50 ;
    const unsigned int MIN_LAYERS = 2 ;
    const unsigned int MAX_NEURONS_IN_LAYER = 1000000 ;
    const float WEIGHT_MAX = 5 ;
    const float WEIGHT_MIN = -5 ;

    const float DEFAULT_FITNESS = 0 ;

    class NeuralNetwork
    {
        public:
            NeuralNetwork ( vector < unsigned int > & InSizes ) ;
            ~ NeuralNetwork ( ) ;
            NeuralNetwork ( const NeuralNetwork & SourceNetwork ) ;
            NeuralNetwork & operator = ( const NeuralNetwork & SourceNetwork ) ;

        private:
            float Fitness ;
            unsigned int NumberLayersInNetwork ;
            vector < Layer * > Layers ;

            void DeleteLayers ( ) ;
    } ;
}

#endif // NEURALNETWORK_H
