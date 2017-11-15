#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Grad
{
	string ime;
	int ID;
};

class Graf
{
    int brojCvorova;
    vector<int> cvorovi;
    vector<bool> posjecen;
    vector<vector<int> > ivice;
    vector<vector<int> > udaljenostPoRedu;
public:
    Graf(int bc):brojCvorova(bc), cvorovi(bc), posjecen(bc), ivice(bc), udaljenostPoRedu(bc)
    {
        for(int i = 0; i < bc; i++) ivice[i].resize(bc);
        for(int i = 0; i < bc; i++) udaljenostPoRedu[i].resize(bc);
    }
    void IspisiIvice();
    void Priprema();
    bool ProvjeriOpseg(int i) { return i > 0 && i < brojCvorova; }
    void DodajIvicu(int i, int j, int udaljenost);
  //  bool JeLiPosjecen(int i){return posjecen[i];}
    void DodajCvor();

    int VratiIndeksSaMinTezinom(int cvor);
    int vratiIndeksSaMinTezinomZaUdaljenostiPoRedu(int cvor);
    vector<int> DajSusjede(int cvor);
    void IspisiUdaljenosti(vector<vector<int> > udaljenosti);
    bool DaLiJeUVektoru(vector<int> v, int cvor);
    int Dijkstra(vector<Grad> v, int poc, int kraj);
    void ispisiUdaljenosti(vector<vector<int> > udaljenosti);
    string GetNaziv(vector<Grad> v, int ID);
};

void Graf::ispisiUdaljenosti(vector<vector<int> > udaljenosti)
{
    cout<<"   ";
     for(int i = 0; i < udaljenosti.size(); i++)
       cout<<i<<"    ";
     cout<<endl;
     for(int i = 0; i < udaljenosti.size(); i++)
     {
      cout<<i<<": ";
      for(int j = 0; j < brojCvorova; j++)
      {
          if(udaljenosti[i][j] < 0)
          {
              cout<<udaljenosti[i][j]<<"   ";
          }
          else{
            cout << udaljenosti[i][j] << "    ";
          }
      }
      cout<<endl;
     }
}

void Graf::DodajIvicu(int i, int j, int udaljenost)
{
     if(!(ProvjeriOpseg(i) || ProvjeriOpseg(j))) { cout<<"Greska! Dodaje se ivica za nepostojeci cvor"; return; }
     else
     {
         ivice[i][j] = ivice[j][i] = udaljenost;
     }
}

void Graf::Priprema()
{
     for(int i(0); i < brojCvorova; i++)
     posjecen[i] = false;
}

void Graf::IspisiIvice()
{
     cout<<"   ";
     for(int i = 0; i < brojCvorova; i++)
       cout<<i<<" ";
     cout<<endl;
     for(int i = 0; i < brojCvorova; i++)
     {
      cout<<i<<": ";
      for(int j = 0; j < brojCvorova; j++)
        cout<<ivice[i][j]<<" ";
      cout<<endl;
     }
}

void Graf::DodajCvor()
{
	vector<int> novi(brojCvorova);
	ivice.push_back(novi);

	for(int i = 0; i < brojCvorova + 1; i++)
	{
		ivice[i].resize(brojCvorova + 1);
	}

//	brojCvorova++;
	cvorovi.resize(brojCvorova+1);
	posjecen.resize(brojCvorova+1);
	posjecen.push_back(false);

}

int Graf::VratiIndeksSaMinTezinom(int cvor)
{
    Priprema();
    int minIndeks = -1;
    for(int i = 0; i < brojCvorova; i++)
    {
        if(ivice[cvor][i] != 0  && ivice[cvor][i] != -1)
        {
            if((ivice[cvor][i] >= 0 && !posjecen[i]) && (minIndeks < 0 || ivice[cvor][i] < ivice[cvor][minIndeks]))
            {
                minIndeks = i;
            }
        }
    }
    return minIndeks;
}

int Graf::vratiIndeksSaMinTezinomZaUdaljenostiPoRedu(int cvor)
{
    int minIndeks = -1;
    for(int i = 0; i < brojCvorova; i++)
    {
        if(udaljenostPoRedu[cvor][i] != -1 && udaljenostPoRedu[cvor][i] != 0)
        {
            if((udaljenostPoRedu[cvor][i] >= 0 && !posjecen[i]) && (minIndeks < 0 || udaljenostPoRedu[cvor][i] < udaljenostPoRedu[cvor][minIndeks]))
            {
                minIndeks = i;
        //        cout <<"indeks: " << minIndeks << ", vrijednost: " << udaljenostPoRedu[cvor][i] << endl;
            }
        }
    }
    return minIndeks;
}

vector<int> Graf::DajSusjede(int cvor) // Vraca cvorove koji su susjedi od datog cvora
{
    vector<int> niz;
    for(int i = 0; i < brojCvorova; i++)
    {
        if(ivice[cvor][i] != 0){
           niz.push_back(i);
        }
    }
   /* for(int i = 0; i < niz.size(); i++)
    {
        cout << "susjedi: " << niz[i] << endl;
    }*/
    return niz;
}

void Graf::IspisiUdaljenosti(vector<vector<int> > udaljenosti)
{
    cout<<"   ";
    for(int i = 0; i < brojCvorova; i++)
       cout << i << "    ";
    cout<<endl;
    for(int i = 0; i < brojCvorova; i++)
    {
      cout << i << ": ";
      for(int j = 0; j < brojCvorova; j++)
      {
          if(udaljenosti[i][j] < 0)
          {
              cout<<udaljenosti[i][j]<<"   ";
          }
          else{
            cout << udaljenosti[i][j] << "    ";
          }
      }
     cout<<endl;
    }
}

bool Graf::DaLiJeUVektoru(vector<int> v, int cvor)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == cvor)
        {
            return true;
        }
    }
    return false;
}

int Graf::Dijkstra(vector<Grad> v, int poc, int kraj)
{
    if(poc == kraj) return 0;
    for(int i = 0; i < brojCvorova; i++)
    {
       for(int j = 0; j < brojCvorova; j++)
       {
           udaljenostPoRedu[i][j] = -1;
       }
    }
    Priprema();
    int prethCvor = -1;
    int trenutniCvor = poc;
    prethCvor = poc;
    trenutniCvor = VratiIndeksSaMinTezinom(prethCvor);
    posjecen[poc] = true;
    posjecen[trenutniCvor] = true;
    for(int i = 0; i < brojCvorova; i++)
    {
        if(ivice[poc][i] != 0)
        {
            udaljenostPoRedu[0][i] = ivice[poc][i];
        }
        else
        {
            udaljenostPoRedu[0][i] = -1;
        }
    }
    udaljenostPoRedu[0][poc] = 0;   // udaljenost cvora od sebe samog je nula
    udaljenostPoRedu[1][trenutniCvor] = udaljenostPoRedu[0][trenutniCvor];
    if(kraj == trenutniCvor) return udaljenostPoRedu[1][trenutniCvor];
    int i = 0;
        while(i < brojCvorova-3)   // za dva cvora je vec odredjeno, za prvi, a za drugi i zadnji djelimicno
    {
        for(int j = 0; j < brojCvorova; j++)  // for petlja za sve mouguce susjede
        {
            if(posjecen[j])
            {
                udaljenostPoRedu[i+1][j] = udaljenostPoRedu[i][j];
            }
            else   // sada gledaj prvo da li je susjed da cvorom j, ako jeste onda mijenjaj tezinu ako bude manja
            {
                vector<int> susj(DajSusjede(trenutniCvor)); // ako jeste susjed, a vec je posjecen onda samo prepisi prethodne vrijednosti
                if(DaLiJeUVektoru(susj, j) == true)    // trenutniCvor je vezan za ivice
                {
                    if(posjecen[j])
                    {
                        udaljenostPoRedu[i+1][j] = udaljenostPoRedu[i][j];
                    }
                    if(udaljenostPoRedu[i][j] == -1)  // ako je susjed, a prethodni je beskonacno, onda ce ta sljedeca tezina sig biti bolja od beskonacno
                    {
                        udaljenostPoRedu[i+1][j] = ivice[trenutniCvor][j] + udaljenostPoRedu[i+1][trenutniCvor];
                    }
                    else
                    {      // ako jeste u vektoru, a nije posjecen, onda racunaj vrijednosti, ako je tezina manja azuriraj je
                            int tezina = ivice[trenutniCvor][j];
                            if(udaljenostPoRedu[i+1][trenutniCvor] + tezina < udaljenostPoRedu[i][j])
                            {
                                udaljenostPoRedu[i+1][j] = udaljenostPoRedu[i+1][trenutniCvor] + tezina;
                            }
                            else  // jeste u vektoru, nije posjecen, a tezina nije manja od prethodne, samo prepisi
                            {
                                udaljenostPoRedu[i+1][j] = udaljenostPoRedu[i][j];
                            }
                    }
                }
                else  // ako nije nikako u vektoru, tj. ako uopste nije susjed sa cvorom, onda samo prepisi vrijednosti
                {
                    udaljenostPoRedu[i+1][j] = udaljenostPoRedu[i][j];
                }
            }
        }
        prethCvor = trenutniCvor;
        trenutniCvor = vratiIndeksSaMinTezinomZaUdaljenostiPoRedu(i+1);
        posjecen[trenutniCvor] = true;
        udaljenostPoRedu[i+2][trenutniCvor] = udaljenostPoRedu[i+1][trenutniCvor];
        if(trenutniCvor == kraj)
        {
           // cout << "Udaljenost izmedju gradova " << GetNaziv(v, poc) << " i " << GetNaziv(v, kraj) << " iznosi: " << udaljenostPoRedu[i+2][trenutniCvor] << " km";
            return udaljenostPoRedu[i+2][trenutniCvor];
        }
        i++;
    }
}

string Graf::GetNaziv(vector<Grad> v, int ID)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i].ID == ID) return v[i].ime;
	}
}

bool JeLiUVektoru(vector<Grad> v, string ime)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].ime == ime) return true;
    }
    return false;
}

int VratiID(vector<Grad> v, string ime)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].ime == ime) return v[i].ID;
    }
}

string PretvoriSlova(string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')  // pretvori sva slova u mala
        {
            s[i] = s[i] + 32;
        }
    }
    s[0] = s[0] - 32;  // pocetno slovo stavi veliko
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == ' ')    // izbaci razmak
        {
            s[i] = s[i+1];
        }
        if(s[i] == s[i+1]){   //
            s[i+1] = s[i+1] - 32;  // pocetak druge rijeci u nazivu, stavi veliko slovo
            s.erase(i, 1);  // izbrisi duplikat slova
        }
    }
    return s;
}

int main()
{
	ifstream unos;
	unos.open("gradovi.txt");
	ofstream fout("gradovi.txt", ios::app);
	int brGradova, brPuteva;
	unos >> brGradova >> brPuteva;

	string g1, g2;
	int udaljenost;
	Graf g(brGradova);
	vector<Grad> imena(brGradova);

	int brojac = 0;
	for(int i = 0; i < brPuteva; i++)
	{
		unos >> g1 >> g2 >> udaljenost;

		if(!JeLiUVektoru(imena, g1)){
			imena[brojac].ime = g1;
			imena[brojac].ID = brojac;
			brojac++;
		}
		if(!JeLiUVektoru(imena, g2)){
			imena[brojac].ime = g2;
			imena[brojac].ID = brojac;
			brojac++;
		}

		g.DodajIvicu(VratiID(imena, g1), VratiID(imena, g2), udaljenost);

	}
	unos.close();

	string g3, g4, g5, g6;
	cout << "Unesite dva grada za koji zelite da znate udaljenost izmedju njih: " << endl;
	getline(cin, g3);
	getline(cin, g4);

	g5 = PretvoriSlova(g3);
	g6 = PretvoriSlova(g4);
//	cout << g5 << " " << g6 << endl;
    if(!JeLiUVektoru(imena, g5) && !JeLiUVektoru(imena, g6))
    {
        cout << "Ta dva grada ne postoje u nasoj bazi podataka."<< endl;
    }

	else if((JeLiUVektoru(imena, g5) && !JeLiUVektoru(imena, g6))  || (!JeLiUVektoru(imena, g5) && JeLiUVektoru(imena, g6)))
    {
        cout << "Jedan od gradova ne postoji u nasoj bazi podataka" << endl;
    }
    else
    {
        cout << "Najkraca udaljenost izmedju ova dva grada je: " << g.Dijkstra(imena, VratiID(imena, g5), VratiID(imena, g6)) << "km";
    }

	string noviGrad, susjedi;
	int brSusjednihGradova, novaUdaljenost;
	cout << endl << "Unesite naziv grada: ";
	cin >> noviGrad;
	noviGrad = PretvoriSlova(noviGrad);
	//fout << endl;
	cout << "Unesite broj susjednih gradova: ";
	cin >> brSusjednihGradova;

	int noviGradovi = brGradova + brSusjednihGradova;

	imena.resize(noviGradovi);

	cout << "Unesite susjedne gradove: " << endl;
	for(int i = 0; i < brSusjednihGradova; i++)
	{
		cout << "Ime grada: ";
		cin >> susjedi;
		susjedi = PretvoriSlova(susjedi);
		cout << "Udaljenost od grada " << susjedi << " do " << noviGrad << ": ";
		cin >> novaUdaljenost;

		if(!JeLiUVektoru(imena, noviGrad))
        {
			g.DodajCvor();
			imena[brojac].ime = noviGrad;
			imena[brojac].ID = brojac;
			brojac++;
        }
		if(!JeLiUVektoru(imena, susjedi))
        {
			g.DodajCvor();
			imena[brojac].ime = susjedi;
			imena[brojac].ID = brojac;
			brojac++;
			//fout << noviGrad << " " << susjedi << " " << novaUdaljenost << endl;
		}
			g.DodajIvicu(VratiID(imena, noviGrad), VratiID(imena, susjedi), novaUdaljenost);
			fout << noviGrad << " " << susjedi << " " << novaUdaljenost << endl;
	}

	fout.close();

	return 0;
}
