// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "NeuralNetwork.generated.h"


USTRUCT(immutable, noexport, BlueprintType)
struct FNeuron
{

	//number of inputs into this Neuron
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	int32 inputs;

	//weight of corresponding inputs  weights[inputs] will give you the weight for the incomming...axon?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	TArray<float> weights;

	FNeuron();
	
	FNeuron(int32 numInputs) : inputs(numInputs)
	{
		inputs = numInputs;
		//the +1 is for the bias or threshold for activation
		for (int32 i = 0; i < numInputs + 1; i++)
		{
			float test = (FMath::RandRange(0.0f, 1.0f));
			UE_LOG(LogTemp, Error, TEXT("--------------------weights are  : %f"), test);

			weights.Emplace(test);
		}
	}
	
	
};

//stores the number of neurons in its layer
USTRUCT(noexport, BlueprintType)
struct FNeuronLayer
{

	UPROPERTY()
    int32 NumNeurons;

	UPROPERTY()
        TArray<FNeuron> VecNeurons;

	UPROPERTY()
        int32 NumInputsPerNeuron;


	FNeuronLayer();
	FNeuronLayer(int32 NumNeurons_, int32 NumInputsPerNeuron_) : NumNeurons(NumNeurons_), NumInputsPerNeuron(NumInputsPerNeuron_)
	{
		NumNeurons = NumNeurons_;
		NumInputsPerNeuron = NumInputsPerNeuron_;
		for (int32 i = 0; i < NumNeurons_; i++)
		{
			UE_LOG(LogTemp, Log, TEXT("NumberNeurons_ : %d"), NumNeurons_);
			UE_LOG(LogTemp, Log, TEXT("NumInputsPerNeuron_ %d"), NumInputsPerNeuron_);

			VecNeurons.Emplace(FNeuron(NumInputsPerNeuron_));
		}
	}

};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARALLEL_API UNeuralNetwork : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNeuralNetwork();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	//Incomming Neurons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
    TArray<FNeuron> Neurons;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	TArray<FNeuronLayer> NeuralNetwork;
	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	int32 NumInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	int32 NumOutputs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	int32 NumHiddenLayers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	int32 NeuronsPerHiddenLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	float Bias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	float ActivationResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeuralNetwork")
	TArray<FNeuronLayer> VecLayers;

	/*Main funciton update, feed it our inputs and it will update the network */
	UFUNCTION(BlueprintCallable,Category="Neural Network")
	TArray<float>Update(TArray<float>Inputs);

	/*TODO: should use a wildcard struct*/
	UFUNCTION(BlueprintCallable,Category="Neural Network")
	TArray<float> GenerateInputs(TArray<float> inputs);

	UFUNCTION(BlueprintCallable,Category="Neural Network")
	void CreateNeuralNetwork();
	
		/*Basic Layer Generation, Number of inputs are the amount of weights coming into the layer, number of outputs are the total number of neurons in this layer
	 * TODO: should we automatically add them to the Neural network? why not right?
	 */
	UFUNCTION(BlueprintCallable,Category="Neural Network")
	FNeuronLayer CreateLayer(int32 inputNodes, int32 NeuronsInThisLayer);

	UFUNCTION(BlueprintCallable,Category="Neural Network")
	TArray<FNeuron> GetNeuronsAtLayer(int32 LayerIndex);

	TArray<float> GetOutputWeights();
	
	/*response curve*/
	float Sigmoid(float Activation, float Response);
	
	float Relu(float Activation); //apparently is better? idk ask mat
	
	
	//*Geeks for geeks system*/

	TArray<int32> Topology;
	float LearningRate = 0.005f;
	
	void PropogateForward(FVector& input);

	void BackPropogation(FVector& output);

	void ErrorCalc(FVector& output);

	void UpdateWeights();

	void Train(TArray<FVector*> Data);

	TArray<FVector*> NeuronLayers;

	TArray<FVector*> CacheLayers;

	TArray<FVector> deltas;

	TArray<FVector> weights;

	
		
};

