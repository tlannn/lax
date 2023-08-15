#ifndef LAX_TABLE_H
#define LAX_TABLE_H

#include <cstring>

#include "common/Memory.h"
#include "objects/ObjString.h"
#include "values/Value.h"

#define TABLE_MAX_LOAD 0.75

/**
 * A hash table that can contain Lax values
 *
 * The table stories elements in key-value pairs, with keys being represented as
 * Lax string objects. Key collisions are resolved using open addressing. The
 * next slot is computed via linear probing.
 *
 * The hash function used is defined in the ObjString class.
 */
class Table {
public:
	/// Class constructor.
	Table();

	/// Class destructor.
	~Table();

	/**
	 * Get a value stored in the table.
	 *
	 * @param key the key associated with the value.
	 * @param value the value object where the value copy must be stored.
	 * @return true if the key exists, or false otherwise.
	 */
	bool get(ObjString *key, Value *value);

	/**
	 * Store a value in the table with the given key.
	 *
	 * @param key the key to which the value must be associated.
	 * @param value the value to store.
	 * @return true if no value was already associated to the key, false otherwise.
	 */
	bool set(ObjString *key, Value value);

	/**
	 * Remove from the table the value associated to the given key.
	 *
	 * @param key the key associated with the value.
	 * @return true if a value has effectively been removed, false otherwise.
	 */
	bool remove(ObjString *key);

	void copyTable(Table *to);

	ObjString* findString(const std::string &chars, int length, uint32_t hash);

private:
	/// Structure representing a key-value pair in the table.
	typedef struct Entry {
		ObjString *key = nullptr;
		Value value = Value::null();
	} Entry;

	/**
	 * Resize the table to accept a new amount of entries.
	 *
	 * @param capacity the new capacity of the table.
	 */
	void adjustCapacity(int capacity);

	/**
	 * Find the entry corresponding to a key in an array of entries.
	 *
	 * @param entries the array of entries to look up.
	 * @param capacity the capacity of the array.
	 * @param key the key to look up.
	 * @return the entry corresponding to the key.
	 */
	static Entry* find(Entry *entries, int capacity, ObjString *key);

	int _count;
	int _capacity;
	Entry *_entries;
};

#endif //LAX_TABLE_H
