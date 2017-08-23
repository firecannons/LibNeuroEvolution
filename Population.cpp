#include "Population.h"

namespace LNE
{
    Population :: Population( vector < unsigned int > InSizes , unsigned int InNumberGroups , unsigned int InNumberNetworksPerGroup
               unsigned int InGroupEvolutionGenerations )
    {
        CurrentGeneration = 0 ;
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
        if ( CurrentGroupIndex == NumberGroups )
        {
            if ( Groups [ CurrentGroupIndex ] -> AreNetworksDoneRunning ( ) == true )
            {
                output = true ;
            }
        }
        return output ;
    }

    Network * Population :: GetCurrentNetwork ( ) const
    {
        Network * output ;
        if ( CurrentGroupIndex < NumberGroups )
        {
            if ( Groups -> GetCurrentNetworkIndex ( ) < NumberNetworksPerGroup )
            {
                output = & Groups [ CurrentGroupIndex ] -> GetCurrentNetwork ( ) ;
            }
            else
            {
                output = nullptr ;
            }
        }
        else
        {
            output = nullptr ;
        }
        return output ;
    }

    bool Population :: ToNextNetwork ( )
    {
        if ( CurrentGroupIndex < NumberGroups )
        {
            if ( Groups [ CurrentGroupIndex ] -> GetCurrentNetworkIndex ( ) < NumberNetworksPerGroup )
            {
                Groups [ CurrentGroupIndex ] -> ToNextNetwork ( ) ;
            }
            else
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

    void Population :: Evolve ( )
    {

        if ( CurrentGeneration % GroupEvolutionGenerations == 0 )
        {
            EvolveGroups ( ) ;
        }
        EvolveNetworks ( ) ;
    }

    void SortGroups ( )
    {
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] -> SortNetworks ( ) ;
        }
        GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            unsigned int GroupIterator2 = GroupIterator ;
            while ( GroupIterator2 < NumberGroups )
            {
                if ( Groups [ GroupIterator2 ] -> GetBestNetworksFitness ( ) < Groups [ GroupIterator2 + 1 ] -> GetBestNetworksFitness ( ) )
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
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < NumberGroups )
        {
            Groups [ GroupIterator ] -> Mutate ( ) ;
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

    void Population :: CopyGroups ( vector < HyperParameterGroup * > & SourceGroups )
    {
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < SourceGroups . size ( ) )
        {
            Groups [ GroupIterator ] = new HyperParameterGroup ( SourceGroups [ GroupIterator ] ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

}
