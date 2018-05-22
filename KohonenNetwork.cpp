#include "KohonenNetwork.h"

KohonenNetwork::KohonenNetwork(vector<vector<double>> weights) {
	for (int i = 0; i < NEURON_NUMBER; ++i)
		neurons.push_back(*(new Neuron(weights[i])));
}

void KohonenNetwork::UpdatePotentials(int winner, int epoch) {
	for (int i = 0; i < NEURON_NUMBER; ++i) {
		if (i == winner)
			neurons[i].PotentialUpdate(true, epoch);
		else
			neurons[i].PotentialUpdate(false, epoch);
	}
}

void KohonenNetwork::StartMinDistance(int& winner, double& min_distance, vector<double> object) {
	while (true) {
		if (neurons[winner].GetPotential() >= MIN_POTENTIAL) {
			min_distance = neurons[winner].GetDistance(object);
			return;
		}
		++winner;
		if (winner == NEURON_NUMBER)
			return;
	}
}

void KohonenNetwork::MinDistance(int& winner, double& min_distance, vector<double> object) {
	for (int i = 0; i < NEURON_NUMBER; ++i) {
		if (neurons[i].GetPotential() < MIN_POTENTIAL)
			continue;
		if (neurons[i].GetDistance(object) < min_distance) {
			min_distance = neurons[i].GetDistance(object);
			winner = i;
		}
	}
}

int KohonenNetwork::GetWinner(vector<double> object) {
	double min_distance;
	int winner = 0;

	StartMinDistance(winner, min_distance, object);
	MinDistance(winner, min_distance, object);

	return winner;
}

void KohonenNetwork::Train(vector<vector<double>> objects) {
	int winner, j;
	for (int i = 1; i <= EPOCH_NUMBER; ++i) {
			j = rand() % objects.size();

			winner = GetWinner(objects[j]);
			
			if (winner < NEURON_NUMBER)
				neurons[winner].WeightsUpdate(1 / i, objects[j]);

			UpdatePotentials(winner, i);
	}
}

int KohonenNetwork::GetResult(vector<double> object) {
	double min_distance = neurons[0].GetDistance(object);
	int winner = 0;

	for (int i = 0; i < NEURON_NUMBER; ++i) {
		if (neurons[i].GetDistance(object) < min_distance) {
			min_distance = neurons[i].GetDistance(object);
			winner = i;
		}
	}

	return winner;
}