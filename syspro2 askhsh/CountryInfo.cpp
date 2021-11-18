
#include "CountryInfo.h"
#include "AggregatorShell.h"

CountryInfo * CountryInfo::countriesHead = nullptr;

void CountryInfo::add(CountryInfo * country) {
    if (countriesHead == nullptr) {
        countriesHead = country;
    } else {
        bool duplicate = false;

        CountryInfo *temp = countriesHead;

        while (temp != nullptr) {
            if (temp->name == country->name) {
                duplicate = true;
                break;
            }
            temp = temp->nextCountryInfo;
        }

        if (!duplicate) {
            country->nextCountryInfo = countriesHead;
            countriesHead = country;

        }
    }
}

void CountryInfo::destroy() {
    cout << "Destroying countries \n";

    CountryInfo *temp = countriesHead;

    while (temp != nullptr) {
        CountryInfo *victim = temp;
        temp = temp->nextCountryInfo;
        delete victim;
    }
}

void CountryInfo::print() {
    CountryInfo *temp = countriesHead;

    while (temp != nullptr) {
        if (AggregatorShell::workers == NULL) {
            cout << " -" << temp->name << endl;
        } else {
            cout << " -" << temp->name << " " << AggregatorShell::workers[temp->worker_number].pid << endl;
        }
        temp = temp->nextCountryInfo;
    }
}

int CountryInfo::countCountriesForWorker(int i) {
    CountryInfo *temp = countriesHead;

    int total = 0;

    while (temp != nullptr) {
        if (temp->worker_number == i) {
            total++;
        }

        temp = temp->nextCountryInfo;
    }
    return total;
}

string * CountryInfo::getCountries(int id) {
    int howmany = countCountriesForWorker(id);

    string * countries = new string[howmany];

    int i = 0;

    CountryInfo *temp = countriesHead;

    while (temp != nullptr) {
        if (temp->worker_number == id) {
            countries[i++] = temp->name;
        }
        temp = temp->nextCountryInfo;
    }

    return countries;
}

int  CountryInfo::countAllCountries(){
    int howmanyCountries=0;

    CountryInfo *temp=countriesHead;
    while(temp!=nullptr){
        howmanyCountries++;
        temp=temp->nextCountryInfo;
    }

    cout<<"exoume "<<howmanyCountries<<"countries\n";

    return howmanyCountries;
}

Worker * CountryInfo::getWorker(Worker * workers, string country) {
    CountryInfo *temp = countriesHead;

    while (temp != nullptr) {
        if (temp->name == country) {
            return &workers[temp->worker_number];
        }
        temp = temp->nextCountryInfo;
    }

    return NULL;
}