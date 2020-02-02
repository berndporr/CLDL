#pragma once


#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <ctgmath>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <fstream>
#include <iostream>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>


using namespace std;

class Neuron {
public:
    // constructor de-constructor
    Neuron(int _nInputs);
    ~Neuron();

    // initialisation:
    enum biasInitMethod { B_NONE = 0, B_RANDOM = 1 };
    enum weightInitMethod { W_ZEROS = 0, W_ONES = 1, W_RANDOM = 2 };
    enum actMethod {Act_Sigmoid = 0, Act_Tanh = 1, Act_NONE = 2};

    void initNeuron(int _neuronIndex, int _layerIndex, weightInitMethod _wim, biasInitMethod _bim, Neuron::actMethod _am);
    void setLearningRate(double _learningRate);

    //forward propagation of inputs:
    void setInput(int _index, double _value);
    void propInputs(int _index, double _value);
    void calcOutput();

    //->->forward->-> propagation of error:
    void setErrorAtInput(double _value);
    void propErrorForward(int _index, double _value);
    void calcForwardError();

    //back propagation of error
    void setBackwardError(double _nextSum);  // for the output layer only
    void propErrorBackward(double _nextSum); // used for all layers except the output
    double getBackwardError();

    //MID propagation of error:
    void setMidError(double _leadMidError);
    void calcMidError();
    double getMidError();
    void propMidErrorForward(int _index, double _value);
    void propMidErrorBackward(double _nextSum); // used for all layers except the output


    //learning:
    void setErrorCoeff(int _backwardsCoeff, int _midCoeff, int forwardCoeff);
    void updateWeights();
    double doActivation(double _sum);
    double doActivationPrime(double _input);

    //global settings
    void setGlobalError(double _globalError);

    //getters:
    double getOutput();
    double getForwardError();
    double getSumOutput();
    double getWeights(int _inputIndex);
    double getInitWeights(int _inputIndex);
    double getGlobalError();
    double getWeightChange();
    double getMaxWeight();
    double getMinWeight();
    double getSumWeight();

    double getWeightDistance();
    int getnInputs();

    //saving and inspecting
    void saveWeights();
    void printNeuron();

    inline void setWeight(int _index, double _weight) {
        assert((_index >= 0) && (_index < nInputs));
        weights[_index] = _weight;
    }

private:

    // initialisation:
    int nInputs = 0;
    int myLayerIndex = 0;
    int myNeuronIndex = 0;
    double *initialWeights = 0;
    double learningRate = 0;

    //forward propagation of inputs:
    double *inputs = 0;
    double bias = 0;
    double sum = 0;
    double output = 0;

    //forward propagation of error:
    double *inputErrors = 0;
    double forwardError = 0;

    //back propagation of error
    double backwardError = 0;

    //mid propagation of error
    double *inputMidErrors = 0;
    double midError = 0;

    //learning:
    int backwardsCoeff = 0;
    int midCoeff = 0;
    int forwardCoeff = 0;
    double *weights = 0;
    double weightSum = 0;
    double maxWeight = 1;
    double minWeight = 1;
    double weightChange=0;
    double weightsDifference = 0;
    int actMet = 0;

    //global setting
    double globalError = 0;


};
