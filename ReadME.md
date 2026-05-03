# 🏥 Clinic Management System

A complete **C++ console-based** application for managing clinic operations including doctors, patients, appointments, and billing.

## 📋 Features

### 👨‍⚕️ Admin Features
- Add / Remove doctors
- View all doctors
- View all appointments
- Manage consultation fees & discounts

### 🧑‍🤝‍🧑 Patient Features
- Sign up / Login
- View all doctors
- Search for available appointments by doctor
- Book appointments (with time & date validation)
- View personal appointment history with bill
- Cancel appointments

### 🔧 Technical Highlights
- Input validation (text, numbers, dates, time)
- 24-hour time format with AM/PM display
- Date validation (clinic opening: 1/1/2026)
- Dynamic discount & fee management
- Structured data using C++ `struct`
- Static array-based storage (max: 20 doctors, 50 patients, 100 appointments)

## 🚀 How to Run

### Prerequisites
- C++ compiler (g++, MinGW, or Visual Studio)

### Compilation & Execution

```bash
# Compile
g++ clinic.cpp -o clinic

# Run
./clinic
