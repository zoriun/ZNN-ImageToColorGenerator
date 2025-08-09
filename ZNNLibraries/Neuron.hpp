#pragma once
#include <iostream>
#include <cmath>

double Sigmoid(double x){
    return 1 / (1 + exp(-x));
}

struct Neuron
{
    double Value;
    double ActivatedValue;
    Neuron(double NValue);
    void ActivateNeuron();
};

Neuron::Neuron(double NValue){
    Value = NValue;
}; 

void Neuron::ActivateNeuron(){
    ActivatedValue = Sigmoid(Value);
};