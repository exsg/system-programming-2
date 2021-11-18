
#include "Country.h"
#include "Date.h"
#include "Patient.h"

Country * Country::countriesHead = nullptr;

void Country::add(Country * country) {
    if (countriesHead == nullptr) {
        countriesHead = country;
    } else {
        bool duplicate = false;

        Country *temp = countriesHead;

        while (temp != nullptr) {
            if (temp->name == country->name) {
                duplicate = true;
                break;
            }
            temp = temp->nextCountry;
        }

        if (!duplicate) {
            country->nextCountry = countriesHead;
            countriesHead = country;

        }
    }
}

Date Country::findLastDateForCountry(string country){
    Patient * thisP;
    thisP=Patient::completePatientList;
    Date dummyDate;
    dummyDate.iDD=-1;
    dummyDate.iMM=-1;
    dummyDate.iYYYY=-1;
    if(thisP!=nullptr){
        Date mostRecentDate;
        if(compareDates(thisP->entryDate  ,thisP->exitDate )){
            mostRecentDate=thisP->entryDate;
        }else{
            mostRecentDate=thisP->exitDate;
        }

        while(thisP!=nullptr){
            if(thisP->country==country){
                if(compareDates(thisP->entryDate  ,thisP->exitDate)){
                    if(compareDates(thisP->entryDate , mostRecentDate)){
                        mostRecentDate=thisP->entryDate;
                    }
                }else{
                    if(compareDates(thisP->exitDate , mostRecentDate)){
                        mostRecentDate=thisP->exitDate;
                    }
                }
            }

            thisP=thisP->nextPatient;
        }
        return mostRecentDate;
    }else{
        
        return dummyDate;
    }

}

void Country::destroy() {
    cout << "Destroying countries \n";

    Country *temp = countriesHead;

    while (temp != nullptr) {
        Country *victim = temp;
        temp = temp->nextCountry;
        delete victim;
    }
}

void Country::print() {
    Country *temp = countriesHead;

    while (temp != nullptr) {
        cout << " -" << temp->name << endl;
        temp = temp->nextCountry;
    }
}
