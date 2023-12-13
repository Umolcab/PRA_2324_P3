#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2324_P1/ListLinked.h"

template <typename V>

class HashTable: public Dict<V>{
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		int h(std::string key){
			int sum = 0;
			for(int i = 0; i < key.length(); i++){
				sum += int(key.at(i));
			}
			return sum % max;
		}

	public:
		HashTable(int size){
			max = size;
			table = new ListLinked<TableEntry<V>>[max];
		       	n = 0;
		}

		~HashTable(){
			delete table;
		}

		int capacity(){
			return max;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			out << th.table << std::endl;
		       	return out;
		}

		V operator[](std::string key){
			TableEntry te = TableEntry(key);
			return search(te);
		}

		void insert(std::string key, V value) override{
			TableEntry te = TableEntry(key, value);
			for(int i = 0; i < max; i++){
				if(table[i].search(te)){
					throw std::runtime_error("La clave ya está en el diccionario.");
				}
			}
			table[h(key)].prepend(te);
			n++;
		}

		V search(std::string key) override{
			TableEntry te = TableEntry(key);
			for(int i = 0; i < max; i++){
				if(int pos = table[i].search(te)){
					return table[i].get(pos).value;
				}
			}
			throw std::runtime_error("La clave no se encuenra en el diccionario.");
		}

		V remove(std::string key) override{
			TableEntry te = TableEntry(key);
			for(int i = 0; i < max; i++){
				if(int pos = table[i].search(te)){
					table[i].remove(pos);
					n--;
				}
			}
			throw std::runtime_error("La clave no se encuentra en el diccionario.");
		}

		int entries() override{
			return n;
		}

};

#endif
