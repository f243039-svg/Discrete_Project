#ifndef MODULE6_FUNCTIONS_H
#define MODULE6_FUNCTIONS_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_FUNC = 100;

class FunctionModule {
private:
    string domain[MAX_FUNC];
    string codomain[MAX_FUNC];
    //ordered pairs 
    string mappingDomain[MAX_FUNC];
    string mappingRange[MAX_FUNC];
    int domainCount;
    int codomainCount;
    int mappingCount;

public:
    FunctionModule() {
        domainCount = 0;
        codomainCount = 0;
        mappingCount = 0;
    }


    void addDomainElement(const string& x) {
        if (domainCount < MAX_FUNC)
            domain[domainCount++] = x;
    }

    void addCodomainElement(const string& y) {
        if (codomainCount < MAX_FUNC)
            codomain[codomainCount++] = y;
    }


    void addMapping(const string& x, const string& y) {
        if (mappingCount < MAX_FUNC) {
            mappingDomain[mappingCount] = x;
            mappingRange[mappingCount] = y;
            mappingCount++;
        }
    }

    int findInDomain(const string& x) {
        for (int i = 0; i < domainCount; i++)
            if (domain[i] == x)
                return i;
        return -1;
    }

    int findInCodomain(const string& y) {
        for (int i = 0; i < codomainCount; i++)
            if (codomain[i] == y)
                return i;
        return -1;
    }


    bool isValidFunction() {
        for (int i = 0; i < domainCount; i++) {
            string x = domain[i];
            int count = 0;

            for (int j = 0; j < mappingCount; j++)
                if (mappingDomain[j] == x)
                    count++;

            if (count != 1)
                return false;
        }
        return true;
    }

    //  one to one 
    bool isInjective() {

        for (int i = 0; i < mappingCount; i++) {
            for (int j = i + 1; j < mappingCount; j++) {
                if (mappingRange[i] == mappingRange[j] &&
                    mappingDomain[i] != mappingDomain[j])
                    return false;
            }
        }
        return true;
    }
    //onto
    bool isSurjective() {

        for (int i = 0; i < codomainCount; i++) {
            string y = codomain[i];
            bool found = false;
            for (int j = 0; j < mappingCount; j++)
                if (mappingRange[j] == y)
                    found = true;

            if (!found) return false;
        }
        return true;
    }

    bool isBijective() {
        return isInjective() && isSurjective();
    }

    //loop throuhg the mappings and return the coresponding range 
    string applyFunction(const string& x) {
        for (int i = 0; i < mappingCount; i++)
            if (mappingDomain[i] == x)
                return mappingRange[i];
        return "undefined";
    }

    //range of G must be subset of domain of F
    //output of G is the input of F
    void compose(FunctionModule& g, FunctionModule& result) {

        // domain of result = domain of g
        result.domainCount = g.domainCount;
        for (int i = 0; i < g.domainCount; i++)
            result.domain[i] = g.domain[i];

        // codomain of result is codomain of f
        result.codomainCount = codomainCount;
        for (int i = 0; i < codomainCount; i++)
            result.codomain[i] = codomain[i];

        result.mappingCount = 0;

        // For all x in domain of g
        for (int i = 0; i < g.domainCount; i++) {
            string x = g.domain[i];
            string gx = g.applyFunction(x);
            string fgx = applyFunction(gx);

            // Add mapping: x ,f(g(x))
            result.addMapping(x, fgx);
        }
    }

    // return inverse if the function is injective 
    // swap domain and codomain 
    bool inverse(FunctionModule& inv) {
        if (!isInjective())
            return false;

        inv.domainCount = codomainCount;
        inv.codomainCount = domainCount;

        for (int i = 0; i < codomainCount; i++)
            inv.domain[i] = codomain[i];

        for (int i = 0; i < domainCount; i++)
            inv.codomain[i] = domain[i];

        inv.mappingCount = mappingCount;

        for (int i = 0; i < mappingCount; i++) {
            inv.mappingDomain[i] = mappingRange[i];
            inv.mappingRange[i] = mappingDomain[i];
        }
        return true;
    }


    void printFunction() {
        cout << "f = { ";
        for (int i = 0; i < mappingCount; i++) {
            cout << "(" << mappingDomain[i] << "- " << mappingRange[i] << ")";
            if (i < mappingCount - 1) cout << ", ";
        }
        cout << " }\n";
    }
};

#endif

