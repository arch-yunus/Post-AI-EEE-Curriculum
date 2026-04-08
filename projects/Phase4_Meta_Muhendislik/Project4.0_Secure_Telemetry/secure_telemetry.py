import base64
import hashlib
import json

print("[Meta-Engineering] Phase 4: Asymmetric Crypto Telemetry Pipeline\n")

# Normally, cryptography should be handled by libraries like 'cryptography' or hardware security modules (HSM)
# This is a conceptual implementation of Hash/Signatures demonstrating Hardware Security in Edge Devices.

class SecureDevice:
    def __init__(self, device_id):
        self.device_id = device_id
        self.secret_salt = b"meta_engineer_firmware_salt_2026"

    def sign_telemetry(self, data_dict):
        # 1. Serialize data
        payload = json.dumps(data_dict, sort_keys=True).encode('utf-8')
        
        # 2. Append secret hardware salt
        content_to_sign = payload + self.secret_salt
        
        # 3. Create SHA-256 Hash signature
        signature = hashlib.sha256(content_to_sign).hexdigest()
        
        return {
            "device_id": self.device_id,
            "payload": data_dict,
            "signature": signature
        }

# Server side
def verify_packet(packet):
    expected_salt = b"meta_engineer_firmware_salt_2026"
    payload = json.dumps(packet["payload"], sort_keys=True).encode('utf-8')
    computed_signature = hashlib.sha256(payload + expected_salt).hexdigest()
    
    if computed_signature == packet["signature"]:
        return True
    return False

# ----- SIMULATION -----
robot = SecureDevice("Otonom-Araç-01")

# Valid Telemetry
telemetry = {"speed": 45, "gps_lat": 41.0082, "gps_lon": 28.9784}
packet = robot.sign_telemetry(telemetry)

print(f"📡 Transmitting Packet Over Air:\n{json.dumps(packet, indent=2)}\n")

if verify_packet(packet):
    print("✅ Server: Packet Verified. Command Authenticated.")
else:
    print("❌ Server: Packet REJECTED! Security Compromised.")

# Man in the Middle Attack (MITM)
print("\n[!] MITM Attacker alters the speed to 150 km/h...")
packet["payload"]["speed"] = 150

if verify_packet(packet):
    print("✅ Server: Packet Verified.")
else:
    print("❌ Server: Packet REJECTED! Signature Invalid. Hacker Blocked.")
