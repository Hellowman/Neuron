#include "KohonenNetwork.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

double StringToDouble(string str) {
	istringstream ss(str);
	double a;
	ss >> a;
	return a;
}

vector<string> LineInParts(string line) {
	string line_part;
	stringstream ss(line);
	vector <string> line_array;
	while (ss >> line_part)
		line_array.push_back(line_part);
	return line_array;
}

string GetDistrict(int i) {
	switch (i) {
	case 0:
		return "ÖÀÎ";
	case 1:
		return "ÑÀÎ";
	case 2:
		return "ÑÂÀÎ";
	case 3:
		return "ÂÀÎ";
	case 4:
		return "ŞÂÀÎ";
	case 5:
		return "ŞÀÎ";
	case 6:
		return "ŞÇÀÎ";
	case 7:
		return "ÇÀÎ";
	case 8:
		return "ÑÇÀÎ";
	case 9:
		return "ÍîâîÌÑÊ";
	case 10:
		return "Çåëåíîãğàä";
	default:
		return "error";
	}
}

int GetDistrictIndex(string district) {
	if (district == "ÖÀÎ")
		return 0;
	else if (district == "ÑÀÎ")
		return 1;
	else if (district == "ÑÂÀÎ")
		return 2;
	else if (district == "ÂÀÎ")
		return 3;
	else if (district == "ŞÂÀÎ")
		return 4;
	else if (district == "ŞÀÎ")
		return 5;
	else if (district == "ŞÇÀÎ")
		return 6;
	else if (district == "ÇÀÎ")
		return 7;
	else if (district == "ÑÇÀÎ")
		return 8;
	else if (district == "ÍîâîÌÑÊ")
		return 9;
	else if (district == "Çåëåíîãğàä")
		return 10;
	else
		return -1;
}

// Ñ÷èòûâàíèå âõîäíûõ äàííûõ èç ôàéëà
void GetData(vector<vector<double>>& points, vector<int>& districts) {
	string line;
	vector<string> str_data;

	ifstream fin("libraries.txt", ios::in);
	fin.seekg(0);

	while (!fin.eof()) {
		getline(fin, line);
		str_data = LineInParts(line);
		points.push_back(vector<double>{StringToDouble(str_data[1]), StringToDouble(str_data[2])});
		districts.push_back(GetDistrictIndex(str_data[3]));
	}

	fin.close();
}

// Çàïèñü ğåçóëüòàòîâ â âûõîäíîé ôàéë
void WriteInResults(vector<int> result, double error) {
	ofstream fout("result.txt");

	vector<vector<double>> points;
	vector<int> districts;

	GetData(points, districts);

	for (int i = 0; i < POINTS_NUMBER; ++i)
		fout << i + 1 << ". " << points[i][0] << " " <<
		points[i][1] << " real: " << GetDistrict(districts[i]) << " network:" << GetDistrict(result[i]) << endl;

	fout << error / POINTS_NUMBER * 100 << "%";

	fout.close();
}

// Âû÷èñëåíèå îøèáêè
double Error(vector<int> result, vector<int> districts) {
	int errors = 0;
	for (int i = 0; i < POINTS_NUMBER; ++i) {
		if (result[i] != districts[i])
			++errors;
	}
	return errors;
}

// Ôóíêöèÿ êëàñòåğèçàöèè äàííûõ
void Clastering(KohonenNetwork* network) {
	vector<vector<double>> points;
	vector<int> result, districts;

	GetData(points, districts);

	network->Train(points);

	for (int i = 0; i < POINTS_NUMBER; ++i)
		result.push_back(network->GetResult(points[i]));

	WriteInResults(result, Error(result, districts));
}

vector<vector<double>> InitCenterPoints() {
	return{ { 37.6714, 55.7387}, { 37.5715, 55.8221}, { 37.6714, 55.8221 }, // ÖÀÎ, ÑÀÎ, ÑÂÀÎ
	{ 37.8215, 55.7721 }, { 37.805, 55.6718}, { 37.7216, 55.6222 }, // ÂÀÎ, ŞÂÀÎ, ŞÀÎ
	{ 37.5883, 55.6388 }, { 37.5406, 55.7136 }, { 37.4881, 55.8055 }, // ŞÇÀÎ, ÇÀÎ, ÑÇÀÎ
	{ 37.405, 55.5554 }, { 37.2179, 55.9923 } }; // ÍîâîÌÑÊ, Çåëåíîãğàä
}

int main() {
	KohonenNetwork* network = new KohonenNetwork(InitCenterPoints());

	Clastering(network);

	system("pause");
	return 0;
}