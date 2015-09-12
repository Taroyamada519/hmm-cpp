#include <iostream>
#include <string>
#include <vector>
#include "csv_util.h"

using namespace std;

int main() {
    string path = "csv/e_prob.csv";
    csv_util cu;
    // test CSV to string vector
    cout << "#string#" << endl;
    cout << "vector" << endl;
    vector<string> svec = cu.csv2svec(path);
    for (int i = 0; i < svec.size(); i++) {
        cout << svec[i] << endl;
    }
    // test CSV to string matrix
    cout << "matrix" << endl;
    vector< vector<string> > smatrix = cu.csv2smat(path);
    for (int i = 0; i < smatrix.size(); i++) {
        for (int j = 0; j < smatrix[0].size(); j++) {
            cout << smatrix[i][j] << endl;
        }
    }
    // test CSV to integer vector
    cout << "#int#" << endl;
    cout << "vector" << endl;
    vector<int> vec = cu.csv2ivec(path);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }
    // test CSV to integer matrix
    cout << "matrix" << endl;
    vector< vector<int> > matrix = cu.csv2imat(path);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << endl;
        }
    }
    // test CSV to double vector
    cout << "#double#" << endl;
    cout << "vector" << endl;
    vector<double> dvec = cu.csv2dvec(path);
    for (int i = 0; i < dvec.size(); i++) {
        cout << dvec[i] << endl;
    }
    // test CSV to double matrix
    cout << "matrix" << endl;
    vector< vector<double> > dmatrix = cu.csv2dmat(path);
    for (int i = 0; i < dmatrix.size(); i++) {
        for (int j = 0; j < dmatrix[0].size(); j++) {
            cout << dmatrix[i][j] << endl;
        }
    }

    return 0;
}
