/*
	This file is part of Warzone 2100.
	Copyright (C) 1999-2004  Eidos Interactive
	Copyright (C) 2005-2013  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
#ifndef _CRC_H_
#define _CRC_H_

#include "types.h"
#include "vector.h"
#include <vector>
#include <string>


uint32_t crcSum(uint32_t crc, const void *data, size_t dataLen);
uint32_t crcSumU16(uint32_t crc, const uint16_t *data, size_t dataLen);
uint32_t crcSumVector2i(uint32_t crc, const Vector2i *data, size_t dataLen);

struct Sha256
{
	static const int Bytes = 32;

	bool operator ==(Sha256 const &b) const;
	bool isZero() const;
	void setZero();
	std::string toString() const;
	void fromString(std::string const &s);

	uint8_t bytes[Bytes];
};
Sha256 sha256Sum(void const *data, size_t dataLen);

class EcKey
{
public:
	typedef std::vector<uint8_t> Sig;
	typedef std::vector<uint8_t> Key;
	enum Privacy { Public, Private };

	EcKey();
	EcKey(EcKey const &b);
#ifdef WZ_CXX11
	EcKey(EcKey &&b);
#endif
	~EcKey();
	EcKey &operator =(EcKey const &b);
#ifdef WZ_CXX11
	EcKey &operator =(EcKey &&b);
#endif

	void clear();

	bool empty() const;
	bool hasPrivate() const;

	Sig sign(void const *data, size_t dataLen) const;
	bool verify(Sig const &sig, void const *data, size_t dataLen) const;

	Key toBytes(Privacy privacy) const;
	void fromBytes(Key const &key, Privacy privacy);

	static EcKey generate();

private:
	void *vKey;
	static const int curveId;
};

std::string base64Encode(std::vector<uint8_t> const &bytes);
std::vector<uint8_t> base64Decode(std::string const &str);

#endif //_CRC_H_
