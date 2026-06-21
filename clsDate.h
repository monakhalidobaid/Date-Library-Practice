#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class clsDate
{
	short Year;
	short Month;
	short Day;


protected:

	enum enDateCompare { Before = -1, Equal = 0, After = -1 };

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate.Year = Date1.Year;
		TempDate.Month = Date1.Month;
		TempDate.Day = Date1.Day;
		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;
		Date2.Year = TempDate.Year;
		Date2.Month = TempDate.Month;
		Date2.Day = TempDate.Day;
	}


	// دالة ترجع الاسم المختصر للشهر بناءً على رقمه
	static string MonthShortName(short MonthNumber)
	{
		// مصفوفة تحتوي على أسماء الشهور الـ 12 مرتبة من يناير إلى ديسمبر
		string Months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return (Months[MonthNumber - 1]); // نطرح 1 لأن الفهرسة (Index) في المصفوفات تبدأ من 0
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = {
		"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}

	static vector<string> SplitString(string S1, string Delim)
	{
		vector<string> vString;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + Delim.length()); /* erase() until
			positon and move to next word. */
		}
		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}
		return vString;
	}

	static string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}

	string FormateDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));

		FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));

		FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
	}

	void GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		
	}

public:
	clsDate() {
		GetSystemDate();
	}

	clsDate(string sDate) {
		 *this = StringToDate(sDate);
	}

	clsDate(short Day,short Month, short Year) {
		this->Day = Day;
		this->Month = Month;
		this->Year = Year;
	}

	clsDate(short DateOrderInYear, short Year) {

		*this = GetDateFromDayOrderInYear(DateOrderInYear, Year);

	}

	
	void Print() {
		cout << FormateDate(*this) << endl;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) +
			"/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	clsDate StringToDate(string DateString)
	{
		clsDate Date;
		vector <string> vDate;
		vDate = SplitString(DateString, "/");
		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);
		return Date;
	}

	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return 0;
		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) :
			days[Month - 1];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(Month, Year);
	}


	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month,
		short Year)
	{
		short TotalDays = 0;
		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}

	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(Day, Month, Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;
		Date.Year = Year;
		Date.Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}


	clsDate GetDateFromDayOrderInYear(short DateOrderInYear)
	{
		return GetDateFromDayOrderInYear(DateOrderInYear,Year);
	}


	static short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		short a, y, m;
		a = (14 - Date.Month) / 12;
		y = Date.Year - a;
		m = Date.Month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)
			/ 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}

	// الدالة الرئيسية المسؤولة عن طباعة شكل تقويم الشهر وتنسيقه
	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays; // متغير لتخزين إجمالي عدد أيام هذا الشهر (مثلاً 30 أو 31)

		// حساب ترتيب اليوم الأول في الشهر لمعرفة من أي يوم أسبوعي نبدأ الطباعة (من 0 إلى 6)
		int current = DayOfWeekOrder(1, Month, Year);

		// جلب عدد الأيام الإجمالي للشهر المحدد في تلك السنة
		NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		// طباعة الخط العلوي واسم الشهر بالمنتصف (.c_str() تستخدم لتحويل string إلى مصفوفة char لتتوافق مع printf)
		printf("\n _______________%s_______________\n\n", MonthShortName(Month).c_str());

		// طباعة أسماء أيام الأسبوع كأعمدة ثابتة العرض
		printf(" Sun Mon Tue Wed Thu Fri Sat\n");

		// طباعة الفراغات البادئة قبل اليوم الأول في الشهر
		int i; // تعريف العداد i خارج الحلقات لأننا سنحتاجه في حلقة طباعة الأيام بالأسفل
		for (i = 0; i < current; i++)
		{
			printf("     "); // طباعة 5 مسافات فارغة لكل عمود يسبق بداية اليوم الأول للشهر
		}

		// حلقة تكرارية لطباعة أيام الشهر من يوم 1 إلى اليوم الأخير (NumberOfDays)
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j); // طباعة رقم اليوم محجوزاً في مساحة 5 خانات (%5d) لضمان المحاذاة التامة أسفل اليوم الخاص به

			// زيادة العداد i بمقدار 1 والتحقق فوراً: هل وصلنا إلى نهاية الأسبوع (7 أيام)؟
			if (++i == 7)
			{
				i = 0;         // تصفير العداد للبدء بحساب أسبوع جديد
				printf("\n");  // الانتقال إلى سطر جديد في الطباعة
			}
		}

		// طباعة الخط السفلي لإغلاق شكل التقويم
		printf("\n _________________________________\n");
	}


	// الدالة الرئيسية المسؤولة عن طباعة شكل تقويم الشهر وتنسيقه
	void PrintMonthCalendar()
	{
		return PrintMonthCalendar(Month, Year);
	}

	static void PrintYearCalendar(int Year)
	{
		printf("\n _________________________________\n\n");
		printf(" Calendar - %d\n", Year);
		printf(" _________________________________\n");
		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
		
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(Year);
	}


	static clsDate DateAddDays(short Days, clsDate Date)
	{
		short RemainingDays = Days +
			NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month,Date.Year);
		short MonthDays = 0;
		Date.Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}


	clsDate DateAddDays(short Days)
	{
		return DateAddDays(Days,*this);
	}


	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
		return (Date1.Year < Date2.Year) ||
			(Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
			(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
	}

	bool IsDateLessThan(clsDate Date2) {
		return IsDate1BeforeDate2(*this,Date2);
	}


	static bool IsDateEquals(clsDate Date1, clsDate Date2) {
		return Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day;
	}

	bool IsDateEquals( clsDate Date2) {
		return IsDateEquals(*this,Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInAMonth(Date.Month,
			Date.Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}


	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date.Month)) {
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}
			else {
				Date.Month++;
				Date.Day = 1;
			}
		}
		else {
			Date.Day++;
		}
		return Date;
	}

	clsDate IncreaseDateByOneDay() {
		return IncreaseDateByOneDay(*this);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SawpFlagValue : Days *
			SawpFlagValue;
	}

	int GetDiffrenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	
	}

	static int CalculateMyAgeInDays(clsDate Date) {
		return GetDifferenceInDays(Date, clsDate(), true);
	}

	int CalculateMyAgeInDays() {
			return CalculateMyAgeInDays(*this);
	}


	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}
		//last check day in date should not exceed max days in the current month
			// example if date is 31/1/2022 increasing one month should not be 31 / 2 / 2022, it should
			// be 28/2/2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}


	static clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;

		// تحقق من أن يوم 29 فبراير لا يتحول إلى 29 في سنة غير كبيسة
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth; // سيتحول إلى 28/2
		}

		return Date;
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate Date)
	{
		Date.Year += Years;
		return Date;
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		//Period of 10 years
		Date.Year += 10;
		return Date;
	}



	static clsDate IncreaseDateByXDecades(short Decade, clsDate Date)
	{
		Date.Year += Decade * 10;
		return Date;
	}


	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		//Period of 100 years
		Date.Year += 100;
		return Date;
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		//Period of 1000 years
		Date.Year += 1000;
		return Date;
	}



	clsDate IncreaseDateByOneWeek()
	{
		return IncreaseDateByOneWeek(*this);
	}

	clsDate IncreaseDateByXWeeks(short Weeks)
	{
		return IncreaseDateByXWeeks(Weeks,*this);
	}

	clsDate IncreaseDateByOneMonth()
	{
		return IncreaseDateByOneMonth(*this);
	}


	clsDate IncreaseDateByXDays(short Days)
	{
		return IncreaseDateByXDays(Days,*this);
	}

	clsDate IncreaseDateByXMonths(short Months)
	{
		return IncreaseDateByXMonths(Months,*this);
	}

	clsDate IncreaseDateByOneYear()
	{
		return IncreaseDateByOneYear(*this);
	}

	clsDate IncreaseDateByXYears(short Years)
	{
		return IncreaseDateByXYears(Years,*this);
	}


	clsDate IncreaseDateByOneDecade()
	{
		return IncreaseDateByOneDecade(*this);
	}

	clsDate IncreaseDateByXDecades(short Decade)
	{
		return IncreaseDateByXDecades(Decade ,*this);
	}

	clsDate IncreaseDateByOneCentury()
	{
		return IncreaseDateByOneCentury(*this);
	}

	clsDate IncreaseDateByOneMillennium()
	{
		return IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Month,
					Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}
		return Date;
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;
		//last check day in date should not exceed max days in the current month
			// example if date is 31/3/2022 decreasing one month should not be 31 / 2 / 2022, it should
			// be 28/2/2022

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;

	}


	static clsDate DecreaseDateByXYears(short Years, clsDate Date)
	{
		Date.Year -= Years;
		return Date;
	}


	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		//Period of 10 years
		Date.Year -= 10;
		return Date;
	}

	static clsDate DecreaseDateByXDecades(short Decade, clsDate Date)
	{
		Date.Year -= Decade * 10;
		return Date;
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		//Period of 100 years
		Date.Year -= 100;
		return Date;
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		//Period of 1000 years
		Date.Year -= 1000;
		return Date;
	}

	clsDate DecreaseDateByOneDay()
	{
		return DecreaseDateByOneDay(*this);
	}

	clsDate DecreaseDateByOneWeek()
	{
		return DecreaseDateByOneWeek(*this);
	}

	clsDate DecreaseDateByXWeeks(short Weeks)
	{
		return DecreaseDateByXWeeks(Weeks,*this);
	}

	clsDate DecreaseDateByOneMonth()
	{
		return DecreaseDateByOneMonth(*this);
	}

	clsDate DecreaseDateByXDays(short Days)
	{
		return DecreaseDateByXDays(Days,*this);
	}

	clsDate DecreaseDateByXMonths(short Months)
	{
		return DecreaseDateByXMonths(Months,*this);
	}

	clsDate DecreaseDateByOneYear()
	{
		return DecreaseDateByOneYear(*this);
	}


	clsDate DecreaseDateByXYears(short Years)
	{
		return DecreaseDateByXYears(Years, *this);
	}

	clsDate DecreaseDateByOneDecade()
	{
		return DecreaseDateByOneDecade(*this);
	}

	clsDate DecreaseDateByXDecades(short Decade)
	{
		return DecreaseDateByXDecades(Decade, *this);
	}

	clsDate DecreaseDateByOneCentury()
	{
		return DecreaseDateByOneCentury(*this);
	}

	clsDate DecreaseDateByOneMillennium()
	{
		return DecreaseDateByOneMillennium(*this);
	}


	static bool IsEndOfWeek(clsDate Date) {
		cout << "\nIs it End of Week?";
		return DayOfWeekOrder(Date) == 6;
	}

	static bool IsWeekEnd(clsDate Date) {
		cout << "\nIs it Weekend?";
		return DayOfWeekOrder(Date) > 4;
	}

	static bool IsBusinessDay(clsDate Date) {
		cout << "\nIs it Business Day?";
		return !IsWeekEnd(Date);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {
		return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day;
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {
		return NumberOfDaysInAYear(Date.Year) - NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
	}


	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}


	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DaysCount;
	}

	short CalculateVacationDays(clsDate DateTo)
	{
		return CalculateVacationDays(*this,DateTo);
	}


	static clsDate GetReturnDate(clsDate Date, short VacationDays) {

		// طالما أن أيام الإجازة المطلوبة لم تنتهِ بعد
		while (VacationDays > 0) {

			if (IsBusinessDay(Date)) {
				VacationDays--; // نخصم يوم من الإجازة فقط إذا كان يوم عمل
			}

			// ننتقل لليوم التالي في كل الأحوال (سواء كان عمل أو ويكيند)
			Date = IncreaseDateByOneDay(Date);
		}

		// ملاحظة: بعد انتهاء الـ while، قد يكون تاريخ العودة يصادف ويكيند.
		// إذا كنت تريد أن يرجع الموظف في أول يوم عمل بعد الويكيند، نستخدم هذا الشرط:
		while (IsWeekEnd(Date)) {
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) &&
			!IsDateEquals(Date1, Date2));
	}

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		if (IsDateEquals(Date1, Date2))
			return enDateCompare::Equal;
		/* if (IsDate1AfterDate2(Date1,Date2))
		return enDateCompare::After;*/
		//this is faster
		return enDateCompare::After;
	}


	clsDate GetReturnDate(short VacationDays) {
		return GetReturnDate(*this, VacationDays);
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsValidDate(clsDate Date) {
		return (Date.Month <= 12 && Date.Month > 0 && Date.Day <= NumberOfDaysInAMonth(Date.Month, Date.Year) && Date.Day > 0);
	}

	bool IsValidDate() {
		return IsValidDate(*this);
	}
};

