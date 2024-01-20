#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>

//global using directives: 
using std::cout; 
using std::cin; 
using std::endl; 

using std::string;
using std::vector;

using std::ofstream;
using std::ifstream; 

using std::setw; 
using std::left; 

template<typename T> 
vector<T> convert2Dto1DArray(vector<vector<T>> matrix)
{
	vector<T> list; 

	for (auto& row : matrix)
	{
		for (auto& element : row)
		{
			list.push_back(element); 
		}
	}

	return list; 
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="fullArray"></param>
/// <returns></returns>
template<typename T>
vector<T> reduceArraySize_ByFactorOf9(vector<T> fullArray)
{
	int count = 0; 
	vector<T> reducedArray; 

	double sum = 0; 
	for (int i = 0; i < fullArray.size(); i++)
	{
		sum += fullArray[i]; 

		if (i % 9 == 0)
		{
			double average = sum / 9; 
			reducedArray.push_back(average); 

			sum = 0; //reset every 9 elements
		}
	}

	return reducedArray;
}

template<typename T> 
vector<vector<T>> convert1Dto2DArray(vector<T> list)
{
	vector<vector<T>> twoDequivalent; 

	//closest to square matrix
	int rowCountSub1 = floor(sqrt(list.size()));
	int count = 0; 
	for (int col = 0; col < rowCountSub1; col++)
	{
		vector<T> currentRow; 
		for (int row = 0; row < rowCountSub1; row++)
		{
			T currentElement = list.at(row + col); //will go out of bounds??
			currentRow.push_back(currentElement);
			count++; 
		}
		twoDequivalent.push_back(currentRow); 
	}

	if (count < list.size())
	{
		//add another, final row: 
		vector<T> finalRow; 
		for (int i = count; i < list.size(); i++)
		{
			finalRow.push_back(list.at(i)); 
		}
		twoDequivalent.push_back(finalRow); 
	}

	return twoDequivalent; 
}

template<typename T> 
void print2DArray(vector < vector<T>> matrix)
{
	for (auto& row : matrix)
	{
		for (auto& element : row)
		{
			cout << left << setw(6) << element;
		}
		cout << "\n";
	}
}

//void print3x3()

/// <summary>
/// <para>
/// takes INTEGER average of (row, col)'s 9 neigbors
/// (i - 1, j), (i + 1, j + 1), ... etc.
/// integer averaging used in anticipation of 0 - 255 RGB values for image compression
/// </para> 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="matrix"></param>
/// <returns>a matrix that occupies 9 x less space</returns>
template <typename T>
auto getReducedMatrix(vector<vector<T>> matrix)
{
	vector<vector<T>> reducedMatrix; 
	for (int row = 1; row < matrix.size(); row = row + 3)//Note the "irregular" start index and increment
	{
		vector<T> currentRow;
		for (int col = 1; col < matrix.at(row).size(); col = col + 3) //also note the increment 
		{
			//only access if not out of bounds
			if (col < matrix.at(row).size() - 1) //going to miss some pixels along the edge of the image with this
			{
				//NOTE the suggestive formatting here:
				int average = 
				(
					(matrix[row - 1][col - 1] + matrix[row - 1][col] + matrix[row - 1][col + 1]) +
					(matrix[row][col - 1]	  + matrix[row][col]	 + matrix[row][col + 1])	 +
					(matrix[row + 1][col - 1] + matrix[row + 1][col] + matrix[row + 1][col + 1])

				) / 9;

				currentRow.push_back(average); 
				//okay -> allow integer division for RGB 0 - 255 here 
				//cout << matrix.at(row).at(col) << " "; //for visualizing 
			}
		}
		reducedMatrix.push_back(currentRow);
	}

	return reducedMatrix; 

}
 
vector<vector<int>> generateSimpleTest2DArray()
{
	vector<vector<int>> twoDarray;

	for (int col = 1; col < 10; col++) //9 columns
	{
		vector<int> currentRow;
		for (int row = 10; row < 19; row++) //9 rows 
		{
			currentRow.push_back(col * row);
		}
		twoDarray.push_back(currentRow);
	}

	return twoDarray; 
}

vector<vector<int>> generateRandomTest2DArray(int rows, int cols)
{
	vector<vector<int>> random2Dmatrix; 
	for (int row = 0; row < rows; row++)
	{
		vector<int> currentRow; 
		for (int col = 0; col < cols; col++)
		{
			currentRow.push_back(rand() % 256); //0 - 255 (for RGB) 
		}
		random2Dmatrix.push_back(currentRow); 

	}

	return random2Dmatrix; 
}

int main()
{
	//auto twoDarray = generateSimpleTest2DArray();
	int rows = 60; 
	int cols = 20; 
	auto twoDarray = generateRandomTest2DArray(rows, cols);
	cout << "The full two d array: \n";
	print2DArray(twoDarray); 
	cout << "Dimensions are: " << twoDarray.size() << "x" << twoDarray.at(0).size() << endl; 
	//using 0th row (assuming no jagged matrices)
	cout << "\n\nReducing to average of 3 x 3 blocks (\"CHUNKS\"): " << endl; 
	auto reducedMatrix = getReducedMatrix(twoDarray); 

	//auto oneDequivalent = convert2Dto1DArray(twoDarray);


	//double sum = 0;
	//for (auto& element : oneDequivalent)
	//{ 
	//	sum += element; 
	//	//cout << element << " ";
	//}
	////cout << sum << endl; 
	////cout << "Average of full matrix: "  << sum/oneDequivalent.size() << endl; //~65
	//

	//auto reducedArray = reduceArraySize_ByFactorOf9(oneDequivalent); 

	////cout << "Reduced matrix: " << endl; 
	//double reducedSum = 0; 
	//for (auto& element : reducedArray)
	//{
	//	reducedSum += element; 
	//	//cout << element << " ";
	//}
	////cout << "reduced average: " << reducedSum / reducedArray.size() << endl; 
	//
	//cout << "\n\nThe REDUCED two d array: \n";
	//auto reduced2DArray = convert1Dto2DArray(reducedArray); 
	print2DArray(reducedMatrix);
	cout << "Dimensions are: " << reducedMatrix.size() << "x" << reducedMatrix.at(0).size() << endl; 

	return 0; 
}