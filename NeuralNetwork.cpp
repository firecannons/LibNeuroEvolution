#include "NeuralNetwork.h"

namespace LNE
{

    NeuralNetwork :: NeuralNetwork ( vector < unsigned int > & InSizes )
    {
        Fitness = DEFAULT_FITNESS ;
        NumberLayersInNetwork = InSizes . size ( ) ;
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < InSizes . size ( ) )
        {
            Groups [ LayerIterator ] = new Layer ( InSizes , InNumberNetworksPerGroup ) ;
            LayerIterator = LayerIterator + 1 ;
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

    void NeuralNetwork :: DeleteLayers ( )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < NumberLayersInNetwork )
        {
            delete Layers [ LayerIterator ] ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

    void NeuralNetwork :: CopyNetworks ( vector < Layer * > & SourceLayers )
    {
        unsigned int LayerIterator = 0 ;
        while ( LayerIterator < SourceLayers . size ( ) )
        {
            Layers [ LayerIterator ] = new Layer ( SourceLayers [ LayerIterator ] ) ;
            LayerIterator = LayerIterator + 1 ;
        }
    }

}
