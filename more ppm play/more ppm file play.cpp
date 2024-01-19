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




void writeBlackAndWhiteBarImage(int width, int height)
{
	ofstream imageFile;
	string filename = std::to_string(width) + "x" +
		
					std::to_string(height) + "black-white-bar"+ ".ppm";
	
	imageFile.open(filename);

	imageFile << "P3" << endl; //"magic number" that specifies file format 
	//P1 is black and white (.pbm) -> portable bit map
	//P2 is gray scale (.pgm) -> portable graymap
	//P3 is 24 bit RGB ppm (portable pixel map)  

	imageFile << std::to_string(width) << " "; //"width" pixels wide
	imageFile << std::to_string(height) << endl;// "height" pixels high 

	imageFile << "255 " << endl; //255 specifies max value for color intensity

	//make black and white alternating ("Checkerboard")
	vector<string> black = { "0", "0", "0" }; //R, G, B
	vector<string> white = { "255", "255", "255" };

	int count = 0; 
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (count % 2 == 0) //make black 
			{
				imageFile << black.at(0) << " " << black.at(1) << " " << black.at(2) << endl;
			}

			else //make white
			{
				imageFile << white.at(0) << " " << white.at(1) << " " << white.at(2) << endl; 
			}
			count++; 
		}
	}


	imageFile.close(); 

}


void writeRandomColors(int width, int height)
{
	ofstream imageFile;
	string filename = std::to_string(width) + "x" +
					std::to_string(height) + "random" + ".ppm";

	imageFile.open(filename);

	imageFile << "P3" << endl; 
	imageFile << std::to_string(width) << " "; 
	imageFile << std::to_string(height) << endl; 
	imageFile << "255 " << endl; 

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			imageFile << rand() % 256 << " " << rand() % 256 << rand() % 256 << endl;
		}
	}
}

int main()
{
	srand(time(0)); 

	int width, height; 
	cout << "Enter image width and height (in pixels):" << endl; 
	cin >> width >> height; 
	cout << "Generating image with width x height = " << width << "x" << height << endl; 

	writeBlackAndWhiteBarImage(width, height); 
	writeRandomColors(width, height); 



	return 0; 
}