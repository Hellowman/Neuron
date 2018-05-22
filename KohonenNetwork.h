#pragma once

#include "Constants.h"
#include "Neuron.h"
#include <iostream>

using namespace std;

class KohonenNetwork {
	vector<Neuron> neurons;
	void UpdatePotentials(int winner, int epoch); // Обновление потенциалов нейронов
	int GetWinner(vector<double> object); // Получить индекс нейрона-победителя
	void StartMinDistance(int& winner, double& min_distance, vector<double> object);
	void MinDistance(int& winner, double& min_distance, vector<double> object);

public:
	KohonenNetwork(vector<vector<double>> weights);
	void Train(vector<vector<double>> objects); // Обучение нейронной сети
	int GetResult(vector<double> object); // Метод, определяющий, к какому кластеру принадлежит объект
};