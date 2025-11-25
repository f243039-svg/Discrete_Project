#ifndef MODULE8_PROOFS_H
#define MODULE8_PROOFS_H


#include "Course.h"
#include "Student.h"
#include "Module3_Induction.h"
#include "Module4_Logic.h"
#include <iostream>
#include <string>

using namespace std;

class ProofsModule {
public:

    //check that the student meet eligibility 
    //using module 3 induction
    //Module3 store induction in proof arr
    //M8 will print the proof 
    //agar student need pf for oop it will check if the student has taken pf 
    bool provePrerequisiteChain(const Course courses[], int courseCount,
                                const Student& student, const string& targetCourse) {
        InductionModule im;
        string proof[500];
        int proofCount = 0;


        
        bool result = im.canTakeCourse_StrongInduction(courses, courseCount, student, targetCourse, proof, proofCount);
        cout << endl;
        cout << "proof" << endl;

        for (int i = 0; i < proofCount; i++) {
            cout << proof[i] << "\n";
        }

        cout << " result:"<< (result ? "eligible" : "not eligible")<< "\n";

        return result;
    }

        // check if a conculsion can be logically drived 
        //use inference 

    bool proveLogicDerivation(LogicEngine& engine, const string& conclusion) {
        cout << "\nconclusion: " << conclusion << "\n";

        int newFacts = engine.forwardChaining();
        cout << "new facts:" << newFacts << "\n\n";

        engine.displayInferenceLog();

        bool derived = engine.getFact(conclusion);

        cout << "\nConclusion '" << conclusion << (derived ? "true" : "false") << "\n";

        engine.displayFacts();

        return derived;
    }

    //prove using strong induction that all the strudents cources prove prerequisite
    int checkEnrollmentPrerequisites(const Course courses[], int ccount,
                                     const Student students[], int scount,
                                     const int enrollstdid[], const string enrollcode[],
                                     int pcount) {
        InductionModule im;
        int problems = 0;

        //iterate all the std
        for (int k = 0; k < pcount; k++) {
            int sIdx = enrollstdid[k];
            if (sIdx < 0 || sIdx >= scount) {
                cout <<  "invalid idx" << sIdx << "\n";
                problems++;
                continue;
            }

            const Student& st = students[sIdx];
            const string& ccode = enrollcode[k];

            cout << "\nChecking: Student " << st.getID() << " (" << st.getName() << ")"
                 << " enrolled in " << ccode << "\n";

            string proof[500];
            int proofCount = 0;
            bool ok = im.canTakeCourse_StrongInduction(courses, ccount, st, ccode, proof, proofCount);

            for (int i = 0; i < proofCount; i++) {
                cout << proof[i] << "\n";
            }

            if (!ok) {
                cout << st.getID() << "not eligible for " << ccode << "\n";
                problems++;
            } else {
                cout << st.getID() << " eligible for " << ccode << "\n";
            }
        }
        
        cout << endl;
        cout << "Problems found: " << problems << "\n";
        return problems;
    }

 // show properties 
    void proveFunctionProperties(FunctionModule& f) {
        cout << "\n Property \n";
        cout << "Is valid function? " << (f.isValidFunction() ? "YES" : "NO") << "\n";
        cout << "Is injective? " << (f.isInjective() ? "YES" : "NO") << "\n";
        cout << "Is surjective? " << (f.isSurjective() ? "YES" : "NO") << "\n";
        cout << "Is bijective? " << (f.isBijective() ? "YES" : "NO") << "\n";

    }

    // cal left and right anf then compare
    bool proveSetDistributiveLaw(const string A[], int aSize,
                                 const string B[], int bSize,
                                 const string C[], int cSize) {
       
        string temp1[MAX_SET];
        int bAndc = setIntersection(B, bSize, C, cSize, temp1);

        string left[MAX_SET];
        int leftSize = setUnion(A, aSize, temp1, bAndc, left);

        string aUb[MAX_SET];
        int aUbSize = setUnion(A, aSize, B, bSize, aUb);

        string aUc[MAX_SET];
        int aUcSize = setUnion(A, aSize, C, cSize, aUc);

        string right[MAX_SET];
        int rightSize = setIntersection(aUb, aUbSize, aUc, aUcSize, right);

  
        leftSize = removeDuplicates(left, leftSize);
        rightSize = removeDuplicates(right, rightSize);

        bool equal = areEqualSets(left, leftSize, right, rightSize);

        cout << "\n distributive \n";
        cout << "Left "; printSet(left, leftSize); cout << "\n";
        cout << "Right "; printSet(right, rightSize); cout << "\n";
        cout << "Result " << (equal ? "equal" : "no equal") << "\n";

        return equal;
    }
};

#endif 

