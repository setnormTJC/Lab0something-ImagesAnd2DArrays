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
		image << "P3" << endl;
		image << "3 2" << endl;
		image << "255 " << endl;

		//for (int i = 0; i < 1000; i++)
		//{
			image << "255 255 0\n";
			image << "255 255 255\n";
			image << "0 0 0\n";
			image << "255 0 0" << endl;
			image << "0 255 0\n";
			image << "0 0 255\n";

		//}
 
	}
	image.close(); 

	cout << "done\n";
	return 0; 
}