// 股票作业.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#define W1 0.5
#define W2 0.5

vector<double> Data_CAC;
vector<double> Data_BNP;
vector<double> Data_DANOME;
vector<double> Data_IMERYS;
vector<double> Data_PEUGEOT;
vector<double> Data_TOTAL;
vector<double> Rm_CAC;
vector<double> Ri_BNP;
vector<double> Ri_DANOME;
vector<double> Ri_IMERYS;
vector<double> Ri_PEUGEOT;
vector<double> Ri_TOTAL;

string Trim(string& str);
void Get_Data(const string& s, vector<double>& data);
void Get_Return_Rate(const vector<double>& data, vector<double>& Rm);
double Cov(const vector<double>& X, const vector<double>& Y);
double Var(const vector<double>& X);
double E(const vector<double>& X);
int main()
{
	Get_Data("CAC.csv", Data_CAC);
	Get_Data("BNP Paribas.PA.csv", Data_BNP);
	Get_Data("DANOME.csv", Data_DANOME);
	Get_Data("IMERYS.csv", Data_IMERYS);
	Get_Data("PEUGEOT.csv", Data_PEUGEOT);
	Get_Data("TOTAL.csv", Data_TOTAL);
	Get_Return_Rate(Data_CAC, Rm_CAC);
	Get_Return_Rate(Data_BNP, Ri_BNP);
	Get_Return_Rate(Data_DANOME, Ri_DANOME);
	Get_Return_Rate(Data_IMERYS, Ri_IMERYS);
	Get_Return_Rate(Data_PEUGEOT, Ri_PEUGEOT);
	Get_Return_Rate(Data_TOTAL, Ri_TOTAL);
	double Beta_BNP, Beta_DANOME, Beta_IMERYS, Beta_PEUGEOT, Beta_TOTAL;
	Beta_BNP = Cov(Rm_CAC, Ri_BNP) / Var(Rm_CAC);
	Beta_DANOME = Cov(Rm_CAC, Ri_DANOME) / Var(Rm_CAC);
	Beta_IMERYS = Cov(Rm_CAC, Ri_IMERYS) / Var(Rm_CAC);
	Beta_PEUGEOT = Cov(Rm_CAC, Ri_PEUGEOT) / Var(Rm_CAC);
	Beta_TOTAL = Cov(Rm_CAC, Ri_TOTAL) / Var(Rm_CAC);
	cout << "各支股票的Beta值:" << endl;
	cout <<"BNP:"<<Beta_BNP << "  DANOME:" << Beta_DANOME << "  IMERYS:" << Beta_IMERYS << "  PEUGEOT:" << Beta_PEUGEOT << "  TOTAL:" << Beta_TOTAL << endl;
	//以下一下分别计算不同投资组合的方差和收益
	long double Var_BNP_DANOME = sqrt(powf(W1, 2)*powf(Var(Ri_BNP),2) + powf(W2, 2)*powf(Var(Ri_DANOME),2) + 2 * W1*W2*Cov(Ri_BNP, Ri_DANOME));
	double E_BNP_DANOME = W1 * E(Ri_BNP) + W2 * E(Ri_DANOME);
	cout << "BNP-DANOME投资组合:收益:" << E_BNP_DANOME << "   方差:" << Var_BNP_DANOME<<endl;
	//分割线--------------------
	double Var_BNP_IMERYS = sqrt(powf(W1, 2)*powf(Var(Ri_BNP),2) + powf(W2, 2)*powf(Var(Ri_IMERYS),2) + 2 * W1*W2*Cov(Ri_BNP, Ri_IMERYS));
	double E_BNP_IMERYS = W1 * E(Ri_BNP) + W2 * E(Ri_IMERYS);
	cout << "BNP-IMERYS投资组合:收益:" << E_BNP_IMERYS << "   方差:" << Var_BNP_IMERYS << endl;
	//分割线--------------------
	double Var_BNP_PEUGEOT = sqrt(powf(W1, 2)*powf(Var(Ri_BNP), 2) + powf(W2, 2)*powf(Var(Ri_PEUGEOT),2) + 2 * W1*W2*Cov(Ri_BNP, Ri_PEUGEOT));
	double E_BNP_PEUGEOT = W1 * E(Ri_BNP) + W2 * E(Ri_PEUGEOT);
	cout << "BNP-PEUGEOT投资组合:收益:" << E_BNP_PEUGEOT << "   方差:" << Var_BNP_PEUGEOT << endl;
	//分割线--------------------
	double Var_BNP_TOTAL = sqrt(powf(W1, 2)*powf(Var(Ri_BNP), 2) + powf(W2, 2)*powf(Var(Ri_TOTAL),2) + 2 * W1*W2*Cov(Ri_BNP, Ri_TOTAL));
	double E_BNP_TOTAL = W1 * E(Ri_BNP) + W2 * E(Ri_TOTAL);
	cout << "BNP-TOTAL投资组合:收益:" << E_BNP_TOTAL << "   方差:" << Var_BNP_TOTAL << endl;
	//分割线--------------------
	double Var_DANOME_IMERYS = sqrt(powf(W1, 2)*powf(Var(Ri_DANOME),2) + powf(W2, 2)*powf(Var(Ri_IMERYS),2) + 2 * W1*W2*Cov(Ri_DANOME, Ri_IMERYS));
	double E_DANOME_IMERYS = W1 * E(Ri_DANOME) + W2 * E(Ri_IMERYS);
	cout << "DANOME-IMERYS投资组合:收益:" << E_DANOME_IMERYS << "   方差:" << Var_DANOME_IMERYS << endl;
	//分割线--------------------
	double Var_DANOME_PEUGEOT = sqrt(powf(W1, 2)*powf(Var(Ri_DANOME), 2) + powf(W2, 2)*powf(Var(Ri_PEUGEOT),2) + 2 * W1*W2*Cov(Ri_DANOME, Ri_PEUGEOT));
	double E_DANOME_PEUGEOT = W1 * E(Ri_DANOME) + W2 * E(Ri_PEUGEOT);
	cout << "DANOME-PEUGEOT投资组合:收益:" << E_DANOME_PEUGEOT << "   方差:" << Var_DANOME_PEUGEOT << endl;
	//分割线--------------------
	double Var_DANOME_TOTAL = sqrt(powf(W1, 2)*powf(Var(Ri_DANOME),2) + powf(W2, 2)*powf(Var(Ri_TOTAL), 2) + 2 * W1*W2*Cov(Ri_DANOME, Ri_TOTAL));
	double E_DANOME_TOTAL = W1 * E(Ri_DANOME) + W2 * E(Ri_TOTAL);
	cout << "DANOME-TOTAL投资组合:收益:" << E_DANOME_TOTAL << "   方差:" << Var_DANOME_TOTAL << endl;
	//分割线--------------------
	double Var_IMERYS_PEUGEOT = sqrt(powf(W1, 2)*powf(Var(Ri_IMERYS), 2) + powf(W2, 2)*powf(Var(Ri_PEUGEOT), 2) + 2 * W1*W2*Cov(Ri_IMERYS, Ri_PEUGEOT));
	double E_IMERYS_PEUGEOT = W1 * E(Ri_IMERYS) + W2 * E(Ri_PEUGEOT);
	cout << "IMERYS-PEUGEOT投资组合:收益:" << E_IMERYS_PEUGEOT << "   方差:" << Var_IMERYS_PEUGEOT << endl;
	//分割线--------------------
	double Var_IMERYS_TOTAL = sqrt(powf(W1, 2)*powf(Var(Ri_IMERYS), 2) + powf(W2, 2)*powf(Var(Ri_TOTAL), 2) + 2 * W1*W2*Cov(Ri_IMERYS, Ri_TOTAL));
	double E_IMERYS_TOTAL = W1 * E(Ri_IMERYS) + W2 * E(Ri_TOTAL);
	cout << "IMERYS-TOTAL投资组合:收益:" << E_IMERYS_TOTAL << "   方差:" << Var_IMERYS_TOTAL << endl;
	//分割线--------------------
	double Var_PEUGEOT_TOTAL = sqrt(powf(W1, 2)*powf(Var(Ri_PEUGEOT), 2) + powf(W2, 2)*powf(Var(Ri_TOTAL), 2) + 2 * W1*W2*Cov(Ri_PEUGEOT, Ri_TOTAL));
	double E_PEUGEOT_TOTAL = W1 * E(Ri_PEUGEOT) + W2 * E(Ri_TOTAL);
	cout << "PEUGEOT-TOTAL投资组合:收益:" << E_PEUGEOT_TOTAL << "   方差:" << Var_PEUGEOT_TOTAL << endl;
	system("pause");
}

string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

void Get_Data(const string& s, vector<double>& data)
{
	ifstream fin(s);
	string line;
	int flag = 0;//确保不执行第一行
	while (getline(fin, line))
	{
		if (flag)
		{
			istringstream sin(line);
			vector<string> fields;
			string field;
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符  
			{
				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中  
			}
			string Adj_Close = Trim(fields[5]);
			data.push_back(atof(const_cast<const char *>(Adj_Close.c_str())));
		}
		++flag;
	}
}

void Get_Return_Rate(const vector<double>& data, vector<double>& Rm)
{
	for (auto i = 1; i < data.size(); ++i)
		Rm.push_back((data[i] - data[i - 1]) / data[i - 1]);
}

double E(const vector<double>& X)
{
	double Sum = 0;
	for (auto i = X.cbegin(); i != X.cend(); ++i)
		Sum += *i;
	return Sum / X.size();
}

double Cov(const vector<double>& X, const vector<double>& Y)
{
	vector<double> tmp;
	for (auto i = X.cbegin(), j = Y.cbegin(); i != X.cend() && j != Y.cend(); ++i, ++j)
		tmp.push_back((*i)*(*j));
	return E(tmp)-E(X)*E(Y);
}

double Var(const vector<double>& X)
{
	vector<double> tmp;
	for (auto i = X.cbegin(); i != X.cend(); ++i)
		tmp.push_back((*i)*(*i));
	return E(tmp)-E(X)*E(X);
}