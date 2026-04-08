# Phase 3: Otonom Sistemler ve Sensör Füzyonu (Autonomous Systems) - High Density

Bu faz, "akıllı" bir sistemin dış dünyayı algılama (Perception), kendi konumunu belirleme (Localization) ve güvenli bir yol haritası çizme (Planning) yeteneklerinin birleştiği zirve noktasıdır. Burada matematik artık sadece bir araç değil, aracın hayatta kalma stratejisidir.

---

## 📚 1. Yüksek Yoğunluklu Kaynaklar (Expert Level Reference)

### A. Localization & SLAM
*   **Sebastian Thrun - Probabilistic Robotics:** Otonom sistemlerin "İncili". Bayes Filtreleri (Kalman, Particle) ve SLAM algoritmalarının matematiksel temeli.
*   **Cyrill Stachniss SLAM Course (YouTube/University of Bonn):** Modern SLAM teknikleri (G2O, Factor Graphs) üzerine en iyi ders serisi.

### B. Control Theory & Planning
*   **Model Predictive Control (MPC):** Modern otonom araçlarda en çok kullanılan, gelecekteki hataları öngörerek kısıtlar altında (hard constraints) optimizasyon yapan kontrol mimarisi.
*   **Steven LaValle - Planning Algorithms:** Yol planlama (A*, RRT, PRM) dünyasının en kapsamlı rehberi.

### C. Middleware & System Integration
*   **ROS2 (Robot Operating System) Documentation:** Dağıtık bir robotik sistem kurmanın endüstri standardı. DDS (Data Distribution Service) protokolünü anlamak kritik.

---

## 🔬 2. Teknik Derinlik: Sensör Füzyonu ve Kontrol Matematiği

### A. Extended Kalman Filter (EKF) vs. Unscented Kalman Filter (UKF)
Düşük gürültülü ve doğrusal olmayan (non-linear) sistemleri tahmin etmek için EKF kullanılırken (Taylor serisi yaklaşımı), yüksek dereceli non-lineerliklerde UKF (Sigma Points) daha kararlıdır.
*   **Deep Dive:** Mahalanobis mesafesi kullanarak gelen sensör verisinin "outlier" (hatalı sıçrama) olup olmadığını istatistiksel olarak nasıl reddedeceğinizi öğrenin.

### B. Path Planning: Frenet Frame Optimization
Otonom sürüşte yol planlama genellikle otoyolun merkez çizgisine göre (S, D koordinatları) yapılır.
*   **Teknik Detay:** Jitter'sız (pürüzsüz) bir yörünge için 5. dereceden polinomlar (Quintic Polynomials) kullanarak hız, ivme ve jerk kısıtlarını optimize edin.

---

## 🔨 3. Solo Builder Projeleri (Cyber-Physical System Mastery)

### Proje 3.0: 2D SLAM ve Lidar Odometri (Python/C++ Hybrid)
*   **Görev:** ROS2 altında bir Lidar sensörü ile (veya simülasyonda Gazebo/Ignition) çevre haritalaması yapın. Gmapping veya Cartographer paketlerini kullanarak odometre hatalarını IMU ile füzyonlayın.
*   **Challenge:** Harita üzerindeki "Loop Closure" (döngü kapatma) anındaki koordinat düzeltmelerini izleyin.

### Proje 3.1: Model Predictive Control (MPC) ile Çizgi Takibi
*   **Görev:** Aracınızı sadece PID ile değil, sistemin fiziksel limitlerini (maksimum direksiyon açısı, maksimum fren) bilen bir MPC kontrolörü ile sürün.
*   **Tool:** Python'da `cvxopt` veya C++'ta `CasADi` gibi optimizasyon kütüphanelerini kullanarak "Kost Fonksiyonu" minimize edin.

### Proje 3.2: Behavior Tree (Davranış Ağacı) ile Karar Mekanizması
*   **Görev:** Karmaşık bir otonom görev kurgulayın (Örn: "Durağa git, yolcu al, engel varsa dur").
*   **Teknik:** Finite State Machine'lerin (FSM) hantallığından kurtulup, profesyonel robotikte kullanılan **Behavior Trees** (`BehaviorTree.CPP`) kütüphanesini sisteminize entegre edin.

---

## 🛠️ 4. Profesyonel Mimari: ROS2 ve DDS

Otonom araçlarda tek bir `main.cpp` yoktur. Sistem onlarca mikro-servis (Nodes) şeklinde çalışır.
- **Middleware Excellence:** ROS2'nin altındaki DDS katmanında `Reliability` ve `Durability` (Quality of Service - QoS) ayarlarını doğru yaparak, kritik kontrol mesajlarının asla kaybolmamasını garanti altına alın.
- **Lifecycle Nodes:** Sistemin boot-up (başlatma) sırasında tüm sensörlerin doğru konfigürasyonda açıldığından emin olmak için "Managed Nodes" mimarisini kullanın.

---

## 🧠 5. Master Methodology

1.  **İstatistiki Düşünme:** Sensör verisine asla %100 güvenmeyin. Her ölçümün bir varyansı (hata payı) olduğunu ve gerçekliğin olasılıksal bir bulut olduğunu kabul edin.
2.  **Simulation to Reality (Sim2Real):** Algoritmanı önce simülasyonda (Gazebo/NVIDIA Isaac) %99 başarıya ulaştır, sonra gerçeğe aktar. Donanım hataları gerçektir; simülasyon kusursuzdur. Farkı (Reality Gap) anlamaya çalış.
3.  **Hata Analizi (Post-Mortem):** Aracın neden yoldan çıktığını log dökümlerinden (rosbag files) saniye saniye analiz etmeden bir sonraki adıma geçme.
