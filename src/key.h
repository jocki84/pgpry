/*
 * pgpry alpha - PGP private key password recovery
 * Copyright (C) 2010 Jonas Gehring
 *
 * file: key.h
 * Represents a PGP key
 */


#ifndef KEY_H_
#define KEY_H_


#include "main.h"

#include <openssl/rsa.h>
#include <openssl/dsa.h>

#include "cryptutils.h"
#include "string2key.h"

class PIStream;
class POStream;


class Key
{
	public:
		Key();
		Key(const Key &other);
		~Key();

		bool locked() const;
		uint32_t dataLength() const;
		const uint8_t *data() const;
		const String2Key &string2Key() const;

		PIStream &operator<<(PIStream &in);
		POStream &operator>>(POStream &out);

		Key &operator=(const Key &other);

	private:
		bool m_locked;
		uint8_t m_version;

		CryptUtils::PublicKeyAlgorithm m_algorithm;
		RSA *m_rsa;
		DSA *m_dsa;

		String2Key m_s2k;
		uint32_t m_datalen;
		uint8_t *m_data;

		uint32_t m_time;
		uint16_t m_expire;
};

// Convenience operators
inline PIStream &operator>>(PIStream &in, Key &key)
{
	return (key << in);
}

inline POStream &operator<<(POStream &out, Key &key)
{
	return (key >> out);
}


#endif // KEY_H_