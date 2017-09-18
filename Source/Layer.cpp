#include "Layer.h"

namespace LNE
{
    Layer :: Layer ( unsigned int InSizeOfLayer , unsigned int InSizeOfNextLayer )
    {
        SizeOfLayer = InSizeOfLayer ;
        SizeOfNextLayer = InSizeOfNextLayer ;
        Weights . resize ( SizeOfLayer ) ;
        unsigned int RowIterator = 0 ;
        while ( RowIterator < SizeOfLayer )
        {
            Weights [ RowIterator ] . resize ( SizeOfNextLayer ) ;
            RowIterator = RowIterator + 1 ;
        }
        Values . resize ( SizeOfLayer ) ;
        RandomizeWeights ( ) ;
    }

    Layer :: ~ Layer ( )
    {
    }

    Layer :: Layer ( const Layer & SourceLayer)
    {
        * this = SourceLayer ;
    }

    Layer & Layer :: operator = ( const Layer & SourceLayer )
    {
        if ( this == & SourceLayer )
        {
            return * this ;
        }
        SizeOfLayer = SourceLayer . SizeOfLayer ;
        SizeOfNextLayer = SourceLayer . SizeOfNextLayer ;
        Weights = SourceLayer . Weights ;
        Values = SourceLayer . Values ;
        return * this ;
    }

    void Layer :: SetAt ( unsigned int Position , float Value )
    {
        Values [ Position ] = Value ;
    }

    float Layer :: GetAt ( unsigned int Position )
    {
        return Values [ Position ] ;
    }

    void Layer :: Pump ( Layer & DestLayer )
    {
        unsigned int NextLayerIterator = 0 ;
        while ( NextLayerIterator < SizeOfNextLayer )
        {
            float Sum = 0 ;
            unsigned int RowIterator = 0 ;
            while ( RowIterator < SizeOfLayer )
            {
                Sum = Sum + Values [ RowIterator ] * Weights [ RowIterator ] [ NextLayerIterator ] ;
                RowIterator = RowIterator + 1 ;
            }
            Sum = Relu ( Sum ) ;
            //Sum = Heaviside ( Sum ) ;
            DestLayer . SetAt ( NextLayerIterator , Sum ) ;
            NextLayerIterator = NextLayerIterator + 1 ;
        }
    }

    void Layer :: Mutate ( float WeightShiftChance , float WeightNewChance , float WeightShiftRangeTop ,
            float WeightShiftRangeBottom , float WeightNewRangeTop , float WeightNewRangeBottom )
    {
        float WeightShiftRange = WeightShiftRangeTop - WeightShiftRangeBottom ;
        float WeightNewRange = WeightNewRangeTop - WeightNewRangeBottom ;
        unsigned int RowIterator = 0 ;
        while ( RowIterator < SizeOfLayer )
        {
            unsigned int NextLayerIterator = 0 ;
            while ( NextLayerIterator < SizeOfNextLayer )
            {
                float RandomNumber = GetProb ( ) ;
                if ( RandomNumber < WeightNewChance )
                {
                    float NewAmount = GetProb ( ) * WeightNewRange + WeightNewRangeBottom ;
                    Weights [ RowIterator ] [ NextLayerIterator ] = NewAmount ;
                }

                RandomNumber = GetProb ( ) ;
                if ( RandomNumber < WeightShiftChance )
                {
                    float StartingValue = Weights [ RowIterator ] [ NextLayerIterator ] ;
                    float ShiftAmount = GetProb ( ) * WeightShiftRange + WeightShiftRangeBottom ;
                    Weights [ RowIterator ] [ NextLayerIterator ] = StartingValue + ShiftAmount ;
                }
                NextLayerIterator = NextLayerIterator + 1 ;
            }
            RowIterator = RowIterator + 1 ;
        }
    }

    unsigned int Layer :: GetSizeOfLayer ( )
    {
        return SizeOfLayer ;
    }

    unsigned int Layer :: GetSizeOfNextLayer ( )
    {
        return SizeOfNextLayer ;
    }

    float Layer :: GetWeightAt ( unsigned int IndexInLayer , unsigned int IndexInNextLayer ) const
    {
        return Weights [ IndexInLayer ] [ IndexInNextLayer ] ;
    }

    void Layer :: RandomizeWeights ( )
    {
        float Difference = RANDOMIZE_WEIGHT_NEW_MAX - RANDOMIZE_WEIGHT_NEW_MIN ;
        unsigned int RowIterator = 0 ;
        while ( RowIterator < SizeOfLayer )
        {
            unsigned int NextLayerIterator = 0 ;
            while ( NextLayerIterator < SizeOfNextLayer )
            {
                Weights [ RowIterator ] [ NextLayerIterator ] = GetProb ( ) * Difference + RANDOMIZE_WEIGHT_NEW_MIN ;
                NextLayerIterator = NextLayerIterator + 1 ;
            }
            RowIterator = RowIterator + 1 ;
        }
    }
}
