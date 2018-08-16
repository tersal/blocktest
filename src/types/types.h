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
		base_unit();
} 

class uint256 {
	public:
		// Empty constructor, it initializes the 
		// array of data to zero.
		uint256();
		
		/**
		 * This cosntructor receives a vector with 32 bytes
		 * and this vector is used to initialize the data array.
		 */
		 uint256(const std::vector<unsigned char>& v);
		 
		 // Used to compare between uint256 variables
		 int Compare(const uint256& other);
		 
		 // Overload of operators
		 bool operator==(const uint256& other);
		 bool operator!=(const uint256& other);
		 bool operator<(const uint256& other);
		 bool operator>(const uint256& other);
};

#endif