#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "LibNeuroEvolutionMath.h"

namespace LNE
{
    const float RANDOMIZE_WEIGHT_NEW_MAX = 1 ;
    const float RANDOMIZE_WEIGHT_NEW_MIN = -1 ;
    class Layer
    {
        public:
            Layer ( unsigned int InSizeOfLayer , unsigned int InSizeOfNextLayer ) ;
            ~ Layer ( ) ;
            Layer ( const Layer & SourceLayer ) ;
            Layer & operator = ( const Layer & SourceLayer ) ;
            void SetAt ( unsigned int Position , float Value ) ;
            float GetAt ( unsigned int Position ) ;
            void Pump ( Layer & DestLayer )

        private:
            vector < vector < float > > Weights ;
            vector < float > Values ;
            unsigned int SizeOfLayer ;
            unsigned int SizeOfNextLayer ;

            RandomizeWeights ( ) ;

    };
}

#endif // LAYER_H
