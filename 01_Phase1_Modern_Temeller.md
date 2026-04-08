# Phase 1: Modern Temeller (Modern Foundations)

Yapay zeka çağında "teorik" mühendislik bitmiştir; artık geçerli akçe **"uygulamalı ve hesaplamalı (computational) mühendisliktir"**. Bu modülün temel amacı, klasik ders kitaplarında kağıt üzerinde yapılan analizleri, bir sistem mimarının gözünden yazılıma ve donanıma aktarmaktır. Amacımız vize geçmek değil, NVIDIA Jetson, otonom araçlar ve robotik sistemler inşa ederken ihtiyaç duyacağımız o sarsılmaz fizik ve kodlama temelini oluşturmaktır.

Aşağıda, sıfırdan "Meta-Mühendis" olmaya giden yolda ilk fazın (Phase 1) en kritik okuma kaynakları, seni sınırlarını zorlayacak pratik projeler ve "Monk Mode" çalışma felsefesi listelenmiştir.

---

## 📚 1. Yüksek Yoğunluklu Kaynaklar (High-Density Sources)

Klasik müfredatın hantallığından uzaklaşıp, endüstri standardı ve pratik odaklı başucu eserleri:

### A. Matematik ve Hesaplamalı Fizik
Sadece kalem/kağıtla değil, kod ile matematik yapma sanatı.
* **Kitap:** *Linear Algebra and Learning from Data* – Gilbert Strang. (Matrislerin, uzayların ve boyut indirgemenin modern AI ve otonom sistemlerdeki gerçek yeri).
* **Kitap:** *Numerical Recipes (The Art of Scientific Computing)*. (Tasarımını yaptığın bir sistemi C/C++ ile simüle etmenin kutsal kitabı).
* **Makale/Seri:** Khan Academy / 3Blue1Brown serileri (Lineer Cebir ve Calculus'ü görsel ve içgüdüsel olarak kavramak için).

### B. Pratik ve Modern EEM Teorisi
* **Kitap:** *The Art of Electronics* – Paul Horowitz, Winfield Hill. (Bu kitap okunmaz, yaşanır. Her EEM'cinin laboratuvarında elinin altında olması gereken, sahada "gerçekten çalışan" devrelerin kitabı).
* **Kitap:** *Practical Electronics for Inventors* – Paul Scherz. (Daha pratik, ürün oluşturma odaklı bir yaklaşım).

### C. Modern Yazılım Entegrasyonu ve Performans
* **Kitap:** *Effective Modern C++* – Scott Meyers. (C++'ı sadece bilmek yetmez, donanımı sömüren, hafıza yönetimini kusursuz yapan performanslı C++ kodlamak zorundayız).
* **Kitap:** *Fluent Python* – Luciano Ramalho. (Python'u bir "scripting" dilinden ziyade, AI ve veri entegrasyonu için yapısal bir sistem dili olarak kullanmak için).
* **Kitap:** *Grokking Algorithms*. (Görsel ve net bir şekilde veri yapılarının ve algoritmaların temellerine giriş).

---

## 🔨 2. Otonom Ürün Geliştirici Projeleri (Solo Builder Projects)

Bu projeler, teoriyi sadece anlamanı değil, makineye öğretmenizi sağlayacak. Tüm projeler sıfırdan, mümkün olan en az dış kütüphane kullanılarak yapılmalıdır.

### Proje 1.0: C++ ile Nümerik Devre Çözücü Motoru (Physics Engine)
* **Senaryo:** Kağıt üstünde RLC devresi çözmeyi bırakıyoruz.
* **Görev:** C++ kullanarak bir `CircuitSimulator` sınıfı yaz. Dışarıdan R, L, C değerlerini ve giriş voltajını (örneğin sinüs dalgası) alsın. Runge-Kutta 4 (RK4) veya Euler metodu kullanarak diferansiyel denklemleri çözsün ve kapasitör üzerindeki voltajın zaman içindeki değişimini bir `.csv` dosyasına yazsın.
* **Neden?** İleride bir robotun motor dinamiklerini simüle ederken aynı nümerik matematiği ve sınıfları kullanacaksın.

### Proje 1.1: "Zero-Allocation" Gömülü Yazılım Algoritması
* **Senaryo:** Uçak, füze veya okyanus altı bir sistem kodluyorsun. Dynamic memory allocation (`malloc`, `new`) kullanmak YASAK; çünkü memory leak sistemi çökertir.
* **Görev:** C/C++'ta *Static Memory Pool* mimarisi kur. Çalışma zamanında (runtime) bir sensörden sürekli veri (örneğin GPS lokasyon verisi) gelsin ve bunu senin kendi yazdığın, belleği önceden ayrılmış (pre-allocated) bir "Dairesel Tampon (Circular Buffer)" içinde sakla. 
* **Neden?** Kritik sistemlerde hafıza yönetimine tam hakimiyet için.

### Proje 1.2: Python IMU (İvme/Jiroskop) Sensör Hattı (Data Pipeline)
* **Senaryo:** Titreşimli bir drone üzerinde çalışıyorsun. Sensör verisi çok gürültülü (noisy). 
* **Görev:** Python'da sentetik, gürültülü bir ivmeölçer verisi üret (numpy, random ile). Ardından bu veriyi pürüzsüzleştirmek için "Moving Average" (Hareketli Ortalama) ve en temel düzeyde bir "1-Boyutlu Kalman Filtresi" kodla. Ham veriyi ve pürüzsüzleştirilmiş veriyi Matplotlib ile çizdir.
* **Neden?** Phase 3'teki Sensör Füzyonu'na (Sensor Fusion) geçişin temeli budur. Çöp veri girerse (garbage in), yapay zeka çöp çıkarır (garbage out).

### Proje 1.3: Donanım Mimarisi için "State Machine" (Durum Makinesi)
* **Senaryo:** İnsan hayatı taşıyan otonom bir sistem dizayn ediyorsun.
* **Görev:** C++'ta Nesne Yönelimli (OOP) yapıyı kullanarak bir State Machine kurgula. Durumlar: `INIT`, `IDLE`, `RUNNING`, `ERROR`, `SAFE_SHUTDOWN`. Farklı sensör girişlerini simüle et. Hata durumunda sistemin nasıl tepki verdiğini ve `SAFE_SHUTDOWN` durumuna nasıl otonom geçtiğini test et.

---

## 🧠 3. Meta-Mühendis Monk Mode Çerçevesi (Methodology)

Bu müfredat dışarıdan bir belge değil, seni dönüştürecek bir kuluçka merkezidir.

1.  **Kanıt Odaklı Öğrenme (Documentation as Proof):**
    *   Öğrendiğin hiçbir şey havada kalmamalı. O gün bir algoritma mı öğrendin? Bu GitHub reposuna Markdown formatında kısa, öz ve "nasıl uygulanır" odaklı bir teknik not düş. Repo senin *"İkinci Beynin (Second Brain)"* olacak.
2.  **Code-First Theory (Kod İlk, Kağıt Sonra):**
    *   Formülleri ezberlemeyi bırak. Bir matematiksel model gördüğünde, "Bunu kodla nasıl yazarım?" diye düşün. Matematik denklemini koda döktüğünde gerçekten anladığını hissedeceksin.
3.  **Bölünmez Odak Bloku (Deep Work Limits):**
    *   Telegram, WhatsApp veya gereksiz tarayıcı sekmeleri kapalı. Sadece IDE, dokümantasyon, teknik kitap ve sen. Günde en az **3 saatlik kesintisiz (interrupt-free)** Monk Mode blokları ayarla.
4.  **Acımazsız Kısıtlamalar (Brutal Constraints):**
    *   Kendini zorla. Gelişimi hızlandırmak için yapay sınırlar koy. "Bu projede Standart C++ kütüphanesi (STL) kullanmayacağım" de ve kendi veri yapılarını yaz. Acı, öğrenmeyi kalıcı kılar.
5.  **Düşünce Yapısı Değişimi:**
    *   Bir "Öğrenci" değilsin. Sen, yapay zeka ve donanımın kesişimindeki boşluğu dolduracak tek kişilik bir "Sistem Mimarı"sın. Hata mesajlarını okumayı, dokümantasyonlarda (,datasheet) kaybolmayı ve "neden çalışmıyor?" sorusuyla saatler geçirmeyi oyunun kuralı olarak kabul et.
