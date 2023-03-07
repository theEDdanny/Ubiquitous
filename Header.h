#pragma once

class Configuration {
public:

	char* usr_defined_chars;
	int usr_input_pre_length = 0;
	int total_number_place_values = 0;
	int num_of_dynamic_chars = 0;

	bool hashed_;
	bool repeat_;
	int num_allowed_to_repeat;
	int output_type;
	char* comparison;
	int comparicon_size = 0;

	int static_char_check;
	char place_value_temp[94];
	char* place_value_options;
	int* place_value_options_int;
	int place_value_size = 0;
	long long work_load_length;

	char* SetCharacters(); 
	int Hashed();
	int Repeat();
	int OutputType();
	int SetNumberOfPlaceValues(char* usr_def_chars, int usr_def_chars_length);
	char* BuildPlaceValue();
	long long SetWorkLoadLength();
};

class Processing {
public:

	int* pre_place_value;
	int* place_value_array;
	char* assignment_array;
	char* final_char_array;

	int SolvingAlgorithm(int num_of_dynamic_chars, int place_value_size, int objective);
	char* StaticCharacters(char* usr_defined_chars, int usr_input_pre_length);
	bool checkLuhn(const std::string& cardNo);
	int CheckDigit(char* number, int length);
	bool Repeating(char* final_char_array, int total_number_place_values, int num_allowed_to_repeat);
	bool Compair(char* comparison, char* being_compaired, int length);
	std::string convertToString(char* a, int size);
	std::string md5(std::string input_string);

	int CompairOne(Configuration config);
	int CompairTwo(Configuration config);
	int CompairThree(Configuration config);
	int CompairFour(Configuration config);
	int FileOne(Configuration config);
	int FileTwo(Configuration config);
	int FileThree(Configuration config);
	int FileFour(Configuration config);
	int IntOne(Configuration config);

};

