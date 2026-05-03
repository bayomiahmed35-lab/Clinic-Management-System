#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// ======================================================
// الـ Structs
// ======================================================
struct patient {
    string name;
    int age;
    string id;
    string phone;
    string password;
};

struct doctor {
    string name;
    string specialization;
    string id;
    float ConsultationFee;
    float discount;
    int startHour;
    int endHour;
};

struct appointment {
    string appointmentID;
    string doctorid;
    string patientid;
    string doctorname;
    int day;
    int month;
    int year;
    int time;
    bool status;
    float total;
};

struct admin {
    string name;
    string id;
    string password;
};

// ======================================================
// المتغيرات العامة والثوابت
// ======================================================
const int MAX_DOCTORS = 20;
const int MAX_PATIENTS = 50;
const int ntime = 100;
const int totaladmins = 2;
doctor listofdoctors[MAX_DOCTORS];
patient listofof_patient[MAX_PATIENTS];
appointment listof_appointments[ntime];
admin listofadmins[totaladmins];
int doctorCount = 3;
int appointmentsCount = 1;
int patientsCount = 5;
int admincount = 2;

// ======================================================
// دوال التحقق (Validation)
// ======================================================
void validationtext(string& text) {
    while (true) {
        bool check1 = true;
        for (int i = 0; text[i] != '\0'; i++) {
            if (!((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') || (text[i] == ' '))) {
                check1 = false;
            }
        }
        if (check1)
            break;
        else {
            cout << "Invalid! Enter characters only: ";
            cin >> text;
        }
    }
}

void validation(string& id) {
    while (true) {
        bool check2 = true;
        for (int i = 0; id[i] != '\0'; i++) {
            if (id[i] < '0' || id[i] > '9') {
                check2 = false;
                break;
            }
        }
        if (check2 == true) {
            break;
        }
        else {
            cout << "Invalid! Enter numbers only: ";
            cin >> id;
        }
    }
}

bool check(string id, string type) {
    if (type == "patient") {
        for (int i = 0; i < patientsCount; i++) {
            if (listofof_patient[i].id == id && listofof_patient[i].id != "0") {
                return true;
            }
        }
    }
    else if (type == "doctors") {
        for (int i = 0; i < doctorCount; i++) {
            if (listofdoctors[i].id == id && listofdoctors[i].id != "0") {
                return true;
            }
        }
    }
    else if (type == "appointment") {
        for (int i = 0; i < appointmentsCount; i++) {
            if (listof_appointments[i].appointmentID == id && listof_appointments[i].appointmentID != "0") {
                return true;
            }
        }
    }
    return false;
}

int finddoctorindex(string doctorid) {
    if (check(doctorid, "doctors")) {
        for (int i = 0; i < doctorCount; i++) {
            if (listofdoctors[i].id == doctorid && listofdoctors[i].id != "0") {
                return i;
            }
        }
    }
    return -1;
}

int getValidTime() {
    int hour;
    while (true) {
        cout << "Enter hour (0-23): ";
        cin >> hour;
        if (hour >= 0 && hour <= 23) {
            return hour;
        }
        else {
            cout << "Invalid! Please use 0 for Midnight, and 12 for Noon.\n";
        }
    }
}

void showFormattedTime(int time) {
    if (time == 0 || time == 24) {
        cout << "12:00 AM";
    }
    else if (time == 12) {
        cout << "12:00 PM";
    }
    else if (time > 0 && time < 12) {
        cout << time << ":00 AM";
    }
    else if (time > 12 && time < 24) {
        cout << (time - 12) << ":00 PM";
    }
}

void getValidDate(int& selectedDay, int& selectedMonth, int& selectedYear) {
    const int openingDay = 1, openingMonth = 1, openingYear = 2026;
    while (true) {
        cout << "Enter Date (Day Month Year): ";
        cin >> selectedDay >> selectedMonth >> selectedYear;
        bool isLogical = (selectedDay >= 1 && selectedDay <= 31 && selectedMonth >= 1 && selectedMonth <= 12 && selectedYear >= 2026);
        bool isAfterOpening = false;
        if (selectedYear > openingYear) isAfterOpening = true;
        else if (selectedYear == openingYear) {
            if (selectedMonth > openingMonth) isAfterOpening = true;
            else if (selectedMonth == openingMonth && selectedDay >= openingDay) isAfterOpening = true;
        }
        if (isLogical && isAfterOpening) {
            break;
        }
        else {
            cout << "Invalid! Clinic opened on " << openingDay << "/" << openingMonth << "/" << openingYear << endl;
        }
    }
}

// ======================================================
// دوال التهيئة
// ======================================================
void initializeDoctors() {
    // الأرقام هنا بتمثل الساعات بنظام 24 ساعة
    listofdoctors[0] = { "Dr.Ahmed", "Cardiology", "101", 500, 0, 9, 16 }; // من 9 ص لـ 4  ظ
    listofdoctors[1] = { "Dr.Sarah", "Internal Medicine", "102", 300, 0, 10, 18 }; // من 10 ظ لـ 6 م
    listofdoctors[2] = { "Dr.Tarek", "Eye", "104", 350, 0, 8, 15 }; // من 8 ص ل3م
    doctorCount = 3;
}

void initializePatients() {
    listofof_patient[0] = { "Ahmed_User", 20, "100", "01011", "pass100" };
    listofof_patient[1] = { "Salem_User", 21, "101", "01022", "pass101" };
    listofof_patient[2] = { "Adel_User", 19, "102", "01033", "pass102" };
    listofof_patient[3] = { "Mokhtar_User", 22, "103", "01044", "pass103" };
    listofof_patient[4] = { "Hassan_User", 20, "104", "01055", "pass104" };
    patientsCount = 5;
}void initializeAppointments() {
    // الترتيب: { appointmentID, doctorid, patientid, day, month, year, time, status, total }

    // --- مواعيد دكتور أحمد (101) ---
    listof_appointments[0] = { "100", "101", "0", "Dr. Ahmed", 10, 5, 2026, 9,  false, 500.0 };
    listof_appointments[1] = { "101", "101", "0", "Dr. Ahmed", 10, 5, 2026, 10, false, 500.0 };
    listof_appointments[2] = { "102", "101", "0", "Dr. Ahmed", 10, 5, 2026, 11, false, 500.0 };
    listof_appointments[3] = { "103", "101", "0", "Dr. Ahmed", 10, 5, 2026, 12, false, 500.0 };
    listof_appointments[4] = { "104", "101", "0", "Dr. Ahmed", 10, 5, 2026, 13, false, 500.0 };
    listof_appointments[5] = { "105", "101", "0", "Dr. Ahmed", 10, 5, 2026, 14, false, 500.0 };
    listof_appointments[6] = { "106", "101", "0", "Dr. Ahmed", 10, 5, 2026, 15, false, 500.0 };


    // مواعيد دكتورة سارة (8 مواعيد)
    listof_appointments[8] = { "108", "102", "0", "Dr. Sara", 11, 5, 2026, 10, false, 400.0 };
    listof_appointments[9] = { "109", "102", "0", "Dr. Sara", 11, 5, 2026, 11, false, 400.0 };
    listof_appointments[10] = { "110", "102", "0", "Dr. Sara", 11, 5, 2026, 12, false, 400.0 };
    listof_appointments[11] = { "111", "102", "0", "Dr. Sara", 11, 5, 2026, 13, false, 400.0 };
    listof_appointments[12] = { "112", "102", "0", "Dr. Sara", 11, 5, 2026, 14, false, 400.0 };
    listof_appointments[13] = { "113", "102", "0", "Dr. Sara", 11, 5, 2026, 15, false, 400.0 };
    listof_appointments[14] = { "114", "102", "0", "Dr. Sara", 11, 5, 2026, 16, false, 400.0 };
    listof_appointments[15] = { "115", "102", "0", "Dr. Sara", 11, 5, 2026, 17, false, 400.0 };

    // مواعيد دكتور طارق (8 مواعيد)
    listof_appointments[16] = { "116", "103", "0", "Dr. Tarek", 12, 5, 2026, 8,  false, 300.0 };
    listof_appointments[17] = { "117", "103", "0", "Dr. Tarek", 12, 5, 2026, 9,  false, 300.0 };
    listof_appointments[18] = { "118", "103", "0", "Dr. Tarek", 12, 5, 2026, 10, false, 300.0 };
    listof_appointments[19] = { "119", "103", "0", "Dr. Tarek", 12, 5, 2026, 11, false, 300.0 };
    listof_appointments[20] = { "120", "103", "0", "Dr. Tarek", 12, 5, 2026, 12, false, 300.0 };
    listof_appointments[21] = { "121", "103", "0", "Dr. Tarek", 12, 5, 2026, 13, false, 300.0 };
    listof_appointments[22] = { "122", "103", "0", "Dr. Tarek", 12, 5, 2026, 14, false, 300.0 };
    listof_appointments[23] = { "123", "103", "0", "Dr. Tarek", 12, 5, 2026, 15, false, 300.0 };

    appointmentsCount = 24;
}
void initializeAdmins() {
    listofadmins[0] = { "ahmed","1000","1234" };
    listofadmins[1] = { "mohamed","1001","4321" };
}
// ======================================================
// دوال إدارة الدكاترة
// ======================================================
void addDoctor() {
    if (doctorCount >= 20) {
        cout << "\n[!] Error: System is full (Max 20 Doctors).\n";
        return;
    }

    doctor day;


    int docIDVal = 100 + doctorCount;
    day.id = to_string(docIDVal);

    cout << "\n[System] New Doctor assigned ID: " << day.id << endl;

    cout << "Enter Doctor Name: ";
    cin.ignore();
    getline(cin, day.name);
    validationtext(day.name);

    cout << "Enter Specialization: ";
    getline(cin, day.specialization);
    validationtext(day.specialization);

    cout << "Enter Consultation Fee: ";
    cin >> day.ConsultationFee;

    cout << "Enter Start Work Hour (0-23): ";
    cin >> day.startHour;
    cout << "Enter End Work Hour (0-23): ";
    cin >> day.endHour;
    cout << "Enter Discount (%): ";
    cin >> day.discount;


    int startDay = 2;
    for (int dayOff = 0; dayOff < 3; dayOff++) {
        for (int h = day.startHour; h < day.endHour; h++) {
            if (appointmentsCount < 100) {


                int autoAppID = 100 + appointmentsCount;

                listof_appointments[appointmentsCount].appointmentID = to_string(autoAppID);
                listof_appointments[appointmentsCount].doctorid = day.id;
                listof_appointments[appointmentsCount].doctorname = day.name;
                listof_appointments[appointmentsCount].day = startDay + dayOff;
                listof_appointments[appointmentsCount].month = 5;
                listof_appointments[appointmentsCount].year = 2026;
                listof_appointments[appointmentsCount].time = h;
                listof_appointments[appointmentsCount].status = false;

                float fee = day.ConsultationFee;
                listof_appointments[appointmentsCount].total = fee - (fee * (day.discount / 100.0));

                appointmentsCount++;
            }
        }
    }

    listofdoctors[doctorCount] = day;
    doctorCount++;
    cout << "[+] Doctor added successfully!\n";
}
void removeDoctor() {
    string doctorID;
    cout << "Enter Doctor ID to remove: ";
    cin >> doctorID;
    validation(doctorID);

    int doctorIndex = -1;
    for (int i = 0; i < doctorCount; i++) {
        if (listofdoctors[i].id == doctorID) {
            doctorIndex = i;
            break;
        }
    }

    if (doctorIndex == -1) {
        cout << "Error: Doctor not found!\n";

    }
    else {
        for (int i = doctorIndex; i < doctorCount - 1; i++) {
            listofdoctors[i] = listofdoctors[i + 1];
        }
        doctorCount--;


        for (int i = 0; i < appointmentsCount; ) {
            if (listof_appointments[i].doctorid == doctorID) {

                for (int j = i; j < appointmentsCount - 1; j++) {
                    listof_appointments[j] = listof_appointments[j + 1];
                }
                appointmentsCount--;

            }
            else {
                i++;
            }
        }

        cout << "Doctor and all associated appointments removed successfully!\n";
    }

}


void showAllDoctors() {
    cout << "\n" << string(110, '-') << endl;
    cout << "--- [ List of All Doctors ] ---" << endl;
    cout << string(110, '-') << endl;


    cout << left << setw(8) << "ID"
        << setw(20) << "Name"
        << setw(25) << "Specialization"
        << setw(30) << "Fees & Offers"
        << setw(20) << "Shift (Start-End)" << endl;

    cout << string(110, '-') << endl;

    for (int i = 0; i < doctorCount; i++) {

        float finalPrice = listofdoctors[i].ConsultationFee - (listofdoctors[i].ConsultationFee * listofdoctors[i].discount / 100);

        cout << left << setw(8) << listofdoctors[i].id
            << setw(20) << listofdoctors[i].name
            << setw(25) << listofdoctors[i].specialization;


        if (listofdoctors[i].discount > 0) {

            cout << listofdoctors[i].ConsultationFee << " -> " << finalPrice << " EGP";

            cout << setw(10) << "";
        }
        else {
            cout << listofdoctors[i].ConsultationFee << " EGP";
            cout << setw(20) << "";
        }



        cout << left << setw(2);

        showFormattedTime(listofdoctors[i].startHour);

        cout << " - ";

        showFormattedTime(listofdoctors[i].endHour);


        cout << endl;
    }

    cout << string(110, '-') << endl;
}
// ======================================================
// دوال إدارة المرضى
// ======================================================
string signUp_patient() {
    if (patientsCount >= 50) {
        cout << "\n[!] Error: System is full (Max 50 Patients).\n";
        return "-1";
    }


    int idVal = 100 + patientsCount;
    string assignedID = to_string(idVal);

    listofof_patient[patientsCount].id = assignedID;

    cout << "\n--- [ New Patient Registration ] ---\n";
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, listofof_patient[patientsCount].name);
    validationtext(listofof_patient[patientsCount].name);

    cout << "Create Password: ";
    cin >> listofof_patient[patientsCount].password;

    cout << "Enter Phone: ";
    cin >> listofof_patient[patientsCount].phone;
    validation(listofof_patient[patientsCount].phone);

    cout << "Enter Age: ";
    cin >> listofof_patient[patientsCount].age;

    cout << "\n[Success] Your account has been created!";
    cout << "\n>>> YOUR UNIQUE ID IS: " << assignedID << " <<<\n";

    patientsCount++;
    return assignedID;
}
string login_patient() {
    string inputID, inputPass;
    cout << "\n--- [ Patient Login Portal ] ---\n";
    cout << "Enter your 3-digit ID: ";
    cin >> inputID;
    validation(inputID);
    cout << "Enter Password: ";
    cin >> inputPass;

    for (int i = 0; i < patientsCount; i++) {
        if (listofof_patient[i].id == inputID && listofof_patient[i].password == inputPass) {
            cout << "\nWelcome back, " << listofof_patient[i].name << ".\n";
            return inputID;
        }
    }
    cout << "\n[X] Invalid ID or Password.\n";
    return "-1";
}

string login_admin() { // 
    string inputID, inputPass;
    cout << "\n--- [ Admin Control Login ] ---\n";
    cout << "Admin ID: ";
    cin >> inputID;
    cout << "Admin Password: ";
    cin >> inputPass;

    for (int i = 0; i < totaladmins; i++) {

        if (listofadmins[i].id == inputID && listofadmins[i].password == inputPass) {
            cout << "\n[Access Granted] Welcome, Administrator.\n";
            return inputID;
        }
    }


    cout << "\n[Access Denied] Incorrect Admin credentials.\n";
    return "-1";
}
// ======================================================
// دوال المواعيد
// ======================================================


void showAppointments() {
    cout << " \t\t\t\t\t\t\t\tA LIST TO SHOW ALL APPOINTMENTS\n";
    cout << "\t\t\t\t\t\t\t\t-------------------------------\n\n\n";

    for (int i = 0; i < appointmentsCount; i += 2) {

        int d1 = -1, d2 = -1;
        for (int j = 0; j < doctorCount; j++) {
            if (listofdoctors[j].id == listof_appointments[i].doctorid) d1 = j;
            if (i + 1 < appointmentsCount && listofdoctors[j].id == listof_appointments[i + 1].doctorid) d2 = j;
        }


        cout << "Appointment ID: " << listof_appointments[i].appointmentID;
        cout << "                                        ";
        if (i + 1 < appointmentsCount)
            cout << "Appointment ID: " << listof_appointments[i + 1].appointmentID;
        cout << endl;

        cout << "Doctor name: " << (d1 != -1 ? listofdoctors[d1].name : "N/A");
        cout << "                                   ";
        if (i + 1 < appointmentsCount)
            cout << "Doctor name: " << (d2 != -1 ? listofdoctors[d2].name : "N/A");
        cout << endl;


        cout << "Doctor specialization: " << (d1 != -1 ? listofdoctors[d1].specialization : "N/A");
        cout << "               ";
        if (i + 1 < appointmentsCount)
            cout << "Doctor specialization: " << (d2 != -1 ? listofdoctors[d2].specialization : "N/A");
        cout << endl;


        cout << "Doctor ID: " << listof_appointments[i].doctorid;
        cout << "                                            ";
        if (i + 1 < appointmentsCount)
            cout << "Doctor ID: " << listof_appointments[i + 1].doctorid;
        cout << endl;


        cout << "Consultation Fee: " << listof_appointments[i].total << " EGP";
        cout << "                               ";
        if (i + 1 < appointmentsCount)
            cout << "Consultation Fee: " << listof_appointments[i + 1].total << " EGP";
        cout << endl;


        cout << "Date: " << listof_appointments[i].day << "/" << listof_appointments[i].month << "/" << listof_appointments[i].year;
        cout << "                                         ";
        if (i + 1 < appointmentsCount)
            cout << "Date: " << listof_appointments[i + 1].day << "/" << listof_appointments[i + 1].month << "/" << listof_appointments[i + 1].year;
        cout << endl;


        cout << "Time: " << listof_appointments[i].time << ":00";
        cout << "                                            ";
        if (i + 1 < appointmentsCount)
            cout << "Time: " << listof_appointments[i + 1].time << ":00";
        cout << endl;


        cout << "Status: " << (listof_appointments[i].status ? "booked" : "free");
        cout << "                                           ";
        if (i + 1 < appointmentsCount)
            cout << "Status: " << (listof_appointments[i + 1].status ? "booked" : "free");
        cout << endl;


        cout << "----------------------------------"
            << "                      "
            << "----------------------------------" << endl << endl;
    }
}

void viewMyAppointments(string patientID) {
    float grandTotal = 0;
    bool hasAppointments = false;

    cout << "\n========================================================================================\n";
    cout << "                             YOUR DETAILED BILLING SUMMARY                              \n";
    cout << "========================================================================================\n";

    cout << left << setw(12) << "Patient ID"
        << setw(10) << "Room ID"
        << setw(15) << "Date"
        << setw(12) << "Time"
        << setw(15) << "Doctor ID"
        << "Fees" << endl;
    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < appointmentsCount; i++) {
        if (listof_appointments[i].patientid == patientID && listof_appointments[i].status == true) {


            cout << left << setw(12) << listof_appointments[i].patientid
                << setw(10) << listof_appointments[i].appointmentID
                << listof_appointments[i].day << "/" << listof_appointments[i].month << "/" << listof_appointments[i].year << "   " << setw(5) << " "
                << listof_appointments[i].time << ":00" << setw(7) << " "
                << setw(15) << listof_appointments[i].doctorid
                << listof_appointments[i].total << " EGP" << endl;

            grandTotal += listof_appointments[i].total;
            hasAppointments = true;
        }
    }

    if (!hasAppointments) {
        cout << "\n\t\t\t      No appointments found for ID: " << patientID << endl;
    }


    cout << "----------------------------------------------------------------------------------------\n";
    cout << right << setw(72) << "GRAND TOTAL:" << " " << setw(8) << grandTotal << " EGP" << endl;
    cout << "========================================================================================\n";
}
void cancelAppointment() {
    string targetAppID;
    int day, month, year;

    cout << "Enter Appointment ID to cancel (from the bill): ";
    cin >> targetAppID;
    cout << "Enter Date (Day Month Year): ";
    cin >> day >> month >> year;

    bool found = false;
    for (int i = 0; i < appointmentsCount; i++) {

        if (listof_appointments[i].appointmentID == targetAppID &&
            listof_appointments[i].day == day &&
            listof_appointments[i].month == month &&
            listof_appointments[i].year == year) {


            listof_appointments[i].status = false;
            listof_appointments[i].patientid = "0";

            cout << "[+] Appointment " << targetAppID << " cancelled successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "[!] No matching appointment found. Check your ID and Date again.\n";
    }
}
void userSearchEngine() {
    char choice;
    do {
        string targetID;
        bool found = false;

        cout << "\n--- [ Patient: Search for Doctor Appointments ] ---\n";
        cout << "Enter Doctor ID: ";
        cin >> targetID;
        validation(targetID);

        for (int i = 0; i < doctorCount; i++) {
            if (listofdoctors[i].id == targetID) {
                cout << "\nShowing results for Dr: " << listofdoctors[i].name << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "[!] ID not found. Please check the Doctor ID and try again.\n";
        }
        else {
            cout << left << setw(10) << "App.ID" << setw(15) << "Date" << "Time" << endl;
            bool hasSlots = false;
            for (int i = 0; i < appointmentsCount; i++) {
                if (listof_appointments[i].doctorid == targetID && listof_appointments[i].status == false) {
                    cout << left << setw(10) << listof_appointments[i].appointmentID
                        << listof_appointments[i].day << "/" << listof_appointments[i].month << "/" << listof_appointments[i].year
                        << "  ";
                    showFormattedTime(listof_appointments[i].time);
                    cout << endl;
                    hasSlots = true;
                }
            }
            if (!hasSlots) cout << "No free slots available for this doctor.\n";
        }

        cout << "\nSearch again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
void adminFeeManager() {
    string targetID;
    bool doctorFound = false;

    cout << "\n--- [ Admin: Update Fees & Discounts ] ---" << endl;
    cout << "Enter Doctor ID to modify: ";
    cin >> targetID;

    for (int i = 0; i < doctorCount; i++) {
        if (listofdoctors[i].id == targetID) {
            doctorFound = true;

            float newFee, discountPercent;
            cout << "Current Fee for " << listofdoctors[i].name << " is: " << listofdoctors[i].ConsultationFee << " EGP" << endl;

            cout << "Enter New Consultation Fee (EGP): ";
            cin >> newFee;

            cout << "Enter Discount Percentage (0-100%): ";
            cin >> discountPercent;

            listofdoctors[i].ConsultationFee = newFee;
            listofdoctors[i].discount = discountPercent;


            float finalPrice = newFee * (1.0 - (discountPercent / 100.0));


            int updatedCount = 0;
            for (int j = 0; j < appointmentsCount; j++) {

                if (listof_appointments[j].doctorid == targetID && listof_appointments[j].status == false) {
                    listof_appointments[j].total = finalPrice;
                    updatedCount++;
                }
            }

            cout << "\nSuccess!" << endl;
            cout << "New Base Fee: " << newFee << " EGP" << endl;
            cout << "Discount: " << discountPercent << "%" << endl;
            cout << "Final Price to be paid (for new bookings): " << finalPrice << " EGP" << endl;
            cout << "Total available appointments updated: " << updatedCount << endl;
            cout << "Note: Reserved appointments remained unchanged." << endl;

            break;
        }
    }

    if (!doctorFound) {
        cout << "Error: Doctor with ID " << targetID << " not found!" << endl;
    }
}

int bookappointment(string patientname, string patientid, string doctorid, int day, int month, int year, int time, string appointment_id) {

    if (!check(patientid, "patient")) {
        cout << "[!] Error: Patient ID not found" << endl;
        return 1;
    }
    if (!check(doctorid, "doctors")) {
        cout << "[!] Error: Doctor ID not found." << endl;
        return 2;
    }

    int docIdx = finddoctorindex(doctorid);
    int targetIdx = -1;



    if (docIdx != -1) {
        int start = listofdoctors[docIdx].startHour;
        int end = listofdoctors[docIdx].endHour;

        if (time < start || time >= end) {
            cout << "[!] Error: Dr. " << listofdoctors[docIdx].name
                << " is only available from ";
            showFormattedTime(start);
            cout << " to ";
            showFormattedTime(end);
            cout << endl;
            return 5; // يخرج وما يكملش حجز
        }
    }

    for (int i = 0; i < appointmentsCount; i++) {
        if (check(appointment_id, "appointments")) {
            if (listof_appointments[i].status == true) {
                cout << "[!] Error: This ID is already reserved!" << endl;
                return 3;
            }

            targetIdx = i;
            listof_appointments[targetIdx].patientid = patientid;
            listof_appointments[targetIdx].status = true;
            break;
        }
    }


    if (targetIdx == -1) {

        for (int i = 0; i < appointmentsCount; i++) {
            if (listof_appointments[i].doctorid == doctorid &&
                listof_appointments[i].day == day &&
                listof_appointments[i].month == month &&
                listof_appointments[i].year == year &&
                listof_appointments[i].time == time &&
                listof_appointments[i].status == true) {
                cout << "[!] Error: Doctor is busy at this time." << endl;
                return 4;
            }
        }

        targetIdx = appointmentsCount;
        listof_appointments[targetIdx].doctorid = doctorid;
        listof_appointments[targetIdx].patientid = patientid;
        listof_appointments[targetIdx].day = day;
        listof_appointments[targetIdx].month = month;
        listof_appointments[targetIdx].year = year;
        listof_appointments[targetIdx].time = time;
        listof_appointments[targetIdx].appointmentID = appointment_id;
        listof_appointments[targetIdx].status = true;


        float fee = listofdoctors[docIdx].ConsultationFee;
        float disc = listofdoctors[docIdx].discount;
        listof_appointments[targetIdx].total = fee - (fee * (disc / 100.0));

        appointmentsCount++;
    }


    cout << "\n-------------------------------------------\n";
    cout << "[SUCCESS] Appointment confirmed!" << endl;
    cout << "Patient: " << patientname << " (ID: " << patientid << ")" << endl;
    cout << "With Doctor: " << listofdoctors[docIdx].name << " (ID: " << doctorid << ")" << endl;
    cout << "Appt ID: " << appointment_id << endl;
    cout << "at "; showFormattedTime(listof_appointments[targetIdx].time);
    cout << "\ndate: " << listof_appointments[targetIdx].day << "/" << listof_appointments[targetIdx].month << "/" << listof_appointments[targetIdx].year;
    cout << "\nthe TOTAL fee: " << listof_appointments[targetIdx].total << " EGP\n";
    cout << "the status is: BOOKED\n";
    cout << "-------------------------------------------\n";

    return 0;
}
void logoutPatient() { // شيلنا الباراميتر
    cout << "\n------------------------------------------" << endl;
    cout << "Logged out successfully!" << endl;
    cout << "Thank you for using our Clinic System." << endl;
    cout << "See you again soon!" << endl;
    cout << "------------------------------------------" << endl;
}

void logoutAdmin() {
    cout << "\n------------------------------------------" << endl;
    cout << "Admin Session Ended." << endl;
    cout << "Securely logged out." << endl;
    cout << "------------------------------------------" << endl;
}
// ======================================================
// قوائم المستخدمين
// ======================================================
void patientMenu(string patientID) {
    char choice;
    string patientName = "Patient"; // قيمة افتراضية

    // تجلب اسم المريض
    for (int i = 0; i < patientsCount; i++) {
        if (listofof_patient[i].id == patientID) {
            patientName = listofof_patient[i].name;
            break;
        }
    }

    do {
        cout << "\n\t\tWelcome " << patientName << " to Clinic System\n";
        cout << "\t\t**************\n";
        cout << "1. View All Doctors\n2. Search for Available Appointments\n3. Book Appointment\n";
        cout << "4. View My Appointments\n5. Cancel Appointment\n6. viewallappointments\n7. Logout\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == '1') {
            showAllDoctors();
        }
        else if (choice == '2') {
            userSearchEngine();
        }
        else if (choice == '3') {
            string docid, appid;
            int time, day, month, year;

            showAllDoctors();
            cout << "\nEnter Doctor ID: "; cin >> docid;
            validation(docid);
            cout << "Enter Appointment ID (Room Number): "; cin >> appid;
            validation(appid);
            getValidDate(day, month, year);
            time = getValidTime();

            bookappointment(patientName, patientID, docid, day, month, year, time, appid);
        }
        else if (choice == '4') {
            viewMyAppointments(patientID);
        }
        else if (choice == '5') {

            viewMyAppointments(patientID);

            cancelAppointment();
        }
        else if (choice == '6') {
            showAppointments();
        }
        else if (choice == '7') {
            logoutPatient();

        }
        else {
            cout << "[!] Invalid choice! Please enter a number from 1 to 7.\n";

            cin.ignore(1000, '\n');
        }

    } while (choice != '7');
}

void adminMenu() {
    char choice;
    do {
        cout << "\n\t\tWelcome Admin to Clinic System\n";
        cout << "\t\t************\n";
        cout << "Press\n";
        cout << "1. Add Doctor\n";
        cout << "2. Remove Doctor\n";
        cout << "3. View All Doctors\n";
        cout << "4. View All Appointments\n";
        cout << "5. Manage Doctor Fees\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == '1') {
            addDoctor();
        }
        else if (choice == '2') {
            removeDoctor();
        }
        else if (choice == '3') {
            showAllDoctors();
        }
        else if (choice == '4') {
            showAppointments();
        }
        else if (choice == '5') {
            adminFeeManager();
        }
        else if (choice == '6') {
            logoutAdmin();
        }
        else {

            cout << "[!] Invalid choice! Try again.\n";
        }
    } while (choice != '6');
}


// ======================================================
// الـ Main (بالصورة اللي انت طلبتها)
// ======================================================
int main() {
    initializeDoctors();
    initializePatients();
    initializeAppointments();
    initializeAdmins();
    char userType;

    do {
        cout << "\n\t\tWelcome to Clinic Management System\n";
        cout << "\t\t**************\n";
        cout << "Press\n";
        cout << "1. Patient\n";
        cout << "2. Admin\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> userType;

        if (userType == '1') {  // Patient
            char patientChoice;
            cout << "\n1. Login\n";
            cout << "2. Sign Up\n";
            cout << "Enter choice: ";
            cin >> patientChoice;

            if (patientChoice == '1') {
                string patientID = login_patient();
                if (patientID != "-1") {
                    patientMenu(patientID);
                }
            }
            else if (patientChoice == '2') {
                signUp_patient();
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        else if (userType == '2') {  // Admin
            string adminID = login_admin();
            if (adminID != "-1") {
                adminMenu();
            }
        }
        else if (userType == '3') {
            cout << "Thank you for using the Clinic Management System!\n";
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (userType != '3');

    return 0;
}