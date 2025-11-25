#pragma once
#ifndef MODULE7_RELATIONS_H
#define MODULE7_RELATIONS_H

#include <iostream>
#include <string>
using namespace std;

// max number of elements allowed
const int MAX_REL = 50;

class RelationModule {
private:
    string elements[MAX_REL]; // store elements
    int elementCount;         // how many added

    int matrix[MAX_REL][MAX_REL]; // relation matrix

public:
    RelationModule() {
        elementCount = 0;

        // fill matrix with 0
        for (int r = 0; r < MAX_REL; r++) {
            for (int c = 0; c < MAX_REL; c++) {
                matrix[r][c] = 0;
            }
        }
    }

    // add element into set
    void addElement(const string& e) {
        if (elementCount < MAX_REL)
            elements[elementCount++] = e; // push element
    }

    // add ordered pair (a, b)
    void addPair(const string& a, const string& b) {
        int row = findIndex(a);
        int col = findIndex(b);

        if (row != -1 && col != -1)
            matrix[row][col] = 1; // mark relation
    }

    // find index of element
    int findIndex(const string& x) {
        for (int i = 0; i < elementCount; i++) {
            if (elements[i] == x)
                return i;
        }
        return -1;
    }

    // print relation in set form
    void printRelation() {
        cout << "R = { ";
        bool first = true; // for formatting

        for (int r = 0; r < elementCount; r++) {
            for (int c = 0; c < elementCount; c++) {
                if (matrix[r][c] == 1) {
                    if (!first) cout << ", ";
                    cout << "(" << elements[r] << ", " << elements[c] << ")";
                    first = false;
                }
            }
        }

        cout << " }" << endl;
    }

    // print matrix table
    void printMatrix() {
        cout << endl << "Relation Matrix:" << endl;
        cout << "  ";

        for (int i = 0; i < elementCount; i++)
            cout << elements[i] << " ";
        cout << endl;

        for (int r = 0; r < elementCount; r++) {
            cout << elements[r] << " ";
            for (int c = 0; c < elementCount; c++) {
                cout << matrix[r][c] << " ";
            }
            cout << endl;
        }
    }

    // check reflexive
    bool isReflexive() {
        for (int i = 0; i < elementCount; i++) {
            if (matrix[i][i] == 0) return false;
        }
        return true;
    }

    // check symmetric
    bool isSymmetric() {
        for (int r = 0; r < elementCount; r++) {
            for (int c = 0; c < elementCount; c++) {
                if (matrix[r][c] != matrix[c][r]) return false;
            }
        }
        return true;
    }

    // check antisymmetric
    bool isAntiSymmetric() {
        for (int r = 0; r < elementCount; r++) {
            for (int c = 0; c < elementCount; c++) {
                if (r != c && matrix[r][c] == 1 && matrix[c][r] == 1)
                    return false;
            }
        }
        return true;
    }

    // check transitive
    bool isTransitive() {
        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                if (matrix[i][j] == 1) {
                    for (int k = 0; k < elementCount; k++) {
                        if (matrix[j][k] == 1 && matrix[i][k] == 0)
                            return false;
                    }
                }
            }
        }
        return true;
    }

    // equivalence relation
    bool isEquivalence() {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    // partial order relation
    bool isPartialOrder() {
        return isReflexive() && isAntiSymmetric() && isTransitive();
    }

    // relation composition R1 ∘ R2
    void relationComposition(int result[MAX_REL][MAX_REL],
        int A[MAX_REL][MAX_REL],
        int B[MAX_REL][MAX_REL]) {

        // clear result matrix
        for (int r = 0; r < elementCount; r++) {
            for (int c = 0; c < elementCount; c++) {
                result[r][c] = 0;
            }
        }

        // compute composition
        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                for (int k = 0; k < elementCount; k++) {
                    if (A[i][k] == 1 && B[k][j] == 1)
                        result[i][j] = 1;
                }
            }
        }
    }
};

#endif