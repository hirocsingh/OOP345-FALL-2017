/*
**      NAME: AVINASH SINGH
**      COURSE: OOP345
**      DATE: 26 - SEP - 2017
**      WORKSHOP 4
**      FILE: KVList.h
*/

#include <string>

template <typename K, typename V, int N> class KVList
{
	K keyArray[N];
	V valueArray[N];
	size_t sizeArray;
public:
	KVList() : sizeArray(0)	
	{
		keyArray[0] = '0';
		valueArray[0] = '0';
	}

	size_t size() const 	{	return sizeArray; 	}

	const K& key(unsigned int i) const 	{	
		if (i >= 0 && i < sizeArray){
			return keyArray[i];
		}
		return keyArray[0];
	}

	const V& value(unsigned int i) const {	
		if (i >= 0 && i < sizeArray){
			return valueArray[i];
		}
		return valueArray[0];
	}

	KVList& add(const K& k, const V& v)
	{
		if (sizeArray < N){
			keyArray[sizeArray] = k;
			valueArray[sizeArray] = v;
			sizeArray++;
		}
		return *this;
	}

	int find(const K& k) const 
	{
		int res = 0;
		unsigned int i;
		for (i = 0; i < sizeArray; i++){
			if (keyArray[i] == k){
				res = i;
				break;
			}
		}		
		return i;
	}

	KVList& replace(int i, const K& k, const V& v)
	{
		if (i >= 0 && i < N){
			if (keyArray[i] == k){
				valueArray[i] = v;
			}
		}
		return *this;
	}
};
