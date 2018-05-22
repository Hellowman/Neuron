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
	void WeightsUpdate(double learning_rate, vector<double> x); // ���������� ����� �������
	void PotentialUpdate(bool flag, int epoch); // ���������� ���������� �������
	double GetDistance(vector<double> x); // ���������� ��������� �� ������� �� ������ ��������
	double GetPotential();
};