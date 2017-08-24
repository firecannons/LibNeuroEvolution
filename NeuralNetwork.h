#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

namespace LNE
{
    const float DEFAULT_FITNESS = 0 ;
    class NeuralNetwork
    {
        public:
            NeuralNetwork ( vector < unsigned int > & InSizes ) ;
            ~ NeuralNetwork ( ) ;
            NeuralNetwork ( const NeuralNetwork & SourceNetwork ) ;
            NeuralNetwork & operator = ( const NeuralNetwork & SourceNetwork ) ;

        private:
            float Fitness ;
            vector < Layer * > Layers ;
    } ;
}

#endif // NEURALNETWORK_H
