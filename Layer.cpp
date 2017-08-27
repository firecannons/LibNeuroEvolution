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
        if ( this == & rhs )
        {
            return * this;
        }
        SizeOfLayer = SourceLayer . SizeOfLayer ;
        SizeOfNextLayer = SourceLayer . SizeOfNextLayer ;
        Weights = SourceLayer . Weights ;
        Value = SourceLayer . Values ;
        return *this;
    }

    Layer & Layer :: operator = ( const Layer & SourceLayer )
    {
        if ( this == & rhs )
        {
            return * this ;
        }
        SizeOfLayer = SourceLayer . SizeOfLayer ;
        SizeOfNextLayer = SourceLayer . SizeOfNextLayer ;
        Weights = SourceLayer . Weights ;
        Value = SourceLayer . Values ;
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
            DestLayer . SetAt ( NextLayerIterator , Sum ) ;
            NextLayerIterator = NextLayerIterator + 1 ;
        }
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
