# Phase 2: Gömülü Sistemler ve Uç Yapay Zeka (Embedded & Edge-AI) - High Density

Zekayı buluttan fiziksel dünyaya, doğrudan metalin içine (Bare-Metal) indirgeme aşamasıdır. Bu fazda mühendislik, mikrosaniye düzeyindeki gecikmelerin (latency) ve donanım kısıtlarının mükemmel bir orkestrasyonudur. Otonom bir aracın yapay zeka beynini (Jetson/Xavier) ve kaslarını yönetecek sinir sistemini (RTOS ve MCU) inşa ediyoruz.

---

## 📚 1. Yüksek Yoğunluklu Kaynaklar (Industrial Standard Reference)

### A. Real-Time Architectures
*   **Jane Liu - Real-Time Systems:** RTOS dünyasındaki Scheduling (RMS, EDF) teorilerinin en derin akademik kaynağı.
*   **FreeRTOS Master Class:** Çok izlekli (multi-threaded) donanım yönetimi için temel referans.

### B. High-Performance Edge-AI
*   **NVIDIA CUDA Programming Guide:** GPU hattını doğrudan C++ ile sömürmek için.
*   **TensorRT Developer Guide:** Model çıkarım (inference) hızlandırmasında "Quantization" ve "Layer Fusion" teknikleri.

### C. Safety-Critical Design
*   **ISO 26262 Standard Overview:** Otomotivde fonksiyonel güvenlik (ASIL seviyeleri: A'dan D'ye).
*   **MISRA C:2012:** Donanım kodlamasında "Undefined Behavior" riskini sıfıra indiren kurallar bütünü.

---

## 🔬 2. Teknik Derinlik: RTOS Scheduling ve AI Quantization

### A. RTOS: Priority Inversion (Öncelik Tersinmesi) Problematiği
Gömülü sistemlerin en büyük faciası, düşük öncelikli bir görevin (task), yüksek öncelikli bir görevi (örn: Fren sistemi) dolaylı olarak bloke etmesidir.
*   **Çözüm:** `Priority Inheritance` ve `Priority Ceiling` protokollerinin C++ ortamında (FreeRTOS mutexleri ile) nasıl implemente edildiğini hazmedin.

### B. Edge-AI: INT8 Quantization & Calibration
Bir Deep Learning modelini uçta çalıştırmanın sırrı, 32-bit floating point ağırlıkları 8-bit tam sayılara indirmektir.
*   **Matematiksel Zorluk:** Bilgi kaybını (accuracy loss) minimize etmek için `Entropy Calibration` yapılması gerekir. TensorRT'nin bu süreci donanım üzerinde (Tensor Cores) nasıl optimize ettiğini dökümante edin.

---

## 🔨 3. Solo Builder Projeleri (Hardcore Engineering)

### Proje 2.0: CMSIS ile Register-Level ARM Programlama
*   **Görev:** STM32 üzerinde hiçbir hazır kütüphane (HAL/LL) kullanmadan, doğrudan `Systick` ve `NVIC` registerları üzerinden bir "Gerçek Zamanlı Saat" inşâ edin.
*   **Challenge:** Osiloskop ile `Interrupt Latency` (Kesiş gecikmesi) ölçümü yapın. Donanımın koda verdiği fiziksel tepki süresini nanosaniyelerle hesaplayın.

### Proje 2.1: FreeRTOS tabanlı Otonom Telemetri Sistemi
*   **Görev:** Çok görevli (Multi-tasking) bir mimari kurun.
    1. **Task 1 (Hig-Pri):** Sensör verisi okuma (SPI - 100Hz).
    2. **Task 2 (Med-Pri):** Veri işleme ve Kontrol (LQR/PID).
    3. **Task 3 (Low-Pri):** WiFi/UART üzerinden telemetri aktarımı.
*   **Constraint:** `Queue` ve `StreamBuffer` kullanarak görevler arası veri aktarımını kilitlenmesiz (lock-free) yapmaya çalışın.

### Proje 2.2: TensorRT & C++ Performans Pipeline
*   **Görev:** Jetson üzerinde çalışan bir YOLO modelini Python'dan C++'a taşıyın.
*   **Optimization:** `Pinned Memory` ve `CUDA Streams` kullanarak GPU-CPU veri aktarımı ile hesaplama işlemini örtüştürün (overlap). Bu sayede %30-40 arası FPS artışı yakalayın.

---

## 🛠️ 4. Donanım Vizyonu: Debugging & Monitoring

Gömülü sistem mühendisliği "karanlıkta" yapılamaz.
- **Logic Analyzer:** I2C, SPI ve CAN-Bus hatlarındaki bit seviyesindeki hataları yakalamak için.
- **Memory Profiling:** `Stack Overflow` hatalarını ve `Heap fragmentation` durumlarını izlemek için RTOS araçlarını kullanın.
- **Power Analysis:** Uç cihazda (Edge-AI) batarya ömrünü korumak için işlemcinin `Low Power Mode` geçişlerini ve akım çekişlerini (Power Profile) analiz edin.

---

## 🧠 5. Master Methodology

1.  **Metale Dokun (Bare-Metal Mindset):** Kütüphanelere güvenmeyin. Kütüphane hata verdiğinde datasheet'i açıp o bitin gerçekten nerede takıldığını bulacak sabre sahip olun.
2.  **Safety First (ASIL Compliance):** Yazdığınız her satır kodun "Eğer burası crash olursa araç kaza yapar mı?" sorusuna cevabını verin.
3.  **Hafıza == Kutsal:** Gömülü sistemde bellek sonsuz değildir. Değişkenlerin boyutlarını (uint8_t vs int) titizlikle seçin ve bellek hizalamasına (alignment) dikkat edin.
