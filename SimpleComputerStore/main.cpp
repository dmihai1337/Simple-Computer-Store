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
    // processor -> clock speed
    // memory -> memory
    // graphics card -> memory clock
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







// ==== METHODS ==== //


// method conversion char[] -> int / float
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

// file reading method
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

// output method
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

// sorting method
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

// code validation method
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

// code validation with given component type method
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

// delete from file method
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

// method to search for a component
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

// add to file method
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

// method to add to file by the admin
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

// exit menu method
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

// method to build PC
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

// method to save file changes
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

// method to save wishlist
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

// method to check if a product exists
/*
    @param comp = component checked
*/
bool exists(component comp)
{
    if(!strcmp(comp.code, "NULL"))
        return false;
    return true;
}

// method to configure PC
/*
    @param wl = wishlist
    @param n = number of components
    @param comp_wanted = component wanted
*/
void config(wishlist &wl, int n, char comp_wanted)
{
    char code[50];
    bool found = false;
    cout << "\b----- PC BUILDER -----" << endl << endl;
    cout << "Enter code of the product (from wishlist) you would like to add: ";
    cin.get();
    cin.getline(code, 50);
    if(valid(code))
    {
        for(int i = 0; i < n && !found; i++)
            // if product exists
            if(!strcmp(wl.comp[i].code, code))
            {
                // if the type is correct
                if(wl.comp[i].code[0] == comp_wanted)
                {
                    switch(wl.comp[i].code[0])
                    {
                        case '0': if(exists(wl.PC.processor))
                                  {
                                      system("clear");
                                      cout << "You already have a processor!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.processor = wl.comp[i];
                                      system("clear");
                                      cout << "You added the processor!" << endl;
                                  }
                                  break;
                        case '1': if(exists(wl.PC.memory_ram))
                                  {
                                      system("clear");
                                      cout << "You already have a ram memory!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memory_ram = wl.comp[i];
                                      system("clear");
                                      cout << "You added the ram memory!" << endl;
                                  }
                                  break;
                        case '2': if(exists(wl.PC.memory_rom))
                                  {
                                      system("clear");
                                      cout << "You already have a rom memory!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.memory_rom= wl.comp[i];
                                      system("clear");
                                      cout << "You added the rom memory!" << endl;
                                  }
                                  break;
                        case '3': if(exists(wl.PC.graphics_card))
                                  {
                                      system("clear");
                                      cout << "You already have a graphics card!" << endl;
                                  }
                                  else
                                  {
                                      wl.PC.graphics_card = wl.comp[i];
                                      system("clear");
                                      cout << "You added the graphics card!" << endl;
                                  }
                                  break;
                    }
                    found = true;
                }
            }
        if(!found)
        {
            system("clear");
            cout << "ERROR, product does not exist or is not of the correct type!" << endl;
        }
    }
    else
    {
        system("clear");
        cout << "ERROR, code is not valid!" << endl;
    }
}

// method to output final build
/*
    @param price = total price of PC
    @param PC = PC
    @param bought = boolean to see if customer has bought or not
*/
void output_PC_final(float price, computer PC, bool &bought)
{
    if(price == -1)
        cout << "You don't have all the necessary components!" << endl;
    else
    {
        bought = true;
        component calc[4];
        calc[0] = PC.processor;
        calc[1] = PC.memory_ram;
        calc[2] = PC.memory_rom;
        calc[3] = PC.graphics_card;
        output(calc, 4);
        cout << endl << "-------------------------------------" << endl << endl;
        cout << "TOTAL PRICE: " << price << " EUR!" << endl;
    }
}

// method to empty wishlist
/*
    @param x[] = array of components
    @param n = number of components
*/
void empty_file(component x[], int &n)
{
    if(n == 0)
        cout << "Your wishlist is empty!" << endl;
    else
    {
        cout << "Are you sure you want to empty the wishlist?" << endl << endl;
        char op;
        cout << "1.YES" << endl;
        cout << "2.NO" << endl;
        do
        {
            op = getchar();
        }
        while(op < '1' || op > '2');

        system("clear");
        if(op == '1')
        {
            n = 0;
            cout << "Your wishlist has been emptied!" << endl;
        }
        else
            cout << "Your wishlist has not been emptied!" << endl;
    }
}








// ==== SUBMENUS ==== //


// submenu for outputing desired components
void out_comp( component vec_processors[],      int nr_processors,
               component vec_memory_ram[],     int nr_mem_ram,
               component vec_memory_rom[],     int nr_mem_rom,
               component vec_graphics_cards[], int nr_graph_cards)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESSORS" << endl;
         cout << "2.RAM MEMORY" << endl;
         cout << "3.ROM MEMORY" << endl;
         cout << "4.GRAPHICS CARDS" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': output(vec_processors, nr_processors); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': output(vec_memory_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': output(vec_memory_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': output(vec_graphics_cards, nr_graph_cards); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submenu for selecting sorting criteria
void sort_crit(component vec[], int nr)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ACCORDING TO PRICE" << endl;
         cout << "2.ACCORDING TO PERFORMANCE" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '1': sort(vec, nr, 0); cout << "Price sorting has been successfully completed!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': sort(vec, nr, 1); cout << "Performance sorting has been successfully completed!"; cout << endl << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
         }
    }
    while(op != '0');
}

// submenu for selecting what to sort
void sort_comp( component vec_processors[],     int nr_processors,
                component vec_memory_ram[],     int nr_mem_ram,
                component vec_memory_rom[],     int nr_mem_rom,
                component vec_graphics_cards[], int nr_graph_cards)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESSORS" << endl;
         cout << "2.RAM MEMORY" << endl;
         cout << "3.ROM MEMORY" << endl;
         cout << "4.GRAPHICS CARDS" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': sort_crit(vec_processors, nr_processors); cout << endl; break;
             case '2': sort_crit(vec_memory_ram, nr_mem_ram); cout << endl; break;
             case '3': sort_crit(vec_memory_rom, nr_mem_rom); cout << endl; break;
             case '4': sort_crit(vec_graphics_cards, nr_graph_cards); cout << endl; break;
         }
    }
    while(op != '0');
}

// wishlist submenu
void wishl(component vec_processors[],     int nr_processors,
           component vec_memory_ram[],     int nr_mem_ram,
           component vec_memory_rom[],     int nr_mem_rom,
           component vec_graphics_cards[], int nr_graph_cards,
           component x[],               int &nr_comp)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADD COMPONENT" << endl;
         cout << "2.DELETE COMPONENT" << endl;
         cout << "3.EMPTY WISHLIST" << endl;
         cout << "4.OUTPUT WISHLIST" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': add_file(x, nr_comp); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '2': del_file(x, nr_comp); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '3': empty_file(x, nr_comp); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
             case '4': output(x, nr_comp); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
                       break;
         }
    }
    while(op != '0');
}

// submenu for building PC
void buildPC(wishlist &wl, computer &PC, int n, bool &bought)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADD CPU" << endl;
         cout << "2.ADD RAM" << endl;
         cout << "3.ADD ROM" << endl;
         cout << "4.ADD GPU" << endl;
         cout << "5.BUILD MY PC!" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '5');

         system("clear");
         switch(op)
         {
             // processor
             case '1': config(wl, n, '0'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // ram
             case '2': config(wl, n, '1'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // rom
             case '3': config(wl, n, '2'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // graphics card
             case '4': config(wl, n, '3'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             // build PC
             case '5': output_PC_final(build_PC(PC, wl), PC, bought); cout << endl << system("read -n 1 -s -p\"Press any key!\n\"");
         }
    }
    while(op != '0');
}

// submenu for adding component
void adding  (component vec_processors[],     int nr_processors,
              component vec_memory_ram[],     int nr_mem_ram,
              component vec_memory_rom[],     int nr_mem_rom,
              component vec_graphics_cards[], int nr_graph_cards)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESSOR" << endl;
         cout << "2.RAM MEMORY" << endl;
         cout << "3.ROM MEMORY" << endl;
         cout << "4.GRAPHICS CARD" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': add_file_admin(vec_processors, nr_processors, '0'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': add_file_admin(vec_memory_ram, nr_mem_ram, '1'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': add_file_admin(vec_memory_rom, nr_mem_rom, '2'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': add_file_admin(vec_graphics_cards, nr_graph_cards, '3'); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submenu for deleting component
void deleting(component vec_processors[],     int nr_processors,
              component vec_memory_ram[],     int nr_mem_ram,
              component vec_memory_rom[],     int nr_mem_rom,
              component vec_graphics_cards[], int nr_graph_cards)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.PROCESSOR" << endl;
         cout << "2.RAM MEMORY" << endl;
         cout << "3.ROM MEMORY" << endl;
         cout << "4.GRAPHICS CARD" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '4');

         system("clear");
         switch(op)
         {
             case '1': del_file(vec_processors, nr_processors); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '2': del_file(vec_memory_ram, nr_mem_ram); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '3': del_file(vec_memory_rom, nr_mem_rom); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
             case '4': del_file(vec_graphics_cards, nr_graph_cards); cout << endl << system("read -n 1 -s -p\"Press any key!\n\""); break;
         }
    }
    while(op != '0');
}

// submenu for editing
void edit (component vec_processors[],     int nr_processors,
           component vec_memory_ram[],     int nr_mem_ram,
           component vec_memory_rom[],     int nr_mem_rom,
           component vec_graphics_cards[], int nr_graph_cards)
{
    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADD COMPONENT" << endl;
         cout << "2.DELETE COMPONENT" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '1': adding(vec_processors,  nr_processors,
                              vec_memory_ram, nr_mem_ram,
                              vec_memory_rom, nr_mem_rom,
                              vec_graphics_cards, nr_graph_cards);
                              cout << endl;
                       break;
             case '2': deleting(vec_processors,  nr_processors,
                                vec_memory_ram, nr_mem_ram,
                                vec_memory_rom, nr_mem_rom,
                                vec_graphics_cards, nr_graph_cards);
                                cout << endl;
                       break;
         }
    }
    while(op != '0');
}


// submenu => customer
void client(component vec_processors[],     int nr_processors,
            component vec_memory_ram[],     int nr_mem_ram,
            component vec_memory_rom[],     int nr_mem_rom,
            component vec_graphics_cards[], int nr_graph_cards,
            wishlist &wl,                   int &nr_comp,
            computer &PC,                   char nf[])

{
    // check if customer has bought PC
    bool bought = false;
    // if customer wants to leave the menu
    bool wish_exit = false;

    char op;
    do
    {
        system("clear");
        cout << "\b----- PC BUILDER -----" << endl << endl;
        cout << "1.OUTPUT" << endl;
        cout << "2.SORT" << endl;
        cout << "3.WISHLIST" << endl;
        cout << "4.BUILD PC" << endl;
        cout << "0.EXIT" << endl;
        do
        {
            op = getchar();
        }
        while(op < '0' || op > '4');

        system("clear");
        switch(op)
        {
            case '0': exit(wish_exit); break;
            case '1': out_comp(vec_processors,  nr_processors,
                               vec_memory_ram, nr_mem_ram,
                               vec_memory_rom, nr_mem_rom,
                               vec_graphics_cards, nr_graph_cards);
                      break;
            case '2': sort_comp(vec_processors,  nr_processors,
                                vec_memory_ram, nr_mem_ram,
                                vec_memory_rom, nr_mem_rom,
                                vec_graphics_cards, nr_graph_cards);
                      break;
            case '3': wishl(vec_processors,  nr_processors,
                            vec_memory_ram, nr_mem_ram,
                            vec_memory_rom, nr_mem_rom,
                            vec_graphics_cards, nr_graph_cards,
                            wl.comp, nr_comp);
                      break;
            case '4': buildPC(wl, PC, nr_comp, bought);
        }
    }
    while(!wish_exit);
    save_wishlist(wl, nr_comp, nf);
}

// submenu => admin
void admin(component vec_processors[],     int nr_processors,
           component vec_memory_ram[],     int nr_mem_ram,
           component vec_memory_rom[],     int nr_mem_rom,
           component vec_graphics_cards[], int nr_graph_cards,
           char nf_proc[], char nf_mem_ram[], char nf_mem_rom[], char nf_graph_cards[])

{
    // if customer wants to leave the menu
    bool wish_exit = false;

    char op;
    do
    {
        system("clear");
        cout << "\b----- PC BUILDER -----" << endl << endl;
        cout << "1.OUTPUT" << endl;
        cout << "2.SORT" << endl;
        cout << "3.EDIT" << endl;
        cout << "0.EXIT" << endl;
        do
        {
            op = getchar();
        }
        while(op < '0' || op > '3');

        system("clear");
        switch(op)
        {
            case '0': exit(wish_exit); break;
            case '1': out_comp(vec_processors,  nr_processors,
                               vec_memory_ram, nr_mem_ram,
                               vec_memory_rom, nr_mem_rom,
                               vec_graphics_cards, nr_graph_cards);
                      break;
            case '2': sort_comp(vec_processors,  nr_processors,
                                vec_memory_ram, nr_mem_ram,
                                vec_memory_rom, nr_mem_rom,
                                vec_graphics_cards, nr_graph_cards);
                      break;
            case '3': edit(vec_processors,  nr_processors,
                           vec_memory_ram, nr_mem_ram,
                           vec_memory_rom, nr_mem_rom,
                           vec_graphics_cards, nr_graph_cards);
                      break;
        }
    }
    while(!wish_exit);
    save_file(vec_processors, nr_processors, nf_proc);
    save_file(vec_memory_ram, nr_mem_ram, nf_mem_ram);
    save_file(vec_memory_rom, nr_mem_rom, nf_mem_rom);
    save_file(vec_graphics_cards, nr_graph_cards, nf_graph_cards);
}






// ==== MENU ====  //


void menu(wishlist &wl, computer &PC)
{
    int nr_processors, nr_mem_ram, nr_mem_rom, nr_graph_cards, nr_comp;
    component vec_processors[50];
    component vec_memory_ram[50];
    component vec_memory_rom[50];
    component vec_graphics_cards[50];

    // read processors file
    char f1[] = "processors.txt";
    load(vec_processors, nr_processors, f1);

    // read ram file
    char f2[] = "ram_memory.txt";
    load(vec_memory_ram, nr_mem_ram, f2);

    // read rom file
    char f3[] = "rom_memory.txt";
    load(vec_memory_rom, nr_mem_rom, f3);

    // read graphics cards file
    char f4[] = "graphics_cards.txt";
    load(vec_graphics_cards, nr_graph_cards, f4);

    char f5[] = "wishlist.txt";
    load(wl.comp, nr_comp, f5);

    strcpy(wl.PC.processor.code, "NULL");
    strcpy(wl.PC.memory_ram.code, "NULL");
    strcpy(wl.PC.memory_rom.code, "NULL");
    strcpy(wl.PC.graphics_card.code, "NULL");

    // if customer wants to leave the menu
    bool wish_exit = false;

    char op;
    do
    {
         system("clear");
         cout << "\b----- PC BUILDER -----" << endl << endl;
         cout << "1.ADMIN" << endl;
         cout << "2.CUSTOMER" << endl;
         cout << "0.EXIT" << endl;
         do
         {
             op = getchar();
         }
         while(op < '0' || op > '2');

         system("clear");
         switch(op)
         {
             case '0': exit(wish_exit); break;
             case '1': admin(vec_processors,  nr_processors,
                             vec_memory_ram, nr_mem_ram,
                             vec_memory_rom, nr_mem_rom,
                             vec_graphics_cards, nr_graph_cards,
                             f1, f2, f3, f4); cout << endl;
                             break;
             case '2': client(vec_processors,  nr_processors,
                              vec_memory_ram, nr_mem_ram,
                              vec_memory_rom, nr_mem_rom,
                              vec_graphics_cards, nr_graph_cards,
                              wl, nr_comp, PC, f5); cout << endl;
                              break;
         }
    }
    while(!wish_exit);
}






// ==== MAIN ==== //
int main()
{
    wishlist myWishlist; computer PC;
    menu(myWishlist, PC);
    
    return 0;
}


