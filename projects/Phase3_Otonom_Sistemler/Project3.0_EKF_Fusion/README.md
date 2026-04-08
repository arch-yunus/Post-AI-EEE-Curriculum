# 🤖 Proje 3.0: Sensör Füzyonu ve Kalman Filtresi

Fiziksel sensörler (IMU, Lidar, Kamera, Radar) her zaman gürültülüdür (Noisy). Bir otonom aracın sadece GPS okuyarak şeritte kalması imkansızdır çünkü veriler sapar (drift).

Bu proje otonom sistemlerin beyni olan **Sensör Füzyonunun (Sensor Fusion)** temelini oluşturur.

## 🧮 Ne Öğreneceksin?
* **Predict (Tahmin):** Aracın mevcut hızıyla nerede olması gerektiği matematiği.
* **Update (Güncelleme):** Kusurlu sensör verisinin gelmesi.
* **Kalman Gain (K):** Fiziğe mi yoksa Sensör'e mi daha çok güvenmeliyiz formülü.

## 🚀 Çalıştırma

```bash
# Numpy gereklidir
pip install numpy
python ekf_core.py
```
Çıktılarda belirsizliğin (Uncertainty `P`) zamanla nasıl sıfıra yaklaştığını gözlemle.
