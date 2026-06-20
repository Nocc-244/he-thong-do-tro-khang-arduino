# Hệ thống đo trở kháng sử dụng Arduino Uno

## Giới thiệu

Đây là đồ án môn học về thiết kế và xây dựng hệ thống đo trở kháng dựa trên nền tảng Arduino Uno.

Hệ thống sử dụng bộ tạo tín hiệu DDS AD9833 để tạo tín hiệu kích thích, bộ chuyển đổi ADC ADS1115 để thu thập dữ liệu và màn hình OLED SSD1306 để hiển thị kết quả.

## Phần cứng sử dụng

* Arduino Uno R3
* AD9833 DDS Signal Generator
* ADS1115 ADC 16-bit
* LM358
* LM393
* OLED SSD1306 I2C
* Điện trở chuẩn 10kΩ

## Chức năng

* Tạo tín hiệu kích thích 1 kHz
* Đo tín hiệu đầu vào và đầu ra
* Tính toán giá trị trở kháng
* Ước lượng độ lệch pha
* Hiển thị kết quả trên OLED

## Cấu trúc thư mục

Arduino_Code: Mã nguồn Arduino

Schematic: Sơ đồ nguyên lý

Images: Hình ảnh phần cứng và kết quả

Report: Báo cáo đồ án

## Tác giả

Hà Nguyễn

Kỹ thuật Điện tử và Tin học (EEI)
