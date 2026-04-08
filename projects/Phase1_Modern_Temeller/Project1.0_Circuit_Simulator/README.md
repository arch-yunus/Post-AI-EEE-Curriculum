# 🔌 Proje 1.0: C++ Nümerik Devre Simülatörü (Physics Engine)

Dünyaya hoş geldin Meta-Mühendis. 
Kağıt üzerinde klasik EEM derslerinde öğrendiğimiz RLC devre diferansiyel denklemlerini **koda** döküyoruz. 

Neden? Çünkü geleceğin mimarları otonom bir sistem inşa ettiklerinde, o sistemin fiziksel hareketini, motor dinamiklerini ve elektronik tepkilerini önce C++ üzerinde matematiği ile simüle ederler. Kusursuz kontrol algoritmaları (LQR, MPC), ancak sistemin fiziksel sınırlarını "nümerik olarak" çözebiliyorsan yazılabilir.

Bu projede RLC devresinin 2. derece diferansiyel denklemini yüksek doğruluklu **Runge-Kutta 4 (RK4)** metodu kullanarak Standart C++ (STL) ile çözüyoruz ve zaman bazlı voltaj/akım değerlerini `.csv` dışa aktarıyoruz.

## 🧮 Matematiksel Arka Plan

Seri RLC devresinin Kirchoff Voltaj Yasasına (KVL) göre diferansiyel denklemi:
`V(t) = L*(di/dt) + R*i + (1/C)*q`

Bunu bilgisayarın çözebileceği **birinci dereceden iki state (durum) denklemine** ayırıyoruz:
1. `dq/dt = i`
2. `di/dt = (V(t) - R*i - q/C) / L`

Euler metodu çok fazla hata (drift) yaratacağı için algoritmada yüksek hassasiyetli `RK4` kullanılmıştır. C++ kodu saniyede 10.000 döngü (100 mikrosaniye `dt`) ile sistemi iteratif olarak çözer.

## 🚀 Derleme ve Çalıştırma (Build & Run)

Sisteminde `CMake` ve bir C++ derleyicisi (GCC/Clang/MSVC) kurulu olmalıdır.

```bash
# 1. Build klasörünü oluştur
mkdir build
cd build

# 2. CMake ile konfigürasyonu yap
cmake ..

# 3. Kodu derle
make          # (Linux / Mac için)
cmake --build . # (Windows için)

# 4. Simülatörü çalıştır
./simulator   # (Windows ise .\Debug\simulator.exe vs.)
```

## 📊 İleri Görev: Python Entegrasyonu
Çıktı olarak `simulation_results.csv` dosyası elde edeceksin. Gerçek bir mühendis sadece veriyi üretmez, onu yorumlar.

**Sıradaki Monk Mode Görevin:** Bir Python dosyası (örn: `plotter.py`) oluştur. `pandas` ve `matplotlib` kütüphanelerini kullanarak bu CSV verisini oku ve V(t) step fonksiyonuna karşılık gelen "Sönümlü Titreşim (Damped Oscillation)" eğrisini ekrana çizdir. Parametreleri (`R`, `L`, `C`) değiştirerek sistemin Underdamped ve Overdamped tepkilerini fiziksel olarak gözlemle.
