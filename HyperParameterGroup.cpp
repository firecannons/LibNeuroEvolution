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
        WeightShiftChance = WEIGHt
        CurrentNetworkIndex = 0 ;
        Networks . resize ( NumberNetworks ) ;
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < NumberNetworks )
        {
            Networks [ NetworkIterator ] = new NeuralNetwork ( InSizes ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

    HyperParameterGroup :: ~ HyperParameterGroup ( )
    {
        DeleteNetworks ( ) ;
    }

    HyperParameterGroup :: HyperParameterGroup ( const HyperParameterGroup & SourceGroup )
    {
        * this = SourceGroup ;
    }

    HyperParameterGroup & HyperParameterGroup :: operator = ( const HyperParameterGroup & SourceGroup )
    {
        if ( this == & rhs )
        {
            return * this ;
        }
        else
        {
            DeleteNetworks ( ) ;
            CopyNetworks ( SourceGroup . Networks ) ;
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
                if ( Networks [ NetworkIterator2 ] -> GetFitness ( ) < Networks [ NetworkIterator2 + 1 ] -> GetFitness ( ) )
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

    void HyperParameterGroup :: GetBestNetworkFitness ( ) const
    {
        Networks [ 0 ] -> GetFitness ( ) ;
    }

    bool HyperParameterGroup :: AreNetworksDoneRunning ( ) const
    {
        bool Output = false ;
        if ( CurrentNetworkIndex == NumberNetworksPerGroup )
        {
            Output = true ;
        }
        return Output ;
    }

    NeuralNetwork * HyperParameterGroup :: GetCurrentNetwork ( ) const
    {
        NeuralNetwork * OutputNetwork ;
        if ( CurrentNetworkIndex < NumberNetworksPerGroup )
        {
            OutputNetwork = & Networks [ CurrentNetworkIndex ] ;
        }
        else
        {
            OutputNetwork = nullptr ;
        }
        return OutputNetwork ;
    }

    void HyperParameterGroup :: Mutate ( )
    {

    }

    void HyperParameterGroup :: EndGeneration ( )
    {
        SortNetworks ( ) ;
        KillNetworks ( ) ;
        MutateNetworks ( ) ;
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
            Networks [ NetworkIterator ] = new NeuralNetwork ( SourceNetworks [ NetworkIterator ] ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

    void HyperParameterGroup :: KillNetworks ( )
    {
        unsigned int StartingKillIndex = ceil ( NumberNetworksPerGroup * ( 1 - KillRatio ) ) ;
        unsigned int NetworkIterator = StartingKillIndex ;
        while ( NetworkIterator < NumberNetworksPerGroup )
        {
            unsigned int SourceNetworkIndex = NetworkIterator - StartingKillIndex ;
            * ( Networks [ NetworkIterator ] ) = * ( Networks [ SourceNetworkIndex ] ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

    void HyperParameterGroup :: MutateNetworks ( )
    {
        unsigned int StartingKillIndex = ceil ( NumberNetworksPerGroup * ( 1 - KillRatio ) ) ;
        unsigned int NetworkIterator = StartingKillIndex ;
        while ( NetworkIterator < NumberNetworksPerGroup )
        {
            Networks [ NetworkIterator ] -> Mutate ( ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

}
