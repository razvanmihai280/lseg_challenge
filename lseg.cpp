#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<fstream>
#include<random>
#include <iomanip> 
using namespace std;
#if __cplusplus <= 201103L && !defined(__cpp_lib_filesystem)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#pragma once

string getProjectRoot() {
    fs::path currentFilePath(__FILE__);

    fs::path projectRootPath = currentFilePath.parent_path().parent_path();

    projectRootPath /= currentFilePath.parent_path().filename();

    return projectRootPath.string();
}

int countCSVLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return -1;
    }

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }

    file.close();
    return lineCount;
}



class InfoStock {
    vector<string> noStocks;
    vector<string> timeStamps;
    vector<double> values;

public:

    vector<string> getNoStocks() {
        return noStocks;
    }

    vector<string> getTimeStamps() {
        return timeStamps;
    }

    vector<double> getValues() {
        return values;
    }

    void setNoStocks(vector<string> noStocks) {
        this->noStocks = noStocks;
    }

    void setTimeStamps(vector<string> timeStamps) {
        this->timeStamps = timeStamps;
    }

    void setValues(const vector<double> values) {
        this->values = values;
    }

    void addNoStock(string noStock) {
        noStocks.push_back(noStock);
    }

    void addTimeStamp(string timeStamp) {
        timeStamps.push_back(timeStamp);
    }

    void addValue(double value) {
        values.push_back(value);
    }

    InfoStock() {

    }
    InfoStock(vector<string> noStocks, vector<string> timeStamps, vector<double> values)
    {
        this->noStocks = noStocks;
        this->timeStamps = timeStamps;
        this->values = values;
    }

    InfoStock(const InfoStock& is) {
        this->noStocks = is.noStocks;
        this->timeStamps = is.timeStamps;
        this->values = is.values;
    }
    ~InfoStock() {

    }

    InfoStock& operator = (const InfoStock& is) {
        if (this != &is) {
            this->noStocks = is.noStocks;
            this->timeStamps = is.timeStamps;
            this->values = is.values;
        }
        return *this;
    }

    void addValue(string name, string timeStamp, double value) {
        this->noStocks.push_back(name);
        this->timeStamps.push_back(timeStamp);
        this->values.push_back(value);
    }


    friend ostream& operator<<(ostream& os, const InfoStock& is) {
        os << "-----------------------------------\n";
        os << "| NoStock | TimeStamp   | Value  |\n";
        os << "-----------------------------------\n";
        for (int i = 0; i < is.noStocks.size(); ++i) {
            os << "|  " << is.noStocks[i]
                << "   |  " << is.timeStamps[i]
                << " | ";
            if (is.values[i] < 100) {
                os << " " << fixed << setprecision(2) << is.values[i];
            }
            else {
                os << fixed << setprecision(2) << is.values[i];

            }
            os << " |\n";
        }
        os << "-----------------------------------\n";
        return os;
    }

    friend ofstream& operator<<(ofstream& os, const InfoStock& is) {

        for (int i = 0; i < is.noStocks.size(); ++i) {
            os << is.noStocks[i] << "," << is.timeStamps[i]
                << "," << fixed << setprecision(2) << is.values[i] << endl;
        }
        return os;
    }


    void readCSV(const string filename) {
        ifstream f(filename, ios::in);
        if (f.is_open()) {

            int lineCount = 0;
            string nameS;
            string timeS = "";
            double valueStock = 0;
            string line;
            int poz = 0;
            double sumVal = 0;

            if (countCSVLines(filename) >= 30) {
                if (this->noStocks.size() >= 1) {
                    this->noStocks.clear();
                    this->timeStamps.clear();
                    this->values.clear();
                }
                while (getline(f, line)) {
                    poz = line.find(',');
                    nameS = line;
                    nameS = nameS.substr(0, poz);
                    line.erase(0, poz + 1);

                    poz = line.find(',');
                    timeS = line;
                    timeS = timeS.substr(0, poz);
                    line.erase(0, poz + 1);

                    valueStock = stod(line);

                    addValue(nameS, timeS, valueStock);
                    sumVal += valueStock;
                }
            }
            else {
                cout << "Fisierul nu are peste 30 de inregistrari!" << endl;
            }

        }
        else {
            cout << "Fisierul nu e bun!" << endl;
        }
    }




    static InfoStock getOutliers(InfoStock is) {
        InfoStock outliers;
        if (is.getValues().size() >= 30) {
            double suma = 0;
            for (int i = 0; i < is.getValues().size(); i++) {
                suma += is.getValues()[i];
            }


            double medie = suma / is.getValues().size();
            double variance = 0;

            for (int i = 0; i < is.getValues().size(); i++) {
                variance = variance + pow(is.getValues()[i] - medie, 2);
            }

            double standarddev = sqrt(variance / is.getValues().size());
            for (int i = 0; i < is.getValues().size(); i++) {
                if (abs(is.getValues()[i] - medie) > 2 * standarddev) {
                    cout << is.getNoStocks()[i] << " | " << is.getTimeStamps()[i] << " | " << is.getValues()[i] << " |" << endl;
                    outliers.addValue(is.getNoStocks()[i], is.getTimeStamps()[i], is.getValues()[i]);
                }
            }
        }
        return outliers;
    }

    static InfoStock extract30values(InfoStock is) {
        InfoStock newInfo;
        if (is.getValues().size() >= 30) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, is.getValues().size() - 31); 
            int index = dis(gen);
            for (int i = index; i < index + 30; i++) {
                newInfo.addValue(is.getNoStocks()[i], is.getTimeStamps()[i], is.getValues()[i]);
            }
        }
        return newInfo;
    }
};



string findCsvFile(const string& folderPath, const string& stockName) {
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".csv" && entry.path().stem().string() == stockName) {
                return entry.path().string(); 
            }
        }
    }
    return ""; 
}




int main() {

    int choice;
    string stockName;
    InfoStock is;
    InfoStock isThirty;
    InfoStock outliers;

    while (true) {
        cout << "\nSelect language / Selectati limba:" << endl;
        cout << "1. English" << endl;
        cout << "2. Romana" << endl;
        cout << "0. Exit / Iesire" << endl;

        cout << "\nYour choice / Optiunea dvs.: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnglish language selected." << endl;
            while (true) {
                cout << "\nEnglish Menu:" << endl;
                cout << "1. Enter stock name" << endl; 
                cout << "0. Back to Language Selection " << endl;

                cout << "\nYour choice: ";
                cin >> choice;

                switch (choice) {
              
                case 1:
                    cout << "Enter the exact stock name (e.g., TSLA): ";
                    cin >> stockName;
                    for (char& c : stockName) {
                        c = toupper(c);
                    }
                    cout << "Stock name entered: " << stockName << endl;
                    
                    {
                        string filePath = findCsvFile(getProjectRoot(), stockName);
                        if (!filePath.empty()) {
                           
                            string stockPath = stockName + ".csv";
                            int csvOption;
                            while (true) {
                                cout << "\nCSV File Options Menu:" << endl;
                                cout << "1. View CSV file content" << endl;
                                cout << "2. Extract 30 random values and export:" << endl;
                                cout << "3. Exporting CSV with outliers:" << endl;
                                cout << "0. Back to Main Menu" << endl;
                                is.readCSV(filePath);
                                cout << "\nYour choice: ";
                                cin >> csvOption;

                                switch (csvOption) {
                                case 1:{
                                    cout << "Viewing content of CSV file: " << filePath << endl;
                                    
                                    cout << is << endl;
                                    break;
                                }
                                case 2: {
                                    cout << "Extract 30 random values and export: " << filePath << endl;
                                    isThirty = InfoStock::extract30values(is);
                                    cout << isThirty << endl;
                                    string isThirtyName = stockName + "_30values.csv";
                                    ofstream fThirtyValues(isThirtyName, ios::out);
                                    fThirtyValues << isThirty << endl;
                                    fThirtyValues.close();
                                    break;
                                }
                                case 3: {

                                    cout << "Exporting CSV with outliers: " << filePath << endl;
                                    outliers = InfoStock::getOutliers(is);
                                    cout << outliers << endl;
                                    string outliersName = stockName + "_outliers.csv";
                                    ofstream fOutliers(outliersName, ios::out);
                                    fOutliers << outliers << endl;
                                    fOutliers.close();
                                    break;
                                }
                                case 0:
                                    cout << "Returning to Main Menu..." << endl;
                                    break;
                                default:
                                    cout << "Invalid choice. Try again." << endl;
                                    break;
                                }

                                if (csvOption == 0) {
                                    break; 
                                }
                                break;
                            }
                        }
                        else {
                            cout << "CSV file for " << stockName << " not found. Please enter another stock name." << endl;
                        }
                    }
                    break;
                case 0:
                    cout << "Returning to Language Selection..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
                }

                if (choice == 0) {
                    break; 
                }
            }
            break;
        case 2:
            cout << "\nLimba romana selectata." << endl;
            while (true) {
                cout << "\nMeniu Engleza:" << endl;
                cout << "1. Introdu numele actiunii" << endl; 
                cout << "0. Inapoi la selectia limbii" << endl;

                cout << "\nOptiunea ta: ";
                cin >> choice;

                switch (choice) {

                case 1:
                    cout << "Introdu numele exact al actiunii (de exemplu, TSLA): ";
                    cin >> stockName;
                    for (char& c : stockName) {
                        c = toupper(c); 
                    }
                    cout << "Numele actiunii introdus: " << stockName << endl;
                  
                    {
                        string filePath = findCsvFile(getProjectRoot(), stockName);
                        if (!filePath.empty()) {
                         
                            string stockPath = stockName + ".csv";
                           
                            int csvOption;
                            while (true) {
                                cout << "\nMeniu Optiuni Fisier CSV:" << endl;
                                cout << "1. Vezi continutul fisierului CSV" << endl;
                                cout << "2. Extrage 30 de valori aleatorii si exporta:" << endl;
                                cout << "3. Exporta CSV cu outliers:" << endl;
                                cout << "0. Inapoi la Meniul Principal" << endl;
                                is.readCSV(filePath);
                                cout << "\nOptiunea ta: ";
                                cin >> csvOption;

                                switch (csvOption) {
                                case 1: {
                                    cout << "Vizualizare continut fisier CSV: " << filePath << endl;
                                   
                                    cout << is << endl;
                                    break;
                                }
                                case 2: {
                                    cout << "Extrage 30 de valori aleatorii si exporta: " << filePath << endl;
                                  
                                    isThirty = InfoStock::extract30values(is);
                                    cout << isThirty << endl;
                                    string isThirtyName = stockName + "_30values.csv";
                                    ofstream fThirtyValues(isThirtyName, ios::out);
                                    fThirtyValues << isThirty << endl;
                                    fThirtyValues.close();
                                    break;
                                }
                                case 3: {
                                    cout << "Exporta CSV cu outliers: " << filePath << endl;
                                    outliers = InfoStock::getOutliers(is);
                                    cout << outliers << endl;
                                    string outliersName = stockName + "_outliers.csv";
                                    ofstream fOutliers(outliersName, ios::out);
                                    fOutliers << outliers << endl;
                                    fOutliers.close();
                                    break;
                                }
                                case 0:
                                    cout << "Revenire la Meniul Principal..." << endl;
                                    break;
                                default:
                                    cout << "Optiune invalida. Incearca din nou." << endl;
                                    break;
                                }

                                if (csvOption == 0) {
                                    break; 
                                }
                                break;
                            }
                        }
                        else {
                            cout << "Fisierul CSV pentru " << stockName << " nu a fost gasit. Te rog introdu alt nume de actiune." << endl;
                        }
                    }
                    break;
                case 0:
                    cout << "Revenire la selectia limbii..." << endl;
                    break;
                default:
                    cout << "Optiune invalida. Incearca din nou." << endl;
                    break;
                }

                if (choice == 0) {
                    break;
                }
            }
            break;
        case 0:
            cout << "Exiting / Iesire..." << endl;
            return 0; 
        default:
            cout << "Invalid choice / Optiune invalida. Try again / Incercati din nou." << endl;
            break;
        }
    }

    return 0;
}