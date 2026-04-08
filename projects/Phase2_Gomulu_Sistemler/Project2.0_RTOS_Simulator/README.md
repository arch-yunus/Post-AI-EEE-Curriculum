# 🧠 Proje 2.0: RTOS Multi-Threading Simülatörü

Eğer bir mikrodenetleyicide sensör verisini okurken "while" döngüsünün içinde takılı kalırsan (blocking code), aracının motoru gecikir ve kaza yaparsın. Endüstri standardı gömülü sistemler "Eşzamanlı (Concurrent)" çalışmak zorundadır.

Bu kod kütüphanesi, ileride FreeRTOS veya Zephyr gibi Gerçek Zamanlı İşletim Sistemlerinde (RTOS) karşılaşacağın **"Task Scheduling", "Race Condition" ve "Mutex"** mantığını bilgisayarında saf C++ ile çalıştırabileceğin bir şablondur.

## ⚠️ Race Condition Nedir?
Motor ve Sensör aynı anda hafızadaki ortak bir değişkene yazıp okumaya çalışırsa veriler bozulur, sistem çöker. Bunu engellemek için `std::mutex` (Kilitleme Mekanizması) kullanılmıştır. Biri veriyi kullanırken kapıyı kilitler, işi bitince açar.

## 🚀 Derleme ve Çalıştırma

```bash
mkdir build
cd build
cmake ..
make
./rtos_sim
```
Ekranı izlediğinde Sensör Task'inin (10 Hz) Motordan (4 Hz) daha hızlı güncellediğini ve aralarında hiçbir bellek çakışması (memory collision) olmadığını göreceksin.
