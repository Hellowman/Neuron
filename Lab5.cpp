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
		return "���";
	case 1:
		return "���";
	case 2:
		return "����";
	case 3:
		return "���";
	case 4:
		return "����";
	case 5:
		return "���";
	case 6:
		return "����";
	case 7:
		return "���";
	case 8:
		return "����";
	case 9:
		return "�������";
	case 10:
		return "����������";
	default:
		return "error";
	}
}

int GetDistrictIndex(string district) {
	if (district == "���")
		return 0;
	else if (district == "���")
		return 1;
	else if (district == "����")
		return 2;
	else if (district == "���")
		return 3;
	else if (district == "����")
		return 4;
	else if (district == "���")
		return 5;
	else if (district == "����")
		return 6;
	else if (district == "���")
		return 7;
	else if (district == "����")
		return 8;
	else if (district == "�������")
		return 9;
	else if (district == "����������")
		return 10;
	else
		return -1;
}

// ���������� ������� ������ �� �����
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

// ������ ����������� � �������� ����
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

// ���������� ������
double Error(vector<int> result, vector<int> districts) {
	int errors = 0;
	for (int i = 0; i < POINTS_NUMBER; ++i) {
		if (result[i] != districts[i])
			++errors;
	}
	return errors;
}

// ������� ������������� ������
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
	return{ { 37.6714, 55.7387}, { 37.5715, 55.8221}, { 37.6714, 55.8221 }, // ���, ���, ����
	{ 37.8215, 55.7721 }, { 37.805, 55.6718}, { 37.7216, 55.6222 }, // ���, ����, ���
	{ 37.5883, 55.6388 }, { 37.5406, 55.7136 }, { 37.4881, 55.8055 }, // ����, ���, ����
	{ 37.405, 55.5554 }, { 37.2179, 55.9923 } }; // �������, ����������
}

int main() {
	KohonenNetwork* network = new KohonenNetwork(InitCenterPoints());

	Clastering(network);

	system("pause");
	return 0;
}