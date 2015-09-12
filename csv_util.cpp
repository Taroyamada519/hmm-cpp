#include "csv_util.h"

// convert CSV to double vector
vector<double> csv_util::csv2dvec(string path) {
    vector<string> svec = csv2svec(path);
    vector<double> dvec(svec.size());
    for (int i = 0; i < svec.size(); i++) {
        dvec[i] = cell2double(svec[i]);
    }
    return dvec;
}

// convert CSV to double matrix
vector< vector<double> > csv_util::csv2dmat(string path) {
    vector< vector<string> > smat = csv2smat(path);
    vector< vector<double> > dmat(smat.size(), vector<double>(smat[0].size()));
    for (int i = 0; i < smat.size(); i++) {
        for (int j = 0; j < smat[0].size(); j++) {
            dmat[i][j] = cell2double(smat[i][j]);
        }
    }
    return dmat;
}

// convert CSV to integer vector
vector<int> csv_util::csv2ivec(string path) {
    vector<string> svec = csv2svec(path);
    vector<int> ivec(svec.size());
    for (int i = 0; i < svec.size(); i++) {
        ivec[i] = (int) cell2double(svec[i]);
    }
    return ivec;
}

// convert CSV to integer matrix
vector< vector<int> > csv_util::csv2imat(string path) {
    vector< vector<string> > smat = csv2smat(path);
    vector< vector<int> > imat(smat.size(), vector<int>(smat[0].size()));
    for (int i = 0; i < smat.size(); i++) {
        for (int j = 0; j < smat[0].size(); j++) {
            imat[i][j] = (int) cell2double(smat[i][j]);
        }
    }
    return imat;
}

// convert CSV to string vector
vector<string> csv_util::csv2svec(string path) {
    ifstream fin;
    fin.open(path);
    if (!fin) {
        cout << "Cannot open the file " << endl;
    }
    string str;
    getline(fin, str);
    fin.close();
    return line2svec(str);
}

// convert CSV to string matrix
vector< vector<string> > csv_util::csv2smat(string path) {
    vector< vector<string> > smat(count_row(path));
    ifstream fin;
    fin.open(path);
    if (!fin) {
        cout << "Cannot open the file " << endl;
    }
    string str;
    int i = 0;
    while (getline(fin, str)) {
        smat[i] = line2svec(str);
        i++;
    }
    fin.close();
    return smat;
}

// convert CSV line to string svector
vector<string> csv_util::line2svec(string str) {
    vector<string> svec(count_cell(str));
    int i = 0;
    while (str.find(",") != string::npos) {
        svec[i] = str.substr(0, str.find(","));
        str = str.substr(str.find(",") + 1);
        i++;
    }
    svec[i] = str.substr(0, str.find(","));
    return svec;
}

// convert CSV cell (string data) to double
double csv_util::cell2double(string cell) {
    if (cell.find("/") == string::npos) {
        return stof(cell);
    } else {
        string str1 = cell.substr(0, cell.find("/"));
        string str2 = cell.substr(cell.find("/") + 1);
        return stof(str1) / stof(str2);
    }
}

// count CSV column
int csv_util::count_column(string path) {
    ifstream fin;
    fin.open(path);
    if (!fin) {
        cout << "Cannot open the file " << endl;
        return 1;  // quit
    }
    string str;
    getline(fin, str);
    fin.close();
    return count_cell(str);
}

// count CSV cells per line
int csv_util::count_cell(string str) {
    if (str.find(",") == string::npos) {
        // last cell
        return 1;
    } else {
        // not last cell
        return count_cell(str.substr(str.find(",") + 1)) + 1;
    }
}

// count CSV row(line)
int csv_util::count_row(string path) {
    ifstream fin;
    fin.open(path);
    if (!fin) {
        cout << "Cannot open the file " << endl;
    }
    string str;
    int row = 0;
    while (getline(fin, str)) {
        row++;
    }
    fin.close();
    return row;
}
