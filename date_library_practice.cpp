#pragma warning(disable: 4996) // عشان السي تايم من مكتبة سي لذا بيطلع وارننغ فعشان نشيله نحط ذا السطر

#include <iostream>
#include "clsDate.h"
#include <ctime>

using namespace std;


int main()
{
	clsDate Date1;
	Date1.Print();

	clsDate Date2 = clsDate("4/7/2002");
	Date2.Print();

	clsDate Date3 = clsDate(4,7,2002);
	Date3.Print();

	clsDate Date4 = clsDate(168, 2026);
	Date4.Print();

	Date4 = Date4.DateAddDays(1);
	Date4.Print();
	
	clsDate::CalculateMyAgeInDays(clsDate(4, 7, 2002));


}
