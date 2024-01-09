#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2324_P1/ListLinked.h"
//#include "../../PRA_P1/PRA_2324_P1/ListLinked.h"

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
			out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
			for(int i = 0; i < th.max; i++){
				out << "== Cubeta " << i << "==" << std::endl;
				out << std::endl;
				out << th.table[i] << std::endl; 
			}
			return out;
		}

		V operator[](std::string key){
			return search(key);
		}

		void insert(std::string key, V value) override{
			TableEntry<V> te = TableEntry<V>(key, value);
			for(int i = 0; i < max; i++){
				if(table[i].search(te) != -1){
					throw std::runtime_error("La clave ya está en el diccionario.");
				}
			}
			table[h(key)].prepend(te);
			n++;
		}

		V search(std::string key) override{
			TableEntry<V> te = TableEntry<V>(key);
			int pos;
			for(int i = 0; i < max; i++){
				pos = table[i].search(te);
				if(pos != -1){
					return table[i].get(pos).value;
				}
			}
			throw std::runtime_error("La clave no se encuentra en el diccionario.");
		}

		V remove(std::string key) override{
			TableEntry<V> te = TableEntry<V>(key);
			int pos;
			for(int i = 0; i < max; i++){
				pos = table[i].search(te);
				if(pos != -1){
					n--;
					return table[i].remove(pos).value;
				}
			}
			throw std::runtime_error("La clave no se encuentra en el diccionario.");
		}

		int entries() override{
			return n;
		}

};

#endif
