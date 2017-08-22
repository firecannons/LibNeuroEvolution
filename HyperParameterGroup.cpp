#include "HyperParameterGroup.h"

namespace LNE
{

    HyperParameterGroup :: HyperParameterGroup( vector < unsigned int > & Sizes , unsigned int InNumberNetworks )
    {
        NumberNetworks = InNumberNetworks ;
        MaxWeightShift = DEFAULT_WEIGHT_MAX_SHIFT ;
        MinWeightShift = DEFAULT_WEIGHT_MIN_SHIFT ;
        NewWeightMax = DEFAULT_NEW_WEIGHT_MAX ;
        NewWeightMin = DEFAULT_NEW_WEIGHT_MIN ;
        KillRatio = DEFAULT_KILL_RATIO ;
        MutateRatio = DEFAULT_MUTATE_RATIO ;
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
        //dtor
    }

    HyperParameterGroup::HyperParameterGroup(const HyperParameterGroup& other)
    {
        //copy ctor
    }

    HyperParameterGroup& HyperParameterGroup::operator=(const HyperParameterGroup& rhs)
    {
        if (this == &rhs) return *this; // handle self assignment
        //assignment operator
        return *this;
    }

    void HyperParameterGroup :: DeleteNetworks ( )
    {
        unsigned int NetworkIterator = 0 ;
        while ( NetworkIterator < NumberNetworks )
        {
            delete Networks [ NetworkIterator ] ;
            NetworkIterator = NetworkIterator + 1 ;
        }
    }

}
