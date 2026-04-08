# 🔋 Proje 4.1: C++ Batarya Yönetim Sistemi (BMS) Firmware Simülatörü

Meta-Mühendislik felsefesinin en kritik kurallarından biri: **Güvenli olmayan zeka, bombadır.**
10.000 dolarlık bir dronun veya otonom bir roketin enerjisini lityum-iyon piller sağlar. Bu piller, fiziksel entropi dolayısıyla ısınmaya veya gerilim dengesizliklerine eğilimlidir. Eğer bu pilleri koruyan donanım yazılımı (Firmware) çökerse cihaz yanar.

Bu proje endüstri standartlarındaki bir BMS'in:
- Hücre Voltajını (Overvoltage / Undervoltage)
- Hücre Sıcaklığını (Thermal Runaway / NTC Termistör)

Gerçek zamanlı okuyarak sistemi nasıl nanosaniyeler içerisinde "SAFE STATE" e (Röleleri kapatıp sistemi öldüren güvenli kapanma) kilitlediğini simüle eder.

## 🚀 Derleme ve Çalıştırma

```bash
mkdir build
cd build
cmake ..
make
./bms_sim
```
Konsolda göreceğin simülasyon, "Max Thrust (Tam Gaz)" kalkan bir dronun 2. pil hücresindeki aşırı ısınmayı anında hissedip sistemi nasıl kapattığını (Kill-Switch) gösterecektir.
