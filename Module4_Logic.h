#ifndef MODULE4_LOGIC_H
#define MODULE4_LOGIC_H

#include <iostream>
#include <string>
using namespace std;
//arr size fix
const int MAX_RULES = 100;//rules at 1 time
const int MAX_PREMISES = 10;//premises of 1 rule
const int MAX_FACTS = 200;//max facts
const int MAX_LOG = 500;//inference ki mssg store krny ki max limit

class LogicRule {//ek single rule a structure
public:
    string id;
    string premises[MAX_PREMISES];
    int premiseCount;
    string conclusion;
    string description;

    LogicRule() {
        id = "";
        conclusion = "";
        description = "";//optional text for explanation
        premiseCount = 0;//no of conditions
    }
//initializing rule
    void set(const string& ruleID, const string pList[], int pCount, const string& concl, const string& desc = "")
    {
        id = ruleID;//rule name
        premiseCount = pCount;
        //p copy
        //c set
        //desc set
        for (int x = 0; x < pCount; x++) {
            premises[x] = pList[x];
        }
        conclusion = concl;
        description = desc;
    }
};//p1^p2....pn->q

class LogicEngine {
//manages all rules ,facts or inference
private:
    LogicRule rules[MAX_RULES];//rules
    int ruleCount;//currently added rules
    string factNames[MAX_FACTS];//name of all fact
    bool factValues[MAX_FACTS];//t/f of fact
    int factCount;//total fact
    string inferenceLog[MAX_LOG];//record of applied rules
    int logCount;//log enteries

    int findFactIndex(const string& name) {
        for (int idx = 0; idx < factCount; idx++) {
            if (factNames[idx] == name)
                return idx;
        }
        return -1;//fact address return kryga
    }

    bool evaluatePremises(const LogicRule& r) {
        for (int p = 0; p < r.premiseCount; p++) {
            string premText = r.premises[p];
            if (premText[0] == '!') {//negation
                string actual = premText.substr(1);
                int fIndex = findFactIndex(actual);
                if (fIndex == -1 || factValues[fIndex] == true)
                    return false;
            }
            else {
                int fIndex = findFactIndex(premText);
                if (fIndex == -1 || factValues[fIndex] == false)
                    return false;
            }
        }
        return true;
    }
//adds mssg to inference
    void addLog(const string& msg) {
        if (logCount < MAX_LOG) {
            inferenceLog[logCount++] = msg;
        }
    }

public:
    LogicEngine() {
        ruleCount = 0;
        factCount = 0;
        logCount = 0;
    }

    void addRule(const string& id,
        const string premises[],
        int premCount,
        const string& conclusion,
        const string& description = "")
    {
        if (ruleCount >= MAX_RULES) return;
        rules[ruleCount].set(id, premises, premCount, conclusion, description);
        ruleCount++;
    }

    void setFact(const string& name, bool value) {
        int fIndex = findFactIndex(name);
        if (fIndex == -1) {
            fIndex = factCount++;//t/f set kryga
            factNames[fIndex] = name;
        }
        factValues[fIndex] = value;
    }

    bool getFact(const string& name) {
        int fIndex = findFactIndex(name);
        return (fIndex != -1 && factValues[fIndex]);//return kryga
    }

    int forwardChaining() {
        logCount = 0;
        addLog("forward chaining started");

        int newFacts = 0;
        bool didChange = true;

        while (didChange) {
            didChange = false;//hr rule ko check kryga agr conclusion true toh skip if premises satisfied conclusion fact list mein add ->new fact generate
            for (int r = 0; r < ruleCount; r++) {
                int conclIndex = findFactIndex(rules[r].conclusion);
                if (conclIndex != -1 && factValues[conclIndex] == true)
                    continue;//skip if c already known
                if (evaluatePremises(rules[r])) {//p true
                    setFact(rules[r].conclusion, true);
                    newFacts++;//add new facts
                    string logMsg = "rule " + rules[r].id + " applied: ";
                    for (int p = 0; p < rules[r].premiseCount; p++) {
                        logMsg += rules[r].premises[p];
                        if (p < rules[r].premiseCount - 1)
                            logMsg += " ∧ ";
                    }
                    logMsg += " → " + rules[r].conclusion;
                    addLog(logMsg);
                    didChange = true;
                }
            }
        }

        addLog(" chaining finished new facts = " + to_string(newFacts));
        return newFacts;
    }

    void displayRules() {
        cout << "rules:" << endl;
        for (int r = 0; r < ruleCount; r++) {
            cout << rules[r].id << ": ";
            for (int p = 0; p < rules[r].premiseCount; p++) {
                cout << rules[r].premises[p];
                if (p < rules[r].premiseCount - 1)
                    cout << " ∧ ";
            }
            cout << " → " << rules[r].conclusion;
            if (rules[r].description != "")
                cout << " (" << rules[r].description << ")";
            cout << endl;
        }
    }

    void displayFacts() {
        cout << "facts:" << endl;
        for (int i = 0; i < factCount; i++) {
            cout << factNames[i] << " = "
                << (factValues[i] ? "true" : "false") << endl;
        }
    }

    void displayInferenceLog() {
        cout << "inference log:" << endl;
        for (int i = 0; i < logCount; i++) {
            cout << inferenceLog[i] << endl;
        }
    }

    bool hasContradiction() {
        for (int i = 0; i < factCount; i++) {
            string neg = "!" + factNames[i];
            int j = findFactIndex(neg);
            if (j != -1 && factValues[j] == true && factValues[i] == true)
                return true;
        }
        return false;
    }

    void addFASTUniversityRules() {
        string p1[1] = { "prof_x_teaches_cs101" };
        addRule("r1", p1, 1, "lab_must_be_laba", "faculty lab rule");

        string p2[1] = { "takes_data_structures" };
        addRule("r2", p2, 1, "must_complete_programming", "prerequisite rule");

        string p3[1] = { "room_capacity_exceeded" };
        addRule("r3", p3, 1, "enrollment_conflict", "capacity issue");

        string p4[2] = { "has_prerequisites", "!completed_prerequisites" };
        addRule("r4", p4, 2, "enrollment_blocked", "missing prerequisite");
    }
};

#endif
#pragma once
