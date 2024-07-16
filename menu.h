//#pragma once
//#include "datastockclass.h"
//#include<iostream>
//#include <cstring> // Pentru functii C string
//#include <cstdlib> // Pentru alocare dinamica
//
//using namespace std;
//
//// Verificare suport <filesystem> pentru C++11
//#if __cplusplus <= 201103L && !defined(__cpp_lib_filesystem)
//#include <experimental/filesystem>
//namespace fs = std::experimental::filesystem;
//#else
//#include <filesystem>
//namespace fs = std::filesystem;
//#endif
//
//// Functie pentru a verifica existenta unui fisier CSV cu numele actiunii dorite
//string findCsvFile(const string& folderPath, const string& stockName) {
//    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
//        if (entry.is_regular_file()) {
//            if (entry.path().extension() == ".csv" && entry.path().stem().string() == stockName) {
//                return entry.path().string(); // Returnează calea completă către fișierul CSV găsit
//            }
//        }
//    }
//    return ""; // Returnează un șir vid dacă fișierul nu este găsit
//}
//
//// Funcție pentru afișarea meniului de opțiuni pentru fișierul CSV găsit
//void displayCsvFileOptionsMenu(const string& filePath) {
//    int choice;
//
//    while (true) {
//        cout << "\nCSV File Options Menu:" << endl;
//        cout << "1. View CSV file content" << endl;
//        cout << "2. Process CSV data" << endl;
//        cout << "3. Export CSV data" << endl;
//        cout << "0. Back to Main Menu" << endl;
//
//        cout << "\nYour choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            cout << "Viewing content of CSV file: " << filePath << endl;
//            
//            break;
//        case 2:
//            cout << "Processing CSV data from: " << filePath << endl;
//            // Aici puteți implementa funcționalitatea pentru a procesa datele din fișierul CSV
//            break;
//        case 3:
//            cout << "Exporting CSV data from: " << filePath << endl;
//            // Aici puteți implementa funcționalitatea pentru a exporta datele din fișierul CSV
//            break;
//        case 0:
//            cout << "Returning to Main Menu..." << endl;
//            return;
//        default:
//            cout << "Invalid choice. Try again." << endl;
//            break;
//        }
//    }
//}
//
//
//// Funcție pentru afișarea meniului în limba engleză
//void displayMenuEnglish() {
//    int choice;
//    string stockName;
//
//    while (true) {
//        cout << "\nEnglish Menu:" << endl;
//        cout << "1. Option 1" << endl;
//        cout << "2. Option 2" << endl;
//        cout << "3. Enter stock name" << endl; // Noua opțiune pentru introducerea numelui acțiunii
//        cout << "0. Back to Language Selection / Înapoi la selectia limbii" << endl;
//
//        cout << "\nYour choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            cout << "Option 1 selected." << endl;
//            // Aici adăugați funcționalitatea pentru opțiunea 1 în limba engleză
//            break;
//        case 2:
//            cout << "Option 2 selected." << endl;
//            // Aici adăugați funcționalitatea pentru opțiunea 2 în limba engleză
//            break;
//        case 3:
//            cout << "Enter the exact stock name (e.g., TSLA): ";
//            cin >> stockName;
//            for (char& c : stockName) {
//                c = toupper(c); // Folosim funcția toupper pentru a converti caracterul la uppercase
//            }
//            cout << "Stock name entered: " << stockName << endl;
//            // Verificăm dacă există un fișier CSV cu numele acțiunii dorite
//            {
//                string filePath = findCsvFile("C:\\Users\\razva\\source\\repos\\lseg_challenge", stockName);
//                if (!filePath.empty()) {
//                    cout << "Found CSV file for " << stockName << " at: " << filePath << endl;
//                    // Afișăm meniul opțiunilor pentru fișierul CSV găsit
//                    displayCsvFileOptionsMenu(filePath);
//                }
//                else {
//                    cout << "CSV file for " << stockName << " not found. Please enter another stock name." << endl;
//                }
//            }
//            break;
//        case 0:
//            cout << "Returning to Language Selection..." << endl;
//            return;
//        default:
//            cout << "Invalid choice. Try again." << endl;
//            break;
//        }
//    }
//}
//
//// Funcție pentru afișarea meniului în limba română
//void displayMenuRomanian() {
//    int choice;
//    string stockName;
//
//    while (true) {
//        cout << "\nMeniu în limba română:" << endl;
//        cout << "1.Introduceți numele acțiunii" << endl; // Noua opțiune pentru introducerea numelui acțiunii
//        cout << "0. Înapoi la selectia limbii / Back to Language Selection" << endl;
//
//        cout << "\nOpțiunea dvs.: ";
//        cin >> choice;
//
//        switch (choice) {
//      
//        case 1:
//            cout << "Introduceți numele exact al acțiunii (de exemplu, TSLA): ";
//            cin >> stockName;
//            for (char& c : stockName) {
//                c = toupper(c); // Folosim funcția toupper pentru a converti caracterul la uppercase
//            }
//            cout << "Numele acțiunii introdus: " << stockName << endl;
//            // Verificăm dacă există un fișier CSV cu numele acțiunii dorite
//            {
//                string filePath = findCsvFile("C:\\Users\\razva\\source\\repos\\lseg_challenge", stockName);
//                if (!filePath.empty()) {
//                    cout << "Fișierul CSV pentru " << stockName << " a fost găsit la: " << filePath << endl;
//                    // Afișăm meniul opțiunilor pentru fișierul CSV găsit
//                    displayCsvFileOptionsMenu(filePath);
//                }
//                else {
//                    cout << "Fișierul CSV pentru " << stockName << " nu a fost găsit. Vă rugăm să introduceți alt nume de acțiune." << endl;
//                }
//            }
//            break;
//        case 0:
//            cout << "Revenire la selectia limbii..." << endl;
//            return;
//        default:
//            cout << "Opțiune invalidă. Încercați din nou." << endl;
//            break;
//        }
//    }
//}
//
//
//// Functie pentru afisarea meniului de selectare a limbii
//void displayLanguageMenu() {
//    int choice;
//
//    while (true) {
//        cout << "\nSelect language / Selectati limba:" << endl;
//        cout << "1. English / Engleza" << endl;
//        cout << "2. Romana" << endl;
//        cout << "0. Exit / Iesire" << endl;
//
//        cout << "\nYour choice / Optiunea dvs.: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            cout << "\nEnglish language selected." << endl;
//            displayMenuEnglish(); // Afiseaza meniul in limba engleza
//            break;
//        case 2:
//            cout << "\nLimba romana selectata." << endl;
//            displayMenuRomanian(); // Afiseaza meniul in limba romana
//            break;
//        case 0:
//            cout << "Exiting / Iesire..." << endl;
//            exit(0);
//        default:
//            cout << "Invalid choice / Optiune invalida. Try again / Incercati din nou." << endl;
//            break;
//        }
//    }
//}
