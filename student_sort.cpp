#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#define SIZE 10

// Student struct
typedef struct student {
	unsigned int id;
	std::string  f_name;
	std::string	 l_name;
	double 		 gpa;
	std::string  major;
} Student;

// overload << for Student data output
std::ostream& operator << (std::ostream &output, const Student student)
{
	output << student.id << " " << student.f_name << " " << student.l_name << " "
		   << student.gpa << " " << student.major << std::endl;
	return output;
}

// overload >> for Student data input
std::istream& operator >> (std::istream &input, Student &student)
{
	input >> student.id >> student.f_name >> student.l_name >>
			 student.gpa >> student.major;
	return input;
}

// reads data from external file
bool read_data(Student array[], const int size, const char* filename)
{
	std::ifstream file;
	file.open(filename);

	if (file) {
		for (unsigned int i = 0; i < size; i++) {
			file >> array[i];
		}
		return true;
	} else {
		return false;
	}
}
	
// outputs data to external file
void output_data(Student arr1[], Student arr2[], Student mergarr[], const int size) 
{
	std::ofstream outfile;
	outfile.open("output.txt");

	if (outfile) {
		outfile << "Array 1 (unsorted)" << std::endl;
		outfile << "------------------" << std::endl;
		for (unsigned int i = 0; i < size; i++) {
			outfile << arr1[i];
		}

		outfile << std::endl;
		outfile << "Array 2 (unsorted)" << std::endl;
		outfile << "------------------" << std::endl;
		for (unsigned int i = 0; i < size; i++) {
			outfile << arr2[i];
		}

		outfile << std::endl;
		outfile << "Array 3 (sorted)" << std::endl;
		outfile << "------------------" << std::endl;
		for (unsigned int i = 0; i < size * 2; i++) {
			outfile << mergarr[i];
		}

		outfile.close();
	}
}

// prints contents of Student array to screen
void print_array(Student arr[], const int size)
{
	for (unsigned int i = 0; i < size; i++) {
		std::cout << arr[i];
	}
}

// combines both Student arrays into an array
void combine_arrays(Student arr1[], Student arr2[], Student mergarr[], const int size) 
{
	unsigned int j = 0;

	for (unsigned int i = 0; i < size; i++) {
		mergarr[i] = arr1[i];
	}
	for (unsigned int i = size; i < size * 2; i++) {
		mergarr[i] = arr2[j++];
	}
}

// copies contents of array to another (for mergesort)
void copy_array(Student arr[], Student copyarr[], const int size)
{
	for (unsigned int i = 0; i < size; i++) {
		copyarr[i] = arr[i];
	}
}

/* --------------     MERGE SORT FUNCTIONS     ---------------*/

void merge(Student arr[], int begin, int middle, int end, Student temp[])
{
	unsigned int i = begin;
	unsigned int j = middle;

	for (unsigned int k = begin; k < end; k++) {
		if (i < middle && (j >= end || arr[i].id <= arr[j].id)) {
			temp[k] = arr[i];
			i++;
		} else {
			temp[k] = arr[j];
			j++;
		}
	}
}

void mergesplit(Student temp[], int begin, int end, Student arr[])
{
	if (end - begin < 2) {
		return;
	}

	int middle = (begin + end) / 2;
	mergesplit(arr, begin, middle, temp);
	mergesplit(arr, middle, end, temp);
	merge(temp, begin, middle, end, arr);
}

void mergesort(Student arr[], Student temp[], const int size)
{
	copy_array(arr, temp, size);
	mergesplit(temp, 0, size, arr);
}

/*--------------------------------------------------------------*/


int main(int argc, char **argv)
{
	// Student arrays
	Student arr1[SIZE];
	Student arr2[SIZE];
	Student merged_arr[SIZE * 2];
	Student temp[SIZE * 2];

	// for security
	bool tryarr1, tryarr2;

	// extract data from external files into arrays
	tryarr1 = read_data(arr1, SIZE, "stddata1.txt");
	tryarr2 = read_data(arr2, SIZE, "stddata2.txt");

	if (tryarr1 && tryarr2) {
		combine_arrays(arr1, arr2, merged_arr, SIZE);

		// sort the data by id number
		mergesort(merged_arr, temp, SIZE * 2);

		// print to screen
		std::cout << "Array 1 (unsorted)" << std::endl;
		std::cout << "------------------" << std::endl;
		print_array(arr1, SIZE);
		std::cout << std::endl;
		std::cout << "Array 2 (unsorted)" << std::endl;
		std::cout << "------------------" << std::endl;
		print_array(arr2, SIZE);
		std::cout << std::endl;
		std::cout << "Array 3 (sorted)" << std::endl;
		std::cout << "------------------" << std::endl;
		print_array(merged_arr, SIZE * 2);

		// print to external file
		output_data(arr1, arr2, merged_arr, SIZE);
	}

	return 0;
}


