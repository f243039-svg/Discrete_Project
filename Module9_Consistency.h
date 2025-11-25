#ifndef MODULE9_CONSISTENCY_H
#define MODULE9_CONSISTENCY_H

#include <iostream>
#include <string>
using namespace std;

#include "Course.h"
#include "Student.h"
#include "Module3_Induction.h"
#include "Module4_Logic.h"
#include "Module8_Proofs.h"

const int MAX_CHECK = 200;

//validation 
class ConsistencyChecker {

public:

    //check eligibility for cources
    //
    int checkAllPrerequisites(const Course courses[], int courseCount,
                              const Student students[], int studentCount) {
        
        InductionModule im;
        int problems = 0;

        for (int s = 0; s < studentCount; s++) {
            const Student& st = students[s];

            cout << "\nChecking student " << st.getID() << " " << st.getName() << "\n";

            for (int c = 0; c < courseCount; c++) {
                const Course& course = courses[c];
                const string& code = course.getCode();

                if (st.hasCompleted(code))
                    continue;

                string proof[300];
                int proofCount = 0;

                bool ok = im.canTakeCourse_StrongInduction(
                    courses, courseCount, st, code, proof, proofCount
                );

                if (!ok) {
                    problems++;
                    cout << "not eligible " << code << ":\n";
                } else {
                    cout << "eligible" << code << "\n";
                }
            }
        }

      
    }

    //from a conculsion get all the facts and then see if the goal is derived 
    // ex all cources are assigned a faculty 
    bool checkLogicConsistency(LogicEngine& engine, const string conclusions[], int n) {

        cout << "\logic consistency\n";

        bool allGood = true;

        for (int i = 0; i < n; i++) {
            const string& goal = conclusions[i];
            cout << "\nChecking logical conclusion: " << goal << "\n";

            engine.forwardChaining();
            bool result = engine.getFact(goal);

            cout << "Conclusion '" << goal << "': "
                 << (result ? "TRUE" : "FALSE") << "\n";

            if (result) allGood = false;
        }

        cout << "\nLogical consistency: "
             << (allGood ? "OK" : "PROBLEMS DETECTED") << "\n";

        return allGood;
    }

    // check if opposite statements are true
    //negations
    bool detectContradictions(LogicEngine& engine) {

        bool hasContradiction = engine.hasContradiction();

        if (hasContradiction)
            cout << " found\n";
        else
            cout << "not found.\n";

        return hasContradiction;
    }


    int checkEnrollments(const Course courses[], int ccount,
                         const Student students[], int scount,
                         const int sidx[], const string ccode[],
                         int count)
    {
        ProofsModule pm;
        int problems = pm.checkEnrollmentPrerequisites(
            courses, ccount,
            students, scount,
            studentIdx, ccode, count
        );
        return problems;
    }


    void runFullConsistencyCheck(const Course courses[], int courseCount,
                                 const Student students[], int studentCount,
                                 LogicEngine& engine,
                                 const int studentIdx[], const string courseCodes[],
                                 int enrollCount,
                                 const string logicConclusions[], int logicConclusionCount)
    {
        cout << "CONSISTENCY REPORT\n";
 
        int p1 = checkAllPrerequisites(courses, courseCount, students, studentCount);
        int p2 = checkEnrollments(courses, courseCount, students, studentCount,
                                  studentIdx, courseCodes, enrollCount);

        bool logicOk = checkLogicConsistency(engine, logicConclusions, logicConclusionCount);
        bool contradictionFound = detectContradictions(engine);



        cout << "Prerequisite issues:   " << p1 << "\n";
        cout << "Enrollment issues:     " << p2 << "\n";
        cout << "Logic contradictions:  " << (contradictionFound ? "YES" : "NO") << "\n";
        cout << "Logic consistency:     " << (logicOk ? "OK" : "PROBLEM") << "\n";

    
    }

};

#endif

