
// Fill out your copyright notice in the Description page of Project Settings.


#include "NeuralNetwork.h"
#include "GeneticAlgorithm.h"


// Sets default values for this component's properties
UNeuralNetwork::UNeuralNetwork()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickInterval = 1.0f; //Ticks every second, can lower if necessary;
	// ...

	
	/*Construct Neural Network*/
	//Generate a NeuronLayer for the inputs
	//for each input we should have x+1 nuerons;
	//CreateNeuralNetwork();
}


// Called when the game starts
void UNeuralNetwork::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNeuralNetwork::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



TArray<float> UNeuralNetwork::Update(TArray<float> Inputs)
{
	//stores result outputs from each layer
	TArray<float> output;
	float NetInputValue =0;
	int NewWeight =0;
	if(Inputs.Num() < 1)
	{
		UE_LOG(LogTemp,Error,TEXT("Inputs are invalid, please fix"));
		return output;
	}
	
	int32 TotalLayers = NeuralNetwork.Num() -1; //subtract input/output layers
	
	//for each layer:
	for(int32 i = 0; i < NumHiddenLayers +1; ++i)
	{
		/*for each neuron, sum the inputs* weights, send to activation function and get output*/
		for(int32 j = 0; j < VecLayers[i].NumNeurons; ++j)
		{
		
			int inputsToCalc = VecLayers[i].VecNeurons[j].inputs;

			//for each weight
			for(int k = 0; k < inputsToCalc; k++)
			{
				
				NetInputValue += VecLayers[i].VecNeurons[j].weights[k] * Inputs[NewWeight ++];
			}
			//add bias
			NetInputValue += VecLayers[i].VecNeurons[j].weights[NumInputs - 1] * Bias;

			output.Add(Sigmoid(NetInputValue, ActivationResponse));
			NewWeight = 0;
		}
	}
	return output;
		
}



TArray<float> UNeuralNetwork::GenerateInputs(TArray<float> inputs)
{
	return inputs;
	
	//inputs can be anything, possibly a wildcard struct to make things easy
	
	
	/*How I would like this to work*/
	
	//Generate Network
	//Create Layer(LayerType(Convolution/maxpool/FullyConnected/etc), ActivationFunction(Relu/Softmax/Sigmoid), InputSize, OutputChannels, PoolingSizeifNecessary
	//Create Another Layer if wanted
	//Create a third layer or whatever
	
	//Add layers to Network
	//Network.Add(Layer1)
	//Network.Add(Layer2)
	
	//Generate Output Layer
	//Output Layer values are tied to activating a function somehow.....

	
	/*
	*Update Function:
	    Run for however long
	    every loop we update NN with EQS and other values
	    Output/Prediction for NN is obtained and we Run the corresponding Action
	    we update fitness accordingly

	Once the 'generation' has been completed we run the GA
	**update Stats average fitness and best fitness
	generation++
	
	Create New Population of AI
	for every AI
		-Insert Best NeuralNetwork into them
	
	*/
	
}

void UNeuralNetwork::CreateNeuralNetwork()
{
	if(NumHiddenLayers > 0)
	{
		//first hidden layer
		VecLayers.Add(FNeuronLayer(NeuronsPerHiddenLayer,NumInputs));
	
		for(int i=0; i<NumHiddenLayers; i++)
		{
			VecLayers.Add(FNeuronLayer(NeuronsPerHiddenLayer,NeuronsPerHiddenLayer));
		}
		
		VecLayers.Add(FNeuronLayer(NumOutputs,NeuronsPerHiddenLayer));
	}
	else //if no hidden layers, output layer connects directly to input layer
		VecLayers.Add(FNeuronLayer(NumOutputs,NumInputs));

}


FNeuronLayer UNeuralNetwork::CreateLayer(int32 inputNodes, int32 NeuronsInThisLayer)
{
	FNeuronLayer newLayer(NeuronsInThisLayer,inputNodes);
	return newLayer;
	
}

TArray<FNeuron> UNeuralNetwork::GetNeuronsAtLayer(int32 LayerIndex)
{
	return NeuralNetwork[LayerIndex].VecNeurons;
}

TArray<float> UNeuralNetwork::GetOutputWeights()
{
	TArray<FNeuron>temp = GetNeuronsAtLayer(NeuralNetwork.Num()-1);

	return temp[0].weights;
}


float UNeuralNetwork::Sigmoid(float Activation, float Response)
{
	return (1/(1 + FMath::Pow(-Activation,Response)));
}

float UNeuralNetwork::Relu(float Activation)
{
	return FMath::Max(0.0f ,Activation);
}


void UNeuralNetwork::PropogateForward(FVector& input)
{
	
}

void UNeuralNetwork::BackPropogation(FVector& output)
{
	
}

