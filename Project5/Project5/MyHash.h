// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#ifndef MYHASH
#define MYHASH

//#include<iostream> //delete

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const
	{
		return m_count;
	}
	double getLoadFactor() const
	{
		return static_cast<double>(m_count)/m_size;
	}

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

	//void print() const;  // delete



private:
	double m_factor;
	unsigned int getBucketNumber(const KeyType& key) const
	{
		unsigned int hasher(const	KeyType& k);
		unsigned int h = hasher(key);
		unsigned int bucket = h % m_size;
		return bucket;
	}
	struct Node
	{
		ValueType m_value;
		KeyType m_key;
		Node* m_next;
	};
	Node** m_list;
	int m_size;
	int m_count;
	void insert(const KeyType& key, const ValueType& value);
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
	if (maxLoadFactor <= 0) m_factor = 0.5;
	else if (maxLoadFactor > 2) m_factor = 2.0;
	else m_factor = maxLoadFactor;
	m_size = 100;
	m_count = 0;
	m_list = new Node*[m_size];
	for (int i = 0; i < m_size; i++)
		m_list[i] = nullptr;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_list[i] != nullptr) {
			Node* itr = m_list[i];
			while (itr != nullptr)
			{
				Node* tmp = itr;
				itr = itr->m_next;
				delete tmp;
			}
		}
	}

	delete[] m_list;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	unsigned int bucket = getBucketNumber(key);

	if (m_list[bucket] == nullptr)
	{
		m_list[bucket] = new Node;
		m_list[bucket]->m_value = value;
		m_list[bucket]->m_key = key;
		m_list[bucket]->m_next = nullptr;
		m_count++;
	}
	else {
		Node* itr = m_list[bucket];
		Node* prev = nullptr;
		while (itr != nullptr)
		{
			if (key == itr->m_key) {
				itr->m_value = value;
				break;
			}
			prev = itr;
			itr = itr->m_next;
		}

		if (itr == nullptr) {
			prev->m_next = new Node;
			prev = prev->m_next;
			prev->m_value = value;
			prev->m_key = key;
			prev->m_next = nullptr;
			m_count++;
		}
	}
	
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_list[i] != nullptr) {
			Node* itr = m_list[i];
			while (itr != nullptr)
			{
				Node* tmp = itr;
				itr = itr->m_next;
				delete tmp;
			}
		}
	}

	delete[] m_list;
	m_list = new Node*[100];
	for (int i = 0; i < 100; i++)
		m_list[i] = nullptr;
	m_size = 100;
	m_count = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	
	insert(key, value);

	if (m_count > m_size * m_factor) {   //check if exceed

		int oriSize = m_size;
		m_size *= 2;
		Node** oriList = m_list;
		m_count = 0;
		
		m_list = new Node*[m_size];

		//print();
		for (int i = 0; i < m_size; i++)
			m_list[i] = nullptr;

		for (int i = 0; i < oriSize; i++)         //rehash
		{
			if (oriList[i] != nullptr) {
				Node* itr = oriList[i];
				while (itr != nullptr)
				{
					insert(itr->m_key, itr->m_value);
					itr = itr->m_next;
				}
			}
		}

		for (int i = 0; i < oriSize; i++)   //delete original list
		{
			if (oriList[i] != nullptr) {
				Node* itr = oriList[i];
				while (itr != nullptr)
				{
					Node* tmp = itr;
					itr = itr->m_next;
					delete tmp;
				}
			}
		}

		delete[] oriList;
	}	
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const	KeyType& key) const
{
	unsigned int bucket = getBucketNumber(key);
	if (m_list[bucket] == nullptr) return nullptr;
	else {
		Node* itr = m_list[bucket];
		while (itr != nullptr)
		{
			if (key == itr->m_key) return &(itr->m_value);
			itr = itr->m_next;
		}
		if (itr == nullptr) return nullptr;
	}
	return nullptr;
}

/*template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::print() const
{
	int count = 0;
	for (int i = 0; i < m_size; i++)
	{
		cout << '#' << i+1 << ' ';
		if (m_list[i] == nullptr) cout << endl;
		else {
			Node *itr = m_list[i];
			while (itr != nullptr)
			{
				cout << m_list[i]->m_key << "->" << m_list[i]->m_value << "->";
				itr = itr->m_next;
				count++;
			}
			cout << endl;
			
		}
	}
	cout << count << endl;
}*/
 

#endif