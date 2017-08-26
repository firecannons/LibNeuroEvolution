#include "HyperParameterGroup.h"

namespace LNE
{

    HyperParameterGroup :: HyperParameterGroup( vector < unsigned int > & InSizes , unsigned int InNumberNetworksPerGroup )
    {
        NumberNetworksPerGroup = InNumberNetworksPerGroup ;
        WeightShiftRangeTop = DEFAULT_WEIGHT_SHIFT_RANGE_TOP ;
        WeightShiftRangeBottom = DEFAULT_WEIGHT_SHIFT_RANGE_BOTTOM ;
        NewWeightRangeTop = DEFAULT_NEW_WEIGHT_RANGE_TOP ;
        NewWeightRangeBottom = DEFAULT_NEW_WEIGHT_RANGE_BOTTOM ;
        KillRatio = DEFAULT_KILL_RATIO ;
        MutateRatio = DEFAULT_MUTATE_RATIO ;
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
            WeightShiftRangeTop = SourceGroup . WeightShiftRangeTop ;
            WeightShiftRangeBottom = SourceGroup . WeightShiftRangeBottom ;
            NewWeightRangeTop = SourceGroup . NewWeightRangeTop ;
            NewWeightRangeBottom = SourceGroup . NewWeightRangeBottom ;
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

    void HyperParameterGroup :: EndGeneration ( )
    {
        SortNetworks ( ) ;
        KillNetworks ( ) ;
        MutateNetworks ( ) ;
        CurrentNetworkIndex = 0 ;
    }

    void HyperParameterGroup :: Mutate ( )
    {
        MutateKillRatio ( ) ;
        MutateMutateRatio ( ) ;
        MutateWeightShiftRangeTop ( ) ;
        MutateWeightShiftRangeBottom ( ) ;
        ResolveWeightShiftRange ( ) ;
        MutateWeightNewRangeTop ( ) ;
        MutateWeightNewRangeBottom ( ) ;
        ResolveWeightNewRange ( ) ;
        MutateWeightShiftChance ( ) ;
        MutateWeightNewChance ( ) ;
    }

    void HyperParameterGroup :: MutateWeightNewChance ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_New_CHANCE_NEW_CHANCE )
        {
            float WeightNewChanceNewDist = WEIGHT_NEW_CHANCE_NEW_MAX - WEIGHT_NEW_CHANCE_NEW_MIN ;
            float NewValue = GetProb ( ) * WeightNewChanceNewDist + WEIGHT_NEW_CHANCE_NEW_MIN ;
            WeightNewChance = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_NEW_CHANCE_NEW_CHANCE )
        {
            float WeightNewChanceShiftDist = WEIGHT_NEW_CHANCE_SHIFT_MAX - WEIGHT_NEW_CHANCE_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * WeightNewChanceShiftDist + WEIGHT_NEW_CHANCE_SHIFT_MIN ;
            WeightNewChance = MutateRatio + ShiftAmount ;
        }
        if ( WeightNewChance < WEIGHT_NEW_CHANCE_MAX )
        {
            WeightNewChance = WEIGHT_NEW_CHANCE_MAX ;
        }
        else if ( WeightNewChance > WEIGHT_NEW_CHANCE_MIN )
        {
            WeightNewChance = WEIGHT_NEW_CHANCE_MIN ;
        }
    }

    void HyperParameterGroup :: MutateWeightShiftChance ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_CHANCE_NEW_CHANCE )
        {
            float WeightShiftChanceNewDist = WEIGHT_SHIFT_CHANCE_NEW_MAX - WEIGHT_SHIFT_CHANCE_NEW_MIN ;
            float NewValue = GetProb ( ) * WeightShiftChanceNewDist + WEIGHT_SHIFT_CHANCE_NEW_MIN ;
            WeightShiftChance = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_CHANCE_SHIFT_CHANCE )
        {
            float WeightShiftChanceShiftDist = WEIGHT_SHIFT_CHANCE_SHIFT_MAX - WEIGHT_SHIFT_CHANCE_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * NewWeightRangeTopNewDist + WEIGHT_SHIFT_CHANCE_SHIFT_MIN ;
            WeightShiftChance = MutateRatio + ShiftAmount ;
        }
        if ( WeightShiftChance < WEIGHT_SHIFT_CHANCE_MAX )
        {
            WeightShiftChance = WEIGHT_SHIFT_CHANCE_MAX ;
        }
        else if ( WeightShiftChance > WEIGHT_SHIFT_CHANCE_MIN )
        {
            WeightShiftChance = WEIGHT_SHIFT_CHANCE_MIN ;
        }
    }

    void HyperParameterGroup :: ResolveWeightNewRange ( )
    {
        if ( WeightNewRangeTop < WeightNewRangeBottom )
        {
            float Difference = WeightNewRangeBottom - WeightNewRangeTop ;
            WeightNewRangeTop = WeightNewRangeTop + ( Difference / 2 ) ;
            WeightNewRangeBottom = WeightNewRangeBottom - ( Difference / 2 ) ;
        }
    }


    void HyperParameterGroup :: MutateNewWeightRangeBottom ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < NEW_WEIGHT_RANGE_BOTTOM_NEW_CHANCE )
        {
            float NewWeightRangeBottomNewDist = NEW_WEIGHT_RANGE_BOTTOM_NEW_MAX - NEW_WEIGHT_RANGE_BOTTOM_NEW_MIN ;
            float NewValue = GetProb ( ) * NewWeightRangeBottomNewDist + NEW_WEIGHT_RANGE_BOTTOM_NEW_MIN ;
            NewWeightRangeBottom = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < NEW_WEIGHT_RANGE_BOTTOM_SHIFT_CHANCE )
        {
            float NewWeightRangeBottomShiftDist = NEW_WEIGHT_RANGE_BOTTOM_SHIFT_MAX - NEW_WEIGHT_RANGE_BOTTOM_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * NewWeightRangeBottomShiftDist + NEW_WEIGHT_RANGE_BOTTOM_SHIFT_MIN ;
            NewWeightRangeBottom = MutateRatio + ShiftAmount ;
        }
        if ( NewWeightRangeBottom < NEW_WEIGHT_RANGE_BOTTOM_MIN )
        {
            NewWeightRangeBottom = NEW_WEIGHT_RANGE_BOTTOM_MIN ;
        }
        else if ( NewWeightRangeBottom > NEW_WEIGHT_RANGE_BOTTOM_MAX )
        {
            NewWeightRangeBottom = NEW_WEIGHT_RANGE_BOTTOM_MAX ;
        }
    }

    void HyperParameterGroup :: MutateNewWeightRangeTop ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < NEW_WEIGHT_RANGE_TOP_NEW_CHANCE )
        {
            float NewWeightRangeTopNewDist = NEW_WEIGHT_RANGE_TOP_NEW_MAX - NEW_WEIGHT_RANGE_TOP_NEW_MIN ;
            float NewValue = GetProb ( ) * NewWeightRangeTopNewDist + NEW_WEIGHT_RANGE_TOP_NEW_MIN ;
            NewWeightRangeTop = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < NEW_WEIGHT_RANGE_TOP_SHIFT_CHANCE )
        {
            float NewWeightRangeTopShiftDist = NEW_WEIGHT_RANGE_TOP_SHIFT_MAX - NEW_WEIGHT_RANGE_TOP_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * NewWeightRangeTopShiftDist + NEW_WEIGHT_RANGE_TOP_SHIFT_MIN ;
            NewWeightRangeTop = MutateRatio + ShiftAmount ;
        }
        if ( NewWeightRangeTop < NEW_WEIGHT_RANGE_TOP_MIN )
        {
            NewWeightRangeTop = NEW_WEIGHT_RANGE_TOP_MIN ;
        }
        else if ( NewWeightRangeTop > NEW_WEIGHT_RANGE_TOP_MAX )
        {
            NewWeightRangeTop = NEW_WEIGHT_RANGE_TOP_MAX ;
        }
    }

    void HyperParameterGroup :: ResolveWeightShiftRange ( )
    {
        if ( WeightShiftRangeTop < WeightShiftRangeBottom )
        {
            float Difference = WeightShiftRangeBottom - WeightShiftRangeTop ;
            WeightShiftRangeTop = WeightShiftRangeTop + ( Difference / 2 ) ;
            WeightShiftRangeBottom = WeightShiftRangeBottom - ( Difference / 2 ) ;
        }
    }


    void HyperParameterGroup :: MutateWeightShiftRangeBottom ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_BOTTOM_NEW_CHANCE )
        {
            float WeightShiftRangeBottomNewDist = WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MAX - WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MIN ;
            float NewValue = GetProb ( ) * WeightShiftRangeBottomNewDist + WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MIN ;
            WeightShiftRangeBottom = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_CHANCE )
        {
            float WeightShiftRangeBottomShiftDist = WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MAX - WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * WeightShiftRangeBottomShiftDist + WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MIN ;
            WeightShiftRangeBottom = MutateRatio + ShiftAmount ;
        }
        if ( WeightShiftRangeBottom < WEIGHT_SHIFT_RANGE_BOTTOM_MIN )
        {
            WeightShiftRangeBottom = WEIGHT_SHIFT_RANGE_BOTTOM_MIN ;
        }
        else if ( WeightShiftRangeBottom > WEIGHT_SHIFT_RANGE_BOTTOM_MAX )
        {
            WeightShiftRangeBottom = WEIGHT_SHIFT_RANGE_BOTTOM_MAX ;
        }
    }

    void HyperParameterGroup :: MutateWeightShiftRangeTop ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_TOP_NEW_CHANCE )
        {
            float WeightShiftRangeTopNewDist = WEIGHT_SHIFT_RANGE_TOP_NEW_MAX - WEIGHT_SHIFT_RANGE_TOP_NEW_MIN ;
            float NewValue = GetProb ( ) * WeightShiftRangeTopNewDist + WEIGHT_SHIFT_RANGE_TOP_NEW_MIN ;
            WeightShiftRangeTop = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_TOP_SHIFT_CHANCE )
        {
            float WeightShiftRangeTopShiftDist = WEIGHT_SHIFT_RANGE_TOP_SHIFT_MAX - WEIGHT_SHIFT_RANGE_TOP_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * WeightShiftRangeTopShiftDist + WEIGHT_SHIFT_RANGE_TOP_SHIFT_MIN ;
            WeightShiftRangeTop = MutateRatio + ShiftAmount ;
        }
        if ( WeightShiftRangeTop < WEIGHT_SHIFT_RANGE_TOP_MIN )
        {
            WeightShiftRangeTop = WEIGHT_SHIFT_RANGE_TOP_MIN ;
        }
        else if ( WeightShiftRangeTop > WEIGHT_SHIFT_RANGE_TOP_MAX )
        {
            WeightShiftRangeTop = WEIGHT_SHIFT_RANGE_TOP_MAX ;
        }
    }



    void HyperParameterGroup :: MutateWeightShiftRangeBottom ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_BOTTOM_NEW_CHANCE )
        {
            float WeightShiftRangeBottomNewDist = WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MAX - WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MIN ;
            float NewValue = GetProb ( ) * WeightShiftRangeBottomNewDist + WEIGHT_SHIFT_RANGE_BOTTOM_NEW_MIN ;
            WeightShiftRangeBottom = NewValue ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_CHANCE )
        {
            float WeightShiftRangeBottomShiftDist = WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MAX - WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * WeightShiftRangeBottomShiftDist + WEIGHT_SHIFT_RANGE_BOTTOM_SHIFT_MIN ;
            WeightShiftRangeBottom = MutateRatio + ShiftAmount ;
        }
        if ( WeightShiftRangeBottom < WEIGHT_SHIFT_RANGE_BOTTOM_MIN )
        {
            WeightShiftRangeBottom = WEIGHT_SHIFT_RANGE_BOTTOM_MIN ;
        }
        else if ( WeightShiftRangeBottom > WEIGHT_SHIFT_RANGE_BOTTOM_MAX )
        {
            WeightShiftRangeBottom = WEIGHT_SHIFT_RANGE_BOTTOM_MAX ;
        }
    }


    void HyperParameterGroup :: MutateKillRatio ( )
    {
        float RandomNumber = GetProb ( ) ;
        if ( RandomNumber < KILL_RATIO_NEW_CHANCE )
        {
            float KillRatioNewDist = KILL_RATIO_NEW_MAX - KILL_RATIO_NEW_MIN ;
            float NewKillRatio = GetProb ( ) * KillRatioNewDist + KILL_RATIO_NEW_MIN ;
            KillRatio = NewKillRatio ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < KILL_RATIO_SHIFT_CHANCE )
        {
            float KillRatioShiftDist = KILL_RATIO_SHIFT_MAX - KILL_RATIO_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * KillRatioShiftDist + KILL_RATIO_SHIFT_MIN ;
            KillRatio = KillRatio + ShiftAmount ;
        }
        if ( KillRatio < KILL_RATIO_MIN )
        {
            KillRatio = KILL_RATIO_MIN ;
        }
        else if ( KillRatio > KILL_RATIO_MAX )
        {
            KillRatio = KILL_RATIO_MAX ;
        }
    }

    void HyperParameterGroup :: MutateMutateRatio ( )
    {
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < MUTATE_RATIO_NEW_CHANCE )
        {
            float MutateRatioNewDist = MUTATE_RATIO_NEW_MAX - MUTATE_RATIO_NEW_MIN ;
            float NewMutateRatio = GetProb ( ) * MutateRatioNewDist + MUTATE_RATIO_NEW_MIN ;
            MutateRatio = NewMutateRatio ;
        }
        RandomNumber = GetProb ( ) ;
        if ( RandomNumber < MUTATE_RATIO_SHIFT_CHANCE )
        {
            float MutateRatioShiftDist = MUTATE_RATIO_SHIFT_MAX - MUTATE_RATIO_SHIFT_MIN ;
            float ShiftAmount = GetProb ( ) * MutateRatioShiftDist + MUTATE_RATIO_SHIFT_MIN ;
            MutateRatio = MutateRatio + ShiftAmount ;
        }
        if ( MutateRatio < MUTATE_RATIO_MIN )
        {
            MutateRatio = MUTATE_RATIO_MIN ;
        }
        else if ( MutateRatio > MUTATE_RATIO_MAX )
        {
            MutateRatio = MUTATE_RATIO_MAX ;
        }
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
        unsigned int StartingKillIndex = ceil ( NumberNetworksPerGroup * ( 1 - MutateRatio ) ) ;
        unsigned int NetworkIterator = StartingKillIndex ;
        while ( NetworkIterator < NumberNetworksPerGroup )
        {
            Networks [ NetworkIterator ] -> Mutate ( ) ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

}
