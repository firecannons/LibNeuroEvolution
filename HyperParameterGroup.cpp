#include "HyperParameterGroup.h"

namespace LNE
{

    HyperParameterGroup::HyperParameterGroup()
    {
        Networks . clear ( ) ;
    }

    HyperParameterGroup::~HyperParameterGroup()
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

}
