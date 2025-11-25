#pragma once
#ifndef MODULE5_SETS_H
#define MODULE5_SETS_H

#include <iostream>
#include <string>
using namespace std;

// max size for sets
const int MAX_SET = 100;

// remove duplicates from array
int removeDuplicates(string arr[], int size) {
    string temp[MAX_SET]; // temp store
    int newCount = 0;     // count unique

    for (int i = 0; i < size; i++) {
        bool exists = false; // check flag

        for (int j = 0; j < newCount; j++) {
            if (temp[j] == arr[i]) { // if element repeats
                exists = true;
                break;
            }
        }

        if (!exists) temp[newCount++] = arr[i]; // add if unique
    }

    for (int i = 0; i < newCount; i++) arr[i] = temp[i];
    return newCount;
}

// printing set
void printSet(const string arr[], int size) {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " }";
}

// union of sets
int setUnion(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int idx = 0; // result index

    for (int i = 0; i < aSize; i++)
        result[idx++] = A[i];

    for (int i = 0; i < bSize; i++)
        result[idx++] = B[i];

    return removeDuplicates(result, idx);
}

// intersection of sets
int setIntersection(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int idx = 0; // index for result

    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) { // match found
                result[idx++] = A[i];
                break;
            }
        }
    }

    return idx;
}

// difference A - B
int setDifference(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int idx = 0;

    for (int i = 0; i < aSize; i++) {
        bool exists = false;

        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) { // found in B
                exists = true;
                break;
            }
        }

        if (!exists) result[idx++] = A[i]; // only in A
    }

    return idx;
}

// symmetric difference
int setSymmetricDifference(const string A[], int aSize, const string B[], int bSize, string result[]) {
    string tempA[MAX_SET], tempB[MAX_SET];

    int dA = setDifference(A, aSize, B, bSize, tempA);
    int dB = setDifference(B, bSize, A, aSize, tempB);

    int idx = 0;

    for (int i = 0; i < dA; i++) result[idx++] = tempA[i];
    for (int i = 0; i < dB; i++) result[idx++] = tempB[i];

    return idx;
}

// subset check
bool isSubset(const string A[], int aSize, const string B[], int bSize) {
    for (int i = 0; i < aSize; i++) {
        bool exists = false;

        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) {
                exists = true;
                break;
            }
        }

        if (!exists) return false; // A element not in B
    }

    return true;
}

// compare sets
bool areEqualSets(const string A[], int aSize, const string B[], int bSize) {
    if (aSize != bSize) return false;
    return isSubset(A, aSize, B, bSize);
}

// recursive power set
void powerSetRec(const string A[], int n, int pos, string current[], int currSize) {
    if (pos == n) {
        printSet(current, currSize);
        cout << endl; // newline better than \n
        return;
    }

    // exclude case
    powerSetRec(A, n, pos + 1, current, currSize);

    // include case
    current[currSize] = A[pos];
    powerSetRec(A, n, pos + 1, current, currSize + 1);
}

// power set execution
void printPowerSet(const string A[], int n) {
    string current[MAX_SET];
    cout << endl << "Power Set:" << endl;
    powerSetRec(A, n, 0, current, 0);
}

// cartesian product
void cartesianProduct(const string A[], int aSize, const string B[], int bSize) {
    cout << "{ ";

    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < bSize; j++) {
            cout << "(" << A[i] << ", " << B[j] << ")";

            if (!(i == aSize - 1 && j == bSize - 1))
                cout << ", ";
        }
    }

    cout << " }" << endl;
}

#endif