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

struct Color
{
	float r, g, b; 

	Color()
		:r(0), g(0), b(0) {}

	Color(float r, float g, float b)
		:r(r), g(g), b(b)
	{
	}

	~Color()
	{

	}

};

class Image
{
public:
	Image(int width, int height)
		:m_width(width), m_height(height), m_colors(vector<Color>(width* height))
	{

	}

	~Image()
	{

	}


	Color getColor(int x, int y) const
	{
		return m_colors[y * m_width + x]; //figure it out, if you like
	}

	void setColor(const Color& color, int x, int y)
	{
		m_colors[y * m_width + x].r = color.r;
		m_colors[y * m_width + x].g = color.g;
		m_colors[y * m_width + x].b = color.b;
	}

	/// <summary>
	/// supply a filepath to write to
	/// </summary>
	void Export(const char* path) const
	{
		ofstream f;
		f.open(path, std::ios::out | std::ios::binary); //BINARY!

		if (!f.is_open())
		{
			cout << "file not opened!" << endl;

			return;
		}

		unsigned char bmpPad[3] = { 0, 0, 0 }; //padding 

		const int paddingAmount = ((4 - (m_width * 3) % 4) % 4); //don't worry about it


		const int fileHeaderSize = 14; //a BMP thing

		const int informationHeaderSize = 40;

		const int fileSize = fileHeaderSize + informationHeaderSize
			+ m_width * m_height * 3
			+ paddingAmount * m_height;


		unsigned char fileHeader[fileHeaderSize];
		//file type: 
		fileHeader[0] = 'B';
		fileHeader[1] = 'M'; //BitMap? (Not bowel movement)

		//file size: 
		fileHeader[2] = fileSize;
		fileHeader[3] = fileSize >> 8; //bitshift?
		fileHeader[4] = fileSize >> 16;
		fileHeader[5] = fileSize >> 24;

		//"Reserved 1" and 2 (not used)
		fileHeader[6] = 0;
		fileHeader[7] = 0;
		fileHeader[8] = 0;
		fileHeader[9] = 0;

		//pixel data offset: 
		fileHeader[10] = fileHeaderSize + informationHeaderSize;
		fileHeader[11] = 0;
		fileHeader[12] = 0;
		fileHeader[13] = 0;



		//"info header"
		unsigned char informationHeader[informationHeaderSize];

		//header size
		informationHeader[0] = informationHeaderSize;
		informationHeader[1] = 0;
		informationHeader[2] = 0;
		informationHeader[3] = 0;

		//img width: 
		informationHeader[4] = m_width;
		informationHeader[5] = m_width >> 8;
		informationHeader[6] = m_width >> 16;
		informationHeader[7] = m_width >> 24;

		//img HEIGHT: 
		informationHeader[8] = m_height;
		informationHeader[9] = m_height >> 8;
		informationHeader[10] = m_height >> 16;
		informationHeader[11] = m_height >> 24;

		//"planes"
		informationHeader[12] = 1;
		informationHeader[13] = 0;

		//bits per pixel 
		informationHeader[14] = 24; //8 bits for R, 8 for G, 8 for B
		informationHeader[15] = 0;

		//no compression and image size no compression, no etc:
		int stopPointForZeros = informationHeaderSize - 1; // 

		for (int i = 16; i < stopPointForZeros; i++)
		{
			informationHeader[i] = 0;
		}

		f.write(reinterpret_cast<char*> (fileHeader), fileHeaderSize);
		f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				unsigned char r = static_cast<unsigned char> (getColor(x, y).r * 255.0f);
				unsigned char g = static_cast<unsigned char> (getColor(x, y).g * 255.0f);
				unsigned char b = static_cast<unsigned char> (getColor(x, y).b * 255.0f);

				unsigned char color[] = { b, g, r }; //NOTE! b, g, r -> NOT rgb  (bmp idiosyncracy)
													//don't mistake BGR for "background"

				f.write(reinterpret_cast<char*>(color), 3); 
			}
		}

		//padding for every row
		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount); 


		f.close(); 

		cout << "BMP File written" << endl; 
	} //end of beastly Export function 
		//CAREFUL - naming this function lowercase "export" CONFLICTS with export keyword

	void print()
	{
		cout << "Red\tGreen\tBlue" << endl;
		for (auto& color : m_colors)
		{
			cout << color.r << "\t" << color.g << "\t" << color.b << endl;
		}
	}

private: 
	int m_width; 
	int m_height; 

	vector<Color> m_colors; 


};

int main()
{

	//const int width = 640; 
	//const int height = 480; //AKA: 480p (a 4:3 aspect ratio)
	//-> makes a ~1 MB filesize


	//const int width = 1920;
	//const int height = 1080; //AKA: 1080p (a 16:9 aspect ratio)
	// -> makes a 6 MB filesize (6-fold increase follows from 480p being ~ 1MB)


	//const int width = 3840;
	//const int height = 2160; //AKA: "4K" -> double 1080p
							//larger than my 1080p screen resolution 
							
							//this takes a second or two! (and is 24 MB filesize) 

	const int width = 680;
	const int height = 420; 



	//const int width = 4; 
	//const int height = 3; //"small" numbers - ease of analysis 
	//4 x 3 results in 90 Byte filesize
	//40 + 14 = 54 -> the header stuff in BMP file
	
	//90 - 54 = 36
	// 4 * 3 = 12
	// 12 * 3 = 36!!!

	//vector<vector<Color>> pixelColors; 
	//
	//for (int y = 0; y < height; y++)
	//{
	//	vector<Color> currentColumn;
	//	float value = y * 0.1; 
	//	Color c{ value, 1 - value, value };
	//	currentColumn.push_back(c);
	//}

	Image image(width, height);

	int counter = 0; 

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//random-ish color - play with later -> values all range between 0 and 1
			//Color c{
			//			(float)x / (float)width,
			//			1.0f - ((float)x / (float)width),
			//			(float)y / (float)height
			//};
			//This is quite pretty :)

			//silly playing 
			if (counter % 5 == 0)
			{
				Color c{
					1.0f, 0.5f, 0.7f
				};

				image.setColor(c, x, y);
			}

			else
			{
				Color c{
					0.0f, 1.0f, 0.0f
				};

				image.setColor(c, x, y);
			}

			counter++;

			//for examining RGB/BGR values 
			//image.print(); 
		}
	}

	image.Export("image.bmp"); 

	return 0; 
}