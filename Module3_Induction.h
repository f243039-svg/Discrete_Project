#ifndef MODULE3_INDUCTION_H
#define MODULE3_INDUCTION_H

#include "Course.h"
#include "Student.h"
#include <iostream>

using namespace std;

class InductionModule {
private:

    int findCourseIndex(const Course courses[], int total, const string& code) {
        for (int i = 0; i < total; i++)
            if (courses[i].getCode() == code)
                return i;
        return -1;
    }

    bool strongCheck(const Course courses[], int total, int courseIndex,
        const Student& student, string proof[], int& proofCount, bool visited[]) {

        if (visited[courseIndex]) return true;
        visited[courseIndex] = true;

        string courseCode = courses[courseIndex].getCode();
        proof[proofCount++] = "checking prerequisites of " + courseCode;

        int pCount = courses[courseIndex].getPrereqCount();

        if (pCount == 0) {
            proof[proofCount++] = "  no prerequisites = ok";
            return true;
        }

        for (int i = 0; i < pCount; i++) {
            string pre = courses[courseIndex].getPrereq(i);

            proof[proofCount++] = "  requires: " + pre;

            if (!student.hasCompleted(pre)) {
                proof[proofCount++] = " student did not complete " + pre;
                return false;
            }

            proof[proofCount++] = "  completed " + pre;

          
            int preIndex = findCourseIndex(courses, total, pre);
            if (preIndex == -1)
                continue;
            if (!strongCheck(courses, total, preIndex, student, proof, proofCount, visited))
                return false;
        }

        return true;
    }

public:

   
    bool canTakeCourse_Induction(const Course courses[], int total,
        const Student& student, const string& target,
        string proof[], int& proofCount) {

        proofCount = 0;
        proof[proofCount++] = "applying basic induction to check direct prerequisites for: " + target;

        int idx = findCourseIndex(courses, total, target);
        if (idx == -1) {
            proof[proofCount++] = "  course not found in course list!";
            return false;
        }

        int pCount = courses[idx].getPrereqCount();
        if (pCount == 0) {
            proof[proofCount++] = "  no prerequisites = student can take this course.";
            return true;
        }

        // Check direct prereqs ONLY
        for (int i = 0; i < pCount; i++) {
            string pre = courses[idx].getPrereq(i);
            proof[proofCount++] = "  checking direct prerequisite: " + pre;

            if (!student.hasCompleted(pre)) {
                proof[proofCount++] = " student has not completed " + pre;
                return false;
            }
            else {
                proof[proofCount++] = " completed " + pre;
            }
        }

        return true;
    }

    bool canTakeCourse_StrongInduction(const Course courses[], int total,
        const Student& student, const string& target,
        string proof[], int& proofCount) {

        proofCount = 0;
        proof[proofCount++] = "Applying strong induction for recursive prerequisite verification:";
        proof[proofCount++] = "target course: " + target;

        int idx = findCourseIndex(courses, total, target);
        if (idx == -1) {
            proof[proofCount++] = "course not found.";
            return false;
        }

        bool visited[200];
        for (int i = 0; i < 200; i++) visited[i] = false;

        return strongCheck(courses, total, idx, student, proof, proofCount, visited);
    }


    void printInductionProof(string proof[], int count) {
        cout << " induction proof steps" << endl;
        for (int i = 0; i < count; i++)
            cout << proof[i] << endl;
        cout << endl;
    }

};

#endif

#pragma once
