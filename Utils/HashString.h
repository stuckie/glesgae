#ifndef _HASH_STRING_H_
#define _HASH_STRING_H_

#include <string>

namespace GLESGAE
{
	class HashString
	{
		public:			
			explicit HashString() : mHash(0U) {}
			explicit HashString(const char* string) : mHash(0U) { hash(string); }
			explicit HashString(const std::string& string) : mHash(0U) { hash(string.c_str()); }
			
			//! Get the Hashed value.
			inline unsigned int getValue() const { return mHash; }
			
			inline bool operator==(const HashString& rhs) const	{ return (mHash == rhs.mHash); }
			inline bool operator< (const HashString& rhs) const	{ return (mHash < rhs.mHash); }
			inline bool operator!=(const HashString& rhs) const	{ return !(*this == rhs); }

		private:
			inline void hash(const char* string)
			{
				int c;
				while ((c = *string++)) /* http://www.cse.yorku.ca/~oz/hash.html */
					mHash = ((mHash << 5) + mHash) ^ c;
			}
			
			unsigned int mHash;
	};
	
	extern const HashString INVALID_HASHSTRING;
}

#endif
