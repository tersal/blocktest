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

inline unsigned int GetSerializeSize(char a,               int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed char a,        int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned char a,      int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed short a,       int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned short a,     int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed int a,         int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned int a,       int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(signed long a,        int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(unsigned long a,      int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(int64 a,              int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(uint64 a,             int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(float a,              int, int = 0) { return sizeof(a); }
inline unsigned int GetSerializeSize(double a,             int, int = 0) { return sizeof(a); }

template<typename Stream> inline void Serialize(Stream& s, char a,                      int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, signed char a,               int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, unsigned char a,             int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, signed short a,              int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, unsigned short a,            int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, signed int a,                int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, unsigned int a,              int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, signed long a,               int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, unsigned long a,             int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, int64 a,                     int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, uint64 a,                    int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, float a,                     int, int  = 0) { WRITEDATA(s, a); }
template<typename Stream> inline void Serialize(Stream& s, double a,                    int, int  = 0) { WRITEDATA(s, a); }




#endif