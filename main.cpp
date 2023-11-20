#include <iostream>
#include <limits>
#include <vector>
#include <string>

using namespace std;

// Repair Record Structure
// Used to define the repair operation's properties
struct RepairRecord {
    string licensePlate;        // the car's license plate
    string ownerName;           // the owner's name
    string repairDescription;   // a short decription of the operation
    double repairCost;          // floating-point that will contain the price
    vector<string> partsUsed;   // a dynamic array of strings that will contain used parts
    int laborHours;             // how many hour are spend to reapir the car
};

// Clear the input stream's buffer
void cinClear() {
    if (cin.fail()) {
        // get rid of failure state
        cin.clear();
        // discard 'bad' character(s)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Function to add a new repair record
void addRepairRecord(vector<RepairRecord>& records) {

    // Variable to populate input data
    RepairRecord newRecord;

    cout << endl;
    // Get the license plate number
    cout << "Enter license plate number: ";
    cinClear();
    cin >> newRecord.licensePlate;

    // Get the owner's name
    cout << "Enter owner's name: ";
    cinClear();
    cin >> newRecord.ownerName;

    cout << "Enter repair description: ";
    cinClear();
    cin >> newRecord.repairDescription;

    cout << "Enter repair cost: ";
    cinClear();
    cin >> newRecord.repairCost;

    cout << "Enter number of labor hours: ";
    cinClear();
    cin >> newRecord.laborHours;

    cout << "Enter parts used (\"end\" to finish):" << endl;
    string part;
    while (true) {
        cinClear();
        cin >> part;
        if (part == "end") {
            break;
        }
        newRecord.partsUsed.push_back(part);
    }

    // Push the new record at the end of the array
    records.push_back(newRecord);
    cout << "Repair record added successfully!" << endl;
}

// Function to display a single record
void displaySingleRepairRecord(const RepairRecord record) {

    cout << endl;
    // output the current record properties
    cout << "License Plate: " << record.licensePlate << endl;
    cout << "Owner's Name: " << record.ownerName << endl;
    cout << "Repair Description: " << record.repairDescription << endl;
    cout << "Repair Cost: $" << record.repairCost << endl;
    cout << "Labor Hours: " << record.laborHours << endl;
    cout << "Parts Used:" << endl;
    // output the used parts, the part variable refers to the current part
    for (const auto& part : record.partsUsed) {
        cout << "  - " << part << endl;
    }
    // some lines to beautify the output
    cout << "------------------------" << endl;
}

// Function to display all repair records
void displayRepairRecords(const vector<RepairRecord>& records) {

    // some lines to beautify the output
    cout << endl;
    cout << "-- Repair Records --" << endl;

    // iterate over all the records, the record variable refers to the current record
    for (const auto& record : records) {
        displaySingleRepairRecord(record);
    }

}

// Function to search for a repair record by license plate
RepairRecord* searchByLicensePlate(const string& licensePlate, vector<RepairRecord>& records) {
    for (auto& record : records) {
        if (record.licensePlate == licensePlate) {
            return &record;
        }
    }
    return nullptr;
}


int main() {
    // This is the variable where we store all conducted reapirs with their properties.
    // For the example it's intizalized with some data.
    std::vector<RepairRecord> repairRecords = { // Dynamic array, initialized just for the example
        // record 1 with it's properties
        {
            "CA 7345 MT",           // the car's license plate
            "Rangel Valchanov",     // the owner's name
            "Engine Repair",        // a short decription of the operation
            500.0,                  // the price
            {                       // used parts
                "Spark Plug",       // - part 1
                "Oil Filter"        // - part 2
            },
            8                       // hour spend to reapir the car
        },
        // record 2
        {"CB 7543 AC", "Kiril Marchev", "Brake Replacement", 300.0, {"Brake Pads", "Brake Fluid"}, 4},
        // record 3
        {"EH 5645 AA", "Petar Kanev", "Transmission Overhaul", 1200.0, {"Transmission Fluid", "Clutch Kit"}, 12},
        // record 4
        {"EB 2342 KK", "Dimitar Penev", "Suspension Repair", 800.0, {"Strut Assembly", "Control Arm"}, 6},
        // record 5
        {"JKL012", "Charlie Brown", "Electrical System Check", 150.0, {"Battery", "Alternator"}, 2}
    };

    // Integer variable, used to collect user's choice from the main menu.
    int choice;

    // String variable, used when the option search is selected.
    string searchLicensePlate;

    // Main loop, user to iterate over the user's choice
    do {
        // Output the main menu
        cout << endl;
        cout << "-- Car Repair Shop Management System --" << endl;
        cout << "1. Add Repair Record" << endl;
        cout << "2. Display All Repair Records" << endl;
        cout << "3. Search for a Repair Record" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        // Input the user's choice
        cinClear();
        cin >> choice;

        // using switch to chnage the program flow according to the choice
        switch (choice) {
        case 1:
            // First option is selected, adding a new repair
            addRepairRecord(repairRecords);
            break;
        case 2:
            // Second option is selected, let's display all the records
            displayRepairRecords(repairRecords);
            break;
        case 3:
            // Third option is selected, searching for a specific wehicle
            cout << "Enter license plate number to search: ";
            cinClear();
            // input the license plate
            cin >> searchLicensePlate;
            {
                // search all the records for the license plate, null if not found
                RepairRecord* foundRecord = searchByLicensePlate(searchLicensePlate, repairRecords);
                if (foundRecord) {
                    displaySingleRepairRecord(*foundRecord);
                } else {
                    cout << "Record not found." << endl;
                }
            }
            break;
        case 4:
            // Fourth option is selected, exiting
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            // The cohoice is not recognised
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    // Exit to the shell with OK code. No error.
    return 0;
}
