/*main.cpp*/

//
// Chicago Crime Analysis program in modern C++.
//
// <<Mudit Kumar>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "classes.h"

using namespace std;


int main()
{
	string  crimeCodesFilename, crimesFilename;

	cin >> crimeCodesFilename;
	cout << crimeCodesFilename << endl;

	cin >> crimesFilename;
	cout << crimesFilename << endl;
	cout << "** Crime Analysis **" << endl;

	ifstream  codesFile(crimeCodesFilename);
	ifstream  crimesFile(crimesFilename);

	cout << std::fixed;
	cout << std::setprecision(2);

	if (!codesFile.good())
	{
		cout << "**ERROR: cannot open crime codes file: '" << crimeCodesFilename << "'" << endl;
		return -1;
	}
	if (!crimesFile.good())
	{
		cout << "**ERROR: cannot open crimes file: '" << crimesFilename << "'" << endl;
		return -1;
	}

	//data members for parsing
	string IUCR, primeDescription, secondDescription, line, date, arrest,
		domestic, beat, district, ward, community, year;

	bool a, b;  //boolean variables for arrest and domestic

	//create vector of crime codes
	std::vector<CrimeCode> codes;

	//create vector of crimesFile
	std::vector<CrimeReport> reports;

	//skip header line
	getline(codesFile, line);

	//read in input for crime-codes.csv
	//------------------------------------------------------------
	while (getline(codesFile, line))
	{
		stringstream ss(line);
		//parse lines
		getline(ss, IUCR, ',');
		getline(ss, primeDescription, ',');
		getline(ss, secondDescription);

		//cout << IUCR << "," << primeDescription << "," << secondDescription << endl;
		CrimeCode C(IUCR, primeDescription, secondDescription);
		//insert elements in vector
		codes.push_back(C);
	}
	//-------------------------------------------------------------

	//skip header line
	getline(crimesFile, line);
	//read in input for crimes.csv
	while (getline(crimesFile, line))
	{
		stringstream ss(line);
		//parse line
		getline(ss, date, ',');
		getline(ss, IUCR, ',');
		getline(ss, arrest, ',');
		getline(ss, domestic, ',');
		getline(ss, beat, ',');
		getline(ss, district, ',');
		getline(ss, ward, ',');
		getline(ss, community, ',');
		getline(ss, year);

		if (arrest == "TRUE" || arrest == "true") {
			a = true;
		}
		else
		{
			a = false;
		}

		if (domestic == "TRUE" || domestic == "true")
		{
			b = true;
		}
		else
		{
			b = false;
		}

		// cout << date << "," << IUCR << "," << arrest << "," << domestic << "," << beat << "," << district << "," << ward << "," << community << "," << year << endl;

		CrimeReport R(date, IUCR, a, b, stoi(beat),
			stoi(district), stoi(ward), stoi(community), stoi(year));

		//insert elements into vector
		reports.push_back(R);

	} //done with input file: crimes.csv
	cout << endl;
	int count = 0;
	//output date range
	for (CrimeReport &r : reports)
	{
		count++;
		if (count == 1)  //print first date when there is only one crime report
		{
			cout << "Date range: " << r.getDate() << " - ";
			break;
		}

	}
	//get last date
	for (int i = reports.size() - 1; i < reports.size(); i++)
	{
		cout << reports[i].getDate() << endl;
	}
	cout << endl;

	//output total # of crime codes
	int numCodes = codes.size();
	cout << "# of crime codes: " << numCodes << endl;

	//sort the crime codes
	std::sort(codes.begin(),
		codes.end(),
		[](CrimeCode c1, CrimeCode c2)
	{
		if (c1.getCode() < c2.getCode())
		{
			return true;
		}
		else
		{
			return false;
		}
	});
	//output first three crime codes
	count = 0;
	for (CrimeCode &c : codes)
	{
		count++;
		if (count <= 3)
		{
			cout << c.getCode() << ":  " << c.getPrimeInfo() << ":" << c.getSecondaryInfo() << endl;
		}
	}
	cout << "..." << endl;
	//output last three crime codes
	for (int i = codes.size() - 3; i < codes.size(); i++)
	{
		cout << codes[i].getCode() << ":  " << codes[i].getPrimeInfo()
			<< ": " << codes[i].getSecondaryInfo() << endl;
	}
	cout << endl;

	//output total number of crimes
	int numCrimes = reports.size();
	cout << "# of crimes: " << numCrimes << endl;

	//output first 3 crimes
	count = 0;
	for (CrimeReport &r : reports)
	{
		count++;
		if (count <= 3)
		{
			cout << r.getIUCR() << ":  " << r.getDate() << ", " << r.getBeat()
				<< ", " << r.getDistrict() << ", " << r.getWard() << ", " <<
				r.getCommunity();

			if (r.getArrest() == true)
			{
				cout << ", arrested";
			}
			if (r.getDomestic() == true)
			{
				cout << ", domestic violence";
			}
			cout << endl;
		}
	}
	cout << "..." << endl;

	//output the last 3 crimes
	for (int i = reports.size() - 3; i < reports.size(); i++)
	{
		cout << reports[i].getIUCR() << ":  " << reports[i].getDate() << ", " << reports[i].getBeat()
			<< ", " << reports[i].getDistrict() << ", " << reports[i].getWard() << ", " <<
			reports[i].getCommunity();

		if (reports[i].getArrest() == true)
		{
			cout << ", arrested";
		}
		if (reports[i].getDomestic() == true)
		{
			cout << ", domestic violence";
		}
		cout << endl;

	}
	cout << endl;
	cout << "** Top-5 Crimes **" << endl;
	//check each IUCR that appears in the crimes file
	for (CrimeReport &r : reports)
	{
		string code_IUCR = r.getIUCR();
		auto iter = std::find_if(
			codes.begin(), codes.end(),
			[&](CrimeCode& cc)
		{
			if (cc.getCode() == code_IUCR)
			{
				return true;
			}
			else
			{
				return false;
			}
		});
		iter->incrementTotal();
	}
	//sort the total number of occurences
	std::sort(codes.begin(),
		codes.end(),
		[](CrimeCode c1, CrimeCode c2)
	{
		if (c1.getTotal() > c2.getTotal())
		{
			return true;
		}
		else
		{
			return false;
		}
	});
	//output top 5 crimes
	cout << "Code:  " << " Total, " << "Description" << endl;
	int counter = 0;
	for (CrimeCode &c : codes)
	{
		counter++;
		if (counter <= 5)
		{
			cout << c.getCode() << ":   " << c.getTotal() << ", " << c.getPrimeInfo() << ": " << c.getSecondaryInfo()
				<< endl;
		}
	}
	cout << endl;
	cout << "** Done **" << endl;




	return 0;
}
