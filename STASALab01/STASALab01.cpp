
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>


const static int leftEl = -4;
const static int rightEl = 3;

// Optimal Passive Search
// Goldel Selection Search

//Function = (1-x)^2 + exp(x);

//Difference needed = 0.1

float MAIN_FUNCTION(const float& x)
{
	float value = pow(1 - x, 2) + exp(x);
	return value;
}

float getDifferenceBySubdivision(const int& N) // N - number of selections
{
	float division = static_cast<float>(N + 1);
	float dif = (rightEl - leftEl) / division;
	return dif;
}

std::vector<float> getFuncValues(const int& N) // dif - difference
{
	float dif = getDifferenceBySubdivision(N);
	float currentValue = leftEl + dif;
	std::vector<float> returningValues;
	for (int i = 0; i < N; i++)
	{
		returningValues.push_back(MAIN_FUNCTION(currentValue));
		currentValue += dif;
	}
	return returningValues;
}

float min(std::vector<float>& vector)
{
	float minEl = vector[0];
	for (int i = 1; i < vector.size(); i++)
	{
		if (vector[i] < minEl)
		{
			minEl = vector[i];
		}
	}
	return minEl;
}

int main()
{
	// PASSIVE SEARCH
	float currentDifference = (rightEl - leftEl) / 2;
	int numberOfSelections = 1;
	std::cout << "_________________________" << std::endl;
	std::cout << "|Number of | Value x in |" << std::endl;	
	std::cout << "| Dots (N) | minimum    |" << std::endl;
	std::cout << "-------------------------" << std::endl;
	while (currentDifference > 0.1)
	{
		std::vector<float> currentValues = getFuncValues(numberOfSelections);
		float minimalElement = min(currentValues);
		std::cout << "|    " << std::setprecision(2) << std::setfill(' ') << std::left << std::setw(6)
			<< numberOfSelections << "| " << std::setw (3) << minimalElement << " +- ";
		std::cout << std::setfill(' ') << std::setw(4) << currentDifference;
		std::cout << '|' << std::endl;
		numberOfSelections++;
		currentDifference = getDifferenceBySubdivision(numberOfSelections);
	}
	std::cout << "-------------------------" << std::endl << std::endl;
	// END PASSIVE SEARCH

	// GOLDEN RATIO
	std::cout << std::setprecision(4);
	double rightBorder = rightEl;
	double leftBorder = leftEl;
	const double GOLDEN_RATIO = (sqrt(5) - 1) / 2; // ~0.62
	double x1 = (1 - GOLDEN_RATIO) * (rightBorder - leftBorder) + leftBorder;
	double x2 = GOLDEN_RATIO * (rightBorder - leftBorder) + leftBorder;
	// x1 < x2
	std::cout << "__METHOD OF GOLDEN RATIO__" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "|   Start    |    End    |   Lenght  |         |        |" << std::endl;
	std::cout << "|  of int.   |  of int.  |   of int  |  f(ak)  |  f(bk) |" << std::endl;
	std::cout << "|    (ak)    |    (bk)   |    (l)    |         |        |" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	while ((rightBorder - leftBorder) / 2 > 0.1)
	{
		std::cout << "|   " << std::setfill(' ') << std::left << std::setw(9) 
			<< leftBorder;
		std::cout << "|   " << std::setfill(' ') << std::left << std::setw(8) 
			<< rightBorder;
		std::cout << "|   " << std::setfill(' ') << std::left << std::setw(8) 
			<< rightBorder - leftBorder;
		std::cout << "|   " << std::setfill(' ') << std::left << std::setw(6) 
			<< MAIN_FUNCTION(x1);
		std::cout << "|  " << std::setfill(' ') << std::left << std::setw(6) 
			<< MAIN_FUNCTION(x2) << '|' << std::endl;
 		if (MAIN_FUNCTION(x1) > MAIN_FUNCTION(x2))
		{
			leftBorder = x1;
			x1 = x2;
			x2 = GOLDEN_RATIO * (rightBorder - leftBorder) + leftBorder;
		}
		else
		{
			rightBorder = x2;
			x2 = x1;
			x1 = (1 - GOLDEN_RATIO) * (rightBorder - leftBorder) + leftBorder;
		}
	}
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "Minimum of function at " << (leftBorder + rightBorder) / 2 << " +- "
		<< (rightBorder - leftBorder) / 2 << std::endl;
	// END GOLDEN RATIO

	return 0;
}

