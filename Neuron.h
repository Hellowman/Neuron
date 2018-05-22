#pragma once

#include "Constants.h"
#include <vector>
#include <cmath>

using namespace std;

class Neuron {
	vector<double> weights;
	double potential;

public:
	Neuron(vector<double> weights);
	void WeightsUpdate(double learning_rate, vector<double> x); // Обновление весов нейрона
	void PotentialUpdate(bool flag, int epoch); // Обновление потенциала нейрона
	double GetDistance(vector<double> x); // Рассчитать дистанцию от объекта до центра кластера
	double GetPotential();
};