#include "big_integer.h"

#include <iostream>
using namespace std;

// Identifier
const std::string BigInteger::name = "BigInteger";

// Method
void BigInteger::initialize_properties() {
	this->sign = true;
	this->length = 0;
	this->capacity = 0;
	this->value_string = new char[this->initial_capacity]();
	if (this->value_string != NULL) {
		this->capacity = this->initial_capacity;
		this->length = 0;
	}
}

void BigInteger::doubling_capacity() {
	int new_capacity = this->capacity * 2;
	char* new_value_string = new char[new_capacity]();
	if (new_value_string == NULL) return;

	memcpy(new_value_string, this->value_string, this->length);
	delete(this->value_string);

	this->capacity = new_capacity;
	this->value_string = new_value_string;
}

// for test
void BigInteger::print_BI() {
	
	cout << "\n[TEST PRINTGING BIG INTEGER]" << endl;
	cout << "sign : " << this->sign << endl;
	cout << "length : " << this->length << endl;
	cout << "capacity : " << this->capacity << endl;
	cout << "string : " << this->value_string << "\n" << endl;
}


int BigInteger::get_number_length(int number) {
	int tmp = number;
	int length = 1;

	// if negative?

	while (tmp >= 10) {
		tmp = tmp / 10;
		length++;
	}

	return length;
}
int BigInteger::get_number_length(long long number) {
	long long tmp = number;
	int length = 1;

	// if negative?

	while (tmp >= 10) {
		tmp = tmp / 10;
		length++;
	}

	return length;
}

void BigInteger::reverse_string(char* arr) {

	char* tmp_arr = new char[this->capacity] ();

	// arr -> 0987654321
	int last_index = this->length - 1;
	for (int i = 0; i < this->length; i++) {
		tmp_arr[i] = arr[last_index-i];
	}

	this->value_string= tmp_arr;
}

BigInteger::COMPARE_RESULT BigInteger::compare_absolute_value(const BigInteger& big_integer) const {
	int start_index = 0;

	int length = this->length;
	int given_length = big_integer.length;

	if (length > given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
	}
	else if (length < given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
	}
	else {
		for (int place_index = 0; place_index < length; place_index++) {
			if (this->value_string[place_index + start_index] > big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
			}
			else if (this->value_string[place_index + start_index] < big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
			}
		}
	}
	return BigInteger::COMPARE_RESULT::COMPARE_EQUAL;
}

// Method (Interface)
BigInteger::BigInteger() {
	/* Should be implemented */
	// just initialize
	initialize_properties();
	this->value_string[0] = '0';
}

BigInteger::BigInteger(int value) {
	/* Should be implemented */
	initialize_properties();
	
	// neg_flag == 1 means negative number
	//int neg_flag = 0;

	// negative number processing
	if (value < 0) {
		//neg_flag = 1;
		this->sign = false;
		value = value * -1;
	}

	// get number length
	int tmp_length = get_number_length(value);

	while (tmp_length >= this->capacity) {
		doubling_capacity();
	}

	this->length = tmp_length;

	int tmp_num = value;
	char now_num = 0;

	for (int i = 0; i < this->length; i++) {
		now_num = tmp_num % 10;
		tmp_num = tmp_num / 10;

		this->value_string[i] = now_num + '0';
	}

	// reverse
	reverse_string(this->value_string);

}

BigInteger::BigInteger(long long value) {
	/* Should be implemented */
	initialize_properties();

	// neg_flag == 1 means negative number
	//int neg_flag = 0;

	// negative number processing
	if (value < 0) {
		//neg_flag = 1;
		this->sign = false;
		value = value * -1;
	}

	// get number length
	int tmp_length = get_number_length(value);

	while (tmp_length >= this->capacity) {
		doubling_capacity();
	}

	this->length = tmp_length;

	long long tmp_num = value;
	char now_num = 0;

	for (int i = 0; i < this->length; i++) {
		now_num = tmp_num % 10;
		tmp_num = tmp_num / 10;

		this->value_string[i] = now_num + '0';
	}

	// reverse
	reverse_string(this->value_string);
}

BigInteger::BigInteger(std::string value) {
	/* Should be implemented */
	initialize_properties();

	if (value[0] == '-') {
		this->sign = false;
		value = value.substr(1);
	}

	int tmp_length = value.size();
	
	while (tmp_length >= this->capacity) {
		doubling_capacity();
	}

	this->length = tmp_length;
	memcpy(this->value_string, value.c_str(), this->length);
}

BigInteger::BigInteger(const BigInteger& big_integer) {
	this->initialize_properties();

	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
			this->sign = true;
			this->length = 0;
			this->capacity = 0;
		}

		this->value_string = new_value_string;
		memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
		this->sign = big_integer.sign;
		this->length = big_integer.length;
		this->capacity = big_integer.capacity;
	}
}

BigInteger::~BigInteger() {
	if (this->value_string != NULL) {
		delete(this->value_string);
		this->sign = true;
		this->length = 0;
		this->capacity = 0;
	}
}

std::string BigInteger::get_name() const {
	return name;
}

char* BigInteger::get_string() const {
	return this->value_string;
}

BigInteger& BigInteger::operator = (const BigInteger& big_integer) {
	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
			this->sign = true;
			this->length = 0;
			this->capacity = 0;
		}

		this->value_string = new_value_string;
		memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
		this->sign = big_integer.sign;
		this->length = big_integer.length;
		this->capacity = big_integer.capacity;
	}

	return *this;
}

bool BigInteger::operator == (const BigInteger& big_integer) const {
	if (this->length != big_integer.length) {
		return false;
	}

	if (this->sign != big_integer.sign) {
		return false;
	}

	for (unsigned int place_index = 0; place_index < big_integer.length; place_index++) {
		if (this->value_string[place_index] != big_integer.value_string[place_index]) {
			return false;
		}
	}

	return true;
}

bool BigInteger::operator > (const BigInteger& big_integer) const {
	BigInteger::COMPARE_RESULT compare_result;

	// If sign is the same
	if (this->sign == big_integer.sign) {
		// Compare two absolute values
		compare_result = this->compare_absolute_value(big_integer);

		// Compare two positive values
		if (this->sign) {
			if (compare_result == this->COMPARE_LARGER) {
				return true;
			}
			else {
				return false;
			}
		}
		// Compare two negative values
		else {
			if (compare_result == this->COMPARE_SMALLER) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	// No need to compare
	else {
		if (this->sign) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool BigInteger::operator < (const BigInteger& big_integer) const {
	return (big_integer > *this);
}

bool BigInteger::operator >= (const BigInteger& big_integer) const {
	return !(big_integer > *this);
}

bool BigInteger::operator <= (const BigInteger& big_integer) const {
	return !(big_integer < *this);
}

BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
	/* Should be implemented */
	BigInteger result;
	result.initialize_properties();

	// + + 라고 가정
	if (this->sign == big_integer.sign) {
		result.sign = this->sign;

		//this->value_string + big_integer.value_string
		char* num1 = this->value_string;
		char* num2 = big_integer.value_string;

		int num1_size = this->length;
		int num2_size = big_integer.length;

		int max;
		if (num1_size > num2_size) {
			max = num1_size;
		}
		else {
			max = num2_size;
		}

		int num1_index = num1_size - 1;
		int num2_index = num2_size - 1;

		int tmp_result;
		int carry_flag = 0;
		int carry_value = 1;

		int tmp_length = max;

		while (max + 1 >= result.capacity) {
			result.doubling_capacity();
		}

		int index = 0;

		while (num1_index >= 0 || num2_index >= 0) {
			int n1, n2;

			n1 = num1[num1_index] - '0';
			n2 = num2[num2_index] - '0';

			// num1 is min
			if (num1_index < 0 && num2_index >= 0) {
				while (num2_index >= 0) {
					if (carry_flag) {
						tmp_result = carry_value + n1 + n2;
						n1 = 0;
						carry_flag = 0;
					}
					else {
						tmp_result = n2;
					}

					if (tmp_result >= 10) carry_flag = 1;

					result.value_string[index] = tmp_result % 10 + '0';
					index++;

					num2_index--;
					n2 = num2[num2_index] - '0';
				}
			}
			// num2 is min
			else if (num2_index < 0 && num1_index >= 0) {
				while (num1_index >= 0) {
					if (carry_flag) {
						tmp_result = carry_value + n1 + n2;
						n2 = 0;
						carry_flag = 0;
					}
					else {
						tmp_result = n1;
					}

					if (tmp_result >= 10) carry_flag = 1;

					result.value_string[index] = tmp_result % 10 + '0';
					index++;

					num1_index--;
					n1 = num1[num1_index] - '0';
				}
			}
			else {
				if (carry_flag) {
					tmp_result = carry_value + n1 + n2;
					carry_flag = 0;
				}
				else {
					tmp_result = n1 + n2;
				}

				if (tmp_result >= 10) carry_flag = 1;

				result.value_string[index] = tmp_result % 10 + '0';
				index++;

				num1_index--;
				num2_index--;
			}
		}

		if (carry_flag) {
			result.value_string[index] = '1';

			result.length = tmp_length + 1;
		}
		else {

			result.length = tmp_length;
		}
		result.reverse_string(result.value_string);
	}

	return result;
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
	/* Should be implemented */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator * (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator / (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator % (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

std::ostream& operator << (std::ostream& out, const BigInteger& big_integer) {
	// Print minus sign
	if (!big_integer.sign) {
		out << std::string("-");
	}

	// Print values
	out << std::string(big_integer.get_string(), big_integer.length);
	return out;
}

std::istream& operator >> (std::istream& in, BigInteger& big_integer) {
	std::string input_string;
	in >> input_string;

	big_integer = BigInteger(input_string);

	return in;
}
