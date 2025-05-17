#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

struct HashTable {
    Company table[2000];
    bool check[2000];

    HashTable() {
        for (int i = 0; i < 2000; i++) {
            check[i] = false;
        }
    }
};
vector<Company> readCompanyList(string file_name) {
	ifstream fin(file_name);
	vector<Company>company;
	string line;
	getline(fin, line);
	while (getline(fin, line)) {
		stringstream ss(line);
		string name;
		string tax;
		string addr;
		getline(ss, name, '|');
		getline(ss, tax, '|');
		getline(ss, addr, '|');
		Company cmp;
		cmp.name = name;
		cmp.profit_tax = tax;
		cmp.address = addr;
		company.push_back(cmp);

	}
	return company;
}
long long powerof31(int idex) {
    long long res = 1;
    for (int i = 0; i < idex; i++) {
        res = (res*31)%2000;
    }
    return res;
}
long long hashString(string company_name) {
	string s;
	if (company_name.size() < 20) {
		s = company_name;
	}
	else {
		s = company_name.substr(company_name.size() - 20);
	}
	long long hash = 0;
	int idex = 0;
	for (char x : s) {
		hash += (long long)(x) * powerof31(idex);
		idex++;
	}
	hash = hash % 2000;
	return hash;
}

HashTable* createHashTable(vector<Company> list_company) {
	HashTable* htb = new HashTable;
	for (Company x : list_company) {
		int idex = hashString(x.name);
		int start_idex = idex;
		while (htb->check[idex]) {
			idex = (idex + 1) % 2000;
			if (idex == start_idex) {
				return htb;
			}
		}
		htb->table[idex] = x;
		htb->check[idex] = true;
	}
	return htb;
}
void insert(HashTable* hash_table, Company company) {
	int idex = hashString(company.name);
	int start_idex = idex;
	while (hash_table->check[idex]) {
		idex = (idex + 1) % 2000;
		if (idex == start_idex) {
			return ;
		}
	}
	hash_table->table[idex] = company;
	hash_table->check[idex] = true;
}
Company* search(HashTable* hash_table, string company_name) {
	int idex = hashString(company_name);
	int start_idex = idex;
	while (hash_table->check[idex] == true) {
		if (hash_table->table[idex].name == company_name) {
			return &hash_table->table[idex];
		}
		idex = (idex + 1) % 2000;
		if (idex == start_idex) {
			return NULL;
		}
	}
	return NULL;

}
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./main MST.txt input.txt output.txt" << endl;
        return 1;
    }

    string mst_file = argv[1];     // MST.txt
    string input_file = argv[2];   // input.txt
    string output_file = argv[3];  // output.txt

    ifstream fin1(input_file);
    ofstream fout(output_file);

    if (!fin1 || !fout) {
        cerr << "Error: Cannot open input or output file." << endl;
        return 1;
    }

    vector<Company> list = readCompanyList(mst_file);
    HashTable* htb = createHashTable(list);

    string namecty;
    while (getline(fin1, namecty)) {
        namecty.erase(0, namecty.find_first_not_of(" \t\r\n"));
        namecty.erase(namecty.find_last_not_of(" \t\r\n") + 1);

        if (namecty.empty()) continue;

        Company* C = search(htb, namecty);
        if (C) {
            fout << C->name << "|" << C->profit_tax << "|" << C->address << endl;
        } else {
            fout << endl;
        }
    }

    return 0;
}