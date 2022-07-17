#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;





// ==== STRUCTURI === //


// structura unui component
struct component
{
    char tip[20], nume[50], cod[20];
    // fiecare component are o caracteristica
    // procesor -> frecventa
    // memorii -> capacitate
    // placa video -> viteza memoriei
    char caract[50];
    float pret;
};

// structura unui component
struct calculator
{
    component procesor, placa_video;
    component memorie_ram, memorie_rom;
    float pret;
};

// structura unui component
struct wishlist
{
    calculator PC;
    component piese[100];
};







// ==== FUNCTII ==== //


// functie de convertire char[] -> int / float
/*
    @param s[] = sirul
*/
float charArrayToNum(char s[])
{
    float nr = 0.0; int i;
    for(i = 0; s[i] != '\0' && s[i] != '.'; i++)
        if(s[i] != '.')
            nr = nr * 10 + (s[i] - '0');
    int p = 10;
    unsigned long len = strlen(s) - 1;
    while(i < len)
    {
        nr += (s[i + 1] - '0') / (p * 1.00);
        p *= 10;
        i++;
    }
    return nr;
}

// functie de citire din fisier
/*
    @param x[] = vector de componente
    @param n = numarul de componente
    @param nf[] = numele fisierului
*/
void load(component x[], int &n, char nf[])
{
    ifstream fin(nf);
    fin >> n;
    for(int i = 0; i < n; i++)
    {
        fin.get();
        fin.getline(x[i].nume, 50);
        fin.getline(x[i].caract, 50);
        fin.getline(x[i].cod, 20);
        switch(x[i].cod[0])
        {
            case '0': strcpy(x[i].tip, "procesor");
                      break;
            case '1': strcpy(x[i].tip, "memorie_ram");
                      break;
            case '2': strcpy(x[i].tip, "memorie_rom");
                      break;
            case '3': strcpy(x[i].tip, "placa_video");
                      break;
        }
        fin >> x[i].pret;
    }
    fin.close();
}

// functie de afisare
/*
    @param x[] = vector de componente
    @param n = numarul de componente
*/
void afisare(component x[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << "Tipul: " << x[i].tip << endl;
        cout << "Numele: " << x[i].nume << endl;
        switch(x[i].cod[0])
        {
            case '0': cout << "Frecventa: " << x[i].caract << " GHz" << endl;
                      break;
            case '1': cout << "Capacitate: " << x[i].caract << " GB" << endl;
                      break;
            case '2': cout << "Capacitate: " << x[i].caract << " GB" << endl;
                      break;
            case '3': cout << "Viteza memoriei: " << x[i].caract << " GBps" << endl;
                      break;
        }
        cout << "Pretul: " << x[i].pret << " RON" << endl << endl;
    }
    if(n == 0)
        cout << "Nu exista componente!" << endl << endl;
}

// functie de ordonare
/*
    @param x[] = vector de componente
    @param n = numarul de componente
    @param crit = criteriu (0 = dupa pret, 1 = dupa performanta)
*/
void ordonare(component x[], int n, bool crit)
{
    // ordonam componentele dupa pret
    if(!crit)
    {
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++)
                if(x[i].pret > x[j].pret)
                {
                    component aux = x[i];
                    x[i] = x[j];
                    x[j] = aux;
                }
    }
    // ordonam componentele dupa performanta
    else
    {
        // procesoarele => dupa frecventa
        if(x[0].cod[0] == '0')
        {
            for(int i = 0; i < n - 1; i++)
                for(int j = i + 1; j < n; j++)
                    if(charArrayToNum(x[i].caract) > charArrayToNum(x[j].caract))
                    {
                        component aux = x[i];
                        x[i] = x[j];
                        x[j] = aux;
                    }
        }
        // memoriile => dupa capacitate
        else
            if(x[0].cod[0] == '1' || x[0].cod[0] == '2')
            {
                for(int i = 0; i < n - 1; i++)
                    for(int j = i + 1; j < n; j++)
                        if(charArrayToNum(x[i].caract) > charArrayToNum(x[j].caract))
                        {
                            component aux = x[i];
                            x[i] = x[j];
                            x[j] = aux;
                        }
            }
            // memoriile => dupa viteza memoriei
            else
                if(x[0].cod[0] == '3')
                {
                    for(int i = 0; i < n - 1; i++)
                        for(int j = i + 1; j < n; j++)
                            if(charArrayToNum(x[i].caract) > charArrayToNum(x[j].caract))
                            {
                                component aux = x[i];
                                x[i] = x[j];
                                x[j] = aux;
                            }
                }
    }
}

// functie de validare a unui cod
/*
    @param c[] = codul produsului
*/
bool valid(char c[])
{
    char first_digits[] = "0123";
    if(strlen(c) != 6)
        return false;
    for(int i = 0; c[i] != '\0'; i++)
        if(c[i] < '0' || c[i] > '9')
            return false;
    if(!strchr(first_digits, c[0]))
        return false;
    return true;
}

// functie de validare a unui cod in functie de tipul componentului
/*
    @param c[] = codul produsului
    @param comp_cautat = componentul cautat
*/
bool valid_component(char c[], char comp_cautat)
{
    if(c[0] == comp_cautat)
        return true;
    return false;
}

// functie de stergere din fisier
/*
    @param x[] = vector de componente
    @param n = numarul de componente
*/
void del_fisier(component x[], int &n)
{
    char codul[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Introduceti codul produsului pe care doriti sa il stergeti: ";
    cin.get();
    cin.getline(codul, 50);
    bool found = false;
    system("clear");
    if(valid(codul))
    {
        for(int i = 0; i < n && !found; i++)
            if(!strcmp(x[i].cod, codul))
            {
                found = true;
                for(int j = i; j < n - 1; j++)
                    x[j] = x[j + 1];
            }
        if(found)
        {
            cout << "Componentul a fost sters cu succes!" << endl;
            n--;
        }
        else
            cout << "EROARE, componentul nu exista!" << endl;
    }
    else
        cout << "EROARE, codul nu este valid!" << endl;
}

// functie de cautare component dupa cod
/*
    @param codul[] = codul produsului
*/
component cautare_dupa_cod(char codul[])
{
    char nf[29]; int n;
    switch(codul[0])
    {
        case '0': strcpy(nf, "processors.txt");
                  break;
        case '1': strcpy(nf, "ram_memory.txt");
                  break;
        case '2': strcpy(nf, "rom_memory.txt");
                  break;
        case '3': strcpy(nf, "graphics_cards.txt");
                  break;
    }
    component aux_component[10];
    load(aux_component, n, nf);
    for(int i = 0; i < n; i++)
        if(!strcmp(aux_component[i].cod, codul))
            return aux_component[i];
    component comp_rezidual;
    strcpy(comp_rezidual.cod, "NULL");
    return comp_rezidual;
}

// functie de adaugare la fisier
/*
    @param x[] = vector de componente
    @param n = numarul de componente
*/
void add_fisier(component x[], int &n)
{
    char codul[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Introduceti codul produsului pe care doriti sa il adaugati: ";
    cin.get();
    cin.getline(codul, 50);
    bool exista = false;
    // daca codul ar putea fi valid
    if(valid(codul))
    {
        component component_nou = cautare_dupa_cod(codul);
        system("clear");
        if(!strcmp(component_nou.cod, "NULL"))
            cout << "EROARE, componentul nu exista!" << endl;
        else
        {
            for(int i = 0; i < n; i++)
                if(!strcmp(component_nou.cod, x[i].cod))
                    exista = true;
            if(exista)
            {
                cout << "Componentul exista deja in lista, doriti sa il adaugati oricum?" << endl << endl;
                char op;
                cout << "1.DA" << endl;
                cout << "2.NU" << endl;
                do
                {
                    op = getchar();
                }
                while(op < '1' || op > '2');

                system("clear");
                switch(op)
                {
                    case '1': n++;
                              x[n - 1] = component_nou;
                              cout << "Componentul a fost adaugat cu succes!" << endl;
                              break;
                    case '2': cout << "Componentul nu a fost adaugat!" << endl;
                              break;
                }
            }
            else
            {
                n++;
                x[n - 1] = component_nou;
                cout << "Componentul a fost adaugat cu succes!" << endl;
            }
        }
    }
    else
    {
        system("clear");
        cout << "EROARE, codul nu este valid!" << endl;
    }
}

// functie de adaugare la fisier de catre administrator
/*
    @param x[] = vector de componente
    @param n = numarul de componente
    @param comp_dorit = componentul dorit
*/
void add_fisier_admin(component x[], int &n, char comp_dorit)
{
    char codul[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Introduceti codul produsului pe care doriti sa il adaugati:" << endl << endl;
    cout << "Codul: ";
    cin.get();
    cin.getline(codul, 50);
    if(valid(codul) && valid_component(codul, comp_dorit))
    {
        bool exista = false;
        for(int i = 0; i < n; i++)
            if(!strcmp(codul, x[i].cod))
                exista = true;
        if(exista)
        {
            system("clear");
            cout << "Componentul exista deja in lista, doriti sa il adaugati oricum?" << endl << endl;
            char op;
            cout << "1.DA" << endl;
            cout << "2.NU" << endl;
            do
            {
                op = getchar();
            }
            while(op < '1' || op > '2');

            system("clear");
            switch(op)
            {
                case '1': cout << "Numele: "; cin.getline(x[n].nume, 50);
                          cout << "Caracteristica: "; cin.getline(x[n].caract, 50);
                          cout << "Pretul: "; cin >> x[n].pret;
                          strcpy(x[n].cod, codul);
                          switch(x[n].cod[0])
                          {
                              case '0': strcpy(x[n].tip, "procesor");
                                        break;
                              case '1': strcpy(x[n].tip, "memorie_ram");
                                        break;
                              case '2': strcpy(x[n].tip, "memorie_rom");
                                        break;
                              case '3': strcpy(x[n].tip, "placa_video");
                                        break;
                          }
                          n++;
                          system("clear");
                          cout << "Componentul a fost adaugat cu succes!" << endl;
                          break;
                case '2': cout << "Componentul nu a fost adaugat!" << endl;
                          break;
            }
        }
        else
        {
            cout << "Numele: "; cin.getline(x[n].nume, 50);
            cout << "Caracteristica: "; cin.getline(x[n].caract, 50);
            cout << "Pretul: "; cin >> x[n].pret;
            strcpy(x[n].cod, codul);
            switch(x[n].cod[0])
            {
                case '0': strcpy(x[n].tip, "procesor");
                          break;
                case '1': strcpy(x[n].tip, "memorie_ram");
                          break;
                case '2': strcpy(x[n].tip, "memorie_rom");
                          break;
                case '3': strcpy(x[n].tip, "placa_video");
                          break;
            }
            n++;
            system("clear");
            cout << "Componentul a fost adaugat cu succes!" << endl;
        }
    }
    else
    {
        system("clear");
        cout << "EROARE, codul nu este valid!" << endl;
    }
}

// functie iesire din meniu
/*
    @param wish = semafor pentru decizia utilizatorului
*/
void exit(bool &wish)
{
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Esti sigur ca vrei sa parasesti meniul?" << endl << endl;
    char op;
    cout << "1.DA" << endl;
    cout << "2.NU" << endl;
    do
    {
        op = getchar();
    }
    while(op < '1' || op > '2');

    system("clear");
    switch(op)
    {
        case '1': wish = true; break;
        case '2': wish = false; break;
    }
}

// functie de construire a calculatorului
/*
    @param PC = calculatorul
    @param wl = wishlistul
*/
float build_PC(calculator &PC, wishlist wl)
{
    bool incomplet = false;
    // verificare daca exista piesele necesare unei configuratii
    if(!strcmp(wl.PC.procesor.cod, "NULL") || !strcmp(wl.PC.memorie_ram.cod, "NULL") ||
       !strcmp(wl.PC.memorie_rom.cod, "NULL") ||  !strcmp(wl.PC.placa_video.cod, "NULL"))
            incomplet = true;
    else
    {
        PC.procesor    = wl.PC.procesor;
        PC.memorie_ram = wl.PC.memorie_ram;
        PC.memorie_rom = wl.PC.memorie_rom;
        PC.placa_video = wl.PC.placa_video;
        PC.pret = wl.PC.procesor.pret    +
                  wl.PC.memorie_ram.pret +
                  wl.PC.memorie_rom.pret +
                  wl.PC.placa_video.pret;
    }
    if(incomplet)
        return -1;
    return PC.pret;
}

// functie de salvare a unui fisier
/*
    @param x = vector de componente
    @param n = numarul de componente
    @param nf[] = numele fisierului
*/
void save_fisier(component x[], int n, char nf[])
{
    ofstream fout(nf);
    fout << n << endl;
    for(int i = 0; i < n; i++)
    {
        fout << x[i].nume << endl;
        fout << x[i].caract << endl;
        fout << x[i].cod << endl;
        fout << x[i].pret << endl;
    }
    fout.close();
}

// functie de salvare a wishlist-ului
/*
    @param wl = wishlist-ul
    @param n = numarul de componente
    @param nf[] = numele fisierului
*/
void save_wishlist(wishlist wl, int n, char nf[])
{
    ofstream fout(nf);
    fout << n << endl;
    for(int i = 0; i < n; i++)
    {
        fout << wl.piese[i].nume << endl;
        fout << wl.piese[i].caract << endl;
        fout << wl.piese[i].cod << endl;
        fout << wl.piese[i].pret << endl;
    }
    fout.close();
}

// functie de verificare daca un component exista
/*
    @param comp = componentul verificat
*/
bool exists(component comp)
{
    if(!strcmp(comp.cod, "NULL"))
        return false;
    return true;
}

// functie de construire a calculatorului
/*
    @param wl = wishlist-ul
    @param n = numarul de componente din wishlist
    @param comp_dorit = componentul dorit
*/
void configuratie(wishlist &wl, int n, char comp_dorit)
{
    char codul[50];
    bool found = false;
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Introduceti codul produsului (din wishlist) pe care doriti sa il adaugati: ";
    cin.get();
    cin.getline(codul, 50);
    if(valid(codul))
    {
        for(int i = 0; i < n && !found; i++)
            // daca exista componentul
            if(!strcmp(wl.piese[i].cod, codul))
            {
                // daca este de tipul corect
                if(wl.piese[i].cod[0] == comp_dorit)
                {
                    switch(wl.piese[i].cod[0])
                    {
                        case '0': if(exists(wl.PC.procesor))
                                  {
                                      system("clear");
                                      cout << "Ai deja un procesor!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.procesor = wl.piese[i];
                                      system("clear");
                                      cout << "Ai adaugat procesorul!" << endl;
                                  }
                                  break;
                        case '1': if(exists(wl.PC.memorie_ram))
                                  {
                                      system("clear");
                                      cout << "Ai deja memorie ram!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memorie_ram = wl.piese[i];
                                      system("clear");
                                      cout << "Ai adaugat memoria ram!" << endl;
                                  }
                                  break;
                        case '2': if(exists(wl.PC.memorie_rom))
                                  {
                                      system("clear");
                                      cout << "Ai deja memorie rom!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memorie_rom= wl.piese[i];
                                      system("clear");
                                      cout << "Ai adaugat memoria rom!" << endl;
                                  }
                                  break;
                        case '3': if(exists(wl.PC.placa_video))
                                  {
                                      system("clear");
                                      cout << "Ai deja placa video!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.placa_video = wl.piese[i];
                                      system("clear");
                                      cout << "Ai adaugat placa video!" << endl;
                                  }
                                  break;
                    }
                    found = true;
                }
            }
        if(!found)
        {
            system("clear");
            cout << "EROARE, componentul nu exista sau nu este de tipul corect!" << endl;
        }
    }
    else
    {
        system("clear");
        cout << "EROARE, codul nu este valid!" << endl;
    }
}

// functie de afisare a produsului final
/*
    @param pret = pretul total al calculatorului
    @param PC = calculator
    @param cumparat = semafor, arata daca clientul a cumparat un PC sau nu
*/
void afisare_PC_final(float pret, calculator PC, bool &cumparat)
{
    if(pret == -1)
        cout << "Nu ai toate piesele necesare!" << endl;
    else
    {
        cumparat = true;
        component calc[4];
        calc[0] = PC.procesor;
        calc[1] = PC.memorie_ram;
        calc[2] = PC.memorie_rom;
        calc[3] = PC.placa_video;
        afisare(calc, 4);
        cout << endl << "-------------------------------------" << endl << endl;
        cout << "PRET TOTAL: " << pret << " RON!" << endl;
    }
}

// functie de golire totala a wishlist-ului
/*
    @param pret = pretul total al calculatorului
    @param PC = calculator
    @param cumparat = semafor, arata daca clientul a cumparat un PC sau nu
*/
void empty_fisier(component x[], int &n)
{
    if(n == 0)
        cout << "Wishlist-ul tau este gol!" << endl;
    else
    {
        cout << "Esti sigur ca vrei sa golesti wishlist-ul?" << endl << endl;
        char op;
        cout << "1.DA" << endl;
        cout << "2.NU" << endl;
        do
        {
            op = getchar();
        }
        while(op < '1' || op > '2');

        system("clear");
        if(op == '1')
        {
            n = 0;
            cout << "Wishlist-ul tau a fost golit!" << endl;
        }
        else
            cout << "Wishlist-ul tau nu a fost golit!" << endl;
    }
}








// ==== SUBMENIURI ==== //


// submeniu pentru afisarea elementelor dorite
void afis_comp(component vec_procesoare[],  int nr_procesoare,
               component vec_memorii_ram[], int nr_mem_ram,
               component vec_memorii_rom[], int nr_mem_rom,
               component vec_placi_video[], int nr_plc_vid)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESOARE" << endl;
         cout << "2.MEMORII RAM" << endl;
         cout << "3.MEMORII ROM" << endl;
         cout << "4.PLACI VIDEO" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': afisare(vec_procesoare, nr_procesoare); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': afisare(vec_memorii_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': afisare(vec_memorii_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': afisare(vec_placi_video, nr_plc_vid); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submeniu pentru selectarea criteriului de ordonare
void ordon_criteriu(component vec[], int nr)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.DUPA PRET" << endl;
         cout << "2.DUPA PERFORMANTA" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '1': ordonare(vec, nr, 0); cout << "Ordonarea dupa pret a fost realizata!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': ordonare(vec, nr, 1); cout << "Ordonarea dupa performanta a fost realizata!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
         }
    }
    while(op != '0');
}

// submeniu pentru ordonarea elementelor dorite
void ordon_comp(component vec_procesoare[],  int nr_procesoare,
                component vec_memorii_ram[], int nr_mem_ram,
                component vec_memorii_rom[], int nr_mem_rom,
                component vec_placi_video[], int nr_plc_vid)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESOARE" << endl;
         cout << "2.MEMORII RAM" << endl;
         cout << "3.MEMORII ROM" << endl;
         cout << "4.PLACI VIDEO" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': ordon_criteriu(vec_procesoare, nr_procesoare); cout << endl; break;
             case '2': ordon_criteriu(vec_memorii_ram, nr_mem_ram); cout << endl; break;
             case '3': ordon_criteriu(vec_memorii_rom, nr_mem_rom); cout << endl; break;
             case '4': ordon_criteriu(vec_placi_video, nr_plc_vid); cout << endl; break;
         }
    }
    while(op != '0');
}

// submeniu pentru functia de wishlist
void wishl(component vec_procesoare[],  int nr_procesoare,
           component vec_memorii_ram[], int nr_mem_ram,
           component vec_memorii_rom[], int nr_mem_rom,
           component vec_placi_video[], int nr_plc_vid,
           component x[],               int &nr_piese)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADAUGARE COMPONENT" << endl;
         cout << "2.STERGERE COMPONENT" << endl;
         cout << "3.GOLIRE WISHLIST" << endl;
         cout << "4.AFISARE WISHLIST" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': add_fisier(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': del_fisier(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '3': empty_fisier(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '4': afisare(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
         }
    }
    while(op != '0');
}

// submeniu pentru finalizarea construirii calculatorului
void buildPC(wishlist &wl, calculator &PC, int n, bool &cump)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADAUGARE CPU" << endl;
         cout << "2.ADAUGARE RAM" << endl;
         cout << "3.ADAUGARE ROM" << endl;
         cout << "4.ADAUGARE GPU" << endl;
         cout << "5.BUILD MY PC!" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '5');

         system("clear");
         switch(op)
         {
             // procesorul
             case '1': configuratie(wl, n, '0'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // ram
             case '2': configuratie(wl, n, '1'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // rom
             case '3': configuratie(wl, n, '2'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // placa video
             case '4': configuratie(wl, n, '3'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // construim PC-ul
             case '5': afisare_PC_final(build_PC(PC, wl), PC, cump); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
         }
    }
    while(op != '0');
}

// submeniu pentru adaugarea unui component
void adaugare(component vec_procesoare[],  int &nr_procesoare,
              component vec_memorii_ram[], int &nr_mem_ram,
              component vec_memorii_rom[], int &nr_mem_rom,
              component vec_placi_video[], int &nr_plc_vid)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESOR" << endl;
         cout << "2.MEMORIE RAM" << endl;
         cout << "3.MEMORIE ROM" << endl;
         cout << "4.PLACA VIDEO" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': add_fisier_admin(vec_procesoare, nr_procesoare, '0'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': add_fisier_admin(vec_memorii_ram, nr_mem_ram, '1'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': add_fisier_admin(vec_memorii_rom, nr_mem_rom, '2'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': add_fisier_admin(vec_placi_video, nr_plc_vid, '3'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submeniu pentru stergerea unui component
void stergere(component vec_procesoare[],  int &nr_procesoare,
              component vec_memorii_ram[], int &nr_mem_ram,
              component vec_memorii_rom[], int &nr_mem_rom,
              component vec_placi_video[], int &nr_plc_vid)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESOR" << endl;
         cout << "2.MEMORIE RAM" << endl;
         cout << "3.MEMORIE ROM" << endl;
         cout << "4.PLACA VIDEO" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': del_fisier(vec_procesoare, nr_procesoare); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': del_fisier(vec_memorii_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': del_fisier(vec_memorii_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': del_fisier(vec_placi_video, nr_plc_vid); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submeniu pentru functia de modificare
void modif(component vec_procesoare[],  int &nr_procesoare,
           component vec_memorii_ram[], int &nr_mem_ram,
           component vec_memorii_rom[], int &nr_mem_rom,
           component vec_placi_video[], int &nr_plc_vid)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADAUGARE COMPONENT" << endl;
         cout << "2.STERGERE COMPONENT" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '1': adaugare(vec_procesoare,  nr_procesoare,
                                vec_memorii_ram, nr_mem_ram,
                                vec_memorii_rom, nr_mem_rom,
                                vec_placi_video, nr_plc_vid);
                                cout << endl;
                       break;
             case '2': stergere(vec_procesoare,  nr_procesoare,
                                vec_memorii_ram, nr_mem_ram,
                                vec_memorii_rom, nr_mem_rom,
                                vec_placi_video, nr_plc_vid);
                                cout << endl;
                       break;
         }
    }
    while(op != '0');
}


// submeniu => client
void client(component vec_procesoare[],  int nr_procesoare,
            component vec_memorii_ram[], int nr_mem_ram,
            component vec_memorii_rom[], int nr_mem_rom,
            component vec_placi_video[], int nr_plc_vid,
            wishlist &wl,                int &nr_piese,
            calculator &PC,              char nf[])

{
    // verificam daca clientul cumpara ceva pentru personalizarea mesajului de iesire
    bool cumparat = false;
    // tinem minte daca utilizatorul doreste sa iasa din meniu sau nu
    bool wish_exit = false;

    char op;
    do
    {
        system("clear");
        cout << "\b----- PC BUILDER -----" << endl << endl;
        cout << "1.AFISARE" << endl;
        cout << "2.ORDONARE" << endl;
        cout << "3.WISHLIST" << endl;
        cout << "4.BUILD PC" << endl;
        cout << "0.IESIRE" << endl;
        do
        {
            op = getchar();
        }
        while(op < '0' || op > '4');

        system("clear");
        switch(op)
        {
            case '0': exit(wish_exit); break;
            case '1': afis_comp(vec_procesoare,  nr_procesoare,
                                vec_memorii_ram, nr_mem_ram,
                                vec_memorii_rom, nr_mem_rom,
                                vec_placi_video, nr_plc_vid);
                      break;
            case '2': ordon_comp(vec_procesoare,  nr_procesoare,
                                 vec_memorii_ram, nr_mem_ram,
                                 vec_memorii_rom, nr_mem_rom,
                                 vec_placi_video, nr_plc_vid);
                      break;
            case '3': wishl(vec_procesoare,  nr_procesoare,
                            vec_memorii_ram, nr_mem_ram,
                            vec_memorii_rom, nr_mem_rom,
                            vec_placi_video, nr_plc_vid,
                            wl.piese, nr_piese);
                      break;
            case '4': buildPC(wl, PC, nr_piese, cumparat);
        }
    }
    while(!wish_exit);
    save_wishlist(wl, nr_piese, nf);
}

// submeniu => admin
void admin(component vec_procesoare[],  int &nr_procesoare,
           component vec_memorii_ram[], int &nr_mem_ram,
           component vec_memorii_rom[], int &nr_mem_rom,
           component vec_placi_video[], int &nr_plc_vid,
           char nf_proc[], char nf_mem_ram[], char nf_mem_rom[], char nf_plc_vid[])

{
    // tinem minte daca utilizatorul doreste sa iasa din meniu sau nu
    bool wish_exit = false;

    char op;
    do
    {
        system("clear");
        cout << "\b----- PC BUILDER -----" << endl << endl;
        cout << "1.AFISARE" << endl;
        cout << "2.ORDONARE" << endl;
        cout << "3.MODIFICARE" << endl;
        cout << "0.IESIRE" << endl;
        do
        {
            op = getchar();
        }
        while(op < '0' || op > '3');

        system("clear");
        switch(op)
        {
            case '0': exit(wish_exit); break;
            case '1': afis_comp(vec_procesoare,  nr_procesoare,
                                vec_memorii_ram, nr_mem_ram,
                                vec_memorii_rom, nr_mem_rom,
                                vec_placi_video, nr_plc_vid);
                      break;
            case '2': ordon_comp(vec_procesoare,  nr_procesoare,
                                 vec_memorii_ram, nr_mem_ram,
                                 vec_memorii_rom, nr_mem_rom,
                                 vec_placi_video, nr_plc_vid);
                      break;
            case '3': modif(vec_procesoare,  nr_procesoare,
                            vec_memorii_ram, nr_mem_ram,
                            vec_memorii_rom, nr_mem_rom,
                            vec_placi_video, nr_plc_vid);
                      break;
        }
    }
    while(!wish_exit);
    save_fisier(vec_procesoare, nr_procesoare, nf_proc);
    save_fisier(vec_memorii_ram, nr_mem_ram, nf_mem_ram);
    save_fisier(vec_memorii_rom, nr_mem_rom, nf_mem_rom);
    save_fisier(vec_placi_video, nr_plc_vid, nf_plc_vid);
}






// ==== MENIUL ====  //


void meniu(wishlist &wl, calculator &PC)
{
    int nr_procesoare, nr_mem_ram, nr_mem_rom, nr_plc_vid, nr_piese;
    component vec_procesoare[50];
    component vec_memorii_ram[50];
    component vec_memorii_rom[50];
    component vec_placi_video[50];

    // citim procesoarele
    char f1[] = "processors.txt";
    load(vec_procesoare, nr_procesoare, f1);

    // citim procesoarele
    char f2[] = "ram_memory.txt";
    load(vec_memorii_ram, nr_mem_ram, f2);

    // citim procesoarele
    char f3[] = "rom_memory.txt";
    load(vec_memorii_rom, nr_mem_rom, f3);

    // citim procesoarele
    char f4[] = "graphics_cards.txt";
    load(vec_placi_video, nr_plc_vid, f4);

    char f5[] = "wishlist.txt";
    load(wl.piese, nr_piese, f5);

    // la inceput marcam toate componentele din PC ca fiind inexistente
    strcpy(wl.PC.procesor.cod, "NULL");
    strcpy(wl.PC.memorie_ram.cod, "NULL");
    strcpy(wl.PC.memorie_rom.cod, "NULL");
    strcpy(wl.PC.placa_video.cod, "NULL");

    // tinem minte daca utilizatorul doreste sa iasa din meniu sau nu
    bool wish_exit = false;

    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADMINISTRATOR" << endl;
         cout << "2.CLIENT" << endl;
         cout << "0.IESIRE" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '0': exit(wish_exit); break;
             case '1': admin(vec_procesoare,  nr_procesoare,
                             vec_memorii_ram, nr_mem_ram,
                             vec_memorii_rom, nr_mem_rom,
                             vec_placi_video, nr_plc_vid,
                             f1, f2, f3, f4); cout << endl;
                             break;
             case '2': client(vec_procesoare,  nr_procesoare,
                              vec_memorii_ram, nr_mem_ram,
                              vec_memorii_rom, nr_mem_rom,
                              vec_placi_video, nr_plc_vid,
                              wl, nr_piese, PC, f5); cout << endl;
                              break;
         }
    }
    while(!wish_exit);
}






// ==== MAIN ==== //
int main()
{
    wishlist myWishlist; calculator PC;
    meniu(myWishlist, PC);
    
    return 0;
}


