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

    // initialize viterbi variable
    vector<double> v_var(i_prob.size());
    for (int i = 0; i < v_var.size(); i++) {
        v_var[i] = i_prob[i] * o_prob[i][op[0]-1];
    }

    // state path
    vector< vector<int> > path(op.size(), vector<int>(i_prob.size()));
    for (int i = 0; i < path[0].size(); i++) {
        path[0][i] = 0;
    }

    // recursive calculation
    for (int t = 1; t < op.size(); t++) {
        // initialize next viterbi variable
        vector<double> v_var_next(v_var.size());
        for (int j = 0; j < v_var_next.size(); j++) {
            double tempmax = 0;
            int tempmax_num;
            for (int i = 0; i < v_var.size(); i++) {
                if (v_var[i] * t_prob[i][j] * o_prob[j][op[t] - 1] > tempmax) {
                    tempmax = v_var[i] * t_prob[i][j] * o_prob[j][op[t] - 1];
                    tempmax_num = i;
                }
            }
            v_var_next[j] = tempmax;
            path[t][j] = tempmax_num;
        }
        swap(v_var, v_var_next);
    }

    // finish calculation
    double tempmax = 0;
    int tempmax_num;
    for (int i = 0; i < v_var.size(); i++) {
        if (v_var[i] > tempmax) {
            tempmax = v_var[i];
            tempmax_num = i;
        }
    }
    double prob = tempmax;
    int last_state = tempmax_num;

    // trace back
    vector<int> state_path(op.size());
    state_path[state_path.size() - 1] = last_state;
    for (int t = state_path.size() - 2; t >= 0 ; t--) {
        state_path[t] = path[t + 1][state_path[t + 1]];
    }

    // show result
    for (int i = 0; i < state_path.size(); i++) {
        cout << state_path[i] << endl;
    }
    cout << scientific << prob << endl;

    return 0;
}
