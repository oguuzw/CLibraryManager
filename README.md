## Veri Yapıları Ödevi - Kitap Kütüphanesi (C)

Bu proje, bir metin dosyasından (`kitaplar.txt`) kitap bilgilerini okuyup önce bir kuyruk yapısına, sonra ISBN değerine göre sıralanmış döngüsel çift bağlı listeye dönüştüren örnek bir C uygulamasıdır. Program; ekleme (dosyadan), silme, arama, sıralama ve kütüphane bilgisi hesaplama (toplam kitap, toplam sayfa, ortalama sayfa sayısı) gibi temel işlemleri menü tabanlı olarak sunar.

## Dosyalar
- `1.c` : Projenin kaynak kodu. Kuyruk (`kuyruk`) ve çift bağlı halka (`node`) yapıları ile işlem yapar.
- `kitaplar.txt` : Programın okuduğu giriş dosyası. (Proje kökünde olmalı)

## Derleme ve Çalıştırma (Windows - PowerShell)
1. PowerShell açın ve proje dizinine gidin:

```powershell
cd 'C:\Users\oguuz\OneDrive\Desktop\VeriYapilariOdev'
```

2. GCC ile derleyin (MinGW veya benzeri GCC kurulu olmalı):

```powershell
gcc 1.c -o kutuphane.exe
```

3. Programı çalıştırın:

```powershell
.\kutuphane.exe
```

Menüden 1 seçilerek dosyadan ekleme ve listeleme gerçekleştirilebilir.

## `kitaplar.txt` Dosya Formatı
Her satır bir kitap kaydını temsil eder ve alanlar '|' (pipe) ile ayrılmıştır. Beklenen sırayla alanlar:

ISBN|Kitap Adı|Yazar Adı|Tür|SayfaSayısı

Örnek:

```
9786050950953|Simyacı|Paulo Coelho|Roman|184
9789750724556|Kürk Mantolu Madonna|Sabahattin Ali|Klasik|160
```

Not: Program `fscanf` ile `"%lf|%99[^|]|%99[^|]|%99[^|]|%d%*c"` biçiminde okuma yapar. ISBN sayısal (double) formatında beklenir.

## Özellikler
- Dosyadan kuyruk oluşturma
- Kuyruktan ISBN'ye göre sıralı döngüsel çift bağlı liste oluşturma
- Menüde: ekleme (dosyadan), silme (ISBN ile), arama (türe göre ve sayfa uzunluğu sınıflandırması), sıralama (yazar adına göre), kütüphane istatistikleri
- Basit konsol çıktıları ile listeleme

## Bilinen Sorunlar ve Dikkat Edilmesi Gerekenler
- `1.c` içindeki `siralama()` fonksiyonunda bir satır eksik/sözdizimi hatası bulunuyor: `temp2->next->prev = ;` — burası doğru işaret edilecek düğümü atamalıdır. Bu nedenle derleme hatası alabilirsiniz.
- Program, boş `kitaplar.txt` veya beklenmeyen biçimli satırlar için yeterli hata kontrolü yapmıyor; `fscanf` başarısız olduğunda `temp->next = NULL;` gibi erişimler `temp` NULL ise segfault oluşturabilir. Giriş doğrulama eklenmelidir.
- Kuyruktan listeye çevirme sırasında ve silme işlemlerinde bazı bellek temizleme (free) ve NULL kontrolleri eksik olabilir; büyük veri için bellek sızıntısı oluşabilir.

## Önerilen İyileştirmeler (Next steps)
- `siralama()` fonksiyonundaki hatayı düzeltmek ve fonksiyonu test etmek.
- `dosyadanKuyrugaEkle()` içinde `fscanf` başarısız olduğunda oluşabilecek `NULL` erişimlerini engelleyecek kontroller eklemek.
- Bellek sızıntılarını önlemek için program sonlandırılmadan önce kuyruk ve liste düğümlerinin serbest bırakılması (`free`) eklenmeli.
- ISBN'i double yerine string (karakter dizisi) olarak saklamak daha güvenli olabilir (çok uzun ISBN'ler/özel karakterler). Bu sayede `fscanf` formatı da daha esnek olur.
- Unit test veya küçük bir test giriş dosyası ekleyip derleme ve temel işlevleri otomatik doğrulayan betikler oluşturmak.

## Katkıda Bulunma
1. Repo fork'lanır.
2. Yeni bir branch açın (ör. `fix/siralama`).
3. Değişiklikleri yapıp PR açın; değişiklik açıklamasında hangi hataları düzelttiğinizi belirtin.

## Lisans
Bu proje örnek amaçlıdır. İsterseniz uygun bir açık kaynak lisansı (MIT, Apache-2.0 vb.) ekleyebilirsiniz.

---
Hazırlayan: Proje kaynak kodu baz alınarak otomatik oluşturulan README (Türkçe). Kodun detaylı analizi ve testleri önerilir; özellikle `siralama()` fonksiyonundaki sözdizimi hatası düzeltilmeden derleme çalışmayabilir.
