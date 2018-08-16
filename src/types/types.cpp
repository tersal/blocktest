#include <types.h>
#include <cstring>
#include <cassert>

base_unit::base_unit() {
	memset(this->data, 0x00, sizeof(this->data));
}

base_unit::base_unit(const std::vector<unsigned char>& v) {
	assert(v.size() == sizeof(data));
	memcpy(this->data, v.data(), sizeof(this->data));
}

uint256::uint256() {
	memset(this->data, 0x00, sizeof(this->data));
}

uint256::uint256(const std::vector<unsigned char>& v) {
	assert(v.size() == sizeof(data));
	memcpy(this->data, v.data(), sizeof(this->data));
}

int uint256::Compare(const uint256& other) {
	return memcmp(this->data, other.data, sizeof(this->data));
}

bool uint256::operator==(const uint256& other) {
	return (Compare(other) == 0);
}

bool uint256::operator!=(const uint256& other) {
	return (Compare(other) != 0);
}

bool uint256::operator<(const uint256& other) {
	return (Compare(other) < 0);
}

bool uint256::operator>(const uint256& other) {
	return (Compare(other) > 0);
}