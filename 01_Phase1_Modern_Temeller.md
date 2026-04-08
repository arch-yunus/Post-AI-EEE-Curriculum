# Phase 1: Modern Temeller (Modern Foundations) - Master Level

Yapay zeka devrimi sonrası "teorik" mühendislik, yerini **Computational Analysis (Hesaplamalı Analiz)** ve **Mathematical Engineering (Matematik Mühendisliği)** disiplinlerine bırakmıştır. Artık bir mühendis için denklemi çözmek değil, o denklemi en efektif dijital mimaride modellemek esastır. Amacımız, NVIDIA Jetson, otonom araçlar ve robotik sistemler inşa ederken ihtiyaç duyacağımız o sarsılmaz fizik ve kodlama temelini profesyonel seviyeye taşımaktır.

## 📚 1. Yüksek Yoğunluklu Kaynaklar (World-Class Reference Hierarchy)

### A. Uygulamalı Matematik ve Robotik Kinematiği
*   **Gilbert Strang - Linear Algebra and Learning from Data:** Matrislerin AI ve otonom sistemlerdeki gerçek yerini anlamak için. SVD (Singular Value Decomposition) ve Eigenvalue analizlerine odaklanın.
*   **Kevin Lynch - Modern Robotics:** Kinematik, dinamik ve kontrolün Lie Grupları (SO(3), SE(3)) üzerinden modern anlatımı.
*   **Calculus of Variations:** Kontrol teorisinin (LQR/MPC) temeli olan Lagrange çarpanları ve optimizasyon matematiği için klasik kaynaklar.

### B. Computational Physics & Simulation
*   **Numerical Recipes (The Art of Scientific Computing):** Herhangi bir fiziksel sistemi C++ ile simüle etmenin kutsal kitabı.
*   **Art of Electronics (Horowitz & Hill):** Donanım dünyasının "Hacking" ve "Building" odaklı mukaddes kitabı.

### C. Profesyonel Yazılım Standartları
*   **Scott Meyers - Effective Modern C++:** Donanımı sömüren, sıfır-maliyetli (zero-overhead) soyutlamalar için.
*   **MISRA C++ Guidelines:** Güvenlik-kritik (Safety-critical) sistemlerde yazılım geliştirme standartları (Otonomi ve Savunma sanayii standardı).

---

## 🔬 2. Teknik Derinlik: Nümerik Stabilite ve Diferansiyel Çözücüler

Otonom sistem simülasyonlarında en büyük tuzak **Numerical Instability** (Nümerik Kararsızlık) durumudur. Bir denklemi kodlarken sadece `dt` (zaman adımı) kullanmak yetmez; sistemin *stiffness* değerine göre doğru çözücüyü seçmek gerekir.

| Metot | Kararlılık (Stability) | Hesaplama Maliyeti | Kullanım Alanı |
| :--- | :--- | :--- | :--- |
| **Forward Euler** | Düşük (Kritik dt bağımlı) | Çok Düşük | Basit, hızlı prototipler. |
| **Runge-Kutta 4 (RK4)** | Orta/Yüksek | Orta | Dinamik sistem simülasyonları (Motorlar, İHAlar). |
| **Implicit Methods (Backward Euler)** | Çok Yüksek | Yüksek (Matris çevirme gerektirir) | Sert (Stiff) diferansiyel denklemler ve gerçek zamanlı katı fizik. |

---

## 🔨 3. Solo Builder Projeleri (Advanced Tiers)

### Proje 1.0: C++ ile Nümerik Fizik Motoru (Physics Engine) - Deep Dive
Daha önce yazdığımız `CircuitSimulator`'u bir adım ileriye taşıyın. 
*   **Hardcore Challenge:** Sisteme sadece pasif komponentler değil, **LQR (Linear Quadratic Regulator)** kontrolörü ekleyin. 
*   **Teknik Detay:** Durum-Uzay (State-Space) modellerini matris formunda tutun. `x_dot = Ax + Bu` denklemini çözerek sistemin kararlılığını Eigen-değerleri üzerinden kontrol edin.

### Proje 1.1: Zero-Allocation Gömülü Yazılım Mimarisi
*   **Challenge:** Dinamik bellek (`malloc`/`new`) kullanımı kesinlikle yasak.
*   **Mühendislik Kısıtı:** Bir sensör füzyon hattı için `Static Memory Pool` ve `Circular Buffer` kullanarak, sistemin bellek kullanımını derleme zamanında (compile-time) sabitleyin. 
*   **Profesyonel Araç:** `Clang-Static-Analyzer` kullanarak bellek sızıntılarını daha kod derlenmeden yakalayın.

### Proje 1.2: Modern C++ ile Matrix Library İnşası
*   **Challenge:** Hazır kütüphane (Eigen vb.) kullanmadan, `operator overloading` ve `template metaprogramming` kullanarak kendi Matris kütüphanenizi yazın.
*   **Target:** `Matris[3][3] * Vektör[3]` işlemini donanımı yormadan milisaniyeler altında gerçekleştiren, hafıza hizalanmış (Memory-aligned) bir yapı kurun.

---

## ⚙️ 4. Pro-Toolchain: Profesyonel Geliştirme Ortamı

Bir Meta-Mühendis, IDE'nin ötesinde araçlara hükmeder:
- **CMake & Ninja:** Karmaşık C++ projelerini saniyeler içinde derlemek için.
- **Valgrind / ASan:** Bellek hatalarını ve tanımsız davranışları (Undefined Behavior) yakalamak için.
- **Clang-Tidy:** Kodun modern standartlara (C++17/20) ve endüstri standartlarına uygunluğunu denetlemek için.
- **GDB (Advanced):** Core dump'ları analiz ederek sistemin neden çöktüğünü "metal" seviyesinde anlamak için.

---

## 🧠 5. Methodology (Monk Mode Framework)

1.  **Code-First Theory:** Bir teoriyi okurken yan sekmede o teoriyi simüle eden bir C++ dosyası açık olmalı. Kodlamadığın teori senin değildir.
2.  **Brutal Optimization:** Kodun çalışması yetmez; otonom araçta işlemci zamanı altındır. Big-O analizinden öte, `Cache Miss` ve `Branch Prediction` kavramlarını anlayarak kodunu optimize et.
3.  **Documentation (The Second Brain):** Her seansın sonunda `/notes` klasörüne "Engineering Decision Log" tut. "Neden bu algoritmayı seçtim?" sorusunun cevabını dökümante etmeyen mühendis, sadece bir teknisyendir.
