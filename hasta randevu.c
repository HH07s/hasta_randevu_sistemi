#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include <windows.h>

typedef struct{ 
int hastaNo;
char hastaAdı[50];
float randevuSaat;
}Hastalar;

void randevuMenü(int *girdi){ 
printf("Hasta eklemek için: 1\n");
printf("Hasta kayıt aramak için: 2\n");
printf("Randevu saati güncellemek için: 3\n");
printf("Çıkmak için: 4\n");
printf("Seçiminiz: ");
scanf("%d", girdi);
}

void hastaEkle(){ 
Hastalar hasta[30];
for(int i=0;i<30;i++){ 
    printf("%d. hasta için hasta no giriniz: \n", i+1);
    scanf("%d", &hasta[i].hastaNo);
    printf("%d. hasta için hasta ismi giriniz: \n", i+1);
    scanf(" %[^\n]", hasta[i].hastaAdı);
    printf("%d, hasta için randevu saati giriniz: \n", i+1);
    scanf("%f", &hasta[i].randevuSaat);
}
FILE *dosya = fopen("randevular.dat", "wb"); 
if(!dosya){
printf("Dosya açılamadı!"); 
return; }
fwrite(hasta, sizeof(Hastalar), 30, dosya); 
fclose(dosya);

printf("30 hastanın kaydı başarıyla tamamlandı"); 
}

void hastaAra() {
    FILE *dosya = fopen("randevular.dat", "rb");z
    if (!dosya) { printf("Dosya açılamadı!\n"); return; }

    Hastalar hasta[30];
    int adet = fread(hasta, sizeof(Hastalar), 30, dosya);z
    fclose(dosya);

    int aranan;
    printf("Hasta no giriniz: "); 
    scanf("%d", &aranan);

    int bulundu = 0;
    for (int i = 0; i < adet; i++) {
        if (hasta[i].hastaNo == aranan) {
            printf("\nHasta No      : %d\n", hasta[i].hastaNo);
            printf("Hasta Adı     : %s\n", hasta[i].hastaAdı);
            printf("Randevu Saati : %.2f\n", hasta[i].randevuSaat);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) printf("Kayıt bulunamadı!\n");
}

void randevuGüncelle() { 
    FILE *dosya = fopen("randevular.dat", "r+b"); 
    if (!dosya) { printf("Dosya açılamadı!\n"); return; }

    Hastalar hasta[30];
    int adet = fread(hasta, sizeof(Hastalar), 30, dosya);

    int aranan;
    printf("Hasta no giriniz: ");
    scanf("%d", &aranan);

    int onay = 0;
    for (int i = 0; i < adet; i++) {
        if (hasta[i].hastaNo == aranan) {
            float yeniSaat;
            printf("Yeni randevu saati: "); 
            scanf("%f", &yeniSaat);
            fseek(dosya, i * sizeof(Hastalar) + offsetof(Hastalar, randevuSaat), SEEK_SET);
            fwrite(&yeniSaat, sizeof(float), 1, dosya); 
            onay = 1;
            break;
        }
    }

    if (!onay) printf("Hasta bulunamadı!\n"); 
    else       printf("Randevu güncellendi.\n");

    fclose(dosya);
if(!onay){
    printf("İşlem Başarısız Oldu!");
    }
}

int main(){
SetConsoleOutputCP(65001);
SetConsoleCP(65001);
printf("Hoşgeldiniz!\n");
int girdi;
do{
    randevuMenü(&girdi);
    switch(girdi){
        case 1: hastaEkle();    break;
        case 2: hastaAra();     break;
        case 3: randevuGüncelle(); break;
        case 4: printf("Çıkış Yapılıyor..."); break;
        default: printf("Geçersiz Girdi!"); 
    }
    } while(girdi!=4);
return 0;
}
