# 🏎️ Proje 3.1: Object-Oriented C++ Extended Kalman Filter (EKF)

Python'da yazılan EKF mantığını anladıktan sonra, asıl sanayi koduna geçiş yapıyoruz. Otonom bir araçta (örneğin ROS2 C++ Node'ları içinde) sensör füzyonu algoritması bir Class yapısı olarak tasarlanıp bellek yönetimini (Memory Management) kusursuz yapmak zorundadır.

Bu proje, C++ hızında `Predict` (Fizik motoru) ve `Update` (Sensör verisi düzeltmesi) metodlarını ayıran gerçeğe en yakın EKF kodudur.

## 🚀 Derleme ve Çalıştırma

```bash
mkdir build
cd build
cmake ..
make
./ekf_sim
```
Bu sayede her yeni sensör verisinde kovaryans matrislerinin (Belirsizlik / P) nesne yönelimli olarak nasıl küçüldüğünü saf hızda göreceksin.
