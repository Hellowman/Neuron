#pragma once

#include "Constants.h"
#include "Neuron.h"
#include <iostream>

using namespace std;

class KohonenNetwork {
	vector<Neuron> neurons;
	void UpdatePotentials(int winner, int epoch); // ���������� ����������� ��������
	int GetWinner(vector<double> object); // �������� ������ �������-����������
	void StartMinDistance(int& winner, double& min_distance, vector<double> object);
	void MinDistance(int& winner, double& min_distance, vector<double> object);

public:
	KohonenNetwork(vector<vector<double>> weights);
	void Train(vector<vector<double>> objects); // �������� ��������� ����
	int GetResult(vector<double> object); // �����, ������������, � ������ �������� ����������� ������
};