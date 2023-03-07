#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <openssl/md5.h>
#include "Header.h"


int Intro() {

	std::cout << '\n';
	std::cout << "    In general, Ubiquitous is program used to generate data for situations where all possible combinations are required. This   "; std::cout << '\n';
	std::cout << "functionality makes Ubiquitous incredable at performing tasks like generating rainbow tables, and detecting hash collisions.    " << std::endl;
	std::cout << "The magic behind this functionality lies in the solving algorithm. First the total number of possibilities is caculated         " << std::endl;
	std::cout << "based on the size of user input; this number is refferd to as \"work_load\" withen the program. After \"work_load\" is          " << std::endl;
	std::cout << "caculated a loop with the duration of 1 - \"work_load\" is run. Over every itteration, the \"SolvingAlgorithm()\" uses the int  " << std::endl;
	std::cout << "\"i\" into a sequence of numbers that can be directally translated into one posiblaity withen the set." << std::endl;
	std::cout << '\n';
	std::cout << "    After this algorithem, Ubiquitous provides functionalidy to reduce the number of outliers, thus decreasing the size of      " << std::endl;
	std::cout << "\"work_load\". These functionalitys include the ability to seperate static characters and dynamic characters, create custome    " << std::endl;
	std::cout << "character sets, and in some cases removing data where multiple place values repeat." << std::endl;
	std::cout << '\n';

	return 1;
}

char* Configuration::SetCharacters() {

	char* usr_defined_chars_temp = new char[256];

	std::cout << '\n';
	std::cout << "Enter the full string. Indicate dynamic place values with []. Limit: 256 unknown chars" << std::endl; std::cout << '\n';
	std::cin >> usr_defined_chars_temp;
	std::cout << '\n';

	for (int i = 0; i < 256; i++) {

		if (usr_defined_chars_temp[i] != NULL) {

			usr_input_pre_length += 1;
		}
		else {

			break;
		}
	}

	usr_defined_chars = new char[usr_input_pre_length + 1];
	usr_defined_chars[usr_input_pre_length] = '\0';

	for (int i = 0; i < usr_input_pre_length; i++) {

		usr_defined_chars[i] = usr_defined_chars_temp[i];
	}

	delete[] usr_defined_chars_temp;

	bool pass_ = false;
	int static_char = 0;

	for (int a = 0; a < usr_input_pre_length; a++) {

		if (pass_ == false) {

			if (usr_defined_chars[a] == '[' && usr_defined_chars[a + 1] == ']') { // this line needs to be tested with the [ char and the ] char as inputs not indicating a brute force character

				total_number_place_values += 1;
				pass_ = !pass_;
			}
			else {

				total_number_place_values += 1;
			}
		}
		else {

			pass_ = !pass_;
		}
	}

	return usr_defined_chars;
}

int Configuration::SetNumberOfPlaceValues(char* usr_def_chars, int usr_def_chars_length)
{
	// std::cout << "|||| Total Place Values: " << total_number_place_values << std::endl;

	for (int i = 0; i < usr_input_pre_length; i++) { // used to loop through total_number_place_values

		if (usr_defined_chars[i] == '[' || usr_defined_chars[i + 1] == ']') {

			num_of_dynamic_chars += 1;
		}
	}

	// std::cout << "|||| Dynamic Place Values: " << num_of_dynamic_chars << std::endl; std::cout << '\n';

	if (num_of_dynamic_chars < total_number_place_values) {

		static_char_check = 1;  
	}
	else {

		static_char_check = 0;
	}

	return 1;
}

int Configuration::Hashed() {

	std::cout << "Would you like the output to be hashed?" << std::endl; std::cout << '\n';
	std::cout << "Input 1 for yes. Input 0 for no." << std::endl; std::cout << '\n';

	int input_zero;
	std::cin >> input_zero;
	std::cout << '\n';

	if (input_zero == 1) {
		hashed_ = true;
	}
	else if (input_zero == 0) {
		hashed_ = false;
	}
	else {
		std::cout << "Invalid input" << std::endl; std::cout << '\n';
		Hashed();
	}

	return 0;
}

int Configuration::Repeat() {

	std::cout << "Are place values allowed to repeat?" << std::endl; std::cout << '\n';
	std::cout << "Input 1 for yes. Input 0 for no." << std::endl;  std::cout << '\n';

	int input_zero;
	std::cin >> input_zero;
	std::cout << '\n';

	if (input_zero == 1) {

		repeat_ = false;
	}
	else if (input_zero == 0) {

		repeat_ = true;

		std::cout << "How many values are allowed to repeat?" << std::endl;

		std::cin >> num_allowed_to_repeat; std::cout << '\n';

		if (num_allowed_to_repeat > total_number_place_values) {

			std::cout << "Input must be less then total number of characters in the string. Try again." << std::endl;
			Repeat();
		}
	}
	else {

		std::cout << "Invalid input" << std::endl; std::cout << '\n';
		Repeat();
	}

	return 0;
}

int Configuration::OutputType() {
	
	std::cout << "How would you like to use the data generated?" << std::endl; std::cout << '\n';

	std::cout << "For hash collision: Input 0" << std::endl;
	std::cout << "For list generation: Input 1" << std::endl; 
	std::cout << "For int bitches input 2" << std::endl; std::cout << '\n';

	char input_zero;
	std::cin >> input_zero;

	switch (input_zero) {

	case '0':

		output_type = 0;

		std::cout << "Input the hash to find collision for" << std::endl;
		char inital_input[256];
		std::cin >> inital_input;
	
		for (int i = 0; i < 256; i++) {

			if (inital_input[i] != NULL) {
				comparicon_size += 1;
			}
			else {
				break;
			}
		}

		comparison = new char[comparicon_size + 1];
		comparison[comparicon_size] = '\0';

		for (int i = 0; i < comparicon_size; i++) {  // use memcpy for more lightweight code 

			comparison[i] = inital_input[i];
		}

		break;

	case '1':

		output_type = 1;
		break;

	case '2':

		output_type = 2;
		break;

	default:

		std::cout << "Invalid input" << std::endl;
	}

	return 1;
}

char* Configuration::BuildPlaceValue()
{

	const char asc_two_character_set[95] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '~', '`', '!', '@', '#', '$', '%', '^', '&','*', '(',
	')', '-', '_', '=', '+', '[', ']', '{', '}', '|', '\\', ';', ':', '\"', '\'', ',', '<', '.', '>', '/', '?', '\0'};

	std::cout << "Define your character set. " << std::endl; std::cout << '\n';     

	std::cout << "IMPORTANT NOTE: SPACES ARE NOT CURRENTLY INCLUDED IN THE CHARACTER SET DUE TO UNRESOLVED ISSUES." << std::endl;

	std::cout << '\n';

	std::cout << "Input 0 to enter custom character set." << std::endl; // change input to accept values with more then one place value

	std::cout << "Input 1 for all lowercase letters." << std::endl;

	std::cout << "Input 2 for all uppercase letters." << std::endl; 

	std::cout << "Input 3 for all lowercase and uppercase" << std::endl; 

	std::cout << "Input 4 for numbers zero through nine." << std::endl; 

	std::cout << "Input 5 for all special characters." << std::endl; 

	std::cout << "Input 6 for all alphanumeric characters." << std::endl; 

	std::cout << "Input 7 for all numbers and special characters." << std::endl; 

	std::cout << "Input 8 for entire ascII character set." << std::endl;

	std::cout << "Input 9 for intagers" << std::endl;

	// all words in the english dictionaly within a given word length

	// numbers going behond the tens place (nembers with more then one place value) 

	std::cout << '\n';

	int Input_zero;

	std::cin >> Input_zero;
	std::cout << '\n';

	int counter = 0;

	switch (Input_zero) {

	case 0: // input custom place value options

		std::cout << "Input posible characters for one place vlaue. Use a single string with no spaces." << std::endl;

		std::cin >> place_value_temp;

		for (int i = 0; i < 94; i++) {

			if (place_value_temp[i] != NULL) {

				place_value_size += 1;
			}
			else {

				break;
			}
		}

		place_value_options = new char[place_value_size + 1];
		place_value_options[place_value_size] = '\0';

		for (int i = 0; i < place_value_size; i++) {

			place_value_options = place_value_temp;
		}

		std::cout << "|||| Place Value Options: " << place_value_options << std::endl; std::cout << '\n';

		break;

	case 1: // all lowercase letters

		place_value_options = new char[27];
		place_value_options[26] = '\0';
		place_value_size = 26;

		for (int i = 0; i < 26; i++) {
			place_value_options[i] = asc_two_character_set[i];
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 2: // all uppercase letters

		place_value_options = new char[27];
		place_value_options[26] = '\0';
		place_value_size = 26;

		for (int i = 26; i < 52; i++) {
			place_value_options[counter] = asc_two_character_set[i];
			counter += 1;
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 3: // all lower and uppercase letters

		place_value_options = new char[53];
		place_value_options[52] = '\0';
		place_value_size = 52;

		for (int i = 0; i < 52; i++) {
			place_value_options[i] = asc_two_character_set[i];
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 4: // all numbers 0 through 9

		place_value_options = new char[11];
		place_value_options[10] = '\0';
		place_value_size = 10;

		for (int i = 52; i < 62; i++) {
			place_value_options[counter] = asc_two_character_set[i];
			counter += 1;
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 5: // all special characters 

		place_value_options = new char[33];
		place_value_options[32] = '\0';
		place_value_size = 32;

		for (int i = 62; i < 94; i++) {

			place_value_options[counter] = asc_two_character_set[i];
			counter += 1;
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 6: // alphanumeric characters

		place_value_options = new char[63];
		place_value_options[62] = '\0';
		place_value_size = 62;

		for (int i = 0; i < 62; i++) {

			place_value_options[counter] = asc_two_character_set[i];
			counter += 1;
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 7: // all numbers and special characters

		place_value_options = new char[43];
		place_value_options[42] = '\0';
		place_value_size = 42;

		for (int i = 52; i < 94; i++) {

			place_value_options[counter] = asc_two_character_set[i];
			counter += 1;
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 8: // all pisible characters on a kewboard

		place_value_options = new char[95];
		place_value_options[94] = '\0';
		place_value_size = 94;

		for (int i = 0; i < 94; i++) {
			place_value_options[i] = asc_two_character_set[i];
		}

		std::cout << "|||| Place Value Options: "; std::cout << place_value_options << std::endl; std::cout << '\n';

		break;

	case 9: 

		std::cout << "What range of intagers would you like?" << std::endl; std::cout << '\n';
		
		std::cout << "Input the lowest intager: " << std::endl;
		int lowest;
		std::cin >> lowest;

		std::cout << "Input the highest intager: " << std::endl;
		int highest;
		std::cin >> highest;

		for (int i = lowest; i <= highest; i++) {

			place_value_size += 1;
		}

		place_value_options_int = new int[place_value_size + 1];
		place_value_options_int[place_value_size] = '\0';

		for (int a = lowest; a <= highest; a++) {

			place_value_options_int[counter] = a;
			counter += 1;
		}

		for (int e = 0; e < place_value_size; e++) {
			std::cout << place_value_options_int[e] << ", ";
		}

		break;

	default:

		std::cout << "Invalid input" << std::endl;
	}

	return place_value_options;
}

long long Configuration::SetWorkLoadLength()
{
	work_load_length = std::pow((double)place_value_size, (double)num_of_dynamic_chars);

	return work_load_length;
}

int Processing::SolvingAlgorithm(int num_of_dynamic_chars, int place_value_size, int objective) {

	for (int e = 0; e < num_of_dynamic_chars; e++) {

		if (e == 0) {

			pre_place_value[e] = objective;
		}
		else {

			int remainder_check = pre_place_value[e - 1] % place_value_size;

			if (remainder_check == 0) {

				pre_place_value[e] = pre_place_value[e - 1] / place_value_size; // if there is no remainder
			}
			else {

				pre_place_value[e] = pre_place_value[e - 1] / place_value_size + 1; // if there is indeed a remainder 
			}
		}

		int remainder_check_two = pre_place_value[e] % place_value_size;

		if (remainder_check_two == 0) {

			place_value_array[e] = place_value_size;
		}
		else {

			place_value_array[e] = remainder_check_two;
		}
	}

	return 0;
}

char* Processing::StaticCharacters(char* usr_defined_chars, int usr_input_pre_length) {

	int counter_one = 0;
	int counter_two = 0;
	int pass_ = 0;

	for (int a = 0; a < usr_input_pre_length; a++) {

		if (pass_ == 0) {

			if (usr_defined_chars[a] == '[' && usr_defined_chars[a + 1] == ']') {

				final_char_array[counter_one] = assignment_array[counter_two];
				counter_one += 1;
				counter_two += 1;
				pass_ = 1;
			}
			else {

				final_char_array[counter_one] = usr_defined_chars[a];
				counter_one += 1;
			}
		}
		else {

			pass_ = 0;
		}
	}

	return final_char_array;
}

bool Processing::checkLuhn(const std::string& cardNo) {

	int nDigits = cardNo.length();

	int nSum = 0, isSecond = false;

	for (int i = nDigits - 1; i >= 0; i--) {

		int d = cardNo[i] - '0';

		if (isSecond == true)
			d = d * 2;

		nSum += d / 10;
		nSum += d % 10;

		isSecond = !isSecond;
	}
	return (nSum % 10 == 0);
}

int Processing::CheckDigit(char* final_char_array, int total_number_place_values) {

	bool alternate = true;
	int total = 0;

	for (int i = total_number_place_values - 1; i >= 0; i--) {

		int convert = final_char_array[i] - '0';

		if (alternate == true) {

			int temp = convert * 2;
			total += temp / 10;
			total += temp % 10;
		}
		else {

			total += convert;
		}

		alternate = !alternate;
	}

	int check_digit = 10 - (total % 10);

	if (check_digit == 10) {

		check_digit = 0;
	}

	return check_digit;
}

bool Processing::Repeating(char* final_char_array, int total_number_place_values, int num_allowed_to_repeat) {

	bool return_bool = false;

	for (int i = 0; i < total_number_place_values; i++) {

		char temp = final_char_array[i];
		int counter = 1;

		for (int e = 1; e < num_allowed_to_repeat + 1; e++) {

			if (final_char_array[i + e] == temp && (i + e) < total_number_place_values) {

				counter += 1;
			}
			else {

				break;
			}
		}

		if (counter > num_allowed_to_repeat) {

			return_bool = true;
			break;
		}
	}

	return return_bool;
}

bool Processing::Compair(char* comparison, char* being_compaired, int length) {

	int counter = 0;

	// std::cout << comparison << ", " << being_compaired << ", " << length << std::endl;

	for (int i = 0; i < length; i++) {

		// std::cout << comparison[i] << "," << being_compaired[i] << std::endl;

		if (comparison[i] == being_compaired[i]) {
			counter += 1;
		}
	}

	std::cout << '\n';

	if (counter == length) {

		return true;
	}
	else {

		return false;
	}
}

std::string Processing::convertToString(char* a, int size) {

	int i;
	std::string s = "";

	for (i = 0; i < size; i++) {

		s = s + a[i];
	}

	return s;
}

std::string Processing::md5(std::string input_string) {

	unsigned char digest[MD5_DIGEST_LENGTH]; 

	MD5_CTX mdContext;

	MD5_Init(&mdContext);
	MD5_Update(&mdContext, input_string.c_str(), input_string.length());
	MD5_Final(digest, &mdContext);

	char md5string[33];

	for (int i = 0; i < 16; i++)
		sprintf(&md5string[i * 2], "%02x", digest[i]);

	// std::cout << "MD5 hash of '" << input_string << "' is: " << md5string << std::endl;

	return md5string;
}

int Processing::CompairOne(Configuration config) {

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_one;
	std::cout << "Input starting value: "; std::cin >> starting_value_one;

	long long ending_value_one;
	std::cout << "Input ending value: "; std::cin >> ending_value_one;

	for (long long i = starting_value_one; i <= ending_value_one; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);


			if (Compair(config.comparison, final_char_array, config.comparicon_size)) {
				std::cout << "found comparison: " << final_char_array << std::endl;

				break;
			}
		}
		else {

			if (Compair(config.comparison, assignment_array, config.comparicon_size)) {
				std::cout << "found comparison: " << assignment_array << std::endl;

				break;
			}
		}
	}

	return 1;
}

int Processing::CompairTwo(Configuration config) { // converting to string then back to char slows processing time 

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_two;
	std::cout << "Input starting value: "; std::cin >> starting_value_two;

	long long ending_value_two;
	std::cout << "Input ending value: "; std::cin >> ending_value_two;

	for (long long i = starting_value_two; i <= ending_value_two; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			std::string hash_string = md5(convertToString(final_char_array, config.total_number_place_values)); // hash of final_char_array

			char* hash_char = new char[hash_string.size() + 1]; 
			hash_string.copy(hash_char, hash_string.size() + 1);
			hash_char[hash_string.size()] = '\0';

			if (Compair(config.comparison, hash_char, config.comparicon_size)) {
				std::cout << "found collision: " << final_char_array << ", " << hash_char << std::endl;

				delete[] hash_char;
				break;
			}

			delete[] hash_char;
		}
		else {

			std::string hash_string = md5(convertToString(assignment_array, config.num_of_dynamic_chars));

			char* hash_char = new char[hash_string.size() + 1]; 
			hash_string.copy(hash_char, hash_string.size() + 1);
			hash_char[hash_string.size()] = '\0';

			if (Compair(config.comparison, hash_char, config.comparicon_size)) {
				std::cout << "found collision: " << assignment_array << ", " << hash_char << std::endl;

				delete[] hash_char;
				break;
			}

			delete[] hash_char;
		}
	}

	return 1;
}

int Processing::CompairThree(Configuration config) {

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_three;
	std::cout << "Input starting value: "; std::cin >> starting_value_three;

	long long ending_value_three;
	std::cout << "Input ending value: "; std::cin >> ending_value_three;

	for (long long i = starting_value_three; i <= ending_value_three; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			if (!Repeating(final_char_array, config.total_number_place_values, config.num_allowed_to_repeat)) {

				if (Compair(config.comparison, final_char_array, config.comparicon_size)) {

					std::cout << "found comparison: " << final_char_array << std::endl;

					break;
				}
			}
		}
		else {

			if (!Repeating(assignment_array, config.num_of_dynamic_chars, config.num_allowed_to_repeat)) {

				if (Compair(config.comparison, assignment_array, config.comparicon_size)) {

					std::cout << "found comparison: " << assignment_array << std::endl;

					break;
				}
			}
		}
	}

	return 1;
}

int Processing::CompairFour(Configuration config) {

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_two;
	std::cout << "Input starting value: "; std::cin >> starting_value_two;

	long long ending_value_two;
	std::cout << "Input ending value: "; std::cin >> ending_value_two;

	for (long long i = starting_value_two; i <= ending_value_two; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			if (!Repeating(final_char_array, config.total_number_place_values, config.num_allowed_to_repeat)) {

				std::string hash_string = md5(convertToString(final_char_array, config.total_number_place_values)); // hash of final_char_array

				char* hash_char = new char[hash_string.size() + 1];
				hash_string.copy(hash_char, hash_string.size() + 1);
				hash_char[hash_string.size()] = '\0';

				if (Compair(config.comparison, hash_char, config.comparicon_size)) {

					std::cout << "found collision: " << final_char_array << ", " << hash_char << std::endl;

					delete[] hash_char;
					break;
				}

				delete[] hash_char;
			}
		}
		else {
			
			if (!Repeating(assignment_array, config.num_of_dynamic_chars, config.num_allowed_to_repeat)) {

				std::string hash_string = md5(convertToString(assignment_array, config.num_of_dynamic_chars));

				char* hash_char = new char[hash_string.size() + 1];
				hash_string.copy(hash_char, hash_string.size() + 1);
				hash_char[hash_string.size()] = '\0';

				if (Compair(config.comparison, hash_char, config.comparicon_size)) {
					std::cout << "found collision: " << assignment_array << ", " << hash_char << std::endl;

					delete[] hash_char;
					break;
				}

				delete[] hash_char;
			}
		}
	}

	return 1;
}

int Processing::FileOne(Configuration config) {

	std::ofstream file;
	file.open("output.txt");

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_one;
	std::cout << "Input starting value: "; std::cin >> starting_value_one;

	long long ending_value_one;
	std::cout << "Input ending value: "; std::cin >> ending_value_one;

	for (long long i = starting_value_one; i <= ending_value_one; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) {

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			file << final_char_array << std::endl;
		}
		else {

			file << assignment_array << std::endl;
		}
	}

	file.close();

	return 1;
}

int Processing::FileTwo(Configuration config) {

	std::ofstream file;
	file.open("output.txt");

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_two;
	std::cout << "Input starting value: "; std::cin >> starting_value_two;

	long long ending_value_two;
	std::cout << "Input ending value: "; std::cin >> ending_value_two;

	for (long long i = starting_value_two; i <= ending_value_two; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			file << md5(convertToString(final_char_array, config.total_number_place_values)) << std::endl;

		}
		else {

			file << md5(convertToString(assignment_array, config.num_of_dynamic_chars)) << std::endl;
		}
	}

	file.close();

	return 1;
}

int Processing::FileThree(Configuration config) {

	std::ofstream file;
	file.open("output.txt");

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_three;
	std::cout << "Input starting value: "; std::cin >> starting_value_three;

	long long ending_value_three;
	std::cout << "Input ending value: "; std::cin >> ending_value_three;

	for (long long i = starting_value_three; i <= ending_value_three; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) {

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			if (!Repeating(final_char_array, config.total_number_place_values, config.num_allowed_to_repeat)) {

				file << final_char_array << std::endl;
			}
		}
		else {

			if (!Repeating(assignment_array, config.num_of_dynamic_chars, config.num_allowed_to_repeat)) {

				file << assignment_array << std::endl;
			}
		}
	}

	file.close();

	return 1;
}

int Processing::FileFour(Configuration config) {

	std::ofstream file;
	file.open("output.txt");

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_two;
	std::cout << "Input starting value: "; std::cin >> starting_value_two;

	long long ending_value_two;
	std::cout << "Input ending value: "; std::cin >> ending_value_two;

	for (long long i = starting_value_two; i <= ending_value_two; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = config.place_value_options[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { // ask user if what they want the output to be hashed 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			if (!Repeating(final_char_array, config.total_number_place_values, config.num_allowed_to_repeat)) {

				file << md5(convertToString(final_char_array, config.total_number_place_values)) << std::endl;
			}
		}
		else {

			if (!Repeating(assignment_array, config.num_of_dynamic_chars, config.num_allowed_to_repeat)) {

				file << md5(convertToString(assignment_array, config.num_of_dynamic_chars)) << std::endl;
			}
		}
	}

	file.close();

	return 1;
}

int Processing::IntOne(Configuration config) {

	std::cout << "|||| Work Load: " << config.work_load_length << std::endl; std::cout << '\n';

	long long starting_value_one;
	std::cout << "Input starting value: "; std::cin >> starting_value_one;

	long long ending_value_one;
	std::cout << "Input ending value: "; std::cin >> ending_value_one;

	for (long long i = starting_value_one; i <= ending_value_one; i++) {

		SolvingAlgorithm(config.num_of_dynamic_chars, config.place_value_size, i);

		for (int e = 0; e < config.num_of_dynamic_chars; e++) {

			assignment_array[e] = (char)config.place_value_options_int[place_value_array[e] - 1];
		}

		if (config.static_char_check == 1) { 

			StaticCharacters(config.usr_defined_chars, config.usr_input_pre_length);

			std::cout << final_char_array << std::endl;
		}
		else {

			std::cout << assignment_array << std::endl;
		}
	}

	return 1;
}

int main() {

	Intro();

	Configuration config;
	config.SetCharacters();
	config.SetNumberOfPlaceValues(config.usr_defined_chars, config.num_of_dynamic_chars);
	config.Hashed();
	config.Repeat();
	config.OutputType();
	config.BuildPlaceValue();
	config.SetWorkLoadLength();

	Processing process;
	process.pre_place_value = new int[config.num_of_dynamic_chars + 1];
	process.pre_place_value[config.num_of_dynamic_chars] = '\0';
	process.place_value_array = new int[config.num_of_dynamic_chars + 1];
	process.place_value_array[config.num_of_dynamic_chars] = '\0';
	process.assignment_array = new char[config.num_of_dynamic_chars + 1];
	process.assignment_array[config.num_of_dynamic_chars] = '\0';
	process.final_char_array = new char[config.total_number_place_values + 1];
	process.final_char_array[config.total_number_place_values] = '\0';

	switch (config.output_type) {

	case 0:

		if (config.hashed_ == false && config.repeat_ == false) {

			process.CompairOne(config);
		}
		else if (config.hashed_ == true && config.repeat_ == false) {

			process.CompairTwo(config);
		}
		else if (config.hashed_ == false && config.repeat_ == true) {

			process.CompairThree(config);
		}
		else if (config.hashed_ == true && config.repeat_ == true) {

			process.CompairFour(config);
		}

		break;

	case 1:

		if (config.hashed_ == false && config.repeat_ == false) {

			process.FileOne(config);
		}
		else if (config.hashed_ == true && config.repeat_ == false) {

			process.FileTwo(config);
		}
		else if (config.hashed_ == false && config.repeat_ == true) {

			process.FileThree(config);
		}
		else if (config.hashed_ == true && config.repeat_ == true) {

			process.FileFour(config);
		}

		break;

	case 2:

		process.IntOne(config);

		break;
	default:

		std::cout << "Damn son, you done fucked up big time." << std::endl;
		break;
	}

	delete[] process.pre_place_value;
	delete[] process.place_value_array;
	delete[] process.assignment_array;
	delete[] process.final_char_array;
	delete[] config.usr_defined_chars;
	delete[] config.place_value_options;
}