#include <cstdio>
#include <vector>
#include "LibNeuroEvolution.h"
using namespace LNE ;

using namespace std ;

const unsigned int NUMBER_GROUPS = 40 ;
const unsigned int NUMBER_NETWORKS = 30 ;
const unsigned int GROUP_EVOLUTION_GENERATIONS = 10 ;

int main ( )
{
    vector < unsigned int > Sizes ;
    Sizes . push_back ( 2 ) ;
    Sizes . push_back ( 1 ) ;
    Population MyPop ( Sizes , NUMBER_GROUPS , NUMBER_NETWORKS , GROUP_EVOLUTION_GENERATIONS ) ;
    printf ( "Hello World.\n" ) ;
    fflush ( stdout ) ;
    return 0 ;
}
