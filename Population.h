#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "HyperParameterGroup.h"
using namespace std ;

namespace LNE
{
    const float POPULATION_KILL_AMOUNT = 0.3 ;
    const float POPULATION_MUTATE_AMOUNT = 0.3 ;


    class Population
    {
        public:
            Population( vector < unsigned int > InSizes , unsigned int InNumberGroups ,
                       unsigned int InNumberNetworksPerGroup , unsigned int InGroupEvolutionGenerations ) ;

            ~ Population ( ) ;

            Population( const Population & SourcePopulation ) ;

            Population & operator = ( const Population & SourcePopulation ) ;

            unsigned int GetCurrentGeneration ( ) const ;

            bool AreNetworksDoneRunning ( ) const ;

            NeuralNetwork * GetCurrentNetwork ( ) const ;

            void ToNextNetwork ( ) ;

            void EndGeneration ( ) ;





        private:
            vector < HyperParameterGroup * > Groups ;
            unsigned int CurrentGroupIndex ;
            unsigned int CurrentGeneration ;
            unsigned int NumberGroups ;
            unsigned int NumberNetworksPerGroup ;
            unsigned int GroupEvolutionGenerations ;


            void Evolve ( ) ;
            void SortGroups ( ) ;
            void KillGroups ( ) ;
            void MutateGroups ( ) ;
            void EvolveGroups ( ) ;
            void EvolveNetworks ( ) ;
            void ResetIndexes ( ) ;
            void DeleteGroups ( ) ;
            void CopyGroups ( const vector < HyperParameterGroup * > & SourceGroups ) ;

    };

}

namespace LNE
{
    Population :: Population( vector < unsigned int > InSizes , unsigned int InNumberGroups ,
                             unsigned int InNumberNetworksPerGroup , unsigned int InGroupEvolutionGenerations )
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
        printf ( "100\n" ) ;
        fflush ( stdout ) ;
        //Evolve ( ) ;
        printf ( "200\n" ) ;
        fflush ( stdout ) ;
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

    void Population :: SortGroups ( )
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
        unsigned int GroupIterator = 0 ;
        while ( GroupIterator < SourceGroups . size ( ) )
        {
            Groups [ GroupIterator ] = new HyperParameterGroup ( * ( SourceGroups [ GroupIterator ] ) ) ;
            GroupIterator = GroupIterator + 1 ;
        }
    }

}


#endif // POPULATION_H
