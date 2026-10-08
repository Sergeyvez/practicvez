#include <iostream>
#include <new>

using namespace std;

void free_matrix(int **m, int rows) {
    if (!m) return;
    for (int i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

int **alloc_matrix(int rows, int cols) {
    int **m = new (nothrow) int *[rows];
    if (!m) return nullptr;

    for (int i = 0; i < rows; ++i) {
        m[i] = new (nothrow) int[cols];
        if (!m[i]) {
            free_matrix(m, i); 
            return nullptr;
        }
    }
    return m;
}

bool rmatrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!(cin >> m[i][j])) return false;
    return true;
}
void pmatrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j) cout << ' ';
            cout << m[i][j];
        }
        cout << '\n';
    }
}

int **transpose(int **m, int rows, int cols) {
    int **t = alloc_matrix(cols, rows);
    if (!t) return nullptr;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            t[j][i] = m[i][j];
    return t;
}

int main() {
    int rows, cols;

    if (!(cin >> rows >> cols) || rows <= 0 || cols <= 0) { 
        return 1;
    }

    int **m = alloc_matrix(rows, cols);
    if (!m) {
        return 2;
    }

    if (!rmatrix(m, rows, cols)) {
        free_matrix(m, rows);
        return 1;
    }

    int **t = transpose(m, rows, cols);
    if (!t) {
        free_matrix(m, rows);
        return 2;
    } 
    pmatrix(t, cols, rows);

    free_matrix(t, cols);
    free_matrix(m, rows);
    return 0;
}
