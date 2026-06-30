#include<stdio.h> //İhtiyacımız olan kütüphaneleri ekleriz
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include <windows.h>

typedef struct{ //Struct yapımızı kurarız
int hastaNo;
char hastaAdı[50];
float randevuSaat;
}Hastalar;

//Menü yapısı için gereken fonksiyonu kurarız
void randevuMenü(int *girdi){ 
printf("Hasta eklemek için: 1\n");
printf("Hasta kayıt aramak için: 2\n");
printf("Randevu saati güncellemek için: 3\n");
printf("Çıkmak için: 4\n");
printf("Seçiminiz: ");
scanf("%d", girdi);
}

void hastaEkle(){ //Kullanıcıdan hasta bilgilerini alıp dosyaya kaydeden fonksiyonumuz
Hastalar hasta[30];
for(int i=0;i<30;i++){ //Döngü yardımıyla 30 hastanın verilerini tek tek alırız
    printf("%d. hasta için hasta no giriniz: \n", i+1);
    scanf("%d", &hasta[i].hastaNo);
    printf("%d. hasta için hasta ismi giriniz: \n", i+1);
    scanf(" %[^\n]", hasta[i].hastaAdı);
    printf("%d, hasta için randevu saati giriniz: \n", i+1);
    scanf("%f", &hasta[i].randevuSaat);
}
FILE *dosya = fopen("randevular.dat", "wb"); //Verileri ikili (binary) modda yazmak için dosyayı açarız
if(!dosya){
printf("Dosya açılamadı!"); 
return; }
fwrite(hasta, sizeof(Hastalar), 30, dosya); //Toplanan tüm hasta verilerini tek seferde dosyaya yazarız
fclose(dosya);

printf("30 hastanın kaydı başarıyla tamamlandı"); //İşlemin başarılı olduğunu kullanıcıya bildiririz
}

void hastaAra() { //Kayıtlı hastalar arasında arama yapma fonksiyonumuz
    FILE *dosya = fopen("randevular.dat", "rb"); //Okuma modunda binary dosyayı açarız
    if (!dosya) { printf("Dosya açılamadı!\n"); return; }

    Hastalar hasta[30];
    int adet = fread(hasta, sizeof(Hastalar), 30, dosya); //Dosyadaki verileri diziye okuruz
    fclose(dosya);

    int aranan;
    printf("Hasta no giriniz: "); //Aranacak hastanın numarasını kullanıcıdan alırız
    scanf("%d", &aranan);

    int bulundu = 0;
    for (int i = 0; i < adet; i++) { //Aranan hastayı bulma algoritması
        if (hasta[i].hastaNo == aranan) { //Eğer numara eşleşirse bilgileri ekrana yazdırırız
            printf("\nHasta No      : %d\n", hasta[i].hastaNo);
            printf("Hasta Adı     : %s\n", hasta[i].hastaAdı);
            printf("Randevu Saati : %.2f\n", hasta[i].randevuSaat);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) printf("Kayıt bulunamadı!\n"); //İşlem başarısız olursa hata mesajı verdiririz
}

//Kayıtlı hastanın randevu saatini değiştirme fonksiyonumuz
void randevuGüncelle() { 
    FILE *dosya = fopen("randevular.dat", "r+b"); //Hem okuma hem yazma modunda dosyayı açarız
    if (!dosya) { printf("Dosya açılamadı!\n"); return; }

    Hastalar hasta[30];
    int adet = fread(hasta, sizeof(Hastalar), 30, dosya);

    int aranan;
    printf("Hasta no giriniz: "); //Saati güncellenecek hastanın numarasını alırız
    scanf("%d", &aranan);

    int onay = 0;
    for (int i = 0; i < adet; i++) { //Güncellenecek hastayı bulma algoritması
        if (hasta[i].hastaNo == aranan) {
            float yeniSaat;
            printf("Yeni randevu saati: "); //Yeni saati kullanıcıdan alırız
            scanf("%f", &yeniSaat);

            //fseek ile dosya imlecini sadece ilgili hastanın randevu saati kısmına konumlandırırız
            fseek(dosya, i * sizeof(Hastalar) + offsetof(Hastalar, randevuSaat), SEEK_SET);
            fwrite(&yeniSaat, sizeof(float), 1, dosya); //Yeni saati dosyaya doğrudan yazarız
            onay = 1;
            break;
        }
    }

    if (!onay) printf("Hasta bulunamadı!\n"); 
    else       printf("Randevu güncellendi.\n"); //İşlemin başarılı olduğunu belirtiriz

    fclose(dosya);
if(!onay){
    printf("İşlem Başarısız Oldu!"); //Alternatif başarısızlık mesajı
    }
}

int main(){ //Fonksiyonun main ve menü kısmı
SetConsoleOutputCP(65001);
SetConsoleCP(65001);
printf("Hoşgeldiniz!\n");
int girdi;
do{ //do while döngüsü ile kullanıcıdan '4' girilene kadar girdi alırız
    randevuMenü(&girdi);
    switch(girdi){
        case 1: hastaEkle();    break;
        case 2: hastaAra();     break;
        case 3: randevuGüncelle(); break;
        case 4: printf("Çıkış Yapılıyor..."); break; //Girdi '4' olursa işlem sonlanır
        default: printf("Geçersiz Girdi!"); 
    }
    } while(girdi!=4);
return 0;
}
