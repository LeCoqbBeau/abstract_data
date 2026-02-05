//
// Created by mscheman on 10/20/25.
//

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H


namespace ft {

template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};


template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


template <typename T>
struct plus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x + y; }
};


template <typename T>
struct minus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x - y; }
};


template <typename T>
struct multiplies : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


template <typename T>
struct divides : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


template <typename T>
struct modulus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x % y; }
};


template <typename T>
struct negate : unary_function<T, T> {
	T operator () (T CREF x) const { return -x; }
};


template <typename T>
struct equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x == y; }
};


template <typename T>
struct not_equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x != y; }
};


template <typename T>
struct greater : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x > y; }
};


template <typename T>
struct less : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x < y; }
};


template <typename T>
struct greater_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x >= y; }
};


template <typename T>
struct less_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) const { return x <= y; }
};

// Hash Functor
namespace internal {
static const ft::uint64_t	hash_secret[8] = {
	0x2d358dccaa6c78a5ull,
	0x8bb84b93962eacc9ull,
	0x4b33a62ed433d4a3ull,
	0x4d5a2da51de1aa47ull,
	0xa0761d6478bd642full,
	0xe7037ed1a0b428dbull,
	0x90ed1765281c388cull,
	0xaaaaaaaaaaaaaaaaull
};


inline void rapid_num(ft::uint64_t REF A, ft::uint64_t REF B)
{
	ft::uint128_t r = A;
	r *= B;
	A = static_cast<ft::uint64_t>(r);
	B = static_cast<ft::uint64_t>(r >> 64);
}


static ft::uint64_t rapid_mix(uint64_t A, uint64_t B)
{
	rapid_num(A, B);
	return A ^ B;
}


inline ft::uint64_t rapid_read64(ft::uint8_t const* p)
{
	ft::int64_t v;
	ft::memcpy(&v, p, sizeof(uint64_t));
	return v;
}


inline ft::uint32_t rapid_read32(ft::uint8_t const* p)
{
	ft::int32_t v;
	ft::memcpy(&v, p, sizeof(uint32_t));
	return v;
}


inline uint64_t rapidhash(void const* key, size_t len, ft::uint64_t seed, ft::uint64_t const* secret)
{
	uint8_t	const* p = static_cast<uint8_t const*>(key);
	seed ^= rapid_mix(seed ^ secret[2], secret[1]);
	uint64_t	a = 0;
	uint64_t	b = 0;
	size_t		i = len;
	if (FT_LIKELY(len <= 16)) {
		if (len >= 4) {
			seed ^= len;
			if (len >= 8) {
				uint8_t	const*	plast = p + len - 8;
				a = rapid_read64(p);
				b = rapid_read64(plast);
			} else {
				uint8_t const*	plast = p + len - 4;
				a = rapid_read32(p);
				b = rapid_read32(plast);
			}
		} else if (len > 0) {
			a = (static_cast<uint64_t>(p[0]) << 45) | p[len - 1];
			b = p[len >> 1];
		} else {
			a = 0;
			b = 0;
		}
	} else {
		if (len > 112) {
			uint64_t	see1 = seed,	see2 = seed;
			uint64_t	see3 = seed,	see4 = seed;
			uint64_t	see5 = seed,	see6 = seed;
			while (i > 224) {
				seed = rapid_mix(rapid_read64(p) ^ secret[0], rapid_read64(p + 8) ^ seed);
				see1 = rapid_mix(rapid_read64(p + 16) ^ secret[1], rapid_read64(p + 24) ^ see1);
				see2 = rapid_mix(rapid_read64(p + 32) ^ secret[2], rapid_read64(p + 40) ^ see2);
				see3 = rapid_mix(rapid_read64(p + 48) ^ secret[3], rapid_read64(p + 56) ^ see3);
				see4 = rapid_mix(rapid_read64(p + 64) ^ secret[4], rapid_read64(p + 72) ^ see4);
				see5 = rapid_mix(rapid_read64(p + 80) ^ secret[5], rapid_read64(p + 88) ^ see5);
				see6 = rapid_mix(rapid_read64(p + 96) ^ secret[6], rapid_read64(p + 104) ^ see6);
				seed = rapid_mix(rapid_read64(p + 112) ^ secret[0], rapid_read64(p + 120) ^ seed);
				see1 = rapid_mix(rapid_read64(p + 128) ^ secret[1], rapid_read64(p + 136) ^ see1);
				see2 = rapid_mix(rapid_read64(p + 144) ^ secret[2], rapid_read64(p + 152) ^ see2);
				see3 = rapid_mix(rapid_read64(p + 160) ^ secret[3], rapid_read64(p + 168) ^ see3);
				see4 = rapid_mix(rapid_read64(p + 176) ^ secret[4], rapid_read64(p + 184) ^ see4);
				see5 = rapid_mix(rapid_read64(p + 192) ^ secret[5], rapid_read64(p + 200) ^ see5);
				see6 = rapid_mix(rapid_read64(p + 208) ^ secret[6], rapid_read64(p + 216) ^ see6);
				p += 224;
				i -= 224;
			}
			if (i > 112) {
				seed = rapid_mix(rapid_read64(p) ^ secret[0], rapid_read64(p + 8) ^ seed);
				see1 = rapid_mix(rapid_read64(p + 16) ^ secret[1], rapid_read64(p + 24) ^ see1);
				see2 = rapid_mix(rapid_read64(p + 32) ^ secret[2], rapid_read64(p + 40) ^ see2);
				see3 = rapid_mix(rapid_read64(p + 48) ^ secret[3], rapid_read64(p + 56) ^ see3);
				see4 = rapid_mix(rapid_read64(p + 64) ^ secret[4], rapid_read64(p + 72) ^ see4);
				see5 = rapid_mix(rapid_read64(p + 80) ^ secret[5], rapid_read64(p + 88) ^ see5);
				see6 = rapid_mix(rapid_read64(p + 96) ^ secret[6], rapid_read64(p + 104) ^ see6);
				p += 112;
				i -= 112;
			}
			seed ^= see1;
			see2 ^= see3;
			see4 ^= see5;
			seed ^= see6;
			see2 ^= see4;
			seed ^= see2;
		}
		if (i > 16) {
			seed = rapid_mix(rapid_read64(p) ^ secret[2], rapid_read64(p + 8) ^ seed);
			if (i > 32) {
				seed = rapid_mix(rapid_read64(p + 16) ^ secret[2], rapid_read64(p + 24) ^ seed);
				if (i > 48) {
					seed = rapid_mix(rapid_read64(p + 32) ^ secret[1], rapid_read64(p + 40) ^ seed);
					if (i > 64) {
						seed = rapid_mix(rapid_read64(p + 48) ^ secret[1], rapid_read64(p + 56) ^ seed);
						if (i > 80) {
							seed = rapid_mix(rapid_read64(p + 64) ^ secret[2], rapid_read64(p + 72) ^ seed);
							if (i > 96) {
								seed = rapid_mix(rapid_read64(p + 80) ^ secret[1], rapid_read64(p + 88) ^ seed);
							}
						}
					}
				}
			}
		}
		a=rapid_read64(p + i - 16) ^ i;  b=rapid_read64(p + i - 8);
	}
	a ^= secret[1];
	b ^= seed;
	rapid_num(a, b);
	return rapid_mix(a ^ secret[7], b ^ secret[1] ^ i);
}


inline uint64_t doHash(void const* key, size_t len) {
	return internal::rapidhash(key, len, 0, ft::internal::hash_secret);
}


} // internal


template <typename T>
struct hash : unary_function<T, ft::uint64_t> {
	ft::uint64_t operator () (T CREF x) const { return ft::internal::doHash(&x, sizeof(x)); }
};


} // ft


#endif //FUNCTIONAL_H
