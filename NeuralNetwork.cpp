#include "NeuralNetwork.h"

namespace LNE
{

    NeuralNetwork :: NeuralNetwork ( vector < unsigned int > & InSizes )
    {
        if ( AreSizesOk ( InSizes ) )
        {
            Fitness = DEFAULT_FITNESS ;
            NumberLayersInNetwork = InSizes . size ( ) ;
            unsigned int LayerIterator = 0 ;
            Layers . resize ( NumberLayersInNetwork ) ;
            while ( LayerIterator < InSizes . size ( ) )
            {
                if ( LayerIterator == InSizes . size ( ) - 1 )
                {
                    Layers [ LayerIterator ] = new Layer ( InSizes [ LayerIterator ] , 0 ) ;
                }
                else
                {
                    Layers [ LayerIterator ] = new Layer ( InSizes [ LayerIterator ] , InSizes [ LayerIterator + 1 ] ) ;
                }
                LayerIterator = LayerIterator + 1 ;
            }
        }
    }

    NeuralNetwork :: ~ NeuralNetwork ( )
    {
        DeleteLayers ( ) ;
    }

    NeuralNetwork :: NeuralNetwork ( const NeuralNetwork & SourceNetwork )
    {
        * this = SourceNetwork ;
    }

    NeuralNetwork & NeuralNetwork :: operator = ( const NeuralNetwork & SourceNetwork )
    {
        if ( this == & rhs )
        {
            return * this ;
        }
        Fitness = SourceNetwork . Fitness ;
        NumberLayersInNetwork = SourceNetwork . NumberLayersInNetwork ;
        DeleteLayers ( ) ;
        CopyLayers ( SourceNetwork . Layers ) ;
        return * this;
    }

    void NeuralNetwork :: Mutate ( WeightShiftChance , WeightNewChance , WeightShiftRangeTop , WeightShiftRangeBottom ,
                         NewWeightRangeTop , NewWeightRangeBottom )
    {
    unsigned int LayerIterator = 0 ;
        while ( LayerIterator < NumberLayersInNetwork )
        {
            Layers [ LayerIterator ] -> Mutate ( WeightShiftChance , WeightNewChance , WeightShiftRangeTop , WeightShiftRangeBottom ,
                                                     NewWeightRangeTop , NewWeightRangeBottom ) ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

    void NeuralNetwork :: SetInput ( unsigned int Position , float Value )
    {
        Layers [ 0 ] -> SetAt ( Position , Value ) ;
    }

    float NeuralNetwork :: GetOutput ( unsigned int Position )
    {
        float Output = 0 ;
        Output = Layers [ NumberLayersInNetwork ] -> GetAt ( Position ) ;
        return Output ;
    }

    void NeuralNetwork :: Pump ( )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < NumberLayersInNetwork - 1 )
        {
            Layers [ LayerIterator ] -> Pump ( Layers [ LayerIterator + 1 ] ) ;
        }
    }

    bool NeuralNetwork :: AreSizesOk ( vector < unsigned int > & InSizes ) const
    {
        bool Output = true ;
        if ( InSizes . size ( ) > MAX_LAYERS )
        {
            Output = false ;
        }
        else if ( InSizes . size ( ) < MIN_LAYERS )
        {
            Output = false ;
        }
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < InSizes . size ( ) )
        {
            if ( InSizes [ LayerIterator ] . size ( ) > MAX_NEURONS_IN_LAYER )
            {
                Output = false ;
            }
            LayerIterator = LayerIterator + 1 ;
        }
        return Output ;
    }

    void NeuralNetwork :: CopyLayers ( vector < Layer * > & SourceLayers )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < SourceLayers . size ( ) )
        {
            Layers [ LayerIterator ] = new Layer ( SourceLayers [ LayerIterator ] ) ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

    void NeuralNetwork :: DeleteLayers ( )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < NumberLayersInNetwork )
        {
            delete Layers [ LayerIterator ] ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

}
