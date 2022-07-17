#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;





// ==== STRUCTURES === //


// structure of a component
struct component
{
    char type[20], name[50], code[20];
    // every component has a feature
    // procesor -> clock speed
    // memorii -> memory
    // placa video -> memory clock
    char feature[50];
    float price;
};

// structure of a PC
struct computer
{
    component processor, graphics_card;
    component memory_ram, memory_rom;
    float price;
};

// structure of a wishlist
struct wishlist
{
    computer PC;
    component comp[100];
};







// ==== FUNCTIONS ==== //


// convertion char[] -> int / float
/*
    @param s[] = string of chars
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

// file reading function
/*
    @param x[] = array of components
    @param n = number of components
    @param nf[] = name of file
*/
void load(component x[], int &n, char nf[])
{
    ifstream fin(nf);
    fin >> n;
    for(int i = 0; i < n; i++)
    {
        fin.get();
        fin.getline(x[i].name, 50);
        fin.getline(x[i].feature, 50);
        fin.getline(x[i].code, 20);
        switch(x[i].code[0])
        {
            case '0': strcpy(x[i].type, "processor");
                      break;
            case '1': strcpy(x[i].type, "memory_ram");
                      break;
            case '2': strcpy(x[i].type, "memory_rom");
                      break;
            case '3': strcpy(x[i].type, "graphics_card");
                      break;
        }
        fin >> x[i].price;
    }
    fin.close();
}

// output function
/*
    @param x[] = array of components
    @param n = number of components
*/
void output(component x[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << "Type: " << x[i].type << endl;
        cout << "Name: " << x[i].name << endl;
        switch(x[i].code[0])
        {
            case '0': cout << "Clock speed: " << x[i].feature << " GHz" << endl;
                      break;
            case '1': cout << "Memory: " << x[i].feature << " GB" << endl;
                      break;
            case '2': cout << "Memory: " << x[i].feature << " GB" << endl;
                      break;
            case '3': cout << "Memory clock: " << x[i].feature << " GBps" << endl;
                      break;
        }
        cout << "Price: " << x[i].price << " EUR" << endl << endl;
    }
    if(n == 0)
        cout << "No components!" << endl << endl;
}

// sorting function
/*
    @param x[] = array of components
    @param n = number of components
    @param crit = criteria (0 = price, 1 = performance)
*/
void sort(component x[], int n, bool crit)
{
    // price
    if(!crit)
    {
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++)
                if(x[i].price > x[j].price)
                {
                    component aux = x[i];
                    x[i] = x[j];
                    x[j] = aux;
                }
    }
    // performance
    else
    {
        // processors => clock speed
        if(x[0].code[0] == '0')
        {
            for(int i = 0; i < n - 1; i++)
                for(int j = i + 1; j < n; j++)
                    if(charArrayToNum(x[i].feature) > charArrayToNum(x[j].feature))
                    {
                        component aux = x[i];
                        x[i] = x[j];
                        x[j] = aux;
                    }
        }
        // memory => capacity
        else
            if(x[0].code[0] == '1' || x[0].code[0] == '2')
            {
                for(int i = 0; i < n - 1; i++)
                    for(int j = i + 1; j < n; j++)
                        if(charArrayToNum(x[i].feature) > charArrayToNum(x[j].feature))
                        {
                            component aux = x[i];
                            x[i] = x[j];
                            x[j] = aux;
                        }
            }
            // graphics cards => memory clock
            else
                if(x[0].code[0] == '3')
                {
                    for(int i = 0; i < n - 1; i++)
                        for(int j = i + 1; j < n; j++)
                            if(charArrayToNum(x[i].feature) > charArrayToNum(x[j].feature))
                            {
                                component aux = x[i];
                                x[i] = x[j];
                                x[j] = aux;
                            }
                }
    }
}

// code validation function
/*
    @param c[] = code of the product
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

// code validation with given component type
/*
    @param c[] = code of the product
    @param comp_wanted = wanted component
*/
bool valid_component(char c[], char comp_wanted)
{
    if(c[0] == comp_wanted)
        return true;
    return false;
}

// delete from file function
/*
    @param x[] = array of components
    @param n = number of components
*/
void del_file(component x[], int &n)
{
    char codul[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Enter code of product you wish to delete: ";
    cin.get();
    cin.getline(codul, 50);
    bool found = false;
    system("clear");
    if(valid(codul))
    {
        for(int i = 0; i < n && !found; i++)
            if(!strcmp(x[i].code, codul))
            {
                found = true;
                for(int j = i; j < n - 1; j++)
                    x[j] = x[j + 1];
            }
        if(found)
        {
            cout << "Product successfully deleted!" << endl;
            n--;
        }
        else
            cout << "ERROR, product does not exist!" << endl;
    }
    else
        cout << "ERROR, code is not valid!" << endl;
}

// function to search for a component
/*
    @param code[] = code of product
*/
component search_using_code(char code[])
{
    char nf[29]; int n;
    switch(code[0])
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
        if(!strcmp(aux_component[i].code, code))
            return aux_component[i];
    component comp_residual;
    strcpy(comp_residual.code, "NULL");
    return comp_residual;
}

// add to file function
/*
    @param x[] = array of components
    @param n = number of components
*/
void add_file(component x[], int &n)
{
    char code[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Enter code of product you wish to add: ";
    cin.get();
    cin.getline(code, 50);
    bool exists = false;
    // if code is valid
    if(valid(code))
    {
        component component_new = search_using_code(code);
        system("clear");
        if(!strcmp(component_new.code, "NULL"))
            cout << "ERROR, product does not exist!" << endl;
        else
        {
            for(int i = 0; i < n; i++)
                if(!strcmp(component_new.code, x[i].code))
                    exists = true;
            if(exists)
            {
                cout << "Product is already in stock, add it anyway?" << endl << endl;
                char op;
                cout << "1.YES" << endl;
                cout << "2.NO" << endl;
                do
                {
                    op = getchar();
                }
                while(op < '1' || op > '2');

                system("clear");
                switch(op)
                {
                    case '1': n++;
                              x[n - 1] = component_new;
                              cout << "Product successfully added!" << endl;
                              break;
                    case '2': cout << "Product not added!" << endl;
                              break;
                }
            }
            else
            {
                n++;
                x[n - 1] = component_new;
                cout << "Product successfully deleted!" << endl;
            }
        }
    }
    else
    {
        system("clear");
        cout << "ERROR, code is not valid!" << endl;
    }
}

// function to add to file by the admin
/*
    @param x[] = array of components
    @param n = number of components
    @param comp_wanted = component wanted
*/
void add_file_admin(component x[], int &n, char comp_wanted)
{
    char code[50];
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Enter code of product you wish to add: " << endl << endl;
    cout << "Code: ";
    cin.get();
    cin.getline(code, 50);
    if(valid(code) && valid_component(code, comp_wanted))
    {
        bool exists = false;
        for(int i = 0; i < n; i++)
            if(!strcmp(code, x[i].code))
                exists = true;
        if(exists)
        {
            system("clear");
            cout << "Product is already in stock, add it anyway?" << endl << endl;
            char op;
            cout << "1.YES" << endl;
            cout << "2.NO" << endl;
            do
            {
                op = getchar();
            }
            while(op < '1' || op > '2');

            system("clear");
            switch(op)
            {
                case '1': cout << "Name: "; cin.getline(x[n].name, 50);
                          cout << "Feature: "; cin.getline(x[n].feature, 50);
                          cout << "Price: "; cin >> x[n].price;
                          strcpy(x[n].code, code);
                          switch(x[n].code[0])
                          {
                              case '0': strcpy(x[n].type, "processor");
                                        break;
                              case '1': strcpy(x[n].type, "memory_ram");
                                        break;
                              case '2': strcpy(x[n].type, "memory_rom");
                                        break;
                              case '3': strcpy(x[n].type, "graphics_card");
                                        break;
                          }
                          n++;
                          system("clear");
                          cout << "Product successfully added!" << endl;
                          break;
                case '2': cout << "Product not added!" << endl;
                          break;
            }
        }
        else
        {
            cout << "Name: "; cin.getline(x[n].name, 50);
            cout << "Feature: "; cin.getline(x[n].feature, 50);
            cout << "Price: "; cin >> x[n].price;
            strcpy(x[n].code, code);
            switch(x[n].code[0])
            {
                case '0': strcpy(x[n].type, "processor");
                          break;
                case '1': strcpy(x[n].type, "memory_ram");
                          break;
                case '2': strcpy(x[n].type, "memory_rom");
                          break;
                case '3': strcpy(x[n].type, "graphics_card");
                          break;
            }
            n++;
            system("clear");
            cout << "Product successfully added!" << endl;
        }
    }
    else
    {
        system("clear");
        cout << "ERROR, code is not valid!" << endl;
    }
}

// exit menu function
/*
    @param wish = wish to exit the menu
*/
void exit(bool &wish)
{
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Are you sure you want to exit?" << endl << endl;
    char op;
    cout << "1.YES" << endl;
    cout << "2.NO" << endl;
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

// function to build PC
/*
    @param PC = PC
    @param wl = wishlist
*/
float build_PC(computer &PC, wishlist wl)
{
    bool incomplete = false;
    // verificare daca exista piesele necesare unei configuratii
    if(!strcmp(wl.PC.processor.code, "NULL") || !strcmp(wl.PC.memory_ram.code, "NULL") ||
       !strcmp(wl.PC.memory_rom.code, "NULL") ||  !strcmp(wl.PC.graphics_card.code, "NULL"))
            incomplete = true;
    else
    {
        PC.processor    = wl.PC.processor;
        PC.memory_ram = wl.PC.memory_ram;
        PC.memory_rom = wl.PC.memory_rom;
        PC.graphics_card = wl.PC.graphics_card;
        PC.price = wl.PC.processor.price    +
                  wl.PC.memory_ram.price +
                  wl.PC.memory_rom.price +
                  wl.PC.graphics_card.price;
    }
    if(incomplete)
        return -1;
    return PC.price;
}

// function to save file changes
/*
    @param x[] = array of components
    @param n = number of components
    @param nf[] = name of file
*/
void save_file(component x[], int n, char nf[])
{
    ofstream fout(nf);
    fout << n << endl;
    for(int i = 0; i < n; i++)
    {
        fout << x[i].name << endl;
        fout << x[i].feature << endl;
        fout << x[i].code << endl;
        fout << x[i].price << endl;
    }
    fout.close();
}

// function to save wishlist
/*
    @param wl = wishlist
    @param n = number of components
    @param nf[] = name of file
*/
void save_wishlist(wishlist wl, int n, char nf[])
{
    ofstream fout(nf);
    fout << n << endl;
    for(int i = 0; i < n; i++)
    {
        fout << wl.comp[i].name << endl;
        fout << wl.comp[i].feature << endl;
        fout << wl.comp[i].code << endl;
        fout << wl.comp[i].price << endl;
    }
    fout.close();
}

// function to check if a product exists
/*
    @param comp = component checked
*/
bool exists(component comp)
{
    if(!strcmp(comp.code, "NULL"))
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
            if(!strcmp(wl.comp[i].code, codul))
            {
                // daca este de tipul corect
                if(wl.comp[i].code[0] == comp_dorit)
                {
                    switch(wl.comp[i].code[0])
                    {
                        case '0': if(exists(wl.PC.processor))
                                  {
                                      system("clear");
                                      cout << "Ai deja un procesor!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.processor = wl.comp[i];
                                      system("clear");
                                      cout << "Ai adaugat procesorul!" << endl;
                                  }
                                  break;
                        case '1': if(exists(wl.PC.memory_ram))
                                  {
                                      system("clear");
                                      cout << "Ai deja memorie ram!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memory_ram = wl.comp[i];
                                      system("clear");
                                      cout << "Ai adaugat memoria ram!" << endl;
                                  }
                                  break;
                        case '2': if(exists(wl.PC.memory_rom))
                                  {
                                      system("clear");
                                      cout << "Ai deja memorie rom!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memory_rom= wl.comp[i];
                                      system("clear");
                                      cout << "Ai adaugat memoria rom!" << endl;
                                  }
                                  break;
                        case '3': if(exists(wl.PC.graphics_card))
                                  {
                                      system("clear");
                                      cout << "Ai deja placa video!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.graphics_card = wl.comp[i];
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
void afisare_PC_final(float pret, computer PC, bool &cumparat)
{
    if(pret == -1)
        cout << "Nu ai toate piesele necesare!" << endl;
    else
    {
        cumparat = true;
        component calc[4];
        calc[0] = PC.processor;
        calc[1] = PC.memory_ram;
        calc[2] = PC.memory_rom;
        calc[3] = PC.graphics_card;
        output(calc, 4);
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
             case '1': output(vec_procesoare, nr_procesoare); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': output(vec_memorii_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': output(vec_memorii_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': output(vec_placi_video, nr_plc_vid); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
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
             case '1': sort(vec, nr, 0); cout << "Ordonarea dupa pret a fost realizata!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': sort(vec, nr, 1); cout << "Ordonarea dupa performanta a fost realizata!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
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
             case '1': add_file(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': del_file(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '3': empty_fisier(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '4': output(x, nr_piese); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
         }
    }
    while(op != '0');
}

// submeniu pentru finalizarea construirii calculatorului
void buildPC(wishlist &wl, computer &PC, int n, bool &cump)
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
             case '1': add_file_admin(vec_procesoare, nr_procesoare, '0'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': add_file_admin(vec_memorii_ram, nr_mem_ram, '1'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': add_file_admin(vec_memorii_rom, nr_mem_rom, '2'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': add_file_admin(vec_placi_video, nr_plc_vid, '3'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
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
             case '1': del_file(vec_procesoare, nr_procesoare); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': del_file(vec_memorii_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': del_file(vec_memorii_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': del_file(vec_placi_video, nr_plc_vid); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
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
            computer &PC,              char nf[])

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
                            wl.comp, nr_piese);
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
    save_file(vec_procesoare, nr_procesoare, nf_proc);
    save_file(vec_memorii_ram, nr_mem_ram, nf_mem_ram);
    save_file(vec_memorii_rom, nr_mem_rom, nf_mem_rom);
    save_file(vec_placi_video, nr_plc_vid, nf_plc_vid);
}






// ==== MENIUL ====  //


void meniu(wishlist &wl, computer &PC)
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
    load(wl.comp, nr_piese, f5);

    // la inceput marcam toate componentele din PC ca fiind inexistente
    strcpy(wl.PC.processor.code, "NULL");
    strcpy(wl.PC.memory_ram.code, "NULL");
    strcpy(wl.PC.memory_rom.code, "NULL");
    strcpy(wl.PC.graphics_card.code, "NULL");

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
    wishlist myWishlist; computer PC;
    meniu(myWishlist, PC);
    
    return 0;
}


