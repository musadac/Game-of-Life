//Libarary
#include <iostream>
#include <fstream>
#include <array>
#include <windows.h>
//End of Library
using namespace std;//for cout and cin

string name,save;//string defining
const int SizeX = 20;//constant int for Array Size
const int SizeY = 20;//constant int for Array Size
int  Iteration = 0, Values = 0,xa=0,ya=0;//variable defining and intializing
int grid[SizeX][SizeY];//2d array for grid
int copygrid[SizeX][SizeY];//2d array to copy grid
int LD[SizeX][SizeY];//2d array to save death and live 
void File_read(string name);//Function to read a file that user wants too.
void Display(const int SizeX, const int SizeY);//Function to display grid
void Intial(const int SizeX,const int SizeY);//Function to intialize all arrays 
void Copy(const int SizeX, const int SizeY);//Function to copy all arrays
void BCopy(const int SizeX, const int SizeY);//Function to copy secondary grid to main grid
void Live(int SizeX, int SizeY);//Function to check 
int main()//main body
{
	cout << "Enter a file name to give intial values." << endl;//user sees this 
	cin >> name;//user inputs goes here about the file name
	cout << "Enter a file name to save values in it." << endl;//user sees this 
	cin >> save;//user inputs goes here the output file name
	Intial(SizeX, SizeY);//all arrays are intaialized
    File_read(name);//This Function reads the file name and its content
	for (int i = 0; i < Iteration; i++)//for loop to run n  times (n=Iterations)
	{
	  Display( SizeX,  SizeY);//Displays the grid 
	  Copy(SizeX, SizeY);//copy the grid to a secondary grid
	  Live(SizeX, SizeY);//calculates the next step wheather the cell will be live or not
	  BCopy(SizeX, SizeY);//copy the secondary grid to grid 
	  Sleep(150);//sleeps the commands
	  system("cls");//clear out the last outputs
	}
}
void Display(const int SizeX, const int SizeY)//Function to Display output and write outputs in File
{
	fstream Ffile(save,ios::app);//file in which output is going to get changed
	for (int i = 0; i < SizeX; i++)//for loop to check and display '*'or" " depending upon the values of array
	{
		for (int j = 0; j < SizeY; j++)//for loop to check and display '*'or" " depending upon the values of array
		{
			if (grid[i][j] == 0)//if to check wheather grid contains 1 or not
			{
				cout << " "; Ffile << " ";//incase of not displays a space
			}
			else if (grid[i][j] == 1)//if to check wheather grid contains 1 or not
			{
				cout << "*"; Ffile << "*";//displays a * and writes it to the file
			}
		}
		cout << endl; Ffile << endl;//moves the pointer to next line in txt file
		
	}
	Ffile << endl; Ffile << endl;//moves the pointer to next line in txt file x 2
}
void Intial(const int SizeX , const int SizeY)//Function to intialize the values of array
{
	for (int i = 0; i < SizeX ; i++)//for loop to intialize arrays
	{
		for (int j = 0; j < SizeY ; j++)//for loop to intialize all the element of arrays
		{
			grid[i][j] = 0;//[i][j] element is zero of grid array
			copygrid[i][j] = 0;//[i][j] element is zero of copygrid array
		}
	}
}
void Copy(const int SizeX, const int SizeY)//Function that copy the value of grid to copygrid
{
	for (int i = 0; i < SizeX; i++)//for loop to copy
	{
		for (int j = 0; j < SizeX; j++)//for loop to copy all the elememts of grid
		{
			copygrid[i][j] = grid[i][j];//writes the value of grid to copygrid
		}
	}
}
void BCopy(const int SizeX, const int SizeY)//Function that copy the value of LD to grid
{
	for (int i = 0; i < SizeX; i++)//for loop to copy
	{
		for (int j = 0; j < SizeX; j++)//for loop to copy all the elememts of grid
		{
			
			grid[i][j] = LD[i][j];//writes the value of LD to grid
			
		}
	}
}
void File_read(string name)//Function that reads the file
{
	fstream File(name, ios::in);//variable that intialize the file and its function
    File >>Iteration ; File >> Values;//takes and intialize the values
	for (int  i = 0; i < Values; i++)//for loop to take all the values
	{
		File >> ya;//x coordinate from file
		File >> xa;//y coordinate from file
		grid[xa][ya] = 1;//sets the value of grid[x][y] to 1
	}
}
void Live(int SizeX,int SizeY)//function that calculates that wheather cell will be alive or dead at next step
{
	for (int i = 0; i < SizeX; i++)//for loop
	{
		for (int j = 0; j < SizeY ; j++)//for loop
		{
			int Life = 0;//variable life is defined
			//ifs to check the grid 4x4 neighbours of each cell and increase the life count by 1 
			//Calculation
			if (copygrid[i - 1][j - 1] == 1) Life += 1;
			if (copygrid[i - 1][j] == 1) Life += 1;
			if (copygrid[i - 1][j + 1] == 1) Life += 1;
			if (copygrid[i][j - 1] == 1) Life += 1;
			if (copygrid[i][j + 1] == 1) Life += 1;
			if (copygrid[i + 1][j - 1] == 1) Life += 1;
			if (copygrid[i + 1][j] == 1) Life += 1;
			if (copygrid[i + 1][j + 1] == 1) Life += 1;
			//Calculation
			if (copygrid[i][j] == 1 && Life < 2)//if to check if life is smaller than two so that it makes the cell dead by loneliness
			{
				LD[i][j] = 0;//LD[][]=0 so that it marks as dead
			}
			else if (copygrid[i][j] == 1 && Life > 3)//if to check if life is smaller than two so that it makes the cell dead by crowdness
			{
				LD[i][j] = 0;//LD[][]=0 so that it marks as dead
			}
			else if (copygrid[i][j] == 1 && (Life == 2 || Life == 3))//if to check if life is two or three cell remains live
			{
				LD[i][j] = 1;//LD[][]=1 so that it marks as alive
			}
			else if (copygrid[i][j] == 0 && Life == 3)//if to check if life is three cell dead will become alive
			{
				LD[i][j] = 1;//LD[][]=1 so that it marks as alive
			}
			Life = 0;//Life again is intialized to zero as calculatio needs to be done again
		} 

	}
}
