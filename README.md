# 📅 C++ Date & Period Utility Library

> ⚠️ **IMPORTANT:** This project is a **simple training project** developed purely for educational purposes while learning the C++ language and exploring Object-Oriented Programming (OOP) concepts. It aims to practice core logic building and understand how date manipulation works from scratch. 

---

## 📝 Project Description

This project is a lightweight C++ utility library featuring two main classes (`clsDate` and `clsPeriod`) designed from the ground up to handle date manipulation, validation, and time-period processing. Developed using Object-Oriented Programming (OOP) principles, it provides custom implementations for formatting dates, calculating leap years, determining date differences, and detecting overlapping time intervals without relying on heavy external third-party frameworks.

---

## ✨ Key Features

### 1️⃣ Date Management (`clsDate`)
* **Constructor Overloading:** Instantiate date objects using the current system time, a string format (e.g., `"4/7/2002"`), individual properties (`Day, Month, Year`), or by the specific day order in a given year.
* **Date Arithmetic:** Increase or decrease dates flexibly by days, weeks, months, years, decades, or centuries (e.g., `IncreaseDateByXDays`, `DecreaseDateByOneMonth`).
* **Calendar Generation:** Beautifully format and print a structured text-based calendar grid for any specific month or an entire year directly to the console.
* **Business & Vacation Tracking:** Determine weekends, business days, and calculate exact employee return dates based on vacation durations (`CalculateVacationDays`, `GetReturnDate`).
* **Comparisons & Time Differences:** Compare dates (Before, After, Equal) and calculate chronological differences down to days, hours, minutes, and seconds, including calculating precise ages in days.

### 2️⃣ Period Analysis (`clsPeriod`)
* **Overlap Detection:** Implements a robust boolean validation algorithm to check if two distinct time periods intersect or overlap with one another (`IsOverlapPeriods`).

---

## 📂 Project Structure

The codebase is organized into the following file structure:
* **`clsDate.h`**: The core header file containing the full logic for date calculations, string parsing, printing configurations, and structural validation.
* **`clsPeriod.h`**: The header file handling period bounds and logic checks for date range boundaries and overlaps.
* **`Main.cpp`**: The executable entry point containing the `main()` function used to run test cases, showcase library capabilities, and output results to the console.

---
