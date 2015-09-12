#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "csv_util.h"

using namespace std;
// TODO: 状態及び出力を0から始まる数字に対応させる。
int main() {
    csv_util cu;
    // initial probability
    vector<double> i_prob = cu.csv2dvec("csv/i_prob.csv");
    // transition probability
    vector< vector<double> > t_prob = cu.csv2dmat("csv/t_prob.csv");
    // output probability
    vector< vector<double> > o_prob = cu.csv2dmat("csv/o_prob.csv");
    // observed output
    vector<int> op = cu.csv2ivec("csv/output.csv");

    // initialize forward variable
    vector<double> f_var(i_prob.size());
    for (int i = 0; i < f_var.size(); i++) {
        f_var[i] = i_prob[i] * o_prob[i][op[0] - 1];
    }

    // recursive calculation
    for (int t = 1; t < op.size(); t++) {
        // initialize next forward variable
        vector<double> f_var_next(f_var.size());
        for (int j = 0; j < f_var_next.size(); j++) {
            f_var_next[j] = 0;
            for (int i = 0; i < f_var.size(); i++) {
                f_var_next[j] += f_var[i] * t_prob[i][j];
            }
            f_var_next[j] *= o_prob[j][op[t] - 1];
        }
        // swap next forward variable and forward variable
        swap(f_var, f_var_next);
    }

    // calculate probability
    double prob = 0;
    for (int i = 0; i < f_var.size(); i++) {
        prob += f_var[i];
    }
    cout << scientific <<  prob << endl;

    return 0;
}
