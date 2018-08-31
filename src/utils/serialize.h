#ifndef SERIALIZE_H
#define SERIALIZE_H
// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.
#include <vector>
#include <map>

typedef long long int64;
typedef unsigned long long uint64;

static const int VERSION = 101;

/////////////////////////////////////////////////////////////////
//
// Templates for serializing to anything that looks like a stream,
// i.e. anything that supports .read(char*, int) and .write(char*, int)
//

enum {
	// Primary actions
	SER_NETWORK          = (1 << 0),
	SER_DISK             = (1 << 1),
	SER_GETHASH          = (1 << 2),
	
	//Modifiers
	SER_SKIPSIG          = (1 << 16),
	SER_BLOCKHEADERONLY  = (1 << 17),
};

#define IMPLEMENT_SERIALIZE(statements)      \
	unsigned int GetSerializeSize(int nType = 0, int nVersion = VERSION) const \
	{                                                                          \
		const bool fGetSize = true;                                            \
		const bool fWrite = false;                                             \
		const bool fRead = false;                                              \
		unsigned int nSerSize = 0;                                             \
		ser_streamplaceholder s;                                               \
		s.nType = nType;                                                       \
		s.nVersion = nVersion                                                  \
		{statements}                                                           \
		return nSerSize;                                                       \
	}                                                                          \
	template<typename Stream>                                                  \
	void Serialize(Stream& s, int nType = 0, int nVersion = VERSION) const     \
	{                                                                          \
		const bool fGetSize = false;                                           \
		const bool fWrite = true;                                              \
		const bool fRead = false;                                              \
		unsigned int nSerSize = 0;                                             \
		{statements}                                                           \
	}                                                                          \
	template<typename Stream>                                                  \
	void Unserialize(stream& s, int nType = 0, int nVersion = VERSION)         \
	{                                                                          \
		const bool fGetSize = false;                                           \
		const bool fWrite = false;                                             \
		const bool fRead = true;                                               \
		unsigned int nSerSize = 0;                                             \
		{statements}                                                           \
	}
	
#define READWRITE(obj)      (nSerSize += ::SerReadWrite(s, (obj), nType, nVersion))

//
// Basic Types
//
#define WRITEDATA(s, obj)    s.write((char*)&(obj), sizeof(obj))
#define READDATA(s, obj)     s.read((char*)&(obj), sizeof(obj))

inline unsigned int GetSerializeSize(char a,               int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(signed char a,        int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(unsigned char a,      int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(signed short a,       int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(unsigned short a,     int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(signed int a,         int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(unsigned int a,       int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(signed long a,        int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(unsigned long a,      int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(int64 a,              int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(uint64 a,             int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(float a,              int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(double a,             int, int = 0) { return sizeof(a);  }
inline unsigned int GetSerializeSize(bool a,               int, int = 0) { return sizeof(char)}

template<typename Stream> inline void Serialize(Stream& s, char a,                      int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, signed char a,               int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, unsigned char a,             int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, signed short a,              int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, unsigned short a,            int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, signed int a,                int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, unsigned int a,              int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, signed long a,               int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, unsigned long a,             int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, int64 a,                     int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, uint64 a,                    int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, float a,                     int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, double a,                    int, int  = 0) { WRITEDATA(s, a);             }
template<typename Stream> inline void Serialize(Stream& s, bool a,                      int, int  = 0) { char f = a; WRITEDATA(s, f); }

template<typename Stream> inline void Unserialize(Stream& s, char& a,                   int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, signed char& a,            int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, unsigned char& a,          int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, signed short& a,           int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, unsigned short& a,         int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, signed int& a,             int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, unsigned int& a,           int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, signed long& a,            int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, unsigned long& a,          int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, int64& a,                  int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, uint64& a,                 int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, float& a,                  int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, double& a,                 int, int = 0 ) { READDATA(s, a);               }
template<typename Stream> inline void Unserialize(Stream& s, bool& a,                   int, int = 0 ) { char f; READDATA(s, f); a = f;}

/**
 * Compact size
 * size <  253         -- 1 byte
 * size <= USHRT_MAX   -- 3 bytes  (253 + 2 bytes)
 * size <= UINT_MAX    -- 5 bytes  (254 + 4 bytes)
 * size >  UNIT_MAX    -- 9 bytes  (255 + 8 bytes)
 */
 inline unsigned int GetSizeOfCompactSize(uint64 nSize) {
	 if (nSize < UCHAR_MAX - 2)    return sizeof(unsigned char);
	 else if (nSize <= USHRT_MAX)  return sizeof(unsigned char) + sizeof(unsigned short);
	 else if (nSize <= UINT_MAX)   return sizeof(unsigned char) + sizeof(unsigned int);
	 else                          return sizeof(unsigned char) + sizeof(uint64);
 }
 
 template<typename Stream>
 void WriteCompactSize(Stream& os, uint64 nSize) {
	 if (nSize < UCHAR_MAX - 2) {
		 unsigned char chSize = nSize;
		 WRITEDATA(os, chSize);
	 } else if(nSize <= USHRT_MAX) {
		 unsigned char chSize = UCHAR_MAX - 2;
		 unsigned short xSize = nSize;
		 WRITEDATA(os, chSize);
		 WRITEDATA(os, xSize);
	 } else if(nSize <= UINT_MAX) {
		 unsigned char chSize = UCHAR_MAX - 1;
		 unsigned int xSize = nSize;
		 WRITEDATA(os, chSize);
		 WRITEDATA(os, xSize);
	 } else {
		 unsigned char chSize = UCHAR_MAX;
		 WRITEDATA(os, chSize);
		 WRITEDATA(os, nSize);
	 }
	 return;
 }
 
template<typename Stream>
uint64 ReadCompactSize(Stream& is) {
	unsigned char chSize;
	READDATA(is, chSize);
	if (chSize < UCHAR_MAX - 2) {
		return chSize;
	} else if (chSize == (UCHAR_MAX - 2)) {
		unsigned short nSize;
		READDATA(is, nSize);
		return nSize;
	} else if (chSize == (UCHAR_MAX - 1)) {
		unsigned int nSize;
		READDATA(is, nSize);
		return nSize;
	} else {
		uint64 nSize;
		READDATA(is, nSize);
		return nSize;
	}
}

/**
 * Wrapper for serializing arrays and POD
 */
class CFlatData {
	protected:
		char* pbegin;
		char* pend;
	public:
		CFlatData(void* pbeginIn, void* pendIn) : pbegin((char*)pbeginIn), pend((char*)pendIn) { }
		char* begin() { return pbegin; }
		const char* begin() const { return pbegin; }
		char* end() { return pend; }
		const char* end() const { return pend; }
		
		unsigned int GetSerializeSize(int, int=0) const {
			return pend - pbegin;
		}
		
		template<typename Stream>
		void Serialize(Stream& s, int, int = 0) const {
			s.write(pbegin, pend - pbegin);
		}
		
		template<typename Stream>
		void Unserialize(Stream& s, int, int = 0) {
			s.read(pbegin, pend - pbegin);
		}
}

//
// string stored as a fixed length field
//
template<std::size_t LEN>
class CFixedFieldString {
	protected:
		const string* pcstr;
		string* pstr;
		
	public:
		explicit CFixedFieldString(const string& str) : pcstr(&str), pstr(NULL) { }
		explicit CFixedFieldString(string& str) : pcstr(&str), pstr(&str) { }
		
		unsigned int GetSerializeSize(int, int = 0) const {
			return LEN;
		}
		
		template<typename Stream>
		void Serialize(Stream& s, int, int = 0) const {
			char pszBuf[LEN];
			strncpy(pzsBuf, pcstr->c_str(), LEN);
			s.write(pszBuf, LEN)
		}
		
		template<typename Stream>
		void Unserialize(Stream& s, int, int = 0) {
			if (pstr == NULL) {
				throw std::ios_base::failure("CFixedFieldString::Unserialize : Trying to unserialize to const string");
			}
			char pzsBuf[LEN + 1];
			s.read(pszBuf, LEN);
			pszBuf[LEN] = '\0';
			*pstr = pszBuf;
		}
}

//
// Forward declaration
//

// string
template<typename C> unsigned int GetSerializeSize(const basic_string<C>& str, int, int = 0);
template<typename Stream, typename C> void Serialize(Stream& os, const basic_string<C>& str, int, int = 0);
template<typename Stream, typename C> void Unserialize(Stream& is, basic_string<C>& str, int, int = 0);

// Vector
template<typename T, typename A> unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion, const boost::true_type&);
template<typename T, typename A> unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion, const boost::false_type&);
template<typename T, typename A> inline unsigned int GetSerializeSize(const std::vector<T, A>& v, int nType, int nVersion = VERSION);
template<typename Stream, typename T, typename A> void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const boost::true_type&);
template<typename Stream, typename T, typename A> void Serialize_impl(Stream& os, const std::vector<T, A>& v, int nType, int nVersion, const boost::false_type&);
template<typename Stream, typename T, typename A> inline void Serialize(Stream& os, const std::vector<T, A>& v, int nType, int nVersion);
#endif