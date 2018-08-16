#ifndef BLOCKTEST_TYPES
#define BLOCKTEST_TYPES

#include <stdint.h>
#include <vector>

template<unsigned int BITS>
class base_unit {
	private:
		uint8_t SIZE = BITS/8;
		uint8_t data[SIZE];
	public:
		
		// Empty constructor, initializes the internal array with zero
		base_unit();
		
		// This constructor receives a vector that should be from the size defined in the template
		base_unit(const std::vector<unsigned char>& v);
		
		// Used to compare between variables
		int Compare(const base_unit& other);
		
		// Overload of operators
		bool operator==(const base_unit& other);
		bool operator!=(const base_unit& other);
		bool operator<(const base_unit& other);
		bool operator>(const base_unit& other);
		
} 

class uint256 : base_unit<256> {
	public:
		// Empty constructor, it initializes the 
		// array of data to zero.
		uint256();
		
		/**
		 * This cosntructor receives a vector with 32 bytes
		 * and this vector is used to initialize the data array.
		 */
		 uint256(const std::vector<unsigned char>& v) : base_unit<256>(v) {};
};

#endif