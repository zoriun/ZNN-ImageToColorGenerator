// ZNN-ImageToColorGenerator
// Copyright (C) 2025 zoriun
// 
// Licensed under the ZNN-ImageToColorGenerator License v1.0 (February 2025):
// - You may use, copy, modify, and redistribute this software for non-commercial purposes.
// - You must provide visible credit to the original author:
//   Original project by yeahzoriun — https://github.com/yeahzoriun/ZNN-ImageToColorGenerator
// - You may not sell this software or use it in products/services for monetary gain.
// 
// Full license text is available in the LICENSE file included with this source code.

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Neuron.hpp"

std::random_device WeightRD;
std::mt19937 Wgen(WeightRD());
std::uniform_real_distribution<double> WeightDist(-1.0, 1.0);

struct ZNNColorGenerationModelElythra
{
    Neuron InputNeuron1{0.1};
    Neuron InputNeuron2{0.1};
    Neuron InputNeuron3{0.1};

    Neuron HiddenNeuron1{0.0};
    Neuron HiddenNeuron2{0.0};
    Neuron HiddenNeuron3{0.0};

    Neuron OutputNeuron1{0.0};
    Neuron OutputNeuron2{0.0};
    Neuron OutputNeuron3{0.0};

    double Error_R, Error_G, Error_B, Hidden_Error_1, Hidden_Error_2, Hidden_Error_3, Total_Error = -1;

    double Weight_R_1 = WeightDist(Wgen), Weight_R_2 = WeightDist(Wgen), Weight_R_3 = WeightDist(Wgen);
    double Weight_G_1 = WeightDist(Wgen), Weight_G_2 = WeightDist(Wgen), Weight_G_3 = WeightDist(Wgen);
    double Weight_B_1 = WeightDist(Wgen), Weight_B_2 = WeightDist(Wgen), Weight_B_3 = WeightDist(Wgen);
    double HiddenWeight_R_1 = WeightDist(Wgen), HiddenWeight_R_2 = WeightDist(Wgen), HiddenWeight_R_3 = WeightDist(Wgen);
    double HiddenWeight_G_1 = WeightDist(Wgen), HiddenWeight_G_2 = WeightDist(Wgen), HiddenWeight_G_3 = WeightDist(Wgen);
    double HiddenWeight_B_1 = WeightDist(Wgen), HiddenWeight_B_2 = WeightDist(Wgen), HiddenWeight_B_3 = WeightDist(Wgen);
    double Bias = 0;

    double Learning_Rate = 1;
    double ErrorThreshold = 0.0;

    void TrainZNN(std::vector<double> TrainingBias, std::vector<double> TrainingData);
    std::vector<double> GenerateColorFromTraining();
};

void ZNNColorGenerationModelElythra::TrainZNN(std::vector<double> TrainingBias, std::vector<double> TrainingData){

    Weight_R_1 = WeightDist(Wgen), Weight_R_2 = WeightDist(Wgen), Weight_R_3 = WeightDist(Wgen);
    Weight_G_1 = WeightDist(Wgen), Weight_G_2 = WeightDist(Wgen), Weight_G_3 = WeightDist(Wgen);
    Weight_B_1 = WeightDist(Wgen), Weight_B_2 = WeightDist(Wgen), Weight_B_3 = WeightDist(Wgen);
    HiddenWeight_R_1 = WeightDist(Wgen), HiddenWeight_R_2 = WeightDist(Wgen), HiddenWeight_R_3 = WeightDist(Wgen);
    HiddenWeight_G_1 = WeightDist(Wgen), HiddenWeight_G_2 = WeightDist(Wgen), HiddenWeight_G_3 = WeightDist(Wgen);
    HiddenWeight_B_1 = WeightDist(Wgen), HiddenWeight_B_2 = WeightDist(Wgen), HiddenWeight_B_3 = WeightDist(Wgen);

    int iteration = 0;
    double Final_Error;

    Weight_R_1 = .5, Weight_R_2 = .5, Weight_R_3 = .5;
    Weight_G_1 = .5, Weight_G_2 = .5, Weight_G_3 = .5;
    Weight_B_1 = .5, Weight_B_2 = .5, Weight_B_3 = .5;
    HiddenWeight_R_1 = .5, HiddenWeight_R_2 = .5, HiddenWeight_R_3 = .5;
    HiddenWeight_G_1 = .5, HiddenWeight_G_2 = .5, HiddenWeight_G_3 = .5;
    HiddenWeight_B_1 = .5, HiddenWeight_B_2 = .5, HiddenWeight_B_3 = .5;
    Bias = 0;

    while (fabs(Total_Error) > ErrorThreshold){

        if (iteration >= TrainingData.size()){
            break;
        };

        InputNeuron1.Value = TrainingData[iteration];
        InputNeuron2.Value = TrainingData[iteration+1];
        InputNeuron3.Value = TrainingData[iteration+2];

        HiddenNeuron1.Value = (InputNeuron1.Value * Weight_R_1) + (InputNeuron2.Value * Weight_R_2) + (InputNeuron3.Value * Weight_R_3) + Bias;
        HiddenNeuron2.Value = (InputNeuron1.Value * Weight_G_1) + (InputNeuron2.Value * Weight_G_2) + (InputNeuron3.Value * Weight_G_3) + Bias;
        HiddenNeuron3.Value = (InputNeuron1.Value * Weight_B_1) + (InputNeuron2.Value * Weight_B_2) + (InputNeuron3.Value * Weight_B_3) + Bias;

        HiddenNeuron1.ActivateNeuron();
        HiddenNeuron2.ActivateNeuron();
        HiddenNeuron3.ActivateNeuron();

        OutputNeuron1.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_R_1) + (HiddenNeuron1.ActivatedValue * HiddenWeight_R_2) + (HiddenNeuron1.ActivatedValue * HiddenWeight_R_3) + Bias;
        OutputNeuron2.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_G_1) + (HiddenNeuron2.ActivatedValue * HiddenWeight_G_2) + (HiddenNeuron2.ActivatedValue * HiddenWeight_G_3) + Bias;
        OutputNeuron3.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_B_1) + (HiddenNeuron3.ActivatedValue * HiddenWeight_B_2) + (HiddenNeuron3.ActivatedValue * HiddenWeight_B_3) + Bias;

        OutputNeuron1.ActivateNeuron();
        OutputNeuron2.ActivateNeuron();
        OutputNeuron3.ActivateNeuron();

        Error_R = OutputNeuron1.ActivatedValue - TrainingBias[iteration];
        Error_G = OutputNeuron2.ActivatedValue - TrainingBias[iteration+1];
        Error_B = OutputNeuron3.ActivatedValue - TrainingBias[iteration+2];

        Hidden_Error_1 = (Error_R * HiddenWeight_R_1 + Error_R * HiddenWeight_R_2 + Error_R * HiddenWeight_R_3) * HiddenNeuron1.ActivatedValue * (1.0 - HiddenNeuron1.ActivatedValue);
        Hidden_Error_2 = (Error_G * HiddenWeight_G_1 + Error_G * HiddenWeight_G_2 + Error_G * HiddenWeight_G_3) * HiddenNeuron2.ActivatedValue * (1.0 - HiddenNeuron2.ActivatedValue);
        Hidden_Error_3 = (Error_B * HiddenWeight_B_1 + Error_B * HiddenWeight_B_2 + Error_B * HiddenWeight_B_3) * HiddenNeuron3.ActivatedValue * (1.0 - HiddenNeuron3.ActivatedValue);

        Total_Error = (fabs(Error_R) + fabs(Error_G) + fabs(Error_B) + fabs(Hidden_Error_1) + fabs(Hidden_Error_2) + fabs(Hidden_Error_3)) / 6;
        Final_Error = Total_Error;

        if (fabs(Total_Error) > ErrorThreshold){
            Weight_R_1 -= Learning_Rate * Error_R * InputNeuron1.Value;
            Weight_R_2 -= Learning_Rate * Error_R * InputNeuron2.Value;
            Weight_R_3 -= Learning_Rate * Error_R * InputNeuron3.Value;

            Weight_G_1 -= Learning_Rate * Error_G * InputNeuron1.Value;
            Weight_G_2 -= Learning_Rate * Error_G * InputNeuron2.Value;
            Weight_G_3 -= Learning_Rate * Error_G * InputNeuron3.Value;

            Weight_B_1 -= Learning_Rate * Error_B * InputNeuron1.Value;
            Weight_B_2 -= Learning_Rate * Error_B * InputNeuron2.Value;
            Weight_B_3 -= Learning_Rate * Error_B * InputNeuron3.Value;

            HiddenWeight_R_1 -= Learning_Rate * Error_R * HiddenNeuron1.ActivatedValue;
            HiddenWeight_R_2 -= Learning_Rate * Error_R * HiddenNeuron1.ActivatedValue;
            HiddenWeight_R_3 -= Learning_Rate * Error_R * HiddenNeuron1.ActivatedValue;

            HiddenWeight_G_1 -= Learning_Rate * Error_G * HiddenNeuron2.ActivatedValue;
            HiddenWeight_G_2 -= Learning_Rate * Error_G * HiddenNeuron2.ActivatedValue;
            HiddenWeight_G_3 -= Learning_Rate * Error_G * HiddenNeuron2.ActivatedValue;

            HiddenWeight_B_1 -= Learning_Rate * Error_B * HiddenNeuron3.ActivatedValue;
            HiddenWeight_B_2 -= Learning_Rate * Error_B * HiddenNeuron3.ActivatedValue;
            HiddenWeight_B_3 -= Learning_Rate * Error_B * HiddenNeuron3.ActivatedValue;

            Bias -= Learning_Rate * (Error_R + Error_G + Error_B)/3;
        }

        iteration += 3;
    }

    std::cout << "Model trained with " << ((1 - Total_Error) * 100) << "% Accuracy!" << std::endl;
}

std::vector<double> ZNNColorGenerationModelElythra::GenerateColorFromTraining(){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 999);

    double RR, RG, RB;
    RR = (double)dist(gen)/999;
    RG = (double)dist(gen)/999;
    RB = (double)dist(gen)/999;

    InputNeuron1.Value = RR;
    InputNeuron2.Value = RG;
    InputNeuron3.Value = RB;

    HiddenNeuron1.Value = (InputNeuron1.Value * Weight_R_1) + (InputNeuron2.Value * Weight_R_2) + (InputNeuron3.Value * Weight_R_3) + Bias;
    HiddenNeuron2.Value = (InputNeuron1.Value * Weight_G_1) + (InputNeuron2.Value * Weight_G_2) + (InputNeuron3.Value * Weight_G_3) + Bias;
    HiddenNeuron3.Value = (InputNeuron1.Value * Weight_B_1) + (InputNeuron2.Value * Weight_B_2) + (InputNeuron3.Value * Weight_B_3) + Bias;

    HiddenNeuron1.ActivateNeuron();
    HiddenNeuron2.ActivateNeuron();
    HiddenNeuron3.ActivateNeuron();

    OutputNeuron1.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_R_1) + (HiddenNeuron1.ActivatedValue * HiddenWeight_R_2) + (HiddenNeuron1.ActivatedValue * HiddenWeight_R_3) + Bias;
    OutputNeuron2.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_G_1) + (HiddenNeuron2.ActivatedValue * HiddenWeight_G_2) + (HiddenNeuron2.ActivatedValue * HiddenWeight_G_3) + Bias;
    OutputNeuron3.Value = (HiddenNeuron1.ActivatedValue * HiddenWeight_B_1) + (HiddenNeuron3.ActivatedValue * HiddenWeight_B_2) + (HiddenNeuron3.ActivatedValue * HiddenWeight_B_3) + Bias;

    OutputNeuron1.ActivateNeuron();
    OutputNeuron2.ActivateNeuron();
    OutputNeuron3.ActivateNeuron();

    return {OutputNeuron1.ActivatedValue, OutputNeuron2.ActivatedValue, OutputNeuron3.ActivatedValue};
}
