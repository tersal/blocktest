// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.
#include <limits.h>
#include <string>

typedef long long int64;
typedef unsigned long long uint64;

inline int TestuintAdHoc(std::vector<std::string> vArg);

// We have to keep a separate base class without constructors
// so the compiler wil let us use it in a union
template<unsigned int BITS>
class base_uint {
    protected:
        enum { WIDTH = BITS / 32 };
        unsigned int pn[WIDTH];
    public:
        bool operator!() const {
            for (int i = 0; i < WIDTH; i++)
                if (pn[i] != 0)
                    return false;
            return true;
        }
        
        const base_uint operator~() const {
            base_uint ret;
            for (int i = 0; i < WIDTH; i++)
                ret.pn[i] = ~pn[i];
            return ret;
        }
        
        const base_uint operator- const {
            base_uint ret;
            for (int  i = 0; i < WIDTH; i++)
                ret.pn[i] = ~pn[i];
            ret++;
            return ret;
        }
        
        base_uint& operator=(uint64 b) {
            p[0] = (unsigned int)b;
            p[1] = (unsigned int)(b >> 32);
            for (int i = 2; i < WIDTH; i++)
                pn[i] = 0;
            return *this;
        }
        
        base_uint& operator^=(const base_uint& b) {
            for (int i = 0; i < WIDTH; i++)
                pn[i] ^= b.pn[i];
            return *this;
        }
        
        base_uint& operator&=(const base_uint& b) {
            for (int i = 0; i < WIDTH; i++)
                pn[i] &= b.pn[i];
            return *this;
        }
        
        base_uint& operator|=(const base_uint& b) {
            for (int i = 0; i != WIDTH; i++)
                pn[i] |= b.pn[i];
            return *this;
        }
        
        base_uint& operator^=(uint64 b) {
            pn[0] ^= (unsigned int)b;
            pn[1] ^= (unsigned int)(b >> 32);
            return *this;
        }
        
        base_uint& operator&=(uint64 b) {
            pn[0] &= (unsigned int)b;
            pn[1] &= (unsigned int)(b >> 32);
            return *this;
        }
        
        base_uint& operator|=(uint64 b) {
            pn[0] |= (unsigned int)b;
            pn[1] |= (unsigned int)(b >> 32);
            return *this;
        }
        
        base_uint& operator<<=(unsigned int shift) {
            base_uint a(*this);
            for (int i = 0; i < WIDTH; i++)
                pn[i] = 0;
            int k = shift / 32;
            shift = shift % 32;
            for (int i = 0; i < WIDTH; i++) {
                if ((i + k + 1) < WIDTH && shift != 0)
                    pn[i+k+1] |= (a.pn[i] >> (32 - shift));
                if (i + k < WIDTH)
                    pn[i + k] |= (a.pn[i] << shift);
            }
            return *this;
        }
}