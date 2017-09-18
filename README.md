# LibNeuroEvolution
A library to optimize neural networks via evolutionary computing.

## How it works
Your program creates a `Population` which will have `HyperParameterGroup`s inside of it.  Each `HyperParameterGroup` will have some neural networks inside of it.  Your simply have to have a task to test the neural networks on and loop through neural networks that your `Population` will give you.

Internally, a `Population` will evolve an array it `HyperParameterGroup`s it contains.  Each 'HyperParameterGroup' will evolve an array of `NeuralNetworks` it contains. 


## The Source Code
All of the source code for the library is in the Source folder.

## Running the Samples (BinarySample only currently)
* First install make
* Open a terminal and move to the LibNeuroEvolution main directory
* Run `make`
* Then run Bin/BinarySample

## Notes
I found when trying the library on Tic-Tac-Toe that evolution became much slower as the size of the network increased.  If your problem is not very simple, you should use a neural network with backpropagation.
