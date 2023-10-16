#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);



int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: ./interpolate <filename>" << endl;
        exit(1);
    }

    vector<double> fpangles;
    vector<double> coeffs;
    string filename;
    double angle;

    filename = argv[1];
    bool continue_program = true;

    readData(filename, fpangles, coeffs);
    reorder(fpangles, coeffs);

    while (continue_program) {
        cin >> angle;
        cout << endl;
        double answer = -1;
        string decision;

        
        if (angle <= fpangles.at(fpangles.size()-1) && angle >= fpangles.at(0)) {
            answer = interpolation(angle, fpangles, coeffs);

        }

        else {
            cout << "The flight-path angle is out of range." << endl;
            exit(1);
        }

        cout << "The predicted coefficient is: " << answer;
        cout << endl;

        cout << "Would you like to enter another flight-path angle? ";
        cin.ignore();
        getline(cin, decision);
        cout << endl;

        if (decision == "No") {
            continue_program = false;
        }


    }

}

//FUNCTIONS

bool isOrdered(const vector<double> &fpangles) {
    if (fpangles.empty()) {
        return true;
    }

    if (fpangles.size() == 1) {
        return true;
    }

    for (unsigned int i = 0; i < fpangles.size() - 1; i++) {
        if (fpangles.at(i) > fpangles.at(i + 1)) {
            return false;
        }
    }
    return true;
}


void reorder(vector<double> &fpangles, vector<double> &coeffs) {
   

  if (fpangles.empty() || coeffs.empty()) {
        return;
    }  

    

    if (fpangles.size() != coeffs.size()) {
        cout << "Error: vectors are not the same size." << endl;
        exit(1);
    }

    int n = fpangles.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (fpangles.at(j) < fpangles.at(minIndex)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(fpangles.at(i), fpangles.at(minIndex));
            swap(coeffs.at(i), coeffs.at(minIndex));
        }
    }

}


void readData(const string &fileName, vector<double> &fpangles, vector<double> &coeffs) {
    ifstream inFS;
    inFS.open(fileName);
    double cur_fpangles;
    double cur_coeffs;

    if (!inFS.is_open()) {
        cout << "Error opening " << fileName << endl;
        exit(1);
    }

   
    while (inFS >> cur_fpangles >> cur_coeffs) {
        fpangles.push_back(cur_fpangles);
        coeffs.push_back(cur_coeffs);
    } 



    inFS.close();

}

double interpolation(double angle, const vector<double> &fpangles, const vector<double> &coeffs) {



    for (unsigned int i = 0; i < fpangles.size(); i++) {
        if (angle == fpangles.at(i)) {
            return coeffs.at(i);
        }
    }

    double target = -1;

    for (unsigned int i = 0; i < fpangles.size(); i++) {
        if (i < fpangles.size() - 1 && angle >= fpangles.at(i) && angle <= fpangles.at(i+1)) {
            target = coeffs.at(i) + ((angle - fpangles.at(i)) / (fpangles.at(i+1) - fpangles.at(i))) * (coeffs.at(i+1) - coeffs.at(i));
            return target;
        }
    }
    


    return target;


}





