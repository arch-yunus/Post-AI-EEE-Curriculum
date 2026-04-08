# 🛡️ Proje 4.0: Donanım Seviyesi Siber Güvenlik (Secure Telemetry)

Bir mühendis olarak yazdığın otonom sürüş algoritması ne kadar kusursuz olursa olsun, eğer internet üzerinden araca komut gönderen telemetri ağı şifreli değilse aracın hacklenir. Siber Güvenlik, projenin en sonuna bırakılan bir eklenti değil; donanım tasarımına en baştan entegre edilen "Temel Taştır (Root of Trust)".

Bu kod, MQTT veya RAW TCP bağlantısı üzerinden gönderilen bir sensör verisinin ya da motor komutunun yolda (Man-In-The-Middle Attack ile) değiştirildiğinde sunucu tarafından kriptografik imzalar ile nasıl reddedileceğini (Reject) simüle eder.

## 🚀 Çalıştırma

```bash
python secure_telemetry.py
```
Bu sayede bir verinin (payload) arasına eklenen Hash (SHA256) doğrulamasıyla donanımın güvenliğini nasıl garantiye aldığımızı inceleyeceksin. Gerçek endüstride bu "Salt" dediğimiz şifreleme anahtarları, mikrodenetleyicinin kırılamaz özel bir çipine (Secure Element / TPM) fiziksel olarak gömülür.
