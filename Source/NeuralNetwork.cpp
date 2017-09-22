/*
    Programmer: Lucas Winkelman
    File: NeuralNetwork.cpp
    Date: 9/22/2017
    Purpose: NeuralNetwork.cpp contains definitions for the NeuralNetwork class
        in LibNeuroEvolution.
*/

#include "NeuralNetwork.h"

namespace LNE
{

    NeuralNetwork :: NeuralNetwork ( vector < unsigned int > & InSizes )
    {
        if ( AreSizesOk ( InSizes ) )
        {
            Fitness = DEFAULT_FITNESS ;
            NumberLayersInNetwork = InSizes . size ( ) ;
            Layers . resize ( NumberLayersInNetwork ) ;
            unsigned int LayerIterator = 0 ;
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
        NumberLayersInNetwork = 0 ;
        * this = SourceNetwork ;
    }

    NeuralNetwork & NeuralNetwork :: operator = ( const NeuralNetwork & SourceNetwork )
    {
        if ( this == & SourceNetwork )
        {
            return * this ;
        }
        Fitness = SourceNetwork . Fitness ;
        DeleteLayers ( ) ;
        CopyLayers ( SourceNetwork . Layers ) ;
        NumberLayersInNetwork = SourceNetwork . NumberLayersInNetwork ;
        return * this;
    }

    void NeuralNetwork :: Mutate ( float WeightShiftChance , float WeightNewChance , float WeightShiftRangeTop ,
                                  float WeightShiftRangeBottom , float NewWeightRangeTop , float NewWeightRangeBottom )
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

    float NeuralNetwork :: GetOutput ( unsigned int Position ) const
    {
        float Output = 0 ;
        Output = Layers [ NumberLayersInNetwork - 1 ] -> GetAt ( Position ) ;
        return Output ;
    }

    void NeuralNetwork :: Pump ( )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < NumberLayersInNetwork - 1 )
        {
            Layers [ LayerIterator ] -> Pump ( * ( Layers [ LayerIterator + 1 ] ) ) ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

    void NeuralNetwork :: SetFitness ( float InFitness )
    {
        Fitness = InFitness ;
    }

    float NeuralNetwork :: GetFitness ( ) const
    {
        return Fitness ;
    }

    Layer * NeuralNetwork :: GetLayer ( unsigned int LayerNumber )
    {
        return Layers [ LayerNumber ] ;
    }

    unsigned int NeuralNetwork :: GetNumberLayersInNetwork ( ) const
    {
        return NumberLayersInNetwork ;
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
            if ( InSizes [ LayerIterator ] > MAX_NEURONS_IN_LAYER )
            {
                Output = false ;
            }
            LayerIterator = LayerIterator + 1 ;
        }
        return Output ;
    }

    void NeuralNetwork :: CopyLayers ( const vector < Layer * > & SourceLayers )
    {
        Layers . resize ( SourceLayers . size ( ) ) ;
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < SourceLayers . size ( ) )
        {
            Layers [ LayerIterator ] = new Layer ( * ( SourceLayers [ LayerIterator ] ) ) ;
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
