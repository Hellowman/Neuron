#pragma once

#define NUMBER_OF_SETS 16
#define NUMBER_OF_WEIGHTS 5
#define LEARNING_RATE 0.3
#define NUMBER_OF_VARIABLES 4
#define EPOCH_LIMIT 1000

____________________


#pragma once

#include <vector>
#include "Constants.h"

using namespace std;

class StepNeuron
{
    vector<double> weights;
    double GetNet(vector<int> variables);
public:
    StepNeuron();
    int ActivationFunction(vector<int> variables);
    void WeightsUpdate(vector<int> variables, int error);
    vector<double> GetWeights();
    void WeightsReset();
};
____________________

#include "StepNeuron.h"

StepNeuron::StepNeuron()
{
    weights.resize(NUMBER_OF_WEIGHTS);
}

double StepNeuron::GetNet(vector<int> variables)
{
    double net = 0;
    for (int i = 1; i <= NUMBER_OF_VARIABLES; ++i)
        net += weights[i] * variables[i - 1];
    net += weights[0];
    return net;
}

int StepNeuron::ActivationFunction(vector<int> variables)
{
    double net = GetNet(variables);
    return (net >= 0) ? 1 : 0;
}

void StepNeuron::WeightsUpdate(vector<int> variables, int error)
{
    weights[0] += LEARNING_RATE * error;
    for (int i = 1; i < NUMBER_OF_WEIGHTS; ++i)
    {
        weights[i] += LEARNING_RATE * error * variables[i - 1];
    }
}

vector<double> StepNeuron::GetWeights()
{
    return weights;
}

void StepNeuron::WeightsReset()
{
    for (int i = 0; i < NUMBER_OF_WEIGHTS; ++i)
        weights[i] = 0;
}

____________________


#pragma once

#include <cmath>
#include <vector>
#include "Constants.h"

using namespace std;

class SoftsignNeuron
{
    vector<double> weights;
    double GetNet(vector<int> variables);
    double Derivative(double net);
public:
    SoftsignNeuron();
    int ActivationFunction(vector<int> variables);
    void WeightsUpdate(vector<int> variables, int error);
    vector<double> GetWeights();
    void WeightsReset();
};


____________________


#include "SoftsignNeuron.h"

SoftsignNeuron::SoftsignNeuron()
{
    weights.resize(NUMBER_OF_WEIGHTS);
}

double SoftsignNeuron::GetNet(vector<int> variables)
{
    double net = 0;
    for (int i = 1; i <= NUMBER_OF_VARIABLES; ++i)
        net += weights[i] * variables[i - 1];
    net += weights[0];
    return net;
}

double SoftsignNeuron::Derivative(double net)
{
    return 0.5*(1 / pow((1 + fabs(net)), 2));
}

int SoftsignNeuron::ActivationFunction(vector<int> variables)
{
    double net = GetNet(variables);
    double out = 0.5*((net / (1 + fabs(net))) + 1);
    return (out >= 0.5) ? 1 : 0;
}

void SoftsignNeuron::WeightsUpdate(vector<int> variables, int error)
{
    double der = Derivative(GetNet(variables));
    weights[0] += LEARNING_RATE * error * der;
    for (int i = 1; i < NUMBER_OF_WEIGHTS; ++i)
    {
        weights[i] += LEARNING_RATE * error * variables[i - 1] * der;
    }
}

vector<double> SoftsignNeuron::GetWeights()
{
    return weights;
}

void SoftsignNeuron::WeightsReset()
{
    for (int i = 0; i < NUMBER_OF_WEIGHTS; ++i)
        weights[i] = 0;
}




____________________



#pragma once

#include<vector>

using namespace std;

class VariablesCombination
{
    /*
     training_vectors - индексы наборов переменных обучающей выборки
     в соответствии с лексикографическим порядком,
     testing_vectors - индексы наборов переменных тестирующей выборки
     в соответствии с лексикографическим порядком.
     */
    vector<int> training_vectors, testing_vectors;
public:
    VariablesCombination();
    void AddTrainingVector(int index);
    void AddTestingVector(int index);
    vector<int> GetTrainigVectors();
    vector<int> GetTestingVectors();
};



____________________


#include "VariablesCombination.h"

VariablesCombination::VariablesCombination() {}

void VariablesCombination::AddTrainingVector(int index)
{
    training_vectors.push_back(index);
}

void VariablesCombination::AddTestingVector(int index)
{
    testing_vectors.push_back(index);
}

vector<int> VariablesCombination::GetTrainigVectors()
{
    return training_vectors;
}

vector<int> VariablesCombination::GetTestingVectors()
{
    return testing_vectors;
}





____________________




#include <iostream>
#include <vector>
#include <algorithm>
#include "Constants.h"
#include "StepNeuron.h"
#include "SoftsignNeuron.h"
#include "VariablesCombination.h"
using namespace std;

bool Bfunc()
{
    
    bool x1 = 0, x2 = 0, x3 = 0, x4 = 0, F=0 ;
    unsigned int z = 16;
    cout << " F=!(x3+!(x4)+!(x1+x2))\n\n";
    cout << " x1 " << " x2 " << " x3 " << " x4 ";
    cout << "  F\n";
    cout << "---------------------\n";
    while (z--)
    {
        F=!(x3 && !(x4) && !(x1 && x2));
        cout << "| " << x1 << " | " << x2 << " | " << x3 << " | " << x4;
        cout << " | " << F << " | \n";
        
        {
            if (z > 8) x1 = 0;
            else x1 = 1;
        }
        {
            if (z > 12 || (z < 9 && z > 4)) x2 = 0;
            else x2 = 1;
        }
        {
            if (z > 14 || (z < 13 && z > 10) || (z < 9 && z > 6) || (z < 5 && z > 2)) x3 = 0;
            else x3 = 1;
        }
        {
            if (z % 2 == 0) x4 = 0;
            else x4 = 1;
        }
    }
    cout << "---------------------\n";
    cout << "1101110111011111\n";
    return 0;
}


void Print(int err, int ep, vector<int> res, vector<double> weights)
{
    cout << "Total error at epoch " << ep << ": " << err << ", result: ";
    for (int i = 0; i < res.size(); ++i)
        cout << res[i];
    cout << ", weights: ";
    for (int i = 0; i < NUMBER_OF_WEIGHTS; ++i)
        cout << weights[i] << " ";
    cout << endl;
}

template <class T> void PrintCurentFunction(T* neuron, vector<vector<int>> var)
{
    for (int i = 0; i < NUMBER_OF_SETS; ++i)
        cout << neuron->ActivationFunction(var[i]);
    cout << endl;
}

void PrintCombination(vector<int> comb, vector<vector<int>> var)
{
    for (int i = 0; i < comb.size(); ++i)
    {
        for (int j = 0; j < var[i].size(); ++j)
            cout << var[comb[i]][j];
        cout << " ";
    }
    cout << endl;
}

unsigned long long int Factorial(int n)
{
    unsigned long long int result = 1;
    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

unsigned long long int NumberOfCombinations(int n, int k)
{
    return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

/*
 Функция возвращает вектор всевозможных комбинаций переменных, которые входят
 в обучающую выборку. Входные параметры:
 n - общее количество наборов, k - количество наборов в обучающей выборке
*/

vector<VariablesCombination> Combinations(int n, int k)
{
    unsigned long long int comb = NumberOfCombinations(n, k);
    vector<VariablesCombination> result(comb);
    
    vector<int> temp(k, 0);
    temp.resize(n, 1);
    int index = 0;
    
    do
    {
        for (int i = 0; i < temp.size(); i++)
        {
            if (!temp[i])
                result[index].AddTrainingVector(i);
            else
                result[index].AddTestingVector(i);
        }
        ++index;
    } while (next_permutation(temp.begin(), temp.end()));
    return result;
}

/*
 Функция проверки результата обучения при помощи тестирующих наборов переменных; при совпадении целевого реального векторов функции на тестирующих наборах возвращается true, иначе - false
 */
template <class T> bool Test(vector<int> testing_vectors, vector<int> true_function, T* neuron, vector<vector <int>> var)
{
    bool flag = true;
    for (int i = 0; i < testing_vectors.size(); ++i)
        if (true_function[testing_vectors[i]] != neuron->ActivationFunction(var[testing_vectors[i]]))
            flag = false;
    return flag;
}

int GetError(vector<int> comb, vector<int> func, vector<int> current_result)
{
    int error = 0;
    for (int i = 0; i < comb.size(); ++i)
    {
        if (func[comb[i]] != current_result[i])
            ++error;
    }
    return error;
}

template <class T> vector<int> GetCurrentResult(T* neuron, vector<vector<int>> var, vector<int> comb)
{
    vector<int> result(comb.size());
    for (int i = 0; i < comb.size(); ++i)
        result[i] = neuron->ActivationFunction(var[comb[i]]);
    return result;
}

/*
 Функция обучения нейрона; при совпадении целевого и реального векторов функции возвращается true,
 иначе - false. входные параметры:
 neuron - обучаемый нейрон, var - вектор наборов переменных,
 func - вектор целевой функции, k - количество наборов переменных в обучающей выборке.
*/
template <class T> bool Train(T& neuron, vector<vector<int>> var, vector<int> func, int k)
{
    vector<double> current_weights;
    int index, error, epoch, sum_error, temp = -1;
    int combinations_number = (int) NumberOfCombinations(NUMBER_OF_SETS, k);
    vector<int> current_result(k);
    vector<VariablesCombination> combinations = Combinations(NUMBER_OF_SETS, k);
    bool flag = false;
    
    for (int i = 0; i < combinations_number; ++i)
    {
        epoch = 0;
        neuron.WeightsReset();
        current_result = GetCurrentResult(&neuron, var, combinations[i].GetTrainigVectors());
        sum_error = GetError(combinations[i].GetTrainigVectors(), func, current_result);
        if (flag)
            Print(sum_error, epoch, current_result, neuron.GetWeights());
        do
        {
            sum_error = 0;
            for (int j = 0; j < k; ++j)
            {
                index = combinations[i].GetTrainigVectors()[j];
                error = func[index] - neuron.ActivationFunction(var[index]);
                neuron.WeightsUpdate(var[index], error);
            }
            current_result = GetCurrentResult(&neuron, var, combinations[i].GetTrainigVectors());
            sum_error = GetError(combinations[i].GetTrainigVectors(), func, current_result);
            ++epoch;
            current_weights = neuron.GetWeights();
            if (flag)
                Print(sum_error, epoch, current_result, current_weights);
            if (!sum_error && Test(combinations[i].GetTestingVectors(), func, &neuron, var) && !flag)
            {
                temp = i;
                i--;
                flag = true;
            }
        }
        while (sum_error && epoch < EPOCH_LIMIT);
        if (flag && (i == temp))
        {
            PrintCurentFunction(&neuron, var);
            cout << "success at variables combination: ";
            PrintCombination(combinations[i].GetTrainigVectors(), var);
            return true;
        }
    }
    return false;
}

//_______________________________________________________________________________________________

int main()
{
    Bfunc();//вывод булевой функции
    StepNeuron* step_neuron = new StepNeuron();//пороговая
    SoftsignNeuron* ss_neuron = new SoftsignNeuron();//сигмоидальная
    vector<vector<int>> variables{ { 0, 0, 0, 0 },{ 0, 0, 0, 1 },{ 0, 0, 1, 0 },{ 0, 0, 1, 1 },
        { 0, 1, 0, 0 },{ 0, 1, 0, 1 },{ 0, 1, 1, 0 },{ 0, 1, 1, 1 },
        { 1, 0, 0, 0 },{ 1, 0, 0, 1 },{ 1, 0, 1, 0 },{ 1, 0, 1, 1 },
        { 1, 1, 0, 0 },{ 1, 1, 0, 1 },{ 1, 1, 1, 0 },{ 1, 1, 1, 1 } };
    vector<int> true_function{ 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1 };
    
    //обучение на всех наборах переменны, пороговая функция активации
    cout << "Step, all combinations" << endl;
    Train(*step_neuron, variables, true_function, NUMBER_OF_SETS);
    cout << endl;
    
    //обучение на всех наборах переменны, сигмоидальная фа
    cout << "Sigmoid, all combinations" << endl;
    Train(*ss_neuron, variables, true_function, NUMBER_OF_SETS);
    cout << endl;
    
    //обучение на части наборах переменных, пороговая фа
    cout << "Step, min combination" << endl;
    for (int i = 1; i <= NUMBER_OF_SETS; ++i)
    {
        if (Train(*step_neuron, variables, true_function, i))
            break;
    }
    cout << endl;
    
    //обучение на части наборах переменных,сигмоидальная фа
    cout << "Sigmoid, min combination" << endl;
    for (int i = 1; i <= NUMBER_OF_SETS; ++i)
    {
        if (Train(*ss_neuron, variables, true_function, i))
            break;
    }
    
    return 0;
}
