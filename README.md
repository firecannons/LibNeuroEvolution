# LibNeuroEvolution
A library to optimize neural networks via evolutionary computing.

## How it works
Your program creates a `Population`.  Then it must simply loop through Neural Networks that the `Population` will give it.

Internally, a `Population` will evolve an array of `HyperParameterGroups` it contains.  Each `HyperParameterGroup` will evolve an array of `NeuralNetworks` it contains. 


## The Source Code
All of the source code for the library is in the Source folder.

## Running the Samples (BinarySample only currently)
* First install make
* Clone or download the repository<br>`git clone https://github.com/firecannons/LibNeuroEvolution.git`
* Navigate to the LibNeuroEvolution main directory<br>`cd LibNeuroEvolution`
* Run make<br>`make`
* Run binaries in the new Bin folder<br>`./Bin/BinarySample`

## Notes
I found when trying the library on Tic-Tac-Toe that evolution became much slower as the size of the network increased.  If your problem is not very simple, you should use a neural network with backpropagation.
