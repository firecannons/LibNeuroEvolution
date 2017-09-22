/*
    Programmer: Lucas Winkelman
    File: Population.cpp
    Date: 9/22/2017
    Purpose: Population.cpp contains definitions for the Population class
        in LibNeuroEvolution.
*/

#include "Population.h"

namespace LNE
{
    Population :: Population( vector < unsigned int > InSizes , unsigned int InNumberGroups ,
                             unsigned int InNumberNetworksPerGroup , unsigned int InGroupEvolutionGenerations )
    {
        CurrentGeneration = 1 ;
        CurrentGroupIndex = 0 ;
        NumberGroups = InNumberGroups ;
        NumberNetworksPerGroup = InNumberNetworksPerGroup ;
        GroupEvolutionGenerations = InGroupEvolutionGenerations ;
        Groups . resize ( NumberGroups ) ;
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] = new HyperParameterGroup ( InSizes , InNumberNetworksPerGroup ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    Population :: ~ Population ( )
    {
        DeleteGroups ( ) ;
    }

    Population :: Population ( const Population & SourcePopulation )
    {
        NumberGroups = 0 ;
        * this = SourcePopulation ;
    }

    Population & Population :: operator = ( const Population & SourcePopulation )
    {
        if ( this == & SourcePopulation )
        {
            return * this ;
        }
        else
        {
            DeleteGroups ( ) ;
            CopyGroups ( SourcePopulation . Groups ) ;
            CurrentGeneration = SourcePopulation . CurrentGeneration ;
            CurrentGroupIndex = SourcePopulation . CurrentGroupIndex ;
            NumberGroups = SourcePopulation . NumberGroups ;
            NumberNetworksPerGroup = SourcePopulation . NumberNetworksPerGroup ;
            GroupEvolutionGenerations = SourcePopulation . GroupEvolutionGenerations ;
            return * this ;
        }
    }

    unsigned int Population :: GetCurrentGeneration ( ) const
    {
        return CurrentGeneration ;
    }

    bool Population :: AreNetworksDoneRunning ( ) const
    {
        bool output = false ;
        if ( CurrentGroupIndex >= NumberGroups )
        {
            output = true ;
        }
        return output ;
    }

    NeuralNetwork * Population :: GetCurrentNetwork ( ) const
    {
        NeuralNetwork * output ;
        if ( CurrentGroupIndex < NumberGroups )
        {
            if ( Groups [ CurrentGroupIndex ] -> GetCurrentNetworkIndex ( ) < NumberNetworksPerGroup )
            {
                output = Groups [ CurrentGroupIndex ] -> GetCurrentNetwork ( ) ;
            }
            else
            {
                output = NULL ;
            }
        }
        else
        {
            output = NULL ;
        }
        return output ;
    }

    void Population :: ToNextNetwork ( )
    {
        if ( CurrentGroupIndex < NumberGroups )
        {
            Groups [ CurrentGroupIndex ] -> ToNextNetwork ( ) ;
            if ( Groups [ CurrentGroupIndex ] -> GetCurrentNetworkIndex ( ) >= NumberNetworksPerGroup )
            {
                CurrentGroupIndex = CurrentGroupIndex + 1 ;
            }
        }
    }

    void Population :: EndGeneration ( )
    {
        Evolve ( ) ;
        ResetIndexes ( ) ;
        CurrentGeneration = CurrentGeneration + 1 ;
    }

    float Population :: GetBestFitness ( )
    {
        float BestFitness = -999999999 ;
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            float TempFitness = 0 ;
            TempFitness = Groups [ GroupIterator ] -> GetBestNetworkFitness ( ) ;
            if ( TempFitness > BestFitness )
            {
                BestFitness = TempFitness ;
            }
            GroupIterator = GroupIterator + 1 ;
        }
        return BestFitness ;
    }

    NeuralNetwork * Population :: GetBestNetwork ( ) const
    {
        NeuralNetwork * OutputNetwork ;
        OutputNetwork = Groups [ 0 ] -> GetBestNetwork ( ) ;
        return OutputNetwork ;
    }

    void Population :: Evolve ( )
    {
        if ( CurrentGeneration % GroupEvolutionGenerations == 0 )
        {
            EvolveGroups ( ) ;
        }
        EvolveNetworks ( ) ;
    }

    void Population :: SortGroups ( )
    {
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] -> SortNetworks ( ) ;
            GroupIterator = GroupIterator + 1 ;
        }
        GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups - 1 )
        {
            unsigned int GroupIterator2 = GroupIterator ;
            while ( GroupIterator2 < NumberGroups - 1 )
            {
                if ( Groups [ GroupIterator2 ] -> GetBestNetworkFitness ( ) < Groups [ GroupIterator2 + 1 ] -> GetBestNetworkFitness ( ) )
                {
                    HyperParameterGroup * Temp = Groups [ GroupIterator2 ] ;
                    Groups [ GroupIterator2 ] = Groups [ GroupIterator2 + 1 ] ;
                    Groups [ GroupIterator2 + 1 ] = Temp ;
                }
                GroupIterator2 = GroupIterator2 + 1 ;
            }
            GroupIterator = GroupIterator + 1 ;
        }
    }

    void Population :: KillGroups ( )
    {
        unsigned int StartingKillIndex = ceil ( NumberGroups * ( 1 - POPULATION_KILL_AMOUNT ) ) ;
        unsigned int GroupIterator = StartingKillIndex ;
        while ( GroupIterator < NumberGroups )
        {
            unsigned int SourceGroupIndex = GroupIterator - StartingKillIndex ;
            * ( Groups [ GroupIterator ] ) = * ( Groups [ SourceGroupIndex ] ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    void Population :: MutateGroups ( )
    {
        unsigned int StartingMutateIndex = ceil ( NumberGroups * ( 1 - POPULATION_MUTATE_AMOUNT ) ) ;
        unsigned int GroupIterator = StartingMutateIndex ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] -> Mutate ( ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    void Population :: EvolveGroups ( )
    {
        SortGroups ( ) ;
        KillGroups ( ) ;
        MutateGroups ( ) ;
    }

    void Population :: EvolveNetworks ( )
    {
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] -> EndGeneration ( ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    void Population :: ResetIndexes ( )
    {
        CurrentGroupIndex = 0 ;
    }

    void Population :: DeleteGroups ( )
    {
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            delete Groups [ GroupIterator ] ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

    void Population :: CopyGroups ( const vector < HyperParameterGroup * > & SourceGroups )
    {
        Groups . resize ( SourceGroups . size ( ) ) ;
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < SourceGroups . size ( ) )
        {
            Groups [ GroupIterator ] = new HyperParameterGroup ( * ( SourceGroups [ GroupIterator ] ) ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

}
