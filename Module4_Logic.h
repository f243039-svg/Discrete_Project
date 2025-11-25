#ifndef MODULE4_LOGIC_H
#define MODULE4_LOGIC_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_RULES = 100;
const int MAX_PREMISES = 10;
const int MAX_FACTS = 200;
const int MAX_LOG = 500;

class LogicRule {
public:
    string id;
    string premises[MAX_PREMISES];
    int premiseCount;
    string conclusion;
    string description;

    LogicRule() {
        id = "";
        conclusion = "";
        description = "";
        premiseCount = 0;
    }

    void set(const string& ruleID,
        const string pList[],
        int pCount,
        const string& concl,
        const string& desc = "")
    {
        id = ruleID;
        premiseCount = pCount;
        for (int x = 0; x < pCount; x++) {
            premises[x] = pList[x];
        }
        conclusion = concl;
        description = desc;
    }
};

class LogicEngine {
private:
    LogicRule rules[MAX_RULES];
    int ruleCount;
    string factNames[MAX_FACTS];
    bool factValues[MAX_FACTS];
    int factCount;
    string inferenceLog[MAX_LOG];
    int logCount;

    int findFactIndex(const string& name) {
        for (int idx = 0; idx < factCount; idx++) {
            if (factNames[idx] == name)
                return idx;
        }
        return -1;
    }

    bool evaluatePremises(const LogicRule& r) {
        for (int p = 0; p < r.premiseCount; p++) {
            string premText = r.premises[p];
            if (premText[0] == '!') {
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
            fIndex = factCount++;
            factNames[fIndex] = name;
        }
        factValues[fIndex] = value;
    }

    bool getFact(const string& name) {
        int fIndex = findFactIndex(name);
        return (fIndex != -1 && factValues[fIndex]);
    }

    int forwardChaining() {
        logCount = 0;
        addLog("forward chaining started");

        int newFacts = 0;
        bool didChange = true;

        while (didChange) {
            didChange = false;
            for (int r = 0; r < ruleCount; r++) {
                int conclIndex = findFactIndex(rules[r].conclusion);
                if (conclIndex != -1 && factValues[conclIndex] == true)
                    continue;
                if (evaluatePremises(rules[r])) {
                    setFact(rules[r].conclusion, true);
                    newFacts++;
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