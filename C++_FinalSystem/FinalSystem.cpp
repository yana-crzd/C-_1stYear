#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

struct StudentClaim {
    string studentID;
    int amountClaimed;
};

int main() {
    int numberOfStudents;
    
    cout << "Enter number of students in IT3: ";
    cin >> numberOfStudents;
    cout << endl;
    
    string studentAccounts[numberOfStudents];
    int remainingAllowances[numberOfStudents];
    
    cout << "=== STUDENT REGISTRATION ===" << endl; // student registration
    for (int i = 0; i < numberOfStudents; i++) {
        string studentID;
        bool validIf3 = false;
        
        while (!validIf3) {
            cout << "Register your Student ID Number: ";
            cin >> studentID;
            
            validIf3 = true; // Validate exactly 3 digits
            
            if (studentID.length() != 3) { // ichecheck po nito kung 3 digits lang ba yung inenter na ID#
                cout << "Student ID Number must be exactly 3 digits." << endl;
                validIf3 = false;
                continue;
            }
            
            for (int pos = 0; pos < 3; pos++) { // ichecheck po nito kung puro number lang ba yung in-enter for ID#
                if (studentID[pos] < '0' || studentID[pos] > '9') {
                    cout << "Student ID Number must be number only." << endl;
                    validIf3 = false;
                    break;
                }
            }
            
            if (!validIf3)
                continue;
            
            for (int j = 0; j < i; j++) { // ichecheck po nito kung may duplicate ID# na in-enter
                if (studentAccounts[j] == studentID) {
                    cout << "This ID Number is already registered!\n";
                    validIf3 = false;
                    break;
                }
            }
            
            if (validIf3) {
                studentAccounts[i] = studentID;
                remainingAllowances[i] = 2000;
            }
        }
    }
    cout << endl;
    
    int totalAllowance = 2000 * numberOfStudents;
    cout << "The Mayor has released a " << totalAllowance << " allowance for IIT3 section." << endl;
    
    queue <StudentClaim> claimedQueue;
    queue <string> notClaimedQueue;
    int totalClaimed = 0;
    
    unordered_set<string> processedStudents; // tracker if the entered ID# was already processed

    cout << endl;
    cout << "=== CLAIMING PROCESS ===" << endl; // Student claiming process
    for (int currentStudent = 0; currentStudent < numberOfStudents; currentStudent++) { // a loop na kung saan mag-iiterate ito hanggang sa ma-enter lahat ng ID# na nai-register
        string studentID;
        bool validID = false;
        int studentIndex = -1;
        
        while (!validID) { 
            cout << "Enter your Student ID: "; // habang valid yung ID# na i-eenter, magpapaulit-ulit lang 'to dahil may while loop sa taas nito
            cin >> studentID;
            
            if (processedStudents.find(studentID) != processedStudents.end()) { // check if the student already processed
                cout << "Claim for this Student ID Number is complete. It's a one-time process." << endl;
                cout << endl;
                continue;  // skip to next iteration para mag-prompt ulit ng new ID
            }
            
            // Find student in array with exact 3-digit match
            for (int i = 0; i < numberOfStudents; i++) {
                if (studentID.length() == 3 && studentID == studentAccounts[i]) {
                    validID = true;
                    studentIndex = i;
                    break;
                }
            }
            
            if (!validID) {
                cout << "Invalid Student ID. It must be a REGISTERED Student ID Number.\n\n";
                continue;
            }
            
            processedStudents.insert(studentID); // Mark student as processed
            
            cout << "Your Internet Allowance: " << remainingAllowances[studentIndex] << endl;
            
            char answerForClaim;
            do {
                cout << "CLAIM YOUR ALLOWANCE NOW? [Y/N]: "; // asking the user if gusto niya na ba i-claim allowance niya
                cin >> answerForClaim;
                
                if (answerForClaim == 'Y' || answerForClaim == 'y') {
                    int amountToClaim;
                    bool validAmount = false;
                    string amountInString;
                    
                    do {
                        cout << "Enter amount to claim (max " << remainingAllowances[studentIndex] << "): "; // magpapaulit ulit itong i-ask until maging valid yung amount na i-eenter
                        cin >> amountInString;
                        
                        bool isNumber = true;
                        for (char c : amountInString) { 
                            if (!isdigit(c)) { // for each character, it checks if it's not a digit (0-9).
                                isNumber = false;
                                break;
                            }
                        }
                        
                        if (!isNumber) {
                            cout << "Please enter numbers only." << endl; // it will be displayed if the entered amount is not numeric
                            continue;
                        }
                    
                        amountToClaim = stoi(amountInString); // Convert the amount into integer
                        
                        if (amountToClaim <= 0) {
                            cout << "Please enter amount." << endl;
                            continue;
                        }
                        
                        if (amountToClaim > remainingAllowances[studentIndex]) {
                            cout << "Amount exceeds balance. Try again." << endl;
                            continue;
                        }
                        
                        validAmount = true; // 'pag nakarating na rito, the amount will be valid
                        
                        StudentClaim claim;
                        claim.studentID = studentID;
                        claim.amountClaimed = amountToClaim;
                        claimedQueue.push(claim); 
                        
                        remainingAllowances[studentIndex] -= amountToClaim;
                        totalClaimed += amountToClaim;
                        cout << "Successfully claimed " << amountToClaim << "." << endl;
                        cout << "Remaining allowance: " << remainingAllowances[studentIndex] << endl;
                        cout << endl;
                        
                    } while (!validAmount);
                    break; // Exit the Y/N loop after processing
                } 
                else if (answerForClaim == 'N' || answerForClaim == 'n') {
                    notClaimedQueue.push(studentID);
                    cout << "Your allowance remains available for later." << endl;
                    cout << endl;
                    break;
                } 
                else {
                    cout << "Invalid choice. [Type Y/N only]." << endl;
                }
            } while (true); // Loop continues hanggang sa Y/y or N/n ang i-enter ni user
        }
    }

    // cout << endl;
    cout << "=== CLAIM SUMMARY ===" << endl; // Displaying the claim summary
    char viewChoice;
    
    cout << "Which list would you like to view first?" << endl;
    cout << "1. List of Students who claimed their allowance." << endl;
    cout << "2. List of Students who didn't claim their allowance." << endl;
    while (true) { // loop until maging valid yung choice na i-eenter sa viewChoice
        cout << "Enter your choice (1 or 2): ";
        cin >> viewChoice;
        
        if (viewChoice == '1' || viewChoice == '2') {
            break;  // mag-eexit sa loop if the input is valid
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    }

    if (viewChoice == '1') {
        cout << endl;
        cout << "=== STUDENTS WHO CLAIMED ALLOWANCE (" << claimedQueue.size() << ") ===" << endl;
        cout << "ID\t\t\tClaimed\t\t\tRemaining" << endl;
        cout << "--------------------------------" << endl;
        while (!claimedQueue.empty()) {
            StudentClaim claim = claimedQueue.front();
            int remaining = 0;
            for (int i = 0; i < numberOfStudents; i++) {
                if (studentAccounts[i] == claim.studentID) {
                    remaining = remainingAllowances[i];
                    break;
                }
            }
            cout << "#" << claim.studentID << "\t\t\t" << claim.amountClaimed << "\t\t\t" << remaining << endl;
            claimedQueue.pop();
        }
    
        char viewOther;
        while (true) {
            cout << endl;
            cout << "Would you like to view students who didn't claim? [Y/N]: "; // magpapaulit-ulit itong i-ask until maging valid yung input ng user for viewOther (because of the while loop)
            cin >> viewOther;
            
            if (viewOther == 'Y' || viewOther == 'y' || viewOther == 'N' || viewOther == 'n') {
                break;
            }
            else {
                cout << "Please answer Y/N only." << endl;
            }
        }
    
        if (viewOther == 'Y' || viewOther == 'y') {
            cout << endl;
            cout << "=== STUDENTS WHO DIDN'T CLAIM (" << notClaimedQueue.size() << ") ===" << endl;
            cout << "ID\t\t\tRemaining Allowance" << endl;
            cout << "--------------------------" << endl;
            queue<string> notClaimed = notClaimedQueue;
            while (!notClaimed.empty()) {
                string id = notClaimed.front();
                int remaining = 0;
                for (int i = 0; i < numberOfStudents; i++) {
                    if (studentAccounts[i] == id) {
                        remaining = remainingAllowances[i];
                        break;
                    }
                }
                cout << "#" << id << "\t\t\t" << remaining << endl;
                notClaimed.pop();
            }
        }
    }

    else if (viewChoice == '2') {
        cout << endl;
        cout << "=== STUDENTS WHO DIDN'T CLAIM (" << notClaimedQueue.size() << ") ===" << endl;
        cout << "ID\t\t\tRemaining Allowance" << endl;
        cout << "--------------------------------------------------" << endl;
        queue<string> notClaimed = notClaimedQueue;
        while (!notClaimed.empty()) {
            string id = notClaimed.front();
            int remaining = 0;
            for (int i = 0; i < numberOfStudents; i++) {
                if (studentAccounts[i] == id) {
                    remaining = remainingAllowances[i];
                    break;
                }
            }
            cout << "#" << id << "\t\t\t" << remaining << endl;
            notClaimed.pop();
        }
        
        char viewOther;
        // Loop until valid input is received for view other prompt
        while (true) {
            cout << endl;
            cout << "Would you like to view students who claimed? [Y/N]: ";
            cin >> viewOther;
            
            if (viewOther == 'Y' || viewOther == 'y' || viewOther == 'N' || viewOther == 'n') {
                break;
            }
            else {
                cout << "Please answer Y/N only." << endl;
            }
        }
        
        if (viewOther == 'Y' || viewOther == 'y') {
            cout << endl;
            cout << "=== STUDENTS WHO CLAIMED THEIR ALLOWANCE (" << claimedQueue.size() << ") ===" << endl;
            cout << "ID\t\t\tClaimed\t\t\tRemaining Allowance" << endl;
            cout << "--------------------------------------------------" << endl;
            queue<StudentClaim> claimed = claimedQueue;
            while (!claimed.empty()) {
                StudentClaim claim = claimed.front();
                int remaining = 0;
                for (int i = 0; i < numberOfStudents; i++) {
                    if (studentAccounts[i] == claim.studentID) {
                        remaining = remainingAllowances[i];
                        break;
                    }
                }
                cout << "#" << claim.studentID << "\t\t\t" << claim.amountClaimed << "\t\t\t" << remaining << endl;
                claimed.pop();
            }
        }
    }
    
    cout << "\n=== FINAL SUMMARY ===" << endl;
    cout << "Total allowance from Mayor: " << totalAllowance << endl;
    cout << "Total claimed by all students: " << totalClaimed << endl;
    cout << "Total remaining allowance of IT3: " << (totalAllowance - totalClaimed) << endl;
    
    return 0;
}