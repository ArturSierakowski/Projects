#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int WYMIAR = 3;
const int WYMIAR2X = 6;
const int WYGRANA_LINIA = 5;

string wybierz_nazwe(int a)
{
    string gracz;
    cout << "wprowadz nazwe gracza" << a << endl;
    cin >> gracz;
    return gracz;
}
void zmien_znak(vector<vector<char>>& plansza, char& aktualnyZnak, char znakPrzeciwnika)
{
    char znak;
    cout << "Wybierz zeton" <<  endl;
    cin >> znak;
    while (znak == znakPrzeciwnika || znak == ' ')
    {
        cout << "Wybierz inny zeton" << endl;
        cin >> znak;
    }
    if (aktualnyZnak != ' ')
        for (int i = 0; i < WYMIAR2X; i++)
            for (int j = 0; j < WYMIAR2X; j++)
                if (plansza[i][j] == aktualnyZnak)
                    plansza[i][j] = znak;

    aktualnyZnak = znak;
}
void wyswietl_plansze(vector<vector<char>> plansza)
{
    char pion = '\xBA';
    string liniaGorna = "\xC9\xCD\xCB\xCD\xCB\xCD\xBB", liniaSrodkowa = "\xCC\xCD\xCE\xCD\xCE\xCD\xB9", liniaDolna = "\xC8\xCD\xCA\xCD\xCA\xCD\xBC";

    for (int i = 0; i < 2; i++)
    {
        cout << liniaGorna << ' ' << liniaGorna << endl << pion;
        for (int j = 0; j < WYMIAR2X; j++)
        {
            cout << plansza[i * WYMIAR][j] << pion;
            if (j == 2)
                cout << ' ' << pion;
        }
        for (int k = 0; k < 2; k++)
        {
            cout << endl << liniaSrodkowa << ' ' << liniaSrodkowa << endl << pion;
            for (int j = 0; j < WYMIAR2X; j++)
            {
                cout << plansza[1 + i * WYMIAR + k][j] << pion;
                if (j == 2)
                    cout << ' ' << pion;
            }
        }
        cout << endl << liniaDolna << ' ' << liniaDolna << endl;
    }
}
void predefiniowana_plansza(vector<vector<char>> &plansza, char znak1, char znak2)
{
    char s = ' ';
    plansza = {
        {s, znak2, s, s, znak1, s},
        {znak1, znak1, znak2, znak1, znak2, s},
        {s, znak1, s, s, s, s},
        {znak1, znak1, s, s, s, s},
        {znak2, s, znak1, s, znak2, s},
        {s, znak2, s, s, znak2, znak2}
    };
    wyswietl_plansze(plansza);
}
void opis()
{
    cout << "opis programu" << endl;
}
void opcje(vector<vector<char>>& plansza, char& aktualnyZnak, char znak1, char znak2)
{
    cout << "o - predefiniowa plansza" << endl << "z - zmien zeton" << endl;
    cout << "h - opis programu" << endl << "e - wyjscie" << endl;
    char opcja;
    cin >> opcja;
    switch (opcja)
    {
    case 'o':
        predefiniowana_plansza(plansza, znak1, znak2);
        break;
    case 'z':
        zmien_znak(plansza, aktualnyZnak, (znak1 != aktualnyZnak) ? znak1 : (znak2 != aktualnyZnak) ? znak2 : ' ');
        break;
    case 'h':
        opis();
        break;
    case 'e':
        break;
    default:
        cout << "bledna opcja" << endl;
    }
}
void wybierz_pole(vector<vector<char>>& plansza, char& aktualnyZnak, char znak1, char znak2)
{
    string pole;
    char czesc;
    int indeks;
    int x, y;
    do {
        cout << "Wybierz pole" << endl;
        cin >> pole;

        while (pole[0] == 'm')
        {
            opcje(plansza, aktualnyZnak, znak1, znak2);
            cout << "Wybierz pole" << endl;
            cin >> pole;
        }

        czesc = pole[0];
        indeks = pole[1] - '1';
        x = WYMIAR - 1 - indeks / 3;
        y = indeks % 3;

        switch (czesc)
        {
            case 'q':
                break;
            case 'w':
                y += 3;
                break;
            case 'a':
                x += 3;
                break;
            case 's':
                x += 3;
                y += 3;
                break;
            default:
                cout << "Nieprawidlowe pole!" << endl;
        }
    } while (pole.size() != 2 ||
        (czesc != 'q' && czesc != 'w' && czesc != 'a' && czesc != 's') || pole[1] < '1' || pole[1] > '9' || plansza[x][y] != ' ');
    
    plansza[x][y] = aktualnyZnak;
}
void obrot_lewo(vector<vector<char>>& plansza, int a, int b)
{
    for (int i = a; i < WYMIAR + a; i++)
    {
        for (int j = i - a + 1 + b; j < WYMIAR + b; j++)
        {
            int tmp = plansza[i][j];
            plansza[i][j] = plansza[j + (a - b)][i - (a - b)];
            plansza[j + (a - b)][i - (a - b)] = tmp;
        }
    }
    for (int i = a; i < WYMIAR / 2 + a; i++)
    {
        for (int j = b; j < WYMIAR + b; j++)
        {
            int tmp = plansza[i][j];
            plansza[i][j] = plansza[i + 2][j];
            plansza[i + 2][j] = tmp;
        }
    }
}
void obrot_prawo(vector<vector<char>>& plansza, int a, int b)
{
    for (int i = a; i < WYMIAR + a; i++)
    {
        for (int j = i - a + 1 + b; j < WYMIAR + b; j++)
        {
            int tmp = plansza[i][j];
            plansza[i][j] = plansza[j + (a - b)][i - (a - b)];
            plansza[j + (a - b)][i - (a - b)] = tmp;
        }
    }
    for (int j = b; j < WYMIAR / 2 + b; j++)  
    {
        for (int i = a; i < WYMIAR + a; i++)
        {
            int tmp = plansza[i][j];
            plansza[i][j] = plansza[i][j + 2];
            plansza[i][j + 2] = tmp;
        }
    }
}
void wybierz_obrot(vector<vector<char>>& plansza, char& aktualnyZnak, char znak1, char znak2)
{
    string obrot;
    char czesc, kierunek;
    do {
        cout << "Wybierz podplansze i kierunek" << endl;
        cin >> obrot;

        while (obrot[0] == 'm')
        {
            opcje(plansza, aktualnyZnak, znak1, znak2);
            cout << "Wybierz podplansze i kierunek" << endl;
            cin >> obrot;
        }

        czesc = obrot[0];
        kierunek = obrot[1];
        int a = 0, b = 0;

        switch (czesc)
        {
        case 'q':
            break;
        case 'w':
            b += 3;
            break;
        case 'a':
            a += 3;
            break;
        case 's':
            a += 3;
            b += 3;
            break;
        default:
            cout << "Nieprawidlowy obrot!" << endl;
        }
        switch (kierunek)
        {
        case 'z':
            obrot_prawo(plansza, a, b);
            break;
        case 'x':
            obrot_lewo(plansza, a, b);
            break;
        default:
            cout << "Nieprawidlowy obrot!" << endl;
        }
    } while (obrot.size() != 2 || (czesc != 'q' && czesc != 'w' && czesc != 'a' && czesc != 's') ||
        (kierunek != 'z' && kierunek != 'x'));
}
bool wygrana_poziom(vector<vector<char>> plansza, char znak)
{
    for (int i = 0; i < WYMIAR2X; i++)
    {
        int dlugosc = 0;
        for (int j = 0; j < WYMIAR2X; j++)
        {
            if (plansza[i][j] == znak)
            {
                dlugosc++;
                if (dlugosc == 5)
                    return true;
            }
            else if (j < 2)
                dlugosc = 0;
            else
                break;
        }
    }
    return false;
}
bool wygrana_pion(vector<vector<char>> plansza, char znak)
{
    /*for (int j = 0; j < WYGRANA_LINIA; j++)
        for (int i = 0; i < WYGRANA_LINIA; i++)
            if (plansza[i][j] != 'x')
                return false;
    return true;*/

    for (int j = 0; j < WYMIAR2X; j++)
    {
        int dlugosc = 0;
        for (int i = 0; i < WYMIAR2X; i++)
        {
            if (plansza[i][j] == znak)
            {
                dlugosc++;
                if (dlugosc == 5)
                    return true;
            }
            else if (i < 2)
                dlugosc = 0;
            else
                break;
        }
    }
    return false;
}
bool skos_prawo(vector<vector<char>> plansza, char znak, int a, int b)
{
    for (int i = 0; i < WYGRANA_LINIA; i++)
        if (plansza[i + a][i + b] != znak)
            return false;
    return true;
}
bool skos_lewo(vector<vector<char>> plansza, char znak, int a, int b)
{
    for (int i = WYMIAR2X - 1; i >= WYMIAR2X - WYGRANA_LINIA; i--)
        if (plansza[WYMIAR2X - 1 - i + a][i - b] != znak)
            return false;
    return true;
}
bool wygrana_skos(vector<vector<char>> plansza, char znak)
{
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            if (skos_lewo(plansza, znak, i, j) || skos_prawo(plansza, znak, i, j))
                return true;
    return false;
}
bool czyWygrana(vector<vector<char>> plansza, char znak)
{
    return wygrana_poziom(plansza, znak) || wygrana_pion(plansza, znak) || wygrana_skos(plansza, znak);
}
void tura_gracza(vector<vector<char>>& plansza, char aktualnyZnak, char znak1, char znak2)
{
    wybierz_pole(plansza, aktualnyZnak, znak1, znak2);
    wyswietl_plansze(plansza);
    wybierz_obrot(plansza, aktualnyZnak, znak1, znak2);
    wyswietl_plansze(plansza);
}

int main()
{
    vector<vector<char>> plansza(WYMIAR2X, vector<char>(WYMIAR2X, ' '));
    string gracz1 = wybierz_nazwe(1), gracz2 = wybierz_nazwe(2);
    char znak1 = ' ', znak2 = ' ';
    cout << gracz1 << ": ";
    zmien_znak(plansza, znak1, ' ');
    cout << gracz2 << ": ";
    zmien_znak(plansza, znak2, znak1);

    char aktualnyZnak = znak1;
    bool turaGracz1 = true; 

    // predefiniowana_plansza(znak1, znak2);
    wyswietl_plansze(plansza);

    while (!czyWygrana(plansza, aktualnyZnak))
    {
        cout << "tura gracza: " << (turaGracz1 ? gracz1 : gracz2) << ", zeton: " << aktualnyZnak << endl;
        tura_gracza(plansza, aktualnyZnak, znak1, znak2);
        aktualnyZnak = turaGracz1 ? znak2 : znak1;
        turaGracz1 = !turaGracz1;
    }

    cout << "wygrana gracza: " << (turaGracz1 ? gracz1 : gracz2) << endl;
    
    return 0;
}