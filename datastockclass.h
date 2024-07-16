//#pragma once
//
//#include<iostream>
//#include<string>
//#include<vector>
//#include<fstream>
//#include<random>
//#include <iomanip> // Pentru std::setprecision
//using namespace std;
//
//
//int countCSVLines(const string& filename) {
//	ifstream file(filename);
//	if (!file.is_open()) {
//		cout << "Error opening file: " << filename << endl;
//		return -1;
//	}
//
//	int lineCount = 0;
//	string line;
//	while (getline(file, line)) {
//		if (!line.empty()) {
//			lineCount++;
//		}
//	}
//
//	file.close();
//	return lineCount;
//}
//
//
//
//class InfoStock {
//	vector<string> noStocks;
//	vector<string> timeStamps;
//	vector<double> values;
//
//public:
//
//	vector<string> getNoStocks() {
//		return noStocks;
//	}
//
//	vector<string> getTimeStamps() {
//		return timeStamps;
//	}
//
//	vector<double> getValues() {
//		return values;
//	}
//
//	void setNoStocks(vector<string> noStocks) {
//		this->noStocks = noStocks;
//	}
//
//	void setTimeStamps(vector<string> timeStamps) {
//		this->timeStamps = timeStamps;
//	}
//
//	void setValues(const vector<double> values) {
//		this->values = values;
//	}
//
//	void addNoStock(string noStock) {
//		noStocks.push_back(noStock);
//	}
//
//	void addTimeStamp(string timeStamp) {
//		timeStamps.push_back(timeStamp);
//	}
//
//	void addValue(double value) {
//		values.push_back(value);
//	}
//
//	InfoStock() {
//
//	}
//	InfoStock(vector<string> noStocks, vector<string> timeStamps, vector<double> values)
//	{
//		this->noStocks = noStocks;
//		this->timeStamps = timeStamps;
//		this->values = values;
//	}
//
//	InfoStock(const InfoStock& is) {
//		this->noStocks = is.noStocks;
//		this->timeStamps = is.timeStamps;
//		this->values = is.values;
//	}
//	~InfoStock() {
//
//	}
//
//	InfoStock& operator = (const InfoStock& is) {
//		if (this != &is) {
//			this->noStocks = is.noStocks;
//			this->timeStamps = is.timeStamps;
//			this->values = is.values;
//		}
//		return *this;
//	}
//
//	void addValue(string name, string timeStamp, double value) {
//		this->noStocks.push_back(name);
//		this->timeStamps.push_back(timeStamp);
//		this->values.push_back(value);
//	}
//
//	InfoStock printLine(int poz) {
//		InfoStock auxiliar;
//		//	auxiliar.addValue(this->noStocks[poz], this->timeStamps[poz], this->values[poz]);
//		return auxiliar;
//	}
//
//	friend ostream& operator<<(ostream& os, const InfoStock& is) {
//		os << "-----------------------------------\n";
//		os << "| NoStock | TimeStamp   | Value  |\n";
//		os << "-----------------------------------\n";
//		for (int i = 0; i < is.noStocks.size(); ++i) {
//			os << "|  " << is.noStocks[i]
//				<< "   |  " << is.timeStamps[i]
//				<< " | ";
//			if (is.values[i] < 100) {
//				os << " " << fixed << setprecision(2) << is.values[i];
//			}
//			else {
//				os << fixed << setprecision(2) << is.values[i];
//
//			}
//			os << " |\n";
//		}
//		os << "-----------------------------------\n";
//		return os;
//	}
//
//	friend ofstream& operator<<(ofstream& os, const InfoStock& is) {
//
//		for (int i = 0; i < is.noStocks.size(); ++i) {
//			os << is.noStocks[i] << "," << is.timeStamps[i]
//				<< "," << fixed << setprecision(2) << is.values[i] << endl;
//		}
//		return os;
//	}
//
//
//	void readCSV(const string filename) {
//		ifstream f(filename, ios::in);
//		if (f.is_open()) {
//		
//			int lineCount = 0;
//			string nameS;
//			string timeS = "";
//			double valueStock = 0;
//			string line;
//			int poz = 0;
//			double sumVal = 0;
//
//			if (countCSVLines(filename) >= 30) {
//				if (this->noStocks.size() >= 1) {
//					this->noStocks.clear();
//					this->timeStamps.clear();
//					this->values.clear();
//				}
//				while (getline(f, line)) {
//					poz = line.find(',');
//					nameS = line;
//					nameS = nameS.substr(0, poz);
//					//this->noStocks.push_back(nameS);
//					line.erase(0, poz + 1);
//
//					poz = line.find(',');
//					timeS = line;
//					timeS = timeS.substr(0, poz);
//					line.erase(0, poz + 1);
//
//					valueStock = stod(line);
//
//					addValue(nameS, timeS, valueStock);
//					//cout << line.find(',') << endl;
//					sumVal += valueStock;
//				}
//			}
//			else {
//				cout << "Fisierul nu are peste 30 de inregistrari!" << endl;
//			}
//
//		}
//		else {
//			cout << "Fisierul nu e bun!" << endl;
//		}
//	}
//
//
//
//
//	static InfoStock getOutliers(InfoStock is) {
//		InfoStock outliers;
//		if (is.getValues().size() >= 30) {
//			double suma = 0;
//			for (int i = 0; i < is.getValues().size(); i++) {
//				suma += is.getValues()[i];
//			}
//
//
//			double medie = suma / is.getValues().size();
//			double variance = 0;
//
//			for (int i = 0; i < is.getValues().size(); i++) {
//				variance = variance + pow(is.getValues()[i] - medie, 2);
//			}
//
//			double standarddev = sqrt(variance / is.getValues().size());
//			for (int i = 0; i < is.getValues().size(); i++) {
//				if (abs(is.getValues()[i] - medie) > 2 * standarddev) {
//					cout << is.getNoStocks()[i] << " | " << is.getTimeStamps()[i] << " | " << is.getValues()[i] << " |" << endl;
//					outliers.addValue(is.getNoStocks()[i], is.getTimeStamps()[i], is.getValues()[i]);
//				}
//			}
//		}
//		return outliers;
//	}
//
//	static InfoStock extract30values(InfoStock is) {
//		InfoStock newInfo;
//		if (is.getValues().size() >= 30) {
//			random_device rd;
//			mt19937 gen(rd());
//			uniform_int_distribution<> dis(0, is.getValues().size() - 31); // Intervalul de la 0 la size-31 pentru a asigura 30 de puncte
//			int index = dis(gen);
//			for (int i = index; i < index + 30; i++) {
//				newInfo.addValue(is.getNoStocks()[i], is.getTimeStamps()[i], is.getValues()[i]);
//			}
//		}
//		return newInfo;
//	}
//};
