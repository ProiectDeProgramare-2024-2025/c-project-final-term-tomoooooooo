#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALI 100
#define MAX_REZERVARI 100
#define MAX_LEN 100

// Structura pentru sala de sedinta
typedef struct {
    char nume[MAX_LEN];
    int capacitate;
} Sala;

// Structura pentru rezervare
typedef struct {
    char numeSala[MAX_LEN];
    char data[MAX_LEN];
    char zi[MAX_LEN];
    char interval[MAX_LEN];
} Rezervare;

Sala sali[MAX_SALI];
Rezervare rezervari[MAX_REZERVARI];
int nrSali = 0, nrRezervari = 0;

// Incarca salile din fisier
void incarcaSali() {
    FILE *f = fopen("sali.txt", "r");
    if (!f) return;
    while (fscanf(f, "%[^|]|%d\n", sali[nrSali].nume, &sali[nrSali].capacitate) == 2) {
        nrSali++;
    }
    fclose(f);
}

// Salveaza salile in fisier
void salveazaSali() {
    FILE *f = fopen("sali.txt", "w");
    for (int i = 0; i < nrSali; i++) {
        fprintf(f, "%s|%d\n", sali[i].nume, sali[i].capacitate);
    }
    fclose(f);
}

// Incarca rezervarile din fisier
void incarcaRezervari() {
    FILE *f = fopen("rezervari.txt", "r");
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  rezervari[nrRezervari].numeSala,
                  rezervari[nrRezervari].data,
                  rezervari[nrRezervari].zi,
                  rezervari[nrRezervari].interval) == 4) {
        nrRezervari++;
    }
    fclose(f);
}

// Salveaza rezervarile in fisier
void salveazaRezervari() {
    FILE *f = fopen("rezervari.txt", "w");
    for (int i = 0; i < nrRezervari; i++) {
        fprintf(f, "%s|%s|%s|%s\n", rezervari[i].numeSala, rezervari[i].data,
                rezervari[i].zi, rezervari[i].interval);
    }
    fclose(f);
}

// Adauga o noua sala
void adaugaSala() {
    printf("Nume sala: ");
    scanf(" %[^\n]", sali[nrSali].nume);
    printf("Capacitate: ");
    scanf("%d", &sali[nrSali].capacitate);
    nrSali++;
    salveazaSali();
    printf("Sala adaugata cu succes.\n");
}

// Sterge o sala dupa nume
void stergeSala() {
    char nume[MAX_LEN];
    printf("Numele salii de sters: ");
    scanf(" %[^\n]", nume);
    int gasit = 0;
    for (int i = 0; i < nrSali; i++) {
        if (strcmp(sali[i].nume, nume) == 0) {
            for (int j = i; j < nrSali - 1; j++) {
                sali[j] = sali[j + 1];
            }
            nrSali--;
            gasit = 1;
            break;
        }
    }
    if (gasit) {
        salveazaSali();
        printf("Sala stearsa cu succes.\n");
    } else {
        printf("Sala nu a fost gasita.\n");
    }
}

// Afiseaza toate salile
void afiseazaSali() {
    printf("Lista sali:\n");
    for (int i = 0; i < nrSali; i++) {
        printf("%s - capacitate: %d\n", sali[i].nume, sali[i].capacitate);
    }
}

// Afiseaza toate rezervarile
void afiseazaRezervari() {
    printf("Lista rezervari:\n");
    for (int i = 0; i < nrRezervari; i++) {
        printf("%s | %s | %s | %s\n", rezervari[i].numeSala,
               rezervari[i].data, rezervari[i].zi, rezervari[i].interval);
    }
}


// Verifica daca sala este disponibila
int esteDisponibila(char *numeSala, char *data, char *interval) {
    for (int i = 0; i < nrRezervari; i++) {
        if (strcmp(rezervari[i].numeSala, numeSala) == 0 &&
            strcmp(rezervari[i].data, data) == 0 &&
            strcmp(rezervari[i].interval, interval) == 0) {
            return 0; // sala este ocupata
        }
    }
    return 1; // sala este libera
}

// Rezerva o sala
void rezervaSala() {
    Rezervare r;
    printf("Nume sala: ");
    scanf(" %[^\n]", r.numeSala);
    printf("Data (ex: 2025-07-20): ");
    scanf(" %[^\n]", r.data);
    printf("Ziua: ");
    scanf(" %[^\n]", r.zi);
    printf("Interval orar (ex: 14:00-16:00): ");
    scanf(" %[^\n]", r.interval);

    if (!esteDisponibila(r.numeSala, r.data, r.interval)) {
        printf("Sala este deja rezervata in acel interval.\n");
        return;
    }

    rezervari[nrRezervari++] = r;
    salveazaRezervari();
    printf("Rezervare efectuata cu succes.\n");
}

// Anuleaza o rezervare
void anuleazaRezervare() {
    char nume[MAX_LEN], data[MAX_LEN], interval[MAX_LEN];
    printf("Nume sala: ");
    scanf(" %[^\n]", nume);
    printf("Data: ");
    scanf(" %[^\n]", data);
    printf("Interval: ");
    scanf(" %[^\n]", interval);

    int gasit = 0;
    for (int i = 0; i < nrRezervari; i++) {
        if (strcmp(rezervari[i].numeSala, nume) == 0 &&
            strcmp(rezervari[i].data, data) == 0 &&
            strcmp(rezervari[i].interval, interval) == 0) {
            for (int j = i; j < nrRezervari - 1; j++) {
                rezervari[j] = rezervari[j + 1];
            }
            nrRezervari--;
            gasit = 1;
            break;
        }
    }

    if (gasit) {
        salveazaRezervari();
        printf("Rezervare anulata cu succes.\n");
    } else {
        printf("Rezervare inexistenta.\n");
    }
}

// Meniu text pentru utilizator
void meniu() {
    printf("\n--- Meniu ---\n");
    printf("1. Adauga sala\n");
    printf("2. Sterge sala\n");
    printf("3. Afiseaza sali\n");
    printf("4. Rezerva sala\n");
    printf("5. Anuleaza rezervare\n");
    printf("6. Afiseaza rezervari\n");
    printf("0. Iesire\n");
}

int main() {
    incarcaSali(); // incarca salile din fisier
    incarcaRezervari(); // incarca rezervarile din fisier
    int optiune;
    do {
        meniu();
        printf("Optiune: ");
        scanf("%d", &optiune);
        switch (optiune) {
            case 1: adaugaSala(); break;
            case 2: stergeSala(); break;
            case 3: afiseazaSali(); break;
            case 4: rezervaSala(); break;
            case 5: anuleazaRezervare(); break;
            case 6: afiseazaRezervari(); break;
            case 0: printf("Iesire.\n"); break;
            default: printf("Optiune invalida.\n");
        }
    } while (optiune != 0);
    return 0;
}
