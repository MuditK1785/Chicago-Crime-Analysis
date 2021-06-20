/*classes.h*/

//
// Classes for use with Chicago Crime Analysis program, e.g. "CrimeReport" 
// and "CrimeCode".
//
// << Mudit Kumar >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#include <iostream>
#include <string>

using namespace std;


class CrimeCode
{
private:
	string IUCR, Primary, Secondary;
	int Total = 0;	//to keep track of total codes that appear in crimes file

public:
	CrimeCode(string code, string prime, string second)
		: IUCR(code), Primary(prime), Secondary(second)
	{ }

	//Getter Functions
	string getCode() 
	{
		return IUCR;
	}

	string getPrimeInfo()
	{
		return Primary;
	}

	string getSecondaryInfo()
	{
		return Secondary;
	}

	int incrementTotal()
	{
		return Total++;
	}
	int getTotal()
	{
		return Total;
	}

};

class CrimeReport
{
private:
	string Date, Code, Arrested, DomesticViolence;
	bool Arrest, Domestic;
	int Beat, District, Ward, Community, Year;

public:
	CrimeReport(string date, string code, bool arrest, bool domestic, int beat, int district, int ward, int community, int year)
		: Date(date), Code(code), Arrest(arrest), Domestic(domestic), Beat(beat),
		District(district), Ward(ward), Community(community), Year(year)
	{ }

	//Getter Functions 
	bool getArrest()
	{
		return Arrest;
	}
	bool getDomestic()
	{
		return Domestic;
	}
	string getDate()
	{
		return Date;
	}

	string getIUCR()
	{
		return Code;
	}
	
	int getDistrict()
	{
		return District;
	}

	int getBeat()
	{
		return Beat;
	}

	int getWard()
	{
		return Ward;
	}

	int getCommunity()
	{
		return Community;
	}

	int getYear()
	{
		return Year;
	}


};

