// ZNN-ImageToColorGenerator
// Copyright (C) 2025 zoriun
// 
// Licensed under the ZNN-ImageToColorGenerator License v1.0 (February 2025):
// - You may use, copy, modify, and redistribute this software for non-commercial purposes.
// - You must provide visible credit to the original author:
//   Original project by zoriun — https://github.com/zoriun/ZNN-ImageToColorGenerator
// - You may not sell this software or use it in products/services for monetary gain.
// 
// Full license text is available in the LICENSE file included with this source code.

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