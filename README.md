# Bài tập ESP32 ESP-NOW

Repo này gồm chuỗi bài tập thực hành giao thức **ESP-NOW** trên ESP32, từ cơ bản đến nâng cao.

---

## 1. One-way (Gửi một chiều)

- Mô hình đơn giản: **Sender** (Gửi) -> **Receiver** (Nhận).
- Sender cần biết **địa chỉ MAC** của Receiver để gửi gói tin.
- Receiver nhận dữ liệu và hiển thị lên **Serial Monitor** hoặc điều khiển thiết bị (LED/Relay).

---

## 2. Two-way (Giao tiếp hai chiều)

- Hai ESP32 giao tiếp song song (**Peer-to-Peer**).
- Cả 2 board đều đóng vai trò vừa gửi vừa nhận.
- Sử dụng các hàm callback để xử lý sự kiện:
  - `OnDataSent` -> Xác nhận gửi thành công.
  - `OnDataRecv` -> Xử lý dữ liệu nhận được.

---

## 3. Broadcast (Điều khiển đa thiết bị)

- Một **Master** gửi lệnh điều khiển cho nhiều **Slave** cùng lúc.
- Gửi đến địa chỉ MAC đặc biệt: **FF:FF:FF:FF:FF:FF**.
- Tất cả các ESP32 trong phạm vi phủ sóng đều nhận được tín hiệu (không cần add từng MAC).

---

## 4. Advanced (Tiết kiệm năng lượng)

- Kết hợp ESP-NOW với chế độ ngủ sâu (**Deep Sleep**).
- Quy trình tối ưu pin: Thức dậy -> Gửi dữ liệu -> Ngủ ngay lập tức.
- Dùng bộ nhớ **RTC** để lưu biến đếm (không bị mất khi ngủ).

---

## Cách chạy

1. Cài **Arduino IDE** và thêm board ESP32.
2. Nạp code lấy **MAC Address** để biết địa chỉ của board Receiver.
3. Mở code `.ino`, thay thế địa chỉ MAC vào biến `broadcastAddress`.
4. Kết nối ESP32, chọn đúng board và cổng COM.
5. Upload code và mở **Serial Monitor** (115200 baud) để xem kết quả.

---
