#include "Neuron.h"

Neuron::Neuron(vector<double> weights) {
	this->weights = weights;
	potential = START_POTENTIAL;
}

void Neuron::WeightsUpdate(double learning_rate, vector<double> x) {
	for (int i = 0; i < weights.size(); ++i)
		weights[i] += learning_rate * (x[i] - weights[i]);
}

void Neuron::PotentialUpdate(bool flag, int epoch) {
	if (flag)
		potential -= POTENTIAL_CHANGING;
	else
		potential += POTENTIAL_CHANGING / epoch;
}

double Neuron::GetDistance(vector<double> x) {
	double result = 0;
	for (int i = 0; i < weights.size(); ++i)
		result += pow(x[i] - weights[i], 2);
	return sqrt(result);
}

double Neuron::GetPotential() {
	return potential;
}