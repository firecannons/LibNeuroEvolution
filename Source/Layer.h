/*
    Programmer: Lucas Winkelman
    File: Layer.h
    Date: 9/22/2017
    Purpose: Layer.h contains declarations for the Layer class
        in LibNeuroEvolution.
*/

#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "LibNeuroEvolutionMath.h"
using namespace std ;

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
            void Pump ( Layer & DestLayer ) ;
            void Mutate ( float WeightShiftChance , float WeightNewChance , float WeightShiftRangeTop ,
                         float WeightShiftRangeBottom , float WeightNewRangeTop , float WeightNewRangeBottom ) ;
            unsigned int GetSizeOfLayer ( ) ;
            unsigned int GetSizeOfNextLayer ( ) ;
            float GetWeightAt ( unsigned int IndexInLayer , unsigned int IndexInNextLayer ) const ;

        private:
            vector < vector < float > > Weights ;
            vector < float > Values ;
            unsigned int SizeOfLayer ;
            unsigned int SizeOfNextLayer ;

            void RandomizeWeights ( ) ;

    };
}


#endif // LAYER_H
