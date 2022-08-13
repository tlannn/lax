#include "common/StringTable.h"

/// Class constructor.
StringTable::StringTable() : _count(0), _capacity(0), _interned(nullptr) {}

/// Class destructor.
StringTable::~StringTable() {
	delete[] _interned;
}

/// Return a singleton of the class.
std::shared_ptr<StringTable> StringTable::instance() {
	static std::shared_ptr<StringTable> instance {new StringTable};
	return instance;
}

/// Get a string object stored in the table.
ObjString* StringTable::get(const std::string &chars, int length, uint32_t hash) {
	if (_count == 0) return nullptr;

	auto& string = find(_interned, _capacity, chars, length, hash);

	if (string) return string.get();

	return nullptr;
}

/// Store a string object in the table.
bool StringTable::insert(std::unique_ptr<ObjString> key) {
	// Expand the table capacity if the table max load is reached
	if (_count + 1 > _capacity * TABLE_MAX_LOAD) {
		int capacity = GROW_CAPACITY(_capacity);
		adjustCapacity(capacity);
	}

	// Find the entry corresponding to the key
	auto& entry = find(_interned, _capacity, key->getChars(), key->getLength(), key->getHash());
	bool isNewKey = entry == nullptr;
	if (isNewKey) ++_count;

	entry = std::move(key);
	return isNewKey;
}

/// Remove a string object from the table.
bool StringTable::remove(ObjString *key) {
	if (_count == 0) return false;

	// Find the entry
	auto& entry = find(_interned, _capacity, key->getChars(), key->getLength(), key->getHash());
	if (entry == nullptr) return false;

	entry = nullptr;
	return true;
}

/// Resize the table to accept a new amount of entries.
void StringTable::adjustCapacity(int capacity) {
	auto *entries = new std::unique_ptr<ObjString>[capacity];
	_count = 0;

	// Create all new entries for strings
	for (int i = 0; i < _capacity; ++i) {
		entries[i] = std::unique_ptr<ObjString>();
	}

	// Move previous strings in new entry set
	for (int i = 0; i < _capacity; ++i) {
		auto &entry = _interned[i];
		if (entry == nullptr) continue;

		auto& dest = find(entries, capacity, entry->getChars(), entry->getLength(), entry->getHash());
		dest = std::move(entry);

		++_count;
	}

	delete[] _interned;

	_interned = entries;
	_capacity = capacity;
}

/// Find the entry associated to a string in an array of string objects.
std::unique_ptr<ObjString>& StringTable::find(std::unique_ptr<ObjString> *entries, int capacity,
											  const std::string &chars, int length, uint32_t hash) {
	uint32_t index = hash % capacity;

	for (;;) {
		auto& entry = entries[index];

		if (entry == nullptr ||
			entry->getLength() == length && entry->getHash() == hash &&
			memcmp(entry->getChars(), chars.c_str(), length) == 0) {
			return entry;
		}

		index = (index + 1) % capacity;
	}
}
