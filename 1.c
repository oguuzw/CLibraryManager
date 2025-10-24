#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <string.h>

typedef struct kuyruk {
    double ISBN;
    char kitapAdi[100];
    char yazarAdi[100];
    char turu[100];
    int sayfaSayisi;
    struct kuyruk *next;
}kuyruk;

struct kuyruk *kuyrukIlk = NULL;
struct kuyruk *kuyruksSon = NULL;

typedef struct node {
    double ISBN;
    char kitapAdi[100];
    char yazarAdi[100];
    char turu[100];
    int sayfaSayisi;
    struct node *next;
    struct node *prev;
}node;

struct node *listeIlk = NULL;

kuyruk *dosyadanKuyrugaEkle();
void kuyrukYaz(kuyruk *ilk);
void listeYaz();
node *kuyruktanListeyeEkle();
void menu();
void silme();
void arama();
void siralama();
void kutuphaneBilgisi();

int main(){
    menu();
}

// A) ekleme
kuyruk *dosyadanKuyrugaEkle(){
    FILE *dosya = fopen("kitaplar.txt","r");
    if(dosya == NULL){
        printf("dosya acilmadi");
        return NULL;
    }

    kuyruk *temp = NULL;
    while(1){
        kuyruk *yeni = (kuyruk*)malloc(sizeof(kuyruk));

        int okunan = fscanf(dosya,"%lf|%99[^|]|%99[^|]|%99[^|]|%d%*c",&yeni->ISBN,yeni->kitapAdi,yeni->yazarAdi,yeni->turu,&yeni->sayfaSayisi);

        if(okunan != 5){
            temp->next = NULL;
            break;
        }

        if(kuyrukIlk == NULL){
            kuyrukIlk = yeni;
            temp = yeni;
        }else{
            temp->next = yeni;
            temp = yeni;
        }
    }
    fclose(dosya);
    printf("----------------- KUYRUK -----------------");
    kuyrukYaz(kuyrukIlk);
    return kuyrukIlk;
}

node *kuyruktanListeyeEkle(){
    kuyruk *tempUzunluk = kuyrukIlk;
    int kuyrukUzunlugu = 0;
    while(tempUzunluk != NULL){
        kuyrukUzunlugu++;
        tempUzunluk = tempUzunluk->next;
    }
    
    int enDusukIndexSirasi[kuyrukUzunlugu] ;
    bool sayildiMi[kuyrukUzunlugu];
    for(int i = 0 ; i < kuyrukUzunlugu ; i++) sayildiMi[i] = false;

    for(int i = 0 ; i < kuyrukUzunlugu ; i++){
        double enDusukIsbn = DBL_MAX;
        int enDusukIndex;
        kuyruk *tempIndex = kuyrukIlk;

        for(int j = 0 ; j < kuyrukUzunlugu ; j++){
            if(sayildiMi[j]){
                tempIndex = tempIndex->next;
                continue;
            }else{
                if(tempIndex->ISBN < enDusukIsbn){
                    enDusukIsbn = tempIndex->ISBN;
                    enDusukIndex = j;
                }
                tempIndex = tempIndex->next;
            }
        }
        enDusukIndexSirasi[i] = enDusukIndex;
        sayildiMi[enDusukIndex] = true;
    }

    node *tempListe = NULL;
    for(int i = 0 ; i < kuyrukUzunlugu ; i++){
        kuyruk *kuyrukTemp = kuyrukIlk;
        node *yeni = (node*)malloc(sizeof(node));
        for(int j = 0 ; j < kuyrukUzunlugu ; j++){
            if(enDusukIndexSirasi[i] == j){
                if(listeIlk == NULL){
                    listeIlk = yeni;
                    tempListe = yeni;
                    tempListe->next = yeni;
                    tempListe->prev = yeni;
                }else{
                    tempListe->next = yeni;
                    yeni->prev = tempListe;
                    yeni->next = listeIlk;
                    listeIlk->prev = yeni;
                    tempListe = yeni; 
                }
                yeni->ISBN = kuyrukTemp->ISBN;
                strncpy(yeni->kitapAdi, kuyrukTemp->kitapAdi, sizeof(yeni->kitapAdi) - 1);
                yeni->kitapAdi[sizeof(yeni->kitapAdi) - 1] = '\0';

                strncpy(yeni->yazarAdi, kuyrukTemp->yazarAdi, sizeof(yeni->yazarAdi) - 1);
                yeni->yazarAdi[sizeof(yeni->yazarAdi) - 1] = '\0';

                strncpy(yeni->turu, kuyrukTemp->turu, sizeof(yeni->turu) - 1);
                yeni->turu[sizeof(yeni->turu) - 1] = '\0';
                yeni->sayfaSayisi = kuyrukTemp->sayfaSayisi;
                break;
            }
            kuyrukTemp = kuyrukTemp->next;
        }
    }

    node *yazmaTemp = listeIlk;
    printf("\n\n------------- ISBN'ye gore sirali liste ----------\n");
    while(1){
        printf("%.lf|%s|%s|%s|%d\n",yazmaTemp->ISBN,yazmaTemp->kitapAdi,yazmaTemp->yazarAdi,yazmaTemp->turu,yazmaTemp->sayfaSayisi);
        yazmaTemp = yazmaTemp->next;
        if(yazmaTemp == listeIlk) break;
    }
}

void kuyrukYaz(kuyruk *ilk){
    kuyruk *temp = ilk;

    while(temp != NULL){
        printf("\n%s isbn : %.lf",temp->kitapAdi,temp->ISBN);
        temp = temp->next;
    }
}

void listeYaz(){
    node *temp = listeIlk;

    while(1){
        printf("%.lf|%s|%s|%s|%d\n",temp->ISBN,temp->kitapAdi,temp->yazarAdi,temp->turu,temp->sayfaSayisi);
        temp = temp->next;
        if(temp == listeIlk) break;
    }
}

void menu(){
    while(1){
        printf("\n----------------------------------");
        printf("\n1.ekleme");
        printf("\n2.silme");
        printf("\n3.arama");
        printf("\n4.siralama");
        printf("\n5.kutuphane bilgisi");
        printf("\n6.cikis");
        printf("\n----------------------------------\n");
        int secim;
        scanf("%d",&secim);
        switch(secim){
            case 1 : 
                dosyadanKuyrugaEkle();
                kuyruktanListeyeEkle();
                break;
            case 2 : silme();
                break;
            case 3 : arama();
                break;
            case 4 : siralama();
                break;
            case 5 : kutuphaneBilgisi();
                break;
            case 6 :
                return;
            default :
                printf("1-6 arasinda secim yapiniz");        
        }
    }
}

void silme(){
    printf("ISBN numarasi giriniz : ");
    double isbn;
    scanf("%lf",&isbn);

    node *temp = listeIlk;
    bool kitapBulunduMu = false;
    while(1){
        if(temp->ISBN == isbn){
            kitapBulunduMu = true;
            if(temp == listeIlk){
                listeIlk = temp->next;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            printf("%s (%s) listeden silinmiştir\n\n",temp->kitapAdi,temp->yazarAdi);
            free(temp);
            break;
        }
        temp = temp->next;
        if(temp == listeIlk) break;
    }
    if(!kitapBulunduMu){
        printf("kitap bulunamadi\n");
    }
    listeYaz();
}

void arama(){
    node *temp = listeIlk;
    printf("----------------");
    printf("\n1.Roman");
    printf("\n2.Tarih");
    printf("\n3.Klasik");
    printf("\n4.Distopya");
    printf("\ntur giriniz : ");
    int turInt;
    scanf("%d",&turInt);

    char *tur=NULL;
    switch(turInt){
        case 1 : tur = "Roman"; break;
        case 2 : tur = "Tarih"; break;
        case 3 : tur = "Klasik"; break;
        case 4 : tur = "Distopya"; break;
        default : printf("1-4 arasinda giris olmali");
    }

    printf("\nTur : %s",tur);
    while(1){
        char *uzunluk;
        if(strcmp(tur,temp->turu) == 0){
            if(temp->sayfaSayisi <= 200){
                uzunluk = "kisa";
            }else if(temp->sayfaSayisi > 200 && temp->sayfaSayisi <= 400){
                uzunluk = "orta uzunlukta";
            }else{
                uzunluk = "uzun";
            }
            printf("\n%s - %d sayfa (%s)",temp->kitapAdi,temp->sayfaSayisi,uzunluk);
        }
        temp = temp->next;
        if(temp == listeIlk) break;
    }
}

void siralama(){
    node *temp = listeIlk;
    while(1){
        node *temp2 = listeIlk;
        while(1){
            if(strcmp(temp2->yazarAdi,temp2->next->yazarAdi) > 0){
                if(temp2 == listeIlk){
                    listeIlk = temp2->next;
                }
                temp2->prev->next = temp2->next;
                temp2->next->next->prev = temp2;
                temp2->next = temp2->next->next;
                temp2->prev = temp2->next;
                temp2->next->next = temp2;
                temp2->next->prev = ;
                
            }
            temp2 = temp2->next;
            if(temp2 == listeIlk) break;
        }
        temp = temp->next;
        if(temp == listeIlk) break;
        printf("\n");
    }
    
}

void kutuphaneBilgisi(){
    int toplamKitapSayisi = 0;
    int toplamSayfaSayisi = 0;

    node *temp = listeIlk;
    while(1){
        toplamKitapSayisi++;
        toplamSayfaSayisi += temp->sayfaSayisi;
        temp = temp->next;
        if(temp == listeIlk) break;
    }

    double ortalamaSayfaSayisi = toplamSayfaSayisi/toplamKitapSayisi;

    printf("\nToplam kitap sayisi : %d",toplamKitapSayisi);
    printf("\nToplam Sayfa Sayisi : %d",toplamSayfaSayisi);
    printf("\nOrtalama Sayfa Sayisi : %.2lf",ortalamaSayfaSayisi);
}
