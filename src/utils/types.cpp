#include <types.h>
#include <cstring>
#include <cassert>

// Functions used by the base unit
base_unit::base_unit() {
	memset(this->data, 0x00, sizeof(this->data));
}

base_unit::base_unit(const std::vector<unsigned char>& v) {
	assert(v.size() == sizeof(data));
	memcpy(this->data, v.data(), sizeof(this->data));
}

int base_unit::Compare(const base_unit& other) {
	return memcmp(this->data, other.data, sizeof(this->data));
}

int base_unit::operator==(const base_unit& other) {
	return (Compare(other) == 0);
}

bool base_unit::operator!=(const base_unit& other) {
	return (Compare(other) != 0);
}

bool base_unit::operator<(const base_unit& other) {
	return (Compare(other) < 0);
}

bool base_unit::operator>(const base_unit& other) {
	return (Compare(other) > 0);
}