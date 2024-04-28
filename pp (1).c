#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int year;
} Book;

typedef struct Reader {
    int id;
    char firstName[50];
    char lastName[50];
    char address[100];
    char pesel[12];
    char email[100];
    char phoneNumber[15];
    int borrowedBooks[100];
    int borrowedDates[100];
    int returnedDates[100];
    int borrowedCount;
} Reader;

void addBook(Book library[], int *bookCount) {
    Book newBook;
    printf("Podaj tytul ksiazki: ");
    scanf("%s", newBook.title);
    printf("Podaj autora ksiazki: ");
    scanf("%s", newBook.author);
    printf("Podaj rok wydania ksiazki: ");
    scanf("%d", &newBook.year);

    newBook.id = (*bookCount) + 1;
    library[*bookCount] = newBook;
    (*bookCount)++;
    printf("Ksiazka zostala dodana do biblioteki.\n");
}

void addReader(Reader readers[], int *readerCount) {
    Reader newReader;
    printf("Podaj imie czytelnika: ");
    scanf("%s", newReader.firstName);
    printf("Podaj nazwisko czytelnika: ");
    scanf("%s", newReader.lastName);
    printf("Podaj adres czytelnika: ");
    scanf("%s", newReader.address);
    printf("Podaj PESEL czytelnika: ");
    scanf("%s", newReader.pesel);
    printf("Podaj email czytelnika: ");
    scanf("%s", newReader.email);
    printf("Podaj numer telefonu czytelnika: ");
    scanf("%s", newReader.phoneNumber);

    newReader.id = (*readerCount) + 1;
    newReader.borrowedCount = 0;
    readers[*readerCount] = newReader;
    (*readerCount)++;
    printf("Czytelnik zostal dodany do bazy.\n");
}

void borrowBook(Book library[], Reader readers[], int bookCount, int readerCount) {
    int readerId, bookId;
    printf("Podaj identyfikator czytelnika: ");
    scanf("%d", &readerId);
    printf("Podaj identyfikator ksiazki: ");
    scanf("%d", &bookId);

    if (readerId >= 1 && readerId <= readerCount && bookId >= 1 && bookId <= bookCount) {
        if (readers[readerId - 1].borrowedCount < 100) {
            readers[readerId - 1].borrowedBooks[readers[readerId - 1].borrowedCount] = bookId;
            readers[readerId - 1].borrowedDates[readers[readerId - 1].borrowedCount] = time(NULL);
            readers[readerId - 1].returnedDates[readers[readerId - 1].borrowedCount] = -1;
            readers[readerId - 1].borrowedCount++;
            printf("Ksiazka zostala wypozyczona przez czytelnika.\n");
        } else {
            printf("Czytelnik osiagnal limit wypozyczen.\n");
        }
    } else {
        printf("Nieprawidlowe identyfikatory czytelnika lub ksiazki.\n");
    }
}

void returnBook(Book library[], Reader readers[], int bookCount, int readerCount) {
    int readerId, bookId;
    printf("Podaj identyfikator czytelnika: ");
    scanf("%d", &readerId);
    printf("Podaj identyfikator ksiazki: ");
    scanf("%d", &bookId);

    if (readerId >= 1 && readerId <= readerCount && bookId >= 1 && bookId <= bookCount) {
        Reader *reader = &readers[readerId - 1];
        for (int i = 0; i < reader->borrowedCount; i++) {
            if (reader->borrowedBooks[i] == bookId && reader->returnedDates[i] == -1) {
                reader->returnedDates[i] = time(NULL);
                printf("Ksiazka zostala zwrocona.\n");
                return;
            }
        }
        printf("Czytelnik nie wypozyczyl tej ksiazki lub ksiazka zostala juz zwrocona.\n");
    } else {
        printf("Nieprawidlowe identyfikatory czytelnika lub ksiazki.\n");
    }
}

void displayReaderAccount(Reader reader, Book library[], int bookCount) {
    printf("Imie: %s\n", reader.firstName);
    printf("Nazwisko: %s\n", reader.lastName);
    printf("Adres: %s\n", reader.address);
    printf("PESEL: %s\n", reader.pesel);
    printf("Email: %s\n", reader.email);
    printf("Numer telefonu: %s\n", reader.phoneNumber);
    printf("Wypozyczone ksiazki:\n");
    for (int i = 0; i < reader.borrowedCount; i++) {
        int bookId = reader.borrowedBooks[i];
        if (bookId >= 1 && bookId <= bookCount) {
            Book borrowedBook = library[bookId - 1];
            printf("- %s\n", borrowedBook.title);
            printf("  Data wypozyczenia: %s", ctime(&reader.borrowedDates[i]));
            if (reader.returnedDates[i] == -1) {
                printf("  Status: Niezwrocona\n");
            } else {
                printf("  Data zwrotu: %s", ctime(&reader.returnedDates[i]));
                printf("  Status: Zwrocona\n");
            }
        }
    }
}

int main() {
    Book library[100];
    Reader readers[100];
    int bookCount = 0;
    int readerCount = 0;

    while (1) {
        printf("Menu:\n");
        printf("1. Dodaj nowa ksiazke\n");
        printf("2. Dodaj nowego czytelnika\n");
        printf("3. Wypozycz ksiazke\n");
        printf("4. Zwroc ksiazke\n");
        printf("5. Wyswietl stan konta czytelnika\n");
        printf("0. Wyjdz z programu\n");
        int choice;
        printf("Wybierz opcje: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(library, &bookCount);
                break;
            case 2:
                addReader(readers, &readerCount);
                break;
            case 3:
                borrowBook(library, readers, bookCount, readerCount);
                break;
            case 4:
                returnBook(library, readers, bookCount, readerCount);
                break;
            case 5:
                printf("Podaj identyfikator czytelnika do wyswietlenia stanu konta: ");
                int readerId;
                scanf("%d", &readerId);
                if (readerId >= 1 && readerId <= readerCount) {
                    displayReaderAccount(readers[readerId - 1], library, bookCount);
                } else {
                    printf("Nieprawidlowy identyfikator czytelnika.\n");
                }
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Nieprawidlowy wybor.\n");
        }
    }

    return 0;
}
