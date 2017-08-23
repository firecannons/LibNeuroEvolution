#include "HyperParameterGroup.h"

namespace LNE
{

    HyperParameterGroup :: HyperParameterGroup( vector < unsigned int > & InSizes , unsigned int InNumberNetworksPerGroup )
    {
        NumberNetworksPerGroup = InNumberNetworksPerGroup ;
        MaxWeightShift = DEFAULT_WEIGHT_MAX_SHIFT ;
        MinWeightShift = DEFAULT_WEIGHT_MIN_SHIFT ;
        NewWeightMax = DEFAULT_NEW_WEIGHT_MAX ;
        NewWeightMin = DEFAULT_NEW_WEIGHT_MIN ;
        KillRatio = DEFAULT_KILL_RATIO ;
        MutateRatio = DEFAULT_MUTATE_RATIO ;
        CurrentNetworkIndex = 0 ;
        Networks . resize ( NumberNetworks ) ;
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < NumberNetworks )
        {
            Groups [ GroupIterator ] = new HyperParameterGroup ( InSizes , InNumberNetworksPerGroup ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    HyperParameterGroup :: ~ HyperParameterGroup ( )
    {
        DeleteNetworks ( ) ;
    }

    HyperParameterGroup :: HyperParameterGroup ( const HyperParameterGroup & Source )
    {
        * this = Source ;
    }

    HyperParameterGroup & HyperParameterGroup :: operator = ( const HyperParameterGroup & SourceGroup )
    {
        if ( this == & rhs )
        {
            return * this ;
        }
        else
        {
            DeleteGroups ( ) ;
            CopyGroups ( SourceGroup . Networks ) ;
            MaxWeightShift = SourceGroup . MaxWeightShift ;
            MinWeightShift = SourceGroup . MinWeightShift ;
            NewWeightMax = SourceGroup . NewWeightMax ;
            NewWeightMin = SourceGroup . NewWeightMin ;
            KillRatio = SourceGroup . KillRatio ;
            MutateRatio = SourceGroup . MutateRatio ;
            NumberNetworksPerGroup = SourceGroup . NumberNetworksPerGroup ;
            CurrentNetworkIndex = SourceGroup . CurrentNetworkIndex ;
            return * this;
        }
    }

    void HyperParameterGroup :: ToNextNetwork ( )
    {
        if ( CurrentNetworkIndex < NumberNetworksPerGroup )
        {
            CurrentNetworkIndex = CurrentNetworkIndex + 1 ;
        }
    }

    unsigned int HyperParameterGroup :: GetCurrentNetworkIndex ( ) const
    {
        return CurrentNetworkIndex ;
    }

    void HyperParameterGroup :: SortNetworks ( )
    {
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < NumberNetworksPerGroup )
        {
            unsigned int NetworkIterator2 = NetworkIterator ;
            while ( NetworkIterator2 < NumberNetworksPerGroup )
            {
                if ( Networks [ NetworkIterator2 ] -> GetFitness ( ) < Groups [ NetworkIterator2 + 1 ] -> GetFitness ( ) )
                {
                    NeuralNetwork * Temp = Networks [ NetworkIterator2 ] ;
                    Networks [ NetworkIterator2 ] = Networks [ NetworkIterator2 + 1 ] ;
                    Networks [ NetworkIterator2 + 1 ] = Temp ;
                }
                NetworkIterator2 = NetworkIterator2 + 1 ;
            }
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

    void GetBestNetworkFitness ( ) const
    {
        Networks [ 0 ] -> GetFitness ( ) ;
    }

    void HyperParameterGroup :: DeleteNetworks ( )
    {
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < NumberNetworksPerGroup )
        {
            delete Networks [ NetworkIterator ] ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

    void HyperParameterGroup :: CopyNetworks ( vector < NeuralNetwork * > & SourceNetworks )
    {
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < SourceNetworks . size ( ) )
        {
            Groups [ NetworkIterator ] = new NeuralNetwork ( SourceGroups [ NetworkIterator ] ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

}
