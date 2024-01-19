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



int main()
{


	ofstream image; 
	image.open("image.ppm");

	if (image.is_open())
	{
		image << "P3" << endl; //"magic number" that specifies file format 
								//P1 is black and white (.pbm) -> portable bit map
								//P2 is gray scale (.pgm) -> portable graymap
								//P3 is 24 bit RGB ppm (portable pixel map)  

		image << "255 255" << endl; //255 pixels wide, 255 pixels high 
		image << "255 " << endl; //255 specifies max value for color intensity

		//for (int i = 0; i < 1000; i++)
		//{
		for (int row = 0; row < 255; row++)
			//first row 
			for (int col = 0; col < 255; col++)
			{
				string currentRedValue = std::to_string(col); 
				string currentGreenValue = std::to_string(row); 
				string currentBlueValue = std::to_string((row + col) / 2);

				image << currentBlueValue << " "
					<< currentGreenValue << " "
					<< currentRedValue << "\n";
			}

		//}
 
	}
	image.close(); 

	cout << "done\n";
	return 0; 
}