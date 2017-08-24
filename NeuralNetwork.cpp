#include "NeuralNetwork.h"

namespace LNE
{

    NeuralNetwork :: NeuralNetwork ( )
    {
        DEFAULT_FITNESS = 0 ;
    }

    NeuralNetwork :: ~ NeuralNetwork ( )
    {
      //dtor
    }

    NeuralNetwork :: NeuralNetwork ( const NeuralNetwork & other)
    {
      //copy ctor
    }

    NeuralNetwork & NeuralNetwork :: operator = ( const NeuralNetwork & rhs)
    {
      if ( this == & rhs )
      {
          return * this ;
      }
      return * this;
    }

}
