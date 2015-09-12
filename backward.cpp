#include <iostream>
#include <string>
#include <vector>
#include "csv_util.h"

using namespace std;
//TODO: 状態及び出力を0から始まる数字に対応させる。
int main() {
    csv_util cu;
    //initial probability
    vector<double> i_prob = cu.csv2dvec("csv/i_prob.csv");
    //transition probability
    vector< vector<double> > t_prob = cu.csv2dmat("csv/t_prob.csv");
    //output probability
    vector< vector<double> > o_prob = cu.csv2dmat("csv/o_prob.csv");
    //observed output
    vector<int> op = cu.csv2ivec("csv/output.csv");

    //initialize backward variable
    vector<double> b_var(i_prob.size());
    for (int i = 0; i < b_var.size(); i++) {
        b_var[i] = 1;
    }

    //recursive calculation
    for (int t = op.size() - 2; t >= 0; t--) {
        //initialize next backward variable
        vector<double> b_var_next(b_var.size());
        for (int i = 0; i < b_var_next.size(); i++) {
            b_var_next[i] = 0;
            for (int j = 0; j < b_var.size(); j++) {
                b_var_next[i] += b_var[j] * t_prob[i][j] * o_prob[j][op[t + 1] - 1];
            }
        }
        //swap next forward variable and forward variable
        swap(b_var, b_var_next);
    }

    //calculate probability
    double prob = 0;
    for (int i = 0; i < b_var.size(); i++) {
        prob += b_var[i] * i_prob[i] * o_prob[i][op[0] - 1];
    }
    cout << scientific <<  prob << endl;

    return 0;
}
