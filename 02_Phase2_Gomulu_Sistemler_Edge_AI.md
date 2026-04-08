# Phase 2: Gömülü Sistemler ve Uç Yapay Zeka (Embedded & Edge-AI)

Zekayı buluttan (cloud) fiziksel dünyaya, doğrudan metalin içine (bare-metal) indireceğimiz aşamadır. Buradaki amaç sadece LED yakıp söndürmek veya hazır kütüphaneler kullanmak değil; işlemci zamanını, güç tüketimini ve gecikmeyi (latency) mikrosaniye düzeyinde yönetecek sistemleri inşa etmektir. 

Otonom bir aracın yapay zeka beynini (Jetson) ve kaslarını yönetecek sinir sistemini (RTOS ve MCU) kuruyoruz. Donanım affetmez. 

---

## 📚 1. Yüksek Yoğunluklu Kaynaklar

* **Kitap:** *Making Embedded Systems* – Elecia White. (Gömülü yazılım tasarım kalıpları, donanımla konuşan mimariler kurmak için endüstri standardı).
* **Kitap:** *Real-Time Systems and Software* – (Gerçek zamanlı kısıtlamalar, timer'lar ve donanım kesintileri - interrupt detayları).
* **Kitap & Dokümantasyon:** *NVIDIA TensorRT Documentation & CUDA C++ Programming Guide*. (Uç cihazlarda yapay zeka modelini en yüksek performansta (FPS) çalıştırmanın tek yolu modeli donanım mimarisine göre optimize etmektir).
* **Pratik Doküman:** *FreeRTOS Reference Manual*. (Birden çok görevin (task) işlemci üzerinde eşzamanlı olarak nasıl güvenli yönetileceğini anlamak için).

---

## 🔨 2. Otonom Ürün Geliştirici Projeleri (Solo Builder Projects)

### Proje 2.0: Bare-Metal Kesme (Interrupt) ve Timer Yönetimi
* **Senaryo:** Motorlardan okuduğun encoder (hız) verisi saliselik gecikmeyi (latency) bile kabul etmez. Polling (sürekli sorma) yöntemi sistemi kitler.
* **Görev:** STM32 veya benzeri bir ARM Cortex-M serisi mikrodenetleyici al (veya QEMU üzerinden simüle et). Bütün hazır kütüphaneleri (HAL) bir kenara bırak; doğrudan işlemcinin Register (Yazmaç) seviyesine inerek (CMSIS ile) Timer ve donanım kesmelerini (Hardware Interrupts) programla. Bir dış sinyal geldiğinde, ana programın akışını ne kadar sürede kestiğini ölç (Interrupt Latency).

### Proje 2.1: Gerçek Zamanlı İşletim Sistemi (RTOS) İş Parçacığı (Thread) Analizi
* **Senaryo:** Aracının içinde aynı anda hem GPS'ten veri okunması, hem motorlara güç verilmesi hem de bataryanın denetlenmesi gerekiyor.
* **Görev:** FreeRTOS kullanarak 3 farklı "Task" oluştur. Priority (öncelik) seviyelerini ayarla. Bir görevi kasıtlı olarak sonsuz döngüye sokup (starvation) sistemdeki "Watchdog Timer'ın" işlemciyi nasıl resetleyip hayatta tuttuğunu gözlemle ve kodla. Ortak bir belleğe (variable) veya UART hattına yazarken Mutex ve Semaphore mekanizmalarını kullanarak "Race Condition" (Veri Çakışması) hatalarını engelle.

### Proje 2.2: Uçta Kaba Kuvvet (Brute-Force at Edge): TensorRT ile C++ Model Optimizasyonu
* **Senaryo:** Python ile çok güzel bir nesne tanıma (YOLO) modeli eğittin ama bunu Jetson karta attığında 5 FPS alıyor. Ancak sana sistem gereği 30 FPS üzerinden gerçek zamanlı engel tespiti lazım.
* **Görev:** Eğittiğin .pt veya .onnx modelini al, NVIDIA TensorRT kullanarak C++ dilinde "Engined" formata derle. Modeli fp32'den fp16 (veya int8 quantization) kalibrasyonuna indirerek doğruluğu (accuracy) çok düşürmeden FPS'i 4-5 katına çıkaran çıkarım (inference) boru hattını (pipeline) sıfırdan C++ ile yaz.

### Proje 2.3: FPGA ve Kendi AI Donanım Hızlandırıcını Yapmak (Temel Seviye Verilog/VHDL)
* **Senaryo:** Mikroişlemciler seri (sıralı) çalışır, oysa AI devasa matris çarpımlarına (paralel) ihtiyaç duyar. Donanımın mantığını anlamazsan onu hükmedemezsin.
* **Görev:** VHDL veya Verilog (HDL: Hardware Description Language) kullanarak basit bir matris-vektör çarpım donanımı (MAC - Multiply Accumulate unit) dizayn et. Devreyi bir FPGA simülatöründe (ModelSim, Vivado vb.) test et. Sentetik bir nöronun iç donanımını fiziken yarat.

---

## 🧠 3. Meta-Mühendis Monk Mode Çerçevesi

1. **Bare-Metal Deneyimi (Metale Dokun):** İlk gömülü sistem kodlarını yazarken işi kolaylaştıran kütüphanelerden (Arduino vs) kaçın. İşlemcinin datasheet'ine bakarak, hexadecimal adreslere doğrudan bit-maskeleme yaparak donanımı hisset. Acı vericidir ama sistemi "içeriden" anlamanı sağlar.
2. **Logic Analyzer / Osiloskop Vizyonu:** Donanımda "print(x)" ile hata ayıklanmaz. Bir sinyalin fiziksel zamanlamasını, yükselen-düşen kenar sürelerini donanımsal görebilecek zihniyete geç. Kodun fiziksel dünyada kaç volt/milisaniye karşılığı olduğunu düşün.
3. **Yapay Zeka == Matris + Hafıza Genişliği (Memory Bandwidth):** Uç cihazlarda yapay zeka yaparken modelin ağırlıklarına değil, o ağırlıkların cihazın RAM'inden işlemcinin Cache'ine ne kadar hızlı indiğine (Bottleneck) odaklan. İşlem gücünü değil hafıza aktarımını optimize et.
