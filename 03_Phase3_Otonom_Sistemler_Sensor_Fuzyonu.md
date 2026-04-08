# Phase 3: Otonom Sistemler ve Sensör Füzyonu (Autonomous Systems)

Yapay zekanın ve gömülü sistemlerin birleşimi artık otonom, karar alabilen ve çevresiyle etkileşime giren hareketli yapılara (robotlara, dronelara, insansız kara araçlarına) evrildiği aşamadır.

Kör bir robota çevresini algılama yeteneği vereceğiz. Burada modern algoritmik kontrol teorisi, ileri derece matematiksel filtreleme ve Robotik İşletim Sistemi (ROS2) mimarisi "Meta-Mühendisin" silahları olacaktır.

---

## 📚 1. Yüksek Yoğunluklu Kaynaklar

* **Kitap:** *Probabilistic Robotics* – Sebastian Thrun. (Dünyadaki otonom robotların İncili'dir. Belirsizlikleri, SLAM algoritmalarını ve Kalman Filtrelerini matematikten pratiğe taşır).
* **Kitap:** *Modern Control Engineering* – Katsuhiko Ogata. (Fiziksel dünyayı matematiksel denklemlerle modelleyip kontrol altında tutmanın klasik ama efsane kaynağı - dijital/kesikli zaman (discrete) formlarına odaklanılarak okunmalıdır).
* **Kitap / Kılavuz:** *ROS2 Official Documentation / Nav2 Navigation Stack*. (Dünyadaki otonom sistemlerinin ortak dili ve ekosistemi).
* **Kaynak:** *Computer Vision: Algorithms and Applications* – Richard Szeliski. (Kamera verisini sadece yapay zeka ile değil, amaca yönelik algoritmik geometriyle bir araya getirmek için).

---

## 🔨 2. Otonom Ürün Geliştirici Projeleri (Solo Builder Projects)

### Proje 3.0: Otonom Kontrol Mimarisi: Modern State-Space / Model Predictive Control (MPC)
* **Senaryo:** Sadece PID kullanarak bir aracı saatte 100 km hızla giderken virajı otonom döndüremezsin; sistem dinamikleri çok daha komplekstir ve geleceği tahmin etmen (görüş mesafesi vs.) gerekir.
* **Görev:** C++ veya Python (Numpy/Scipy ile) kullanarak bir "Inverted Pendulum" (Ters Sarkaç) veya temel bir araç kinematiği (Bicycle Model) simüle et. Üzerine sistemin kendi fiziksel sınırlarını hesaba katan bir MPC (Model Predictive Control) veya LQR denetleyicisi tasarla. Modelin zaman içindeki fiziksel değişimlerini bir iterasyon matrisiyle tahmin edip en uygun motor komutlarını hesapla.

### Proje 3.1: ROS2 Düğüm Mimarisi (Node Architecture) ve C++ Entegrasyonu
* **Senaryo:** Aracın içindeki tüm sensörlerin (Lidar, Kamera, IMU) ve motorların birbirinden bağımsız ama asenkron ve kusursuz bir senkronizasyonla "konuşması" gerekir.
* **Görev:** ROS2 (Humble/Jazzy fark etmez) üzerinde C++ kullanarak 3 farklı düğüm (node) oluştur:
    1.  `SensorNode`: Sentetik bir Lidar veya IMU verisi (Point Cloud vs.) yayınlar (Publisher).
    2.  `ControlNode`: Bu sensör verisini abone olup (Subscriber) yorumlar ve bir hareket (Cmd_vel) kararı oluşturur.
    3.  `MotorNode`: Bu hareketi işleyip fiziksel motor (simüle edilmiş) için Action/Service katmanına dönüştürür.
* Gerçek zamanlı DDS (Data Distribution Service) altyapısının gecikmelerini (Latency) analiz et.

### Proje 3.2: Körlüğü Bitir: Sensör Füzyonu (Extended Kalman Filter - EKF)
* **Senaryo:** GPS kapalı alanda çekmez ve saniyede sadece 1 Hz veri verir, IMU (ivmeölçer) çok hızlıdır (200 Hz) ancak sürekli x, y ekseninde kayar (drift yapar). Bu iki çöp veriden kesin lokasyon bulman gerekir.
* **Görev:** Bu iki farklı sensörden (farklı frekans ve hata paylarında) gelen verileri matematiksel olarak birleştirerek, robotun bulunduğu (State) konumu ve hızını çıkaran **Extended Kalman Filter (EKF)** kodunu yaz. Kodu ROS2 ve Python kullanarak gazebo ortamında sanal bir araç üzerinde test et. 

### Proje 3.3: Sentetik Görüş ve Kamera Kalibrasyonu (OpenCV + AI)
* **Senaryo:** Kamera donanımı kusurludur; mercekler dünyayı yamuk ve bombeli gösterir. Bu yamuk dünyada otonom sürüş yapılamaz veya derinlik hesaplanamaz. 
* **Görev:** C++ OpenCV kullanarak sıfırdan bir "Chessboard" kalibrasyon script'i yaz. Distorsiyon (Distortion) katsayılarını çıkar ve ham (raw) videoyu eşzamanlı olarak düzelt. Ardından düzeltilmiş görüntü üzerinden basit bir "Şerit Takip (Lane Detection)" (Canny Edge + Hough Transform) veya bir TensorRT engelden kaçma modeli yürüt.

---

## 🧠 3. Meta-Mühendis Monk Mode Çerçevesi

1. **"Simülasyonda Çalışması Hiçbir Şey İfade Etmez." (Fiziksel Şüphecilik):** Simülasyon, fiziksel dünyanın dejenere ve acımasız hatalarını gizler. Simülasyonda mükemmel giden aracın Lidar'ı sahada güneşte kör olur. Tasarımlarında her zaman "Ya sensör bozulursa?", "Ya motor gecikirse?" modelini hesaba kat.
2. **Korkusuz Matematik Kullanımı:** Kalman Filtreleri, Vektör Uzayları, ve Matrix formülasyonları senin sadece gözlemlediğin değil, bizzat şekillendirdiğin araçlar olmalıdır. Formülleri anlamadığında, koda döküp Matrix değerlerinin nasıl güncellendiğini ekranda izle.
3. **C++ ROS2 Pratiği:** Endüstri Python kullanarak sensör verisi aktarmaz; çünkü yavaştır." Python AI analizi içindir, sistemi birbirine bağlayan kan ve damarlar (ROS2 düğümleri) *Modern C++* ile yüksek performanslı olmalıdır.
