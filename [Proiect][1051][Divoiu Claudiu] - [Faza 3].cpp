#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
class BinaryFile {
public:
	virtual void writeToFile(fstream& f) = 0;
	virtual void readFromFile(fstream& f) = 0;
};
class InputFile {
public:
	virtual void readFromText(fstream& f) = 0;
	virtual void readFromCSV(fstream& f) = 0;
};
class Depozit : public InputFile, public BinaryFile {
private:
	int nrProduse = 0;
	string* produse = NULL;
	int* cantitatiProduse = NULL;
	int* preturiProduse = NULL;
	int nrMasini = 0;
	int masiniDisponibile[10] = {}; //ia 0 daca masina de indice i+1 este indisponibila si altceva daca este disponibila pentru livrare;
	friend class Comenzi;
public:
	Depozit() {}
	Depozit(int nrProduse, string* produse, int* cantitatiProduse, int* preturiProduse, int nrMasini, int masiniDisponibile[])
	{
		if (this->nrProduse != 0 && cantitatiProduse != NULL && produse != NULL && preturiProduse != NULL)
		{
			for (int i = 0; i < nrProduse; i++)
			{
				if (preturiProduse[i] < 0) throw new exception("Preturile nu pot fi negative");
			}
			this->nrProduse = nrProduse;
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
			this->cantitatiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->cantitatiProduse[i] = cantitatiProduse[i];  //in cazul in care cantitatea e negativa, magazinul a primit mai multe comenzi decat avea in stoc initial si trebuie sa mai comande
			}
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->preturiProduse[i] = preturiProduse[i];  
			}
		}
		if (this->nrMasini != 0) {
			this->nrMasini = nrMasini;
			for (int i = 0; i < this->nrMasini; i++)
			{
				this->masiniDisponibile[i] = 1;
			}
		}
	}
	Depozit(const Depozit& d)
	{
		this->nrProduse = d.nrProduse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->produse[i] = d.produse[i];
		}
		this->cantitatiProduse = new int[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->cantitatiProduse[i] = d.cantitatiProduse[i];
		}
		this->preturiProduse = new int[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->preturiProduse[i] = d.preturiProduse[i];
		}
		this->nrMasini = d.nrMasini;
		for (int i = 0; i < this->nrMasini; i++)
		{
			this->masiniDisponibile[i] = d.masiniDisponibile[i];
		}
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}
	void setNrProduse(int nrTotalProduse, string* produse, int* cantitatiProduse, int* preturiProduse)
	{
		if (this->nrProduse == 0) throw new exception("Numarul de produse nu poate fi 0");
		else if (produse == NULL || cantitatiProduse == NULL || preturiProduse == NULL) throw new exception("Produsele, cantitatile sau preturile nu pot fi nule");
		else {
			for (int i = 0; i < nrTotalProduse - nrProduse; i++)
			{
				if (preturiProduse[i] < 0) throw new exception("Preturile nu pot fi negative");
			}
			Depozit aux = *this;
			this->nrProduse = nrTotalProduse;
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
			this->produse = new string[this->nrProduse];
			this->cantitatiProduse = new int[this->nrProduse];
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < aux.nrProduse; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitatiProduse[i] = aux.cantitatiProduse[i];
				this->preturiProduse[i] = aux.preturiProduse[i];
			}
			int j = 0;
			for (int i = aux.nrProduse; i < this->nrProduse; i++)
			{
				this->produse[i] = produse[j];
				this->cantitatiProduse[i] = cantitatiProduse[j];
				this->preturiProduse[i] = preturiProduse[j];
				j++;
			}
		}
	}
	void getProduse()
	{
		for (int i = 0; i < this->nrProduse; i++)
			cout << "\n" << this->produse[i];
	}
	void setProduse(int nrProduse, string* produse, int* cantitatiProduse, int* preturiProduse)
	{
		if (this->nrProduse == 0) throw new exception("Numarul de produse nu poate fi 0");
		else if (produse == NULL || cantitatiProduse == NULL || preturiProduse == NULL) throw new exception("Produsele, cantitatile sau preturile nu pot fi nule");
		else {
			for (int i = 0; i < nrProduse; i++)
			{
				if (preturiProduse[i] < 0) throw new exception("Preturile nu pot fi negative");
			}
			Depozit aux = *this;
			this->nrProduse += nrProduse;
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
			this->produse = new string[this->nrProduse];
			this->cantitatiProduse = new int[this->nrProduse];
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < aux.nrProduse; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitatiProduse[i] = aux.cantitatiProduse[i];
				this->preturiProduse[i] = aux.preturiProduse[i];
			}
			int j = 0;
			for (int i = aux.nrProduse; i < this->nrProduse; i++)
			{
				this->produse[i] = produse[j];
				this->cantitatiProduse[i] = cantitatiProduse[j];
				this->preturiProduse[i] = preturiProduse[j];
				j++;
			}
		}
	}
	void getCantitati()
	{
		for (int i = 0; i < this->nrProduse; i++)
			cout << "\n" << this->produse[i] << " " << this->cantitatiProduse[i];
	}
	void setCantitati(string produs, int cantitateProdus)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == produs) this->cantitatiProduse[i] = cantitateProdus;
		}
	}
	void getPreturi()
	{
		for (int i = 0; i < this->nrProduse; i++)
			cout << "\n" << this->produse[i] << " " << this->preturiProduse[i];
	}
	void setPreturi(string produs, int pretProdus)
	{
		if (pretProdus < 0) throw new exception("Pretul nu poate fi negativ");
		else {
			for (int i = 0; i < this->nrProduse; i++)
			{
				if (this->produse[i] == produs) this->preturiProduse[i] = pretProdus;
			}
		}
	}
	int getNrMasini()
	{
		return this->nrMasini;
	}
	void setNrMasini(int nrMasini)
	{
		if (nrMasini > 10 || nrMasini < 0) throw new exception("Numarul de masini e in afara intervalului 0-10");
		else
			if (nrMasini < this->nrMasini)
			{
				this->nrMasini = nrMasini;
			}
			else
			{
				int aux = this->nrMasini;
				this->nrMasini = nrMasini;
				for (int i = aux; i < this->nrMasini; i++)
				{
					this->masiniDisponibile[i] = 1;
				}
			}
	}
	void getMasini()
	{
		for (int i = 0; i < this->nrMasini; i++)
			if (this->masiniDisponibile[i] == 0) cout << "\nMasina " << i + 1 << " nu este disponibila";
			else cout << "\nMasina " << i + 1 << " este disponibila";
	}
	void setMasini(int index, int disponibilitate)
	{
		if (disponibilitate != 0 && disponibilitate != 1) throw new exception("Alege intre 1 si 0");
		else this->masiniDisponibile[index] = disponibilitate;
	}
	void adaugaProdus(string produs, int cantitateProdus, int pretProdus)
	{
		if (pretProdus < 0) throw new exception("Pretul nu poate fi negativ");
		else 
		{
			Depozit aux = *this;
			this->nrProduse++;
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
			this->produse = new string[this->nrProduse];
			this->cantitatiProduse = new int[this->nrProduse];
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < aux.nrProduse; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitatiProduse[i] = aux.cantitatiProduse[i];
				this->preturiProduse[i] = aux.preturiProduse[i];
			}
			this->produse[this->nrProduse - 1] = produs;
			this->cantitatiProduse[this->nrProduse - 1] = cantitateProdus;
			this->preturiProduse[this->nrProduse - 1] = pretProdus;
		}
	}
	void stergeProdus(string produs)
	{
		Depozit aux = *this;
		int index = -1;
		for (int i = 0; i < this->nrProduse; i++)
		{
			cout << "\n" << this->produse[i];
			if (this->produse[i] == produs) index = i;
		}
		if (index != -1)
		{
			this->nrProduse--;
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
			this->produse = new string[this->nrProduse];
			this->cantitatiProduse = new int[this->nrProduse];
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < index; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitatiProduse[i] = aux.cantitatiProduse[i];
				this->preturiProduse[i] = aux.preturiProduse[i];
			}

			for (int i = index; i < this->nrProduse; i++)
			{
				this->produse[i] = aux.produse[i + 1];
				this->cantitatiProduse[i] = aux.cantitatiProduse[i + 1];
				this->preturiProduse[i] = aux.preturiProduse[i + 1];
			}
		}
		else cout << "Produsul nu exista";
	}
	void readFromText(fstream& f) {
		delete[] this->produse;
		delete[] this->cantitatiProduse;
		delete[] this->preturiProduse;
		f >> this->nrProduse;
		this->produse = new string[nrProduse];
		this->cantitatiProduse = new int[this->nrProduse];
		this->preturiProduse = new int[this->nrProduse];
		for (int i = 0; i <this->nrProduse; i++)
		{
			f >> this->produse[i];
			f >> this->cantitatiProduse[i];
			f >> this->preturiProduse[i];
			if (this->preturiProduse[i] < 0) this->preturiProduse[i] = 0;
		}
		f >> this->nrMasini;
		for (int i = 0; i < this->nrMasini; i++)
		{
			f >> this->masiniDisponibile[i];
			if (masiniDisponibile[i] != 0 && masiniDisponibile[i] != 1) masiniDisponibile[i] = 1;
		}
	}
	void readFromCSV(fstream& f) {
		vector <string> row;
		string line, word, temp;
		while (f >> temp)
		{
			row.clear();
			getline(f, line);
			stringstream s(line);
			while (getline(s, word, ',')) row.push_back(word);
			//parcurg tot vectorul cu un iterator si asamblez depozitul din ce e acolo.
		}
	}
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->nrProduse, sizeof(int));
		for (int i = 0; i < this->nrProduse; i++)
		{
			int lg = this->produse[i].length() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(this->produse[i].data(), lg);

			f.write((char*)&this->cantitatiProduse[i], sizeof(int));

			f.write((char*)&this->preturiProduse[i], sizeof(int));
		}
		f.write((char*)&this->nrMasini, sizeof(int));
		for (int i = 0; i < this->nrMasini; i++)
		{
			f.write((char*)&this->masiniDisponibile[i], sizeof(int));
		}
	}
	void readFromFile(fstream& f)
	{
		if (this->nrProduse != 0) {
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
		}
		f.read((char*)&this->nrProduse, sizeof(int));
		this->produse = new string[this->nrProduse];
		this->cantitatiProduse = new int[this->nrProduse];
		this->preturiProduse = new int[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			int lg;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			this->produse[i] = buffer;
			delete[] buffer;
			f.read((char*)&this->cantitatiProduse[i], sizeof(int));
			f.read((char*)&this->preturiProduse[i], sizeof(int));
		}
		f.read((char*)&this->nrMasini, sizeof(int));
		for (int i = 0; i < this->nrMasini; i++)
		{
			f.read((char*)&this->masiniDisponibile[i], sizeof(int));
		}
	}
	bool operator! ()
	{
		if (!nrProduse) return true;
		else return false;
	}
	explicit operator int()
	{
		int s = 1;
		for (int i = 0; i < this->nrProduse; i++)
		{
			s += this->cantitatiProduse[i] * this->preturiProduse[i];
		}
		return s;
	}
	bool operator==(Depozit d)
	{
		return (int)*this == (int)d;
	}
	bool operator< (Depozit d)
	{
		return (int)*this < (int)d;
	}
	Depozit& operator++()
	{
		if (this->nrMasini++ > 10) cout << "Prea multe masini";
		else {
			this->nrMasini++;
			this->masiniDisponibile[this->nrMasini - 1] = 1;
			return *this;
		}
	}
	Depozit& operator++(int)
	{
		Depozit aux;
		if (this->nrMasini++ > 10) cout << "Prea multe masini";
		else {
			this->nrMasini++;
			this->masiniDisponibile[this->nrMasini - 1] = 1;
		}
		return aux;
	}
	int operator[](string produs)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == produs) return this->cantitatiProduse[i];
		}
	}
	Depozit& operator + (const Depozit& d)
	{
		Depozit aux = *this;
		delete[] this->produse;
		delete[] this->cantitatiProduse;
		delete[] this->preturiProduse;
		this->nrProduse += d.nrProduse;
		this->produse = new string[this->nrProduse];
		this->cantitatiProduse = new int[this->nrProduse];
		this->preturiProduse = new int[this->nrProduse];
		for (int i = 0; i < aux.nrProduse; i++)
		{
			this->produse[i] = aux.produse[i];
			this->cantitatiProduse[i] = aux.cantitatiProduse[i];
			this->preturiProduse[i] = aux.preturiProduse[i];
		}
		int j = 0;
		for (int i = aux.nrProduse; i < this->nrProduse; i++)
		{
			this->produse[i] = d.produse[j];
			this->cantitatiProduse[i] = d.cantitatiProduse[j];
			this->preturiProduse[i] = d.preturiProduse[j];
			j++;
		}
		this->nrMasini = d.nrMasini;
		for (int i = 0; i < d.nrMasini; i++)
		{
			this->masiniDisponibile[i] = d.masiniDisponibile[i];
		}
		return *this;
	}
	Depozit& operator=(const Depozit& d)
	{
		if (this != &d) {
			delete[] this->produse;
			delete[] this->cantitatiProduse;
			delete[] this->preturiProduse;
			this->nrProduse = d.nrProduse;
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->produse[i] = d.produse[i];
			}
			this->cantitatiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->cantitatiProduse[i] = d.cantitatiProduse[i];
			}
			this->preturiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->preturiProduse[i] = d.preturiProduse[i];
			}
			this->nrMasini = d.nrMasini;
			for (int i = 0; i < this->nrMasini; i++)
			{
				this->masiniDisponibile[i] = d.masiniDisponibile[i];
			}
		}
		return *this;
	}
	~Depozit()
	{
		delete[] this->produse;
		delete[] this->cantitatiProduse;
		delete[] this->preturiProduse;
	}
	friend istream& operator>>(istream& in, Depozit& d)
	{
		delete[] d.produse;
		delete[] d.cantitatiProduse;
		delete[] d.preturiProduse;
		cout << "\nIntroduceti numarul de produse: ";
		in >> d.nrProduse;
		d.produse = new string[d.nrProduse];
		d.cantitatiProduse = new int[d.nrProduse];
		d.preturiProduse = new int[d.nrProduse];
		for (int i = 0; i < d.nrProduse; i++)
		{
			cout << "\nIntroduceti produsul " << i + 1<<":";
			in >> d.produse[i];
			cout << "\nIntroduceti stocul de produs " << i + 1 << ":";
			in >> d.cantitatiProduse[i];
			cout << "\nIntroduceti pretul produsului " << i + 1 << ":";
			in >> d.preturiProduse[i];
			if (d.preturiProduse[i] < 0) d.preturiProduse[i] = 0;
		}
		cout << "\nIntroduceti numarul de masini de livrare:";
		in >> d.nrMasini;
		for (int i = 0; i < d.nrMasini; i++)
		{
			cout << "\nIntroduceti disponibilitatea masinii " << i + 1 << " (0/1):";
			in >> d.masiniDisponibile[i];
			if (d.masiniDisponibile[i] != 0 && d.masiniDisponibile[i] != 1) d.masiniDisponibile[i] = 1;
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Depozit& d)
	{
		delete[] d.produse;
		delete[] d.cantitatiProduse;
		delete[] d.preturiProduse;
		in >> d.nrProduse;
		d.produse = new string[d.nrProduse];
		d.cantitatiProduse = new int[d.nrProduse];
		d.preturiProduse = new int[d.nrProduse];
		for (int i = 0; i < d.nrProduse; i++)
		{
			in >> d.produse[i];
			in >> d.cantitatiProduse[i];
			in >> d.preturiProduse[i];
			if (d.preturiProduse[i] < 0) d.preturiProduse[i] = 0;
		}
		in >> d.nrMasini;
		for (int i = 0; i < d.nrMasini; i++)
		{
			in >> d.masiniDisponibile[i];
			if (d.masiniDisponibile[i] != 0 && d.masiniDisponibile[i] != 1) d.masiniDisponibile[i] = 1;
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const Depozit& d)
	{
		out << "\n-------------------------";
		out << "\nNumarul de produse din depozit: " << d.nrProduse;
		out << "\nProdusele, preturile si cantitatile produselor din depozit sunt: ";
		for (int i = 0; i < d.nrProduse; i++)
		{
			out << "\n" << d.produse[i] << " " << d.preturiProduse[i] << " " << d.cantitatiProduse[i];
		}
		out << "\nNumarul de masini disponibile: "<<d.nrMasini;
		out << "\nDisponibilitatea masinilor este: ";
		for (int i = 0; i < d.nrMasini; i++)
		{
			out << d.masiniDisponibile[i] << " ";
		}
		out << "\n-------------------------";
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Depozit& d)
	{
		out << d.nrProduse << " ";
		for (int i = 0; i < d.nrProduse; i++)
		{
			out << d.produse[i] << " " << d.preturiProduse[i] << " " << d.cantitatiProduse[i] << " ";
		}
		out << d.nrMasini<< " ";
		for (int i = 0; i < d.nrMasini; i++)
		{
			out << d.masiniDisponibile[i] << " ";
		}
		return out;
	}
};
class DepozitFurnizor :public Depozit {
private:
	map<int, string> produseNoi;
	set<int> timpAsteptare;
public:
	DepozitFurnizor() :Depozit() {}
	DepozitFurnizor(int nrProduse, string* produse, int* cantitatiProduse, int* preturiProduse, int nrMasini, int masiniDisponibile[], map<int, string> produseNoi, set<int> timpAsteptare) :Depozit(nrProduse, produse, cantitatiProduse, preturiProduse, nrMasini, masiniDisponibile) {
		this->produseNoi = produseNoi;
		this->timpAsteptare = timpAsteptare;
	}

};
class Comenzi : public InputFile, public BinaryFile {
private:
	const int idComanda;
	int nrProduse = 0;
	string* produse = NULL;
	int cantitati[100] = {};
	static int id;
	friend class Client;
public:
	Comenzi() : idComanda(id++) {}
	Comenzi(int idComanda, int nrProduse, string* produse, int cantitati[]) :idComanda(idComanda)
	{
		this->nrProduse = nrProduse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->produse[i] = produse[i];
		}
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->cantitati[i] = cantitati[i];
		}
	}
	Comenzi(int nrProduse, string* produse, int cantitati[]) :idComanda(id++)
	{
		this->nrProduse = nrProduse;
		if (this->nrProduse > 0)
		{
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->cantitati[i] = cantitati[i];
			}
		}
		else throw new exception("Comanda trebuie sa contina minim un produs");
	}
	Comenzi(const Comenzi& c) :idComanda(c.idComanda)
	{
		this->nrProduse = c.nrProduse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->produse[i] = c.produse[i];
		}
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->cantitati[i] = c.cantitati[i];
		}
	}
	Comenzi& operator=(const Comenzi& c)
	{
		if (this != &c)
		{
			delete[] this->produse;
			this->nrProduse = c.nrProduse;
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->produse[i] = c.produse[i];
			}
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->cantitati[i] = c.cantitati[i];
			}
		}
		return *this;
	}
	int getIdComanda()
	{
		return this->idComanda;
	}
	static int getId()
	{
		return Comenzi::id;
	}
	static void setId(int nr)
	{
		Comenzi::id = nr;
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}
	void setNrProduse(int nrTotalProduse, string* produse, int* cantitatiProduse)
	{
		if (nrTotalProduse > 0)
		{
			Comenzi aux = *this;
			this->nrProduse = nrTotalProduse;
			delete[] this->produse;
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < aux.nrProduse; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitati[i] = aux.cantitati[i];
			}
			int j = 0;
			for (int i = aux.nrProduse; i < this->nrProduse; i++)
			{
				this->produse[i] = produse[j];
				this->cantitati[i] = cantitati[j];
				j++;
			}
		}
	}
	void getProduse()
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			cout << this->produse[i] << " ";
		}
	}
	void setProduse(int nrProduse, string* produse, int* cantitatiProduse)
	{
		if (nrProduse > 0)
		{
			Comenzi aux = *this;
			this->nrProduse += nrProduse;
			if (aux.nrProduse < this->nrProduse)
			{
				delete[] this->produse;
				this->produse = new string[this->nrProduse];
				for (int i = 0; i < aux.nrProduse; i++)
				{
					this->produse[i] = aux.produse[i];
					this->cantitati[i] = aux.cantitati[i];
				}
				int j = 0;
				for (int i = aux.nrProduse; i < this->nrProduse; i++)
				{
					this->produse[i] = produse[j];
					this->cantitati[i] = cantitatiProduse[j];
					j++;
				}
			}
		}
	}
	void getCantitati()
	{
		for (int i = 0; i < this->nrProduse; i++)
			cout << "\n" << this->produse[i] << " " << this->cantitati[i];
	}
	void setCantitati(string produs, int cantitate)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == produs) this->cantitati[i] = cantitate;
		}
	}
	void adaugaProdus(string produs, int cantitate)
	{
		Comenzi aux = *this;
		this->nrProduse++;
		delete[] this->produse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < aux.nrProduse; i++)
		{
			this->produse[i] = aux.produse[i];
			this->cantitati[i] = aux.cantitati[i];
		}
		this->produse[this->nrProduse - 1] = produs;
		this->cantitati[this->nrProduse - 1] = cantitate;
	}
	void stergeProdus(string produs)
	{
		Comenzi aux = *this;
		int index = -1;
		for (int i = 0; i < this->nrProduse; i++)
		{
			cout << "\n" << this->produse[i];
			if (this->produse[i] == produs) index = i;
		}
		if (index != -1)
		{
			this->nrProduse--;
			delete[] this->produse;
			this->produse = new string[this->nrProduse];
			for (int i = 0; i < index; i++)
			{
				this->produse[i] = aux.produse[i];
				this->cantitati[i] = aux.cantitati[i];
			}

			for (int i = index; i < this->nrProduse; i++)
			{
				this->produse[i] = aux.produse[i + 1];
				this->cantitati[i] = aux.cantitati[i + 1];
			}
		}
		else cout << "Produsul nu exista";
	}
	void readFromText(fstream& f) {
		delete[] this->produse;
		f >> this->nrProduse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			f >> this->produse[i];
			f >> this->cantitati[i];
		}
	}
	void readFromCSV(fstream& f) {
		//to do
	}
	void writeToFile(fstream& f)
	{	
		f.write((char*)&this->nrProduse, sizeof(int));
		for (int i = 0; i < this->nrProduse; i++)
		{
			int lg = this->produse[i].length() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(this->produse[i].data(), lg);

			f.write((char*)&this->cantitati[i], sizeof(int));
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->produse;
		f.read((char*)&this->nrProduse, sizeof(int));
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			int lg;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			this->produse[i] = buffer;
			delete[] buffer;
			f.read((char*)&this->cantitati[i], sizeof(int));
		}
	}
	bool operator==(const Comenzi& c)
	{
		if (this->nrProduse != c.nrProduse) return false;
		else {
			int k = 0;
			for (int i = 0; i < this->nrProduse; i++)
			{
				int ok = -1;
				for (int j = 0; j < this->nrProduse; j++) {
					if (this->produse[i] == c.produse[j] && this->cantitati[j] == c.cantitati[j]) ok = i;
				}
				if (ok != -1) k++;
			}

			if (k == this->nrProduse) return true;
			else return false;
		}
	}
	bool operator<(Comenzi c)
	{
		return (int)this < (int)c;
	}
	bool operator! ()
	{
		if (!this->nrProduse) return true;
		else return false;
	}
	explicit operator int()
	{
		int s = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			s += this->cantitati[i];
		}
		return s;
	}
	Comenzi& operator++ ()
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->cantitati[i]++;
		}
		return *this;
	}
	Comenzi operator++ (int)
	{
		Comenzi aux;
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->cantitati[i]++;
		}
		return aux;
	}
	Comenzi& operator + (const Comenzi& c)
	{
		Comenzi aux = *this;
		delete[] this->produse;
		this->nrProduse += c.nrProduse;
		this->produse = new string[this->nrProduse];
		for (int i = 0; i < aux.nrProduse; i++)
		{
			this->produse[i] = aux.produse[i];
			this->cantitati[i] = aux.cantitati[i];
		}
		int j = 0;
		for (int i = aux.nrProduse; i < this->nrProduse; i++)
		{
			this->produse[i] = c.produse[j];
			this->cantitati[i] = c.cantitati[j];
			j++;
		}
		return *this;
	}
	void operator[](string produs)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == produs) cout << "\n" << this->produse[i] <<  this->cantitati[i];
		}
	}
	~Comenzi()
	{
		delete[] this->produse;
	}
	friend istream& operator>>(istream& in, Comenzi& c)
	{
		delete[] c.produse;
		cout << "\nIntroduceti numarul de produse: ";
		in >> c.nrProduse;
		if (c.nrProduse <= 0)
		{
			c.nrProduse = 0;
			c.produse = NULL;
		}
		else
		{
			c.produse = new string[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				cout << "\nIntroduceti produsul " << i + 1 << ":";
				in >> c.produse[i];
				cout << "\nIntroduceti cantitatea de produs " << i + 1 << ": ";
				in >> c.cantitati[i];
			}
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Comenzi& c)
	{
		delete[] c.produse;
		in >> c.nrProduse;
		if (c.nrProduse <= 0)
		{
			c.nrProduse = 0;
			c.produse = NULL;
		}
		else
		{
			c.produse = new string[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				in >> c.produse[i];
				in >> c.cantitati[i];
			}
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const Comenzi& c)
	{
		out << "\n---------------------";
		out << "\nId-ul comenzii este: " << c.idComanda;
		out << "\nNumarul de produse din comanda este: " << c.nrProduse;
		out << "\nProdusele si cantitatile din comanda sunt: ";
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << "\n" << c.produse[i] << " " << c.cantitati[i];
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Comenzi& c)
	{
		out << c.idComanda<<" ";
		out << c.nrProduse<<" ";
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << c.produse[i] << " " << c.cantitati[i]<< " ";
		}
		return out;
	}
};
int Comenzi::id = 1;
class ComandaSpeciala :public Comenzi {
private:
	list<int> listaReduceri;
public:
	ComandaSpeciala() :Comenzi() {}
	ComandaSpeciala(const Comenzi& c, list<int>listaReduceri) :Comenzi(c){
		this->listaReduceri = listaReduceri;
	}
};
class Angajati : public InputFile, public BinaryFile{
	char* nume;
	char* prenume;
	int varsta = 0;
	int salariu = 0;
	int vechime = 0;
	int oreLucru = 0;
	int nrComenzi = 0;
	Comenzi* listaComenzi[10] = {};
	friend class Comenzi;
public:
	Angajati() 
	{
		this->nume = new char[strlen("anonim") + 1];
		strcpy(this->nume, "anonim");
		this->prenume = new char[strlen("anonim") + 1];
		strcpy(this->prenume, "anonim");
	}
	Angajati(char* nume, char* prenume, int varsta, int salariu, int vechime, int oreLucru, int nrComenzi, Comenzi* listaComenzi[10])
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->prenume = new char[strlen(prenume) + 1];
		strcpy(this->prenume, prenume);
		if (varsta < 16) throw new exception("Varsta este prea mica");
		if (salariu < 0) throw new exception("Salariul nu poate fi negativ");
		if (vechime < 0) throw new exception("Vechimea nu poate fi negativa");
		if (oreLucru < 0) throw new exception("Orele de lucru nu pot fi negative");
		this->varsta = varsta;
		this->salariu = salariu;
		this->vechime = vechime;
		this->oreLucru = oreLucru;
		this->nrComenzi = nrComenzi;
		if (nrComenzi > 0)
		{
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*listaComenzi[i]);
			}
		}
		else if (nrComenzi > 10) throw new exception("Un angajat nu poate avea mai mult de 10 comenzi concomitent");
		else throw new exception("Numarul de comenzi nu poate fi negativ");
	}
	Angajati(const Angajati& a)
	{
		this->nume = new char[strlen(a.nume) + 1];
		strcpy(this->nume, a.nume);
		this->prenume = new char[strlen(a.prenume) + 1];
		strcpy(this->prenume, a.prenume);
		this->varsta = a.varsta;
		this->salariu = a.salariu;
		this->vechime = a.vechime;
		this->oreLucru = a.oreLucru;
		this->nrComenzi = a.nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*a.listaComenzi[i]);
		}
	}
	char* getNume()
	{
		return this->nume;
	}
	void setNume(char* nume)
	{
		if (nume != NULL)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			this->nume = nume;
		}
	}
	char* getPrenume()
	{
		return this->prenume;
	}
	void setPrenume(char* prenume)
	{
		if (prenume != NULL)
		{
			delete[] this->prenume;
			this->prenume = new char[strlen(prenume) + 1];
			this->prenume = prenume;
		}
	}
	int getVarsta()
	{
		return this->varsta;
	}
	void setVarsta(int varsta)
	{
		if (varsta > 16)
		{
			this->varsta = varsta;
		}
	}
	int getSalariu()
	{
		return this->salariu;
	}
	void setSalariu(int salariu)
	{
		if (salariu > 0)
		{
			this->salariu = salariu;
		}
	}
	int getVechime()
	{
		return this->vechime;
	}
	void setVechime(int vechime)
	{
		if (vechime > this->vechime)
		{
			this->vechime = vechime;
		}
	}
	int getOreLucru()
	{
		return this->oreLucru;
	}
	void setOreLucru(int oreLucru)
	{
		if (oreLucru > 0)
		{
			this->oreLucru = oreLucru;
		}
	}
	int getNrComenzi()
	{
		return this->nrComenzi;
	}
	void setNrComenzi(int nrTotalComenzi, Comenzi* listaComenzi[])
	{
		if (nrTotalComenzi == 0)
		{
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->listaComenzi[i];
			}
		}
		else if (nrTotalComenzi > 0)
		{
			Angajati aux = *this;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->listaComenzi[i];
			}
			this->nrComenzi = nrTotalComenzi;
			for (int i = 0; i < aux.nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
			}
			int j = 0;
			for (int i = aux.nrComenzi; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*listaComenzi[j]);
				j++;
			}
		}
	}
	void getComenzi()
	{
		for (int i = 0; i < this->nrComenzi; i++)
			cout << *listaComenzi[i];

	}
	void setComenzi(int nrComenzi, Comenzi* listaComenzi[])
	{
		Angajati aux = *this;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
		}
		this->nrComenzi += nrComenzi;
		for (int i = 0; i < aux.nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
		}
		int j = 0;
		for (int i = aux.nrComenzi; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*listaComenzi[j]);
			j++;
		}
	}
	void adaugaComanda(Comenzi* comanda)
	{
		Angajati aux = *this;
		for(int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
		}
		this->nrComenzi++;
		for (int i = 0; i < aux.nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
		}
		listaComenzi[this->nrComenzi - 1] = new Comenzi(*comanda);
	}
	void stergeComanda(int idComanda)
	{
		Angajati aux = *this;
		int index = operator[](idComanda);
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete listaComenzi[i];
		}
		this->nrComenzi--;
		for (int i = 0; i < index; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
		}
		for (int i = index; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i + 1]);
		}
	}
	void readFromText(fstream& f)
	{
		delete[] this->nume;
		delete[] this->prenume;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
		}
		char aux[20], aux1[20];
		f >> aux;
		this->nume = new char[strlen(aux) + 1];
		strcpy(this->nume, aux);
		f >> aux1;
		this->prenume = new char[strlen(aux1) + 1];
		strcpy(this->prenume, aux1);
		f >> this->varsta;
		f >> this->vechime;
		f >> this->oreLucru;
		f >> this->nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi;
		}
		for (int i = 0; i < this->nrComenzi; i++)
		{
			f >> (*listaComenzi[i]);
		}
	}
	void readFromCSV(fstream& f)
	{
		//to do pe baza la ofstream;
	}
	void writeToFile(fstream& f)
	{
		int lg = strlen(this->nume) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume, lg);
		lg = strlen(this->prenume) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->prenume, lg);
		f.write((char*)&this->varsta, sizeof(int));
		f.write((char*)&this->salariu, sizeof(int));
		f.write((char*)&this->vechime, sizeof(int));
		f.write((char*)&this->oreLucru, sizeof(int));
		f.write((char*)&this->nrComenzi, sizeof(int));
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i]->writeToFile(f);
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->nume;
		delete[] this->prenume;
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->nume = buffer;
		delete[] buffer;

		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->prenume = buffer;
		delete[] buffer;

		f.read((char*)&this->varsta, sizeof(int));
		f.read((char*)&this->salariu, sizeof(int));
		f.read((char*)&this->vechime, sizeof(int));
		f.read((char*)&this->oreLucru, sizeof(int));
		f.read((char*)&this->nrComenzi, sizeof(int));
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete listaComenzi[i];
			this->listaComenzi[i] = new Comenzi;
			this->listaComenzi[i]->readFromFile(f);
		}
	}
	Angajati& operator++ ()
	{
		this->vechime++;
		return *this;
	}
	Angajati& operator++ (int)
	{
		Angajati a = *this;
		this->vechime++;
		return a;
	}
	explicit operator int()
	{
		return this->salariu;
	}
	bool operator!()
	{
		if (this->nrComenzi) return false;
		else return true;
	}
	bool operator<(Angajati a)
	{
		return (int)this < (int)a;
	}
	bool operator==(const Angajati& a)
	{
		if (this->nrComenzi != a.nrComenzi) return false;
		else {
			int k = 0;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				int ok = -1;
				for (int j = 0; j < this->nrComenzi; j++) {
					if (this->listaComenzi[i] == a.listaComenzi[j]) ok = i;
				}
				if (ok != -1) k++;
			}

			if (k == this->nrComenzi) return true;
			else return false;
		}
	}
	Angajati& operator+(int oreSuplimentare)
	{
		this->oreLucru += oreSuplimentare;
		return *this;
	}
	int operator[](int idComanda)
	{
		for (int i = 0; i < this->nrComenzi; i++)
			if (listaComenzi[i]->getIdComanda() == idComanda) return i;
	}
	Angajati& operator=(const Angajati& a)
	{
		if (this != &a)
		{
			delete[] this->nume;
			delete[] this->prenume;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete listaComenzi[i];
			}
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
			this->prenume = new char[strlen(a.prenume) + 1];
			strcpy(this->prenume, a.prenume);
			this->varsta = a.varsta;
			this->salariu = a.salariu;
			this->vechime = a.vechime;
			this->oreLucru = a.oreLucru;
			this->nrComenzi = a.nrComenzi;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*a.listaComenzi[i]);
			}
		}
		return *this;
	}
	~Angajati() {
		delete[] this->nume;
		delete[] this->prenume;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete listaComenzi[i];
		}
	}
	friend istream& operator>>(istream& in, Angajati& a)
	{
		delete[] a.nume;
		delete[] a.prenume;
		for (int i = 0; i < a.nrComenzi; i++)
		{
			delete a.listaComenzi[i];
		}
		char aux[20], aux1[20];
		cout << "\nNume: ";
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		cout << "\nPrenume: ";
		in >> aux1;
		a.prenume = new char[strlen(aux1) + 1];
		strcpy(a.prenume, aux1);
		cout << "\nVarsta: ";
		in >> a.varsta;
		cout << "\nVechime: ";
		in >> a.vechime;
		cout << "\nOre de lucru: ";
		in >> a.oreLucru;
		cout << "\nNumar Comenzi: ";
		in >> a.nrComenzi;
		if (a.nrComenzi <= 0) a.nrComenzi = 0;
		else {
			for (int i = 0; i < a.nrComenzi; i++)
			{
				a.listaComenzi[i] = new Comenzi;
			}
			for (int i = 0; i < a.nrComenzi; i++)
			{
				in >> (*a.listaComenzi[i]);
			}
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Angajati& a)
	{
		delete[] a.nume;
		delete[] a.prenume;
		for (int i = 0; i < a.nrComenzi; i++)
		{
			delete a.listaComenzi[i];
		}
		char aux[20];
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		in >> aux;
		a.prenume = new char[strlen(aux) + 1];
		strcpy(a.prenume, aux);
		in >> a.varsta;
		in >> a.vechime;
		in >> a.oreLucru;
		in >> a.nrComenzi;
		if (a.nrComenzi <= 0) a.nrComenzi = 0;
		else {
			for (int i = 0; i < a.nrComenzi; i++)
			{
				a.listaComenzi[i] = new Comenzi;
			}
			for (int i = 0; i < a.nrComenzi; i++)
			{
				in >> (*a.listaComenzi[i]);
			}
		}
		cout << a.nume;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Angajati& a)
	{
		out << "\n---------------------";
		out << "\nNumele angajatului este " << a.nume << " " << a.prenume;
		out << "\nVarsta angajatului este " << a.varsta;
		out << "\nSalariul angajatului este " << a.salariu;
		out << "\nVechimea angajatului este " << a.vechime;
		out << "\nProgramul angajatului are " << a.oreLucru << " ore de lucru";
		out << "\nAngajatul are " << a.nrComenzi << " comenzi";
		out << "\nComenzile angajatului sunt:";
		for (int i = 0; i < a.nrComenzi; i++)
		{
			out <<"\n"<<*a.listaComenzi[i];
		}
		out << "\n---------------------";
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Angajati& a)
	{
		out << a.nume << " " << a.prenume<<" ";
		out << a.varsta << " ";
		out << a.salariu<< " ";
		out << a.vechime<< " ";
		out << a.oreLucru << " ";
		out << a.nrComenzi << " ";
		for (int i = 0; i < a.nrComenzi; i++)
		{
			out << *a.listaComenzi[i]<< " ";
		}
		return out;
	}
};
class Client : public InputFile, public BinaryFile {
private:
	string nume = "Anonim";
	string prenume = "Anonim";
	string email = "Anonim";
	char* telefon = NULL;
	int nrComenzi = 0;
	Comenzi* listaComenzi[10] = {};
public:
	Client() {
		this->telefon = new char[strlen("necunoscut") + 1];
		strcpy(this->telefon, "necunoscut");
	}
	Client(string nume, string prenume, string email, char* telefon, int nrComenzi, Comenzi* listaComenzi[10])
	{
		this->nume = nume;
		this->prenume = prenume;
		this->email = email;
		if (strlen(telefon) != 10) throw new exception("Numarul de telefon trebuie sa aiba 10 cifre");
		else {
			this->telefon = new char[11];
			strcpy(this->telefon, telefon);
		}
		this->nrComenzi = nrComenzi;
		if (this->nrComenzi <= 0) this->nrComenzi = 0;
		else {
			for (int i = 0; i < nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*listaComenzi[i]);
			}
		}
	}
	Client(const Client& c)
	{
		this->nume = c.nume;
		this->prenume = c.prenume;
		this->email = c.email;
		this->telefon = new char[11];
		strcpy(this->telefon, c.telefon);
		this->nrComenzi = c.nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*c.listaComenzi[i]);
		}
	}
	string getNume()
	{
		return this->nume;
	}
	void setNume(string nume)
	{
		if (nume.length()!= 0)
			this->nume = nume;
	}
	string getPrenume()
	{
		return this->prenume;
	}
	void setPrenume(string prenume)
	{
		if (prenume.length() != 0)
			this->prenume = prenume;
	}
	string getEmail()
	{
		return this->email;
	}
	void setEmail(string email)
	{
		if (email.length() != 0)
			this->email = email;
	}
	char* getTelefon()
	{
		return this->telefon;
	}
	void setTelefon(char* telefon)
	{
		if (telefon != NULL && strlen(telefon) == 10)
		{
			delete[] this->telefon;
			this->telefon = new char[strlen(telefon) + 1];
			strcpy(this->telefon, telefon);
		}
	}
	int getNrComenzi()
	{
		return this->nrComenzi;
	}
	void setNrComenzi(int nrTotalComenzi, Comenzi* listaComenzi[])
	{
		if (nrTotalComenzi > 0)
		{
			Client aux = *this;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->listaComenzi[i];
			}
			this->nrComenzi = nrTotalComenzi;
			for (int i = 0; i < aux.nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
			}
			int j = 0;
			for (int i = aux.nrComenzi; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*listaComenzi[j]);
				j++;
			}
		}
		else if (nrTotalComenzi == 0)
		{
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->listaComenzi[i];
			}
			this->nrComenzi = nrTotalComenzi;
		}
	}
	void getComenzi()
	{
		for (int i = 0; i < this->nrComenzi; i++)
			cout << *listaComenzi[i];

	}
	void setComenzi(int nrComenzi, Comenzi* listaComenzi[])
	{
		if (nrComenzi > 0)
		{
			Client aux = *this;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->listaComenzi[i];
			}
			this->nrComenzi += nrComenzi;
			for (int i = 0; i < aux.nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
			}
			int j = 0;
			for (int i = aux.nrComenzi; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*listaComenzi[j]);
				j++;
			}
		}
	}
	void adaugaComanda(Comenzi* comanda)
	{
		Client aux = *this;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
		}
		this->nrComenzi++;
		for (int i = 0; i < aux.nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
		}
		listaComenzi[this->nrComenzi - 1] = new Comenzi(*comanda);
	}
	void stergeComanda(int idComanda)
	{
		Client aux = *this;
		int index = operator[](idComanda);
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete listaComenzi[i];
		}
		this->nrComenzi--;
		for (int i = 0; i < index; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i]);
		}
		for (int i = index; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi(*aux.listaComenzi[i + 1]);
		}
	}
	void readFromText(fstream& f)
	{
		delete[] this->telefon;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
		}
		f >> this->nume;
		f >> this->prenume;
		f >> this->email;
		this->telefon = new char[11];
		f >> this->telefon;
		f >> this->nrComenzi;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i] = new Comenzi;
		}
		for (int i = 0; i < this->nrComenzi; i++)
		{
			f >> (*this->listaComenzi[i]);
		}
	}
	void readFromCSV(fstream& f)
	{
		//to do pe baza la ostream
	}
	void writeToFile(fstream& f)
	{
		int lg = this->nume.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume.data(), lg);

		lg = this->prenume.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->prenume.data(), lg);

		lg = this->email.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->email.data(), lg);

		lg = strlen(this->telefon) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->telefon, lg);

		f.write((char*)&this->nrComenzi, sizeof(int));
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listaComenzi[i]->writeToFile(f);
		}
	}
	void readFromFile(fstream& f)
	{
		delete[] this->telefon;

		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->nume = buffer;
		delete[] buffer;

		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->prenume = buffer;
		delete[] buffer;

		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->email = buffer;
		delete[] buffer;
		
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		char* telefon = new char[lg];
		f.read(buffer, lg);
		for (int i = 0; i < lg; i++)
		{
			telefon[i] = buffer[i];
		}
		delete[] buffer;

		f.read((char*)&this->nrComenzi, sizeof(int));
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->listaComenzi[i];
			this->listaComenzi[i] = new Comenzi;
			this->listaComenzi[i]->readFromFile(f);
		}
	}
	Client& operator+(string email)
	{
		this->email = email;
		return *this;
	}
	Client& operator++ ()
	{
		for (int i = 0; i < nrComenzi; i++)
		{
			for (int j = 0; j < listaComenzi[i]->getNrProduse(); j++)
			{
				listaComenzi[i]->cantitati[j]++;
			}
		}
		return *this;
	}
	Client& operator++ (int)
	{
		Client c = *this;
		for (int i = 0; i < nrComenzi; i++)
		{
			for (int j = 0; j < listaComenzi[i]->getNrProduse(); j++)
			{
				listaComenzi[i]->cantitati[j]++;
			}
		}
		return c;
	}
	bool operator< (Client c)
	{
		return (int)this < (int)c;
	}
	operator int()
	{
		int s = 0;
		for (int i = 0; i < nrComenzi; i++)
		{
			s += (int)listaComenzi[i];
		}
		return s;
	}
	int operator[](int idComanda)
	{
		for (int i = 0; i < this->nrComenzi; i++)
			if (listaComenzi[i]->getIdComanda() == idComanda) return i;
	}
	bool operator==(const Client& a)
	{
		if (this->nrComenzi != a.nrComenzi) return false;
		else {
			int k = 0;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				int ok = -1;
				for (int j = 0; j < this->nrComenzi; j++) {
					if (this->listaComenzi[i] == a.listaComenzi[j]) ok = i;
				}
				if (ok != -1) k++;
			}

			if (k == this->nrComenzi) return true;
			else return false;
		}
	}
	bool operator!()
	{
		if (this->nrComenzi) return false;
		else return true;
	}
	Client& operator= (const Client& c)
	{
		if (this != &c)
		{
			delete[] this->telefon;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete listaComenzi[i];
			}
			this->nume = c.nume;
			this->prenume = c.prenume;
			this->email = c.email;
			this->telefon = new char[11];
			strcpy(this->telefon, c.telefon);
			this->nrComenzi = c.nrComenzi;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->listaComenzi[i] = new Comenzi(*c.listaComenzi[i]);
			}
		}
		return *this;
	}
	~Client() {
		delete[] this->telefon;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete listaComenzi[i];
		}
	}
	friend istream& operator>> (istream& in, Client& c)
	{
		delete[] c.telefon;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			delete c.listaComenzi[i];
		}
		cout << "\nNume: ";
		in >> c.nume;
		cout << "\nPrenume: ";
		in >> c.prenume;
		cout << "\nEmail: ";
		in >> c.email;
		c.telefon = new char[11];
		cout << "\nTelefon: ";
		in >> c.telefon;
		cout << "Numarul de comenzi: ";
		in >> c.nrComenzi;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			c.listaComenzi[i] = new Comenzi;
		}
		for (int i = 0; i < c.nrComenzi; i++)
		{
			in >> (*c.listaComenzi[i]);
		}
		return in;
	}
	friend ifstream& operator>> (ifstream& in, Client& c)
	{
		delete[] c.telefon;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			delete c.listaComenzi[i];
		}
		in >> c.nume;
		in >> c.prenume;
		in >> c.email;
		c.telefon = new char[11];
		in >> c.telefon;
		in >> c.nrComenzi;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			c.listaComenzi[i] = new Comenzi;
		}
		for (int i = 0; i < c.nrComenzi; i++)
		{
			in >> (*c.listaComenzi[i]);
		}
		return in;
	}
	friend ostream& operator<< (ostream& out, const Client& c)
	{
		out << "\n-------------------";
		out << "\nNumele clientului este " << c.nume << " " << c.prenume;
		out << "\nEmail-ul clientului este: " << c.email;
		out << "\nNumarul de telefon al clientului este: " << c.telefon;
		out << "\nNumarul de comenzi ale clientulului este " << c.nrComenzi;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			out << "\n" << *c.listaComenzi[i];
		}
		out << "\n-------------------";
		return out;
	}
	friend ofstream& operator<< (ofstream& out, const Client& c)
	{
		out << c.nume << " " << c.prenume << " ";
		out << c.email << " ";
		out << c.telefon << " ";
		out << c.nrComenzi << " ";
		for (int i = 0; i < c.nrComenzi; i++)
		{
			out << *c.listaComenzi[i] << " ";
		}
		return out;
	}
};
class Magazin : public Depozit
{
private:
	string adresa = "Necunoscut";
	int nrClienti = 0;
	int nrAngajati = 0;
	Client** listaClienti = NULL;
	Angajati** listaAngajati = NULL;
	friend class Comenzi;
	friend class Client;
public:
	Magazin() {};
	Magazin(int nrProduse, string* produse, int* cantitatiProduse, int* preturiProduse, int nrMasini, int masiniDisponibile[5], string adresa, int nrClienti, int nrAngajati, Client** listaClienti, Angajati** listaAngajati) :Depozit(nrProduse, produse, cantitatiProduse, preturiProduse, nrMasini, masiniDisponibile)
	{
		this->adresa = adresa;
		this->nrClienti = nrClienti;
		this->nrAngajati = nrAngajati;
		if (this->nrClienti <= 0)
		{
			this->listaClienti = NULL;
			this->nrClienti = 0;
		}
		else {
			this->listaClienti = new Client * [this->nrClienti];
			for (int i = 0; i < this->nrClienti; i++)
			{
				this->listaClienti[i] = new Client(*listaClienti[i]);
			}
		}
		if (this->nrAngajati <= 0)
		{
			this->nrAngajati = NULL;
			this->nrAngajati = 0;
		}
		else
		{
			this->listaAngajati = new Angajati * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
			{
				this->listaAngajati[i] = new Angajati(*listaAngajati[i]);
			}
		}
	}
	Magazin(const Depozit& d, string adresa, int nrClienti, int nrAngajati, Client** listaClienti, Angajati** listaAngajati) :Depozit(d)
	{
		this->adresa = adresa;
		this->nrClienti = nrClienti;
		this->nrAngajati = nrAngajati;
		if (this->nrClienti <= 0)
		{
			this->nrClienti = 0;
			this->listaClienti = NULL;
		}
		else {
			this->listaClienti = new Client * [this->nrClienti];
			for (int i = 0; i < this->nrClienti; i++)
			{
				this->listaClienti[i] = new Client(*listaClienti[i]);
			}
		}
		if (this->nrAngajati <= 0)
		{
			this->nrAngajati = 0;
			this->listaAngajati = NULL;
		}
		else
		{
			this->listaAngajati = new Angajati * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
			{
				this->listaAngajati[i] = new Angajati(*listaAngajati[i]);
			}
		}
	}
	Magazin(const Magazin& m):Depozit(m)
	{
		this->nrAngajati = m.nrAngajati;
		this->listaAngajati = new Angajati * [this->nrAngajati];
		this->adresa = m.adresa;
		this->nrClienti = m.nrClienti;
		this->listaClienti = new Client * [this->nrClienti];
		for (int i = 0; i < this->nrClienti; i++)
		{
			this->listaClienti[i] = new Client(*m.listaClienti[i]);
		}
		this->listaAngajati = new Angajati * [this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->listaAngajati[i] = new Angajati(*m.listaAngajati[i]);
		}
	}
	string getAdresa()
	{
		return this->adresa;
	}
	void setAdresa(string adresa)
	{
		if (adresa.length() != 0)
			this->adresa = adresa;
	}
	int getNrClienti()
	{
		return this->nrClienti;
	}
	void setNrClienti(int nrClienti, Client** listaClienti)
	{
		if (nrClienti > 0)
		{
			int nrAux = this->nrClienti;
			Client** listaAux;
			listaAux = new Client * [this->nrClienti];
			for (int i = 0; i < this->nrClienti; i++)
			{
				listaAux[i] = new Client(*this->listaClienti[i]);
			}
			for (int i = 0; i < this->nrClienti; i++)
			{
				delete this->listaClienti[i];
			}
			delete[] this->listaClienti;
			this->nrClienti = nrClienti;
			this->listaClienti = new Client * [this->nrClienti];
			for (int i = 0; i < nrAux; i++)
			{
				this->listaClienti[i] = new Client(*listaAux[i]);
			}
			int j = 0;
			for (int i = nrAux; i < this->nrClienti; i++)
			{
				this->listaClienti[i] = listaClienti[j];
				j++;
			}
		}
		else if (nrClienti == 0)
		{
			this->nrClienti = nrClienti;
			for (int i = 0; i < this->nrClienti; i++)
			{
				delete this->listaClienti[i];
			}
			delete[] this->listaClienti;
		}
	}
	void getClienti()
	{
		for (int i = 0; i < this->nrClienti; i++)
		{
			cout << *this->listaClienti[i] << "\n";
		}
	}
	void setClienti(int nrClienti, Client* listaClienti[])
	{
		if (nrClienti >= 0)
		{
			int nrAux = this->nrClienti;
			Client** listaAux;
			listaAux = new Client * [this->nrClienti];
			for (int i = 0; i < this->nrClienti; i++)
			{
				listaAux[i] = new Client(*this->listaClienti[i]);
			}
			for (int i = 0; i < this->nrClienti; i++)
			{
				delete this->listaClienti[i];
			}
			delete[] this->listaClienti;
			this->nrClienti += nrClienti;
			this->listaClienti = new Client * [this->nrClienti];
			for (int i = 0; i < nrAux; i++)
			{
				this->listaClienti[i] = new Client(*listaAux[i]);
			}
			int j = 0;
			for (int i = nrAux; i < this->nrClienti; i++)
			{
				this->listaClienti[i] = listaClienti[j];
				j++;
			}
		}
	}
	int getNrAngajati()
	{
		return this->nrAngajati;
	}
	void setNrAngajati(int nrAngajati, Angajati** listaAngajati)
	{
		if (nrAngajati > 0)
		{
			int nrAux = this->nrAngajati;
			Angajati** listaAux;
			listaAux = new Angajati * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
			{
				listaAux[i] = new Angajati(*this->listaAngajati[i]);
			}
			for (int i = 0; i < this->nrAngajati; i++)
			{
				delete this->listaAngajati[i];
			}
			delete[] this->listaAngajati;
			this->nrAngajati = nrAngajati;
			this->listaAngajati = new Angajati * [this->nrAngajati];
			for (int i = 0; i < nrAux; i++)
			{
				this->listaAngajati[i] = new Angajati(*listaAux[i]);
			}
			int j = 0;
			for (int i = nrAux; i < this->nrAngajati; i++)
			{
				this->listaAngajati[i] = listaAngajati[j];
				j++;
			}
		}
		else if (nrAngajati == 0)
		{
			for (int i = 0; i < this->nrAngajati; i++)
			{
				delete this->listaAngajati[i];
			}
			delete[] this->listaAngajati;
			this->nrAngajati = nrAngajati;
		}
	}
	void getAngajati()
	{
		for (int i = 0; i < this->nrAngajati; i++)
		{
			cout << this->listaAngajati[i] << "\n";
		}
	}
	void setAngajati(int nrAngajati, Angajati** listaAngajati)
	{
		if (nrAngajati >= 0)
		{
			int nrAux = this->nrAngajati;
			Angajati** listaAux;
			listaAux = new Angajati * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
			{
				listaAux[i] = new Angajati(*this->listaAngajati[i]);
			}
			for (int i = 0; i < this->nrAngajati; i++)
			{
				delete this->listaAngajati[i];
			}
			delete[] this->listaAngajati;
			this->nrAngajati += nrAngajati;
			this->listaAngajati = new Angajati * [this->nrAngajati];
			for (int i = 0; i < nrAux; i++)
			{
				this->listaAngajati[i] = new Angajati(*listaAux[i]);
			}
			int j = 0;
			for (int i = nrAux; i < this->nrAngajati; i++)
			{
				this->listaAngajati[i] = listaAngajati[j];
				j++;
			}
		}
	}
	void adaugaAngajat(Angajati a)
	{
		int nrAux = this->nrAngajati;
		Angajati** listaAux;
		listaAux = new Angajati * [this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
		{
			listaAux[i] = new Angajati(*this->listaAngajati[i]);
		}
		for (int i = 0; i < this->nrAngajati; i++)
		{
			delete this->listaAngajati[i];
		}
		delete[] this->listaAngajati;
		this->nrAngajati++;
		this->listaAngajati = new Angajati * [this->nrAngajati];
		for (int i = 0; i < nrAux; i++)
		{
			this->listaAngajati[i] = new Angajati(*listaAux[i]);
		}
		listaAngajati[this->nrAngajati - 1] = &a;
	}
	void adaugaClient(Client c)
	{
		int nrAux = this->nrClienti;
		Client** listaAux;
		listaAux = new Client * [this->nrClienti];
		for (int i = 0; i < this->nrClienti; i++)
		{
			listaAux[i] = new Client(*this->listaClienti[i]);
		}
		for (int i = 0; i < this->nrClienti; i++)
		{
			delete this->listaClienti[i];
		}
		delete[] this->listaClienti;
		this->nrClienti++;
		this->listaClienti = new Client * [this->nrClienti];
		for (int i = 0; i < nrAux; i++)
		{
			this->listaClienti[i] = new Client(*listaAux[i]);
		}
		this->listaClienti[this->nrClienti - 1] = &c;
	}
	void readFromText(fstream& f)
	{
		for (int i = 0; i < this->nrClienti; i++)
		{
			delete this->listaClienti[i];
		}
		for (int i = 0; i < this->nrAngajati; i++)
		{
			delete this->listaAngajati[i];
		}
		delete[] this->listaClienti;
		delete[] this->listaAngajati;
		f >> this->adresa;
		f >> this->nrAngajati;
		this->listaAngajati = new Angajati * [this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->listaAngajati[i] = new Angajati;
		}
		for (int i = 0; i < this->nrAngajati; i++)
		{
			f >> *this->listaAngajati[i];
		}
		f >> this->nrClienti;
		this->listaClienti = new Client * [this->nrClienti];
		for (int i = 0; i < this->nrClienti; i++)
		{
			this->listaClienti[i] = new Client;
		}
		for (int i = 0; i < this->nrClienti; i++)
		{
			f >> *this->listaClienti[i];
		}
		f >> (Depozit&)*this;
	}
	void readFromCSV(fstream& f)
	{

	}
	void writeToFile(fstream& f)
	{
		int lg = this->adresa.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->adresa.data(), lg);
		
		f.write((char*)&this->nrAngajati, sizeof(int));
		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->listaAngajati[i]->writeToFile(f);
		}

		f.write((char*)&this->nrClienti, sizeof(int));
		for (int i = 0; i < this->nrClienti; i++)
		{
			this->listaClienti[i]->writeToFile(f);
		}
	}
	void readFromFile(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->adresa = buffer;
		delete[] buffer;

		for (int i = 0; i < this->nrAngajati; i++)
		{
			delete this->listaAngajati[i];
		}
		delete[] this->listaAngajati;
		f.read((char*)&this->nrAngajati, sizeof(int));
		listaAngajati = new Angajati * [this->nrAngajati];
		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->listaAngajati[i] = new Angajati;
			this->listaAngajati[i]->readFromFile(f);
		}

		for (int i = 0; i < this->nrClienti; i++)
		{
			delete this->listaClienti[i];
		}
		delete[] this->listaClienti;
		f.read((char*)&this->nrClienti, sizeof(int));
		listaClienti = new Client * [this->nrClienti];
		for (int i = 0; i < this->nrClienti; i++)
		{
			this->listaClienti[i] = new Client;
			this->listaClienti[i]->readFromFile(f);
		}
	}
	void operator[](string telefon)
	{
		for (int i = 0; i < this->nrClienti; i++)
		{
			if (this->listaClienti[i]->getTelefon() == telefon)
			{
				this->listaClienti[i]->getComenzi();
			}
		}
	}
	Magazin& operator+(Client c)
	{
		adaugaClient(c);
		return *this;
	}
	Magazin& operator+(Angajati a)
	{
		adaugaAngajat(a);
		return *this;
	}
	Magazin& operator++()
	{
		for (int i = 0; i < this->nrAngajati; i++)
		{
			int vechime = this->listaAngajati[i]->getVechime();
			this->listaAngajati[i]->setVechime(vechime++);
		}
		return *this;
	}
	Magazin& operator++(int)
	{
		Magazin aux = *this;
		for (int i = 0; i < this->nrAngajati; i++)
		{
			int vechime = this->listaAngajati[i]->getVechime();
			this->listaAngajati[i]->setVechime(vechime++);
		}
		return aux;
	}
	explicit operator int()
	{
		int necesarS = 0;
		for (int i = 0; i < this->nrAngajati; i++)
		{
			necesarS += this->listaAngajati[i]->getSalariu();
		}
		return necesarS;
	}
	bool operator! () 
	{
		if (this->nrClienti) return false;
		else return true;
 	}
	bool operator< (Magazin m)
	{
		if ((int)*this < (int)m) return true;
		else return false;
	}
	bool operator== (Magazin m)
	{
		if (this->adresa == m.adresa) return true;
		else return false;
	}
	Magazin& operator=(const Magazin& m)
	{
		if (this != &m)
		{
			for (int i = 0; i < this->nrClienti; i++)
			{
				delete this->listaClienti[i];
			}
			for (int i = 0; i < this->nrAngajati; i++)
			{
				delete this->listaAngajati[i];
			}
			delete[] this->listaClienti;
			delete[] this->listaAngajati;
			this->nrAngajati = m.nrAngajati;
			this->listaAngajati = new Angajati * [this->nrAngajati];
			this->adresa = m.adresa;
			this->nrClienti = m.nrClienti;
			this->listaClienti = new Client * [this->nrClienti];
			for (int i = 0; i < this->nrClienti; i++)
			{
				this->listaClienti[i] = new Client(*m.listaClienti[i]);
			}
			this->listaAngajati = new Angajati * [this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
			{
				this->listaAngajati[i] = new Angajati(*m.listaAngajati[i]);
			}
			this->Depozit::operator=(m);
		}
		return *this;
	}
	~Magazin() {
		for (int i = 0; i < this->nrClienti; i++)
		{
			delete this->listaClienti[i];
		}
		for (int i = 0; i < this->nrAngajati; i++)
		{
			delete this->listaAngajati[i];
		}
		delete[] this->listaClienti;
		delete[] this->listaAngajati;
	}
	friend istream& operator>>(istream& in, Magazin& m)
	{
		for (int i = 0; i < m.nrClienti; i++)
		{
			delete m.listaClienti[i];
		}
		for (int i = 0; i < m.nrAngajati; i++)
		{
			delete m.listaAngajati[i];
		}
		delete[] m.listaClienti;
		delete[] m.listaAngajati;
		cout << "\nAdresa magazinului este: ";
		in >> m.adresa;
		cout << "\nNumarul de angajati este: ";
		in >> m.nrAngajati;
		m.listaAngajati = new Angajati * [m.nrAngajati];
		for (int i = 0; i < m.nrAngajati; i++)
		{
			m.listaAngajati[i] = new Angajati;
		}
		cout << "\nIntroduceti Angajatii: ";
		for (int i = 0; i < m.nrAngajati; i++)
		{
			in >> *m.listaAngajati[i];
		}
		cout << "\nNumarul de clienti este: ";
		in >> m.nrClienti;
		m.listaClienti = new Client * [m.nrClienti];
		for (int i = 0; i < m.nrClienti; i++)
		{
			m.listaClienti[i] = new Client;
		}
		cout << "\nIntroduceti Clientii: ";
		for (int i = 0; i < m.nrClienti; i++)
		{
			in >> *m.listaClienti[i];
		}
		in >> (Depozit&)m;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Magazin& m)
	{
		for (int i = 0; i < m.nrClienti; i++)
		{
			delete m.listaClienti[i];
		}
		for (int i = 0; i < m.nrAngajati; i++)
		{
			delete m.listaAngajati[i];
		}
		delete[] m.listaClienti;
		delete[] m.listaAngajati;
		in >> m.adresa;
		in >> m.nrAngajati;
		m.listaAngajati = new Angajati * [m.nrAngajati];
		for (int i = 0; i < m.nrAngajati; i++)
		{
			m.listaAngajati[i] = new Angajati;
		}
		for (int i = 0; i < m.nrAngajati; i++)
		{
			in >> *m.listaAngajati[i];
		}
		in >> m.nrClienti;
		m.listaClienti = new Client * [m.nrClienti];
		for (int i = 0; i < m.nrClienti; i++)
		{
			m.listaClienti[i] = new Client;
		}
		for (int i = 0; i < m.nrClienti; i++)
		{
			in >> *m.listaClienti[i];
		}
		in >> (Depozit&)m;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Magazin& m)
	{
		
		out << "\n---------------------";
		out << "\nAdresa magazinului este: " << m.adresa;
		out << "\nLista de angajati a magazinului este: ";
		for (int i = 0; i < m.nrAngajati; i++)
		{
			out << "\n" << (*m.listaAngajati[i]);
		}
		out << "\nLista de clienti a magazinului este: ";
		for (int i = 0; i < m.nrClienti; i++)
		{
			out << "\n" << (*m.listaClienti[i]);
		}
		out << (Depozit)m;
		out << "\n---------------------";
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Magazin& m)
	{

		out << m.adresa<<" ";
		for (int i = 0; i < m.nrAngajati; i++)
		{
			out << (*m.listaAngajati[i])<<" ";
		}
		for (int i = 0; i < m.nrClienti; i++)
		{
			out << (*m.listaClienti[i])<<" ";
		}
		out << (Depozit)m << " ";
		return out;
	}
};
class Rapoarte {
public:
	static void listaDepozite(vector <Depozit> d)
	{
		ofstream f("raport.txt");
		for (int i = 0; i < d.size(); i++)
		{
			cout << d[i];
			f << d[i];
		}
		f.close();
	}
	static void listaComenzi(vector<Comenzi> c)
	{
		ofstream f("raport.txt");
		for (int i = 0; i < c.size(); i++)
		{
			cout << c[i];
			f << c[i];
		}
		f.close();
	}
	static void listaAngajati(vector<Angajati> a)
	{
		ofstream f("raport.txt");
		for (int i = 0; i < a.size(); i++)
		{
			cout << a[i];
			f << a[i];
		}
		f.close();
	}
	static void listaClienti(vector<Client> cl)
	{
		ofstream f("raport.txt");
		for (int i = 0; i < cl.size(); i++)
		{
			cout << cl[i];
			f << cl[i];
		}
		f.close();
	}
	static void listaMagazine(vector<Magazin> m)
	{
		ofstream f("raport.txt");
		for (int i = 0; i < m.size(); i++)
		{
			cout << m[i];
			f << m[i];
		}
		f.close();
	}
	static void raportActivitate1(int nrD, int nrC, int nrA, int nrCl, int nrM)
	{
		cout << "\nIn urma sesiunii actuale aveti:";
		cout << "\n" << nrD << " depozite";
		cout << "\n" << nrC << " comenzi";
		cout << "\n" << nrA << " angajati";
		cout << "\n" << nrCl << " clienti";
		cout << "\n" << nrM << " magazine";
	}
	static void raportActivitate2(int nrElementeAdaugate, int nrElementeSterse)
	{

	}
};
class Meniu {
public:
	static void Display(int subMeniu)
	{
		if (subMeniu == 0) {
			system("cls");
			cout << "\nAlegeti varianta:";
			cout << "\n1.Rapoarte";
			cout << "\n2.Adaugati date";
			cout << "\n3.Stergeti date";
			cout << "\n4.Iesire";
		}
		else if (subMeniu == 1) {
			system("cls");
			cout << "\nAlegeti raportul:";
			cout << "\n1.Lista Depozite";
			cout << "\n2.Lista Comenzi";
			cout << "\n3.Lista Angajati";
			cout << "\n4.Lista Clienti";
			cout << "\n5.Lista Magazine";
			cout << "\n0.Revenire la meniul principal";
		}
		else if (subMeniu == 2) {
			system("cls");
			cout << "\n0.Revenire la meniul principal";
			cout << "\n1.Adaugare Depozite";
			cout << "\n2.Adaugare Comenzi";
			cout << "\n3.Adaugare Angajati";
			cout << "\n4.Adaugare Clienti";
			cout << "\n5.Adaugare Magazine";
		}
		else if (subMeniu == 3) {
			system("cls");
			cout << "\n0.Revenire la meniul principal";
			cout << "\n1.Stergere Depozite";
			cout << "\n2.Stergere Comenzi";
			cout << "\n3.Stergere Angajati";
			cout << "\n4.Stergere Clienti";
			cout << "\n5.Stergere Magazine";
		}
		cout << endl;
	}
	static int Procesor(int& subMeniu, vector<Depozit>& d, vector<Comenzi>& c, vector<Angajati>& a, vector <Client>& cl, vector<Magazin>& m)
	{
		if (subMeniu == 1)
		{
			int alegere;
			Display(1);
			cin >> alegere;
			if (alegere == 1) {
				Rapoarte::listaDepozite(d);
				cout << endl;
				system("pause");
				return 1;
			}
			else if (alegere == 2) {
				Rapoarte::listaComenzi(c);
				cout << endl;
				system("pause");
				return 1;
			}
			else if (alegere == 3) {
				Rapoarte::listaAngajati(a);
				cout << endl;
				system("pause");
				return 1;
			}
			else if (alegere == 4)
			{
				Rapoarte::listaClienti(cl);
				cout << endl;
				system("pause");
				return 1;
			}
			else if (alegere == 5)
			{
				Rapoarte::listaMagazine(m);
				cout << endl;
				system("pause");
				return 1;
			}
			else if (alegere == 0) return 0;
			return 1;
		}
		else if (subMeniu == 2) {
			int alegere;
			Display(2);
			cin >> alegere;
			if (alegere == 1) {
				Depozit dAux;
				cin >> dAux;
				d.push_back(dAux);
				return 2;
			}
			else if (alegere == 2) {
				Comenzi cAux;
				cin >> cAux;
				c.push_back(cAux);
				return 2;
			}
			else if (alegere == 3) {
				Angajati aAux;
				cin >> aAux;
				a.push_back(aAux);
				return 2;
			}
			else if (alegere == 4)
			{
				Client clAux;
				cin >> clAux;
				cl.push_back(clAux);
				return 2;
			}
			else if (alegere == 5)
			{
				Magazin mAux;
				cin >> mAux;
				m.push_back(mAux);
				return 2;
			}
			else if (alegere == 0) return 0;
			return 1;
		}
		else if (subMeniu == 3) {
			int alegere;
			Display(3);
			cin >> alegere;
			if (alegere == 1) {
				int pozitie;
				cout << "\nPozitie ";
				cin >> pozitie;
				vector<Depozit>::iterator it;
				it = d.begin() + pozitie;
				d.erase(it);
				return 3;
			}
			else if (alegere == 2) {
				int pozitie;
				cout << "\nPozitie ";
				cin >> pozitie;
				vector<Comenzi>::iterator it;
				it = c.begin() + pozitie;
				c.erase(it);
				return 3;
			}
			else if (alegere == 3) {
				int pozitie;
				cout << "\nPozitie ";
				cin >> pozitie;
				vector<Angajati>::iterator it;
				it = a.begin() + pozitie;
				a.erase(it);
				return 3;
			}
			else if (alegere == 4)
			{
				int pozitie;
				cout << "\nPozitie ";
				cin >> pozitie;
				vector<Client>::iterator it;
				it = cl.begin() + pozitie;
				cl.erase(it);
				return 3;
			}
			else if (alegere == 5)
			{
				int pozitie;
				cout << "\nPozitie ";
				cin >> pozitie;
				vector<Magazin>::iterator it;
				it = m.begin() + pozitie;
				m.erase(it);
				return 3;
			}
			else if (alegere == 0) return 0;
			return 3;
		}
		else if (subMeniu == 4) {
			cout << "\nLa revedere!";
			return 4;
		}
	};
	static void Controller(vector<Depozit>& d, vector<Comenzi>& c, vector<Angajati>& a, vector <Client>& cl, vector<Magazin>& m)
	{
		int subMeniu = 0;
		int ok = 1;
		while (ok) {
			Display(subMeniu);
			cin >> subMeniu;
			if (subMeniu == 4) ok = 0;
			subMeniu = Procesor(subMeniu, d, c, a, cl, m);
		}
	}
};
int main(int argc, const char** argv)
{
	string fDepozit;
	string fComenzi;
	string fAngjatati;
	string fClienti;
	string fMagazine;
	fDepozit = "Depozite.txt";
	fComenzi = "Comenzi.txt";
	fAngjatati = "Angajati.txt";
	fClienti = "Clienti.txt";
	fMagazine = "Magazine.txt";
	if (!(argc == 1 || argc == 6 || argc == 2))
	{
		cout << "Aplicatia trebuie sa primeasca fie 5 fisiere text fie nici unul";
		return 0;
	}
	else if (argc == 6)
	{
		fDepozit = argv[1];
		fComenzi = argv[2];
		fAngjatati = argv[3];
		fClienti = argv[4];
		fMagazine = argv[5];

		ifstream fD(fDepozit);
		ifstream fC(fComenzi);
		ifstream fA(fAngjatati);
		ifstream fCl(fClienti);
		ifstream fM(fMagazine);

		vector<Depozit> d;
		vector<Comenzi> c;
		vector<Angajati> a;
		vector<Client> cl;
		vector<Magazin> m;

		int nrD = 0;
		int nrC = 0;
		int nrA = 0;
		int nrCl = 0;
		int nrM = 0;

		fstream bD_In("DepozitB.txt", ios::in | ios::binary);
		fstream bC_In("ComenziB.txt", ios::in | ios::binary);
		fstream bA_In("AngajatiB.txt", ios::in | ios::binary);
		fstream bCl_In("ClientiB.txt", ios::in | ios::binary);
		fstream bM_In("MagazineB.txt", ios::in | ios::binary);

		if (!(bD_In.peek() == bD_In.eof() || bC_In.peek() == bC_In.eof() || bA_In.peek() == bA_In.eof() || bCl_In.peek() == bCl_In.eof() || bM_In.peek() == bM_In.eof()))
		{
			bD_In.read((char*)&nrD, sizeof(int));
			bC_In.read((char*)&nrC, sizeof(int));
			bA_In.read((char*)&nrA, sizeof(int));
			bCl_In.read((char*)&nrCl, sizeof(int));
			bM_In.read((char*)&nrM, sizeof(int));

			for (int i = 0; i < nrD; i++)
			{
				Depozit dF;
				dF.readFromFile(bD_In);
				d.push_back(dF);
			}
			for (int i = 0; i < nrC; i++)
			{
				Comenzi cF;
				cF.readFromFile(bC_In);
				c.push_back(cF);
			}
			for (int i = 0; i < nrA; i++)
			{
				Angajati aF;
				aF.readFromFile(bA_In);
				a.push_back(aF);
			}
			for (int i = 0; i < nrCl; i++)
			{
				Client clF;
				clF.readFromFile(bCl_In);
				cl.push_back(clF);
			}
			for (int i = 0; i < nrM; i++)
			{
				Magazin mF;
				mF.readFromFile(bM_In);
				m.push_back(mF);
			}
		}

		bD_In.close();
		bC_In.close();
		bA_In.close();
		bCl_In.close();
		bM_In.close();

		fD >> nrD;
		fC >> nrC;
		fA >> nrA;
		fCl >> nrCl;
		fM >> nrM;

		for (int i = 0; i < nrD; i++)
		{
			Depozit dF;
			fD >> dF;
			d.push_back(dF);
		}
		nrD += d.size();

		for (int i = 0; i < nrC; i++)
		{
			Comenzi cF;
			fC >> cF;
			c.push_back(cF);
		}
		nrC += c.size();

		for (int i = 0; i < nrA; i++)
		{
			Angajati aF;
			fA >> aF;
			a.push_back(aF);
		}
		nrA += a.size();

		for (int i = 0; i < nrCl; i++)
		{
			Client clF;
			fCl >> clF;
			cl.push_back(clF);
		}
		nrCl += cl.size();

		for (int i = 0; i < nrM; i++)
		{
			Magazin mF;
			fM >> mF;
			m.push_back(mF);
		}
		nrM += m.size();

		fD.close();
		fC.close();
		fA.close();
		fCl.close();
		fM.close();
		
		Meniu::Controller(d, c, a, cl, m);
		//Rapoarte::raportActivitate1(nrD, nrC, nrA, nrCl, nrM);

		fstream bD_Out("DepozitB.txt", ios::out | ios::binary);
		fstream bC_Out("ComenziB.txt", ios::out | ios::binary);
		fstream bA_Out("AngajatiB.txt", ios::out | ios::binary);
		fstream bCl_Out("ClientiB.txt", ios::out | ios::binary);
		fstream bM_Out("MagazineB.txt", ios::out | ios::binary);

		bD_Out.write((char*)&nrD, sizeof(int));
		bC_Out.write((char*)&nrC, sizeof(int));
		bA_Out.write((char*)&nrA, sizeof(int));
		bCl_Out.write((char*)&nrCl, sizeof(int));
		bM_Out.write((char*)&nrM, sizeof(int));

		bD_Out.close();
		bC_Out.close();
		bA_Out.close();
		bCl_Out.close();
		bM_Out.close();

		fstream bD_Out_App("DepozitB.txt", ios::out | ios::binary | ios::app);
		fstream bC_Out_App("ComenziB.txt", ios::out | ios::binary | ios::app);
		fstream bA_Out_App("AngajatiB.txt", ios::out | ios::binary | ios::app);
		fstream bCl_Out_App("ClientiB.txt", ios::out | ios::binary | ios::app);
		fstream bM_Out_App("MagazineB.txt", ios::out | ios::binary | ios::app);

		for (int i = 0; i < d.size(); i++)
		{
			d[i].writeToFile(bD_Out_App);
		}
		for (int i = 0; i < c.size(); i++)
		{
			c[i].writeToFile(bC_Out_App);
		}
		for (int i = 0; i < a.size(); i++)
		{
			a[i].writeToFile(bA_Out_App);
		}
		for (int i = 0; i < cl.size(); i++)
		{
			cl[i].writeToFile(bCl_Out_App);
		}
		for (int i = 0; i < m.size(); i++)
		{
			m[i].writeToFile(bM_Out_App);
		}

		bD_Out_App.close();
		bC_Out_App.close();
		bA_Out_App.close();
		bCl_Out_App.close();
		bM_Out_App.close();

		return 0;
	}
	else if (argc == 1)
	{
	vector<Depozit> d;
	vector<Comenzi> c;
	vector<Angajati> a;
	vector<Client> cl;
	vector<Magazin> m;

	int nrD = 0;
	int nrC = 0;
	int nrA = 0;
	int nrCl = 0;
	int nrM = 0;

	fstream bD_In("DepozitB.txt", ios::in | ios::binary);
	fstream bC_In("ComenziB.txt", ios::in | ios::binary);
	fstream bA_In("AngajatiB.txt", ios::in | ios::binary);
	fstream bCl_In("ClientiB.txt", ios::in | ios::binary);
	fstream bM_In("MagazineB.txt", ios::in | ios::binary);

	if (!(bD_In.peek() == bD_In.eof() || bC_In.peek() == bC_In.eof() || bA_In.peek() == bA_In.eof() || bCl_In.peek() == bCl_In.eof() || bM_In.peek() == bM_In.eof()))
	{
		bD_In.read((char*)&nrD, sizeof(int));
		bC_In.read((char*)&nrC, sizeof(int));
		bA_In.read((char*)&nrA, sizeof(int));
		bCl_In.read((char*)&nrCl, sizeof(int));
		bM_In.read((char*)&nrM, sizeof(int));

		for (int i = 0; i < nrD; i++)
		{
			Depozit dF;
			dF.readFromFile(bD_In);
			d.push_back(dF);
		}
		for (int i = 0; i < nrC; i++)
		{
			Comenzi cF;
			cF.readFromFile(bC_In);
			c.push_back(cF);
		}
		for (int i = 0; i < nrA; i++)
		{
			Angajati aF;
			aF.readFromFile(bA_In);
			a.push_back(aF);
		}
		for (int i = 0; i < nrCl; i++)
		{
			Client clF;
			clF.readFromFile(bCl_In);
			cl.push_back(clF);
		}
		for (int i = 0; i < nrM; i++)
		{
			Magazin mF;
			mF.readFromFile(bM_In);
			m.push_back(mF);
		}
	}

	bD_In.close();
	bC_In.close();
	bA_In.close();
	bCl_In.close();
	bM_In.close();

	Meniu::Controller(d, c, a, cl, m);
	//Rapoarte::raportActivitate1(nrD, nrC, nrA, nrCl, nrM);

	fstream bD_Out("DepozitB.txt", ios::out | ios::binary);
	fstream bC_Out("ComenziB.txt", ios::out | ios::binary);
	fstream bA_Out("AngajatiB.txt", ios::out | ios::binary);
	fstream bCl_Out("ClientiB.txt", ios::out | ios::binary);
	fstream bM_Out("MagazineB.txt", ios::out | ios::binary);

	bD_Out.write((char*)&nrD, sizeof(int));
	bC_Out.write((char*)&nrC, sizeof(int));
	bA_Out.write((char*)&nrA, sizeof(int));
	bCl_Out.write((char*)&nrCl, sizeof(int));
	bM_Out.write((char*)&nrM, sizeof(int));

	bD_Out.close();
	bC_Out.close();
	bA_Out.close();
	bCl_Out.close();
	bM_Out.close();

	fstream bD_Out_App("DepozitB.txt", ios::out | ios::binary | ios::app);
	fstream bC_Out_App("ComenziB.txt", ios::out | ios::binary | ios::app);
	fstream bA_Out_App("AngajatiB.txt", ios::out | ios::binary | ios::app);
	fstream bCl_Out_App("ClientiB.txt", ios::out | ios::binary | ios::app);
	fstream bM_Out_App("MagazineB.txt", ios::out | ios::binary | ios::app);

	for (int i = 0; i < d.size(); i++)
	{
		d[i].writeToFile(bD_Out_App);
	}
	for (int i = 0; i < c.size(); i++)
	{
		c[i].writeToFile(bC_Out_App);
	}
	for (int i = 0; i < a.size(); i++)
	{
		a[i].writeToFile(bA_Out_App);
	}
	for (int i = 0; i < cl.size(); i++)
	{
		cl[i].writeToFile(bCl_Out_App);
	}
	for (int i = 0; i < m.size(); i++)
	{
		m[i].writeToFile(bM_Out_App);
	}

	bD_Out_App.close();
	bC_Out_App.close();
	bA_Out_App.close();
	bCl_Out_App.close();
	bM_Out_App.close();

	return 0;
	}
	else if (argc == 2  && strcmp("test", argv[1]) == 0)
	{
	
	////Depozit
	//Depozit d1;
	//string produse[2] = { "pietre","caramizi" };
	//int cantitatiProduse[2] = { 2, 2 };
	//int preturiProduse[2] = { 1, 2 };
	//int nrMasini = 1;
	//int masiniDisponibile[1] = { 1 };
	//Depozit d2(2, produse, cantitatiProduse, preturiProduse, nrMasini, masiniDisponibile);
	////cout << d1 << "\n";
	////cout << d2 << "\n";
	//Depozit d3(d2);
	//cout << d3 << "\n";
	//d1 = d3;
	//cout << d1 << "\n";
	//cin >> d1;
	//cout << d1;
	
	////Setteri si getteri pentru parametrii:
	////cout<<d2.getNrProduse();
	////d2.setNrProduse(4, produse,cantitatiProduse, preturiProduse);
	////d2.setProduse(2, produse, cantitatiProduse, preturiProduse);
	////d2.getProduse();
	////d2.setCantitati("caramizi", 3);
	////d2.getCantitati();
	////d2.setPreturi("caramizi", 10);
	////d2.getPreturi();
	////d2.setNrMasini(2);
	////cout<<d2.getNrMasini();
	////d2.setMasini(0, 0);
	////d2.getMasini();
	//
	////Operatori
	//cout << (int)d2;
	////cout<<d2["caramizi"];
	////d1 + d2;
	////cout << d1;
	///*d1++;
	//cout << d1;
	//++d1;
	//cout << d1;*/
	////if (d1 < d2) cout << "e bine";
	////if (d2 == d2) cout << "e bine";
	////if (!d1) cout << "e bine";


	////Metode:
	////d2.adaugaProdus("chestii", 2, 1);
	////d2.stergeProdus("pietre");
	////d2.getProduse();

	////Comenzi

	//Comenzi c1;
	////cout << c1;
	//Comenzi c2(2, produse, cantitatiProduse);
	////cout << c2;
	//Comenzi c3(c2);
	////cout << c3;
	//c1 = c2;
	////cout << c1;
	////cin >> c1;
	////cout << c1;

	////Setteri si getteri:

	////cout<< c2.getId();
	////cout<< c2.setId(4);
	////cout<< c2.setId(3);
	////cout << c2.getIdComanda();
	////c2.setProduse(2, produse, cantitatiProduse);
	////c2.setNrProduse(6, produse, cantitatiProduse);
	////c2.getProduse();
	////c2.setCantitati("pietre", 6);
	////c2.getCantitati();
	//////c2.getCantitati();
	////c2.adaugaProdus("pavele", 1);
	////c2.getProduse();
	////c2.stergeProdus("pietre");
	////c2.getProduse();

	////Operatori:

	///*c2.operator[]("caramizi");
	//c1 + c2;
	//cout << c1;
	//c1++;
	//++c1;
	//cout << c1;
	//cout << "\n" << (int)c1;
	//if (c1 < c2) cout << "e bine";
	//else cout << "nu e bine";
	//c1 = c2;
	//if (c1 == c2) cout << "e bine";
	//else cout << "nu e bine";
	//cout << endl;
	//bool a;
	//a = (c1 == c2);*/

	////Metode:
	//// c1.adaugaProdus("bolovani", 2);
	//// c1.stergeProduse("pietre");
	//

	////Angajati

	//Angajati a1;
	////cout << a1;
	////Angajati(char* nume, char* prenume, int varsta, int salariu, int vechime, int oreLucru, int nrComenzi, Comenzi * listaComenzi[10])
	//char nume[] = "Divoiu";
	//char prenume[] = "Claudiu";
	//int varsta = 20;
	//int salariu = 4000;
	//int vechime = 1;
	//int oreLucru = 40;
	//int nrComenzi = 2;
	//Comenzi* listaComenzi[10] = { &c1, &c2 };
	//Angajati a2(nume, prenume, varsta, salariu, vechime, oreLucru, nrComenzi, listaComenzi);
	//Angajati a3(a2);
	////cout << a2;
	////cout << a3;
	//a1 = a2;
	////cout << a1;
	////cin >> a1;
	////cout << a1;
	////a2.setNrComenzi(4, listaComenzi);
	////a2.setComenzi(2, listaComenzi);
	////a2.getComenzi();
	////Setteri si getteri:
	//
	////char nume[] = "gigel";
	////char prenume[] = "ionel";
	////a2.getNume();
	////a2.setNume(nume)
	////a2.getPrenume();
	////a2.setPrenume(prenume);
	////a2.getOreLucru();
	////a2.setOreLucru(50);
	////a2.getSalariu();
	////a2.setSalariu(5000);
	////a2.getVechime();
	////a2.setVechime(2);
	////a2.getVarsta();
	////a2.setVarsta(30);
	////a2.getNrComenzi();

	////Operatori:
	////a2 + 30;
	////cout<< a2.getOreLucru();
	///*a2++;
	//++a2;
	//cout << a2.getVechime();*/
	////cout << (int)a2;
	////if (a2 == a2) cout<< "e bine";
	////a1.setSalariu(1000);
	////if (a2 < a1)cout << "e bine";
	////if (!a2) cout << "n-are";
	////else cout << "are";
	////Metode:

	//// a2.adaugaComanda(&c1);
	////a2.stergeComanda(1);
	////a2.getComenzi();

	////Client
	//Client cl1;
	////cout << cl1;
	//string email = "divoiuclaudiu@gmail.com";
	//char telefon[] = "0724753007";
	//Client cl2(nume, prenume, email, telefon, nrComenzi, listaComenzi);
	////cout << cl2;
	//Client cl3(cl2);
	////cout << cl3;
	//cl1 = cl3;
	////cout << cl1;
	////cin >> cl2;
	////cout << cl2;

	////Setteri si getteri:
	///*cl1.setNume(nume);
	//cl1.getNume();
	//cl1.setPrenume(prenume);
	//cl1.getPrenume();
	//cl1.setEmail(email);
	//cl1.getEmail();
	//cl1.getTelefon();
	//cl1.setTelefon(telefon);
	//cl1.getNrComenzi();
	//cl1.getComenzi();
	//cl1.setNrComenzi(2, listaComenzi);
	//cl1.setComenzi(2, listaComenzi);
	//cl1.getComenzi();*/

	////Metode:
	///*cl1.adaugaComanda(&c1);
	//cl2.stergeComanda(1);*/

	////Operatori:
	////cl1++;
	////++cl1;
	////cl1 + email;
	////if (cl2 < cl1)cout << "e bine";
	////if (!cl2) cout << "n-are";
	////else cout << "are";
	////cout << (int)cl1;


	////Magazin
	//Magazin m1;
	////cout << m1;
	//string adresa = "Strada Bihor";
	//Client** listaClienti;
	//listaClienti = new Client*[2];
	//listaClienti[0] = { &cl1};
	//listaClienti[1] = { &cl2 };
	//Angajati** listaAngajati;
	//listaAngajati = new Angajati * [2];
	//listaAngajati[0] = { &a1 };
	//listaAngajati[1] = { &a2 };
	//Magazin m2(2, produse, cantitatiProduse, preturiProduse, nrMasini, masiniDisponibile, adresa, 2, 2, listaClienti, listaAngajati );
	////cout << m2;
	//Magazin m3(d1, adresa, 2, 2, listaClienti, listaAngajati);
	////cout << m3;
	//Magazin m4(m3);
	////cout << m4;
	//m1 = m4;
	////cout << m1;
	////cin >> m1;
	////cout << m1;
	////m2.setNrClienti(4,listaClienti);
	////m2.getClienti();
	/*Magazin* mp = &m1;
	Depozit* dp = &d1;
	vector<Depozit*> lista;
	lista.push_back(mp);
	lista.push_back(dp);*/
	return 0;
	}
	else cout << "Aplicatia trebuie sa primeasca fie 5 fisiere fie nici unul";
	return 0;
}
