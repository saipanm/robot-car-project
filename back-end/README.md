# Robot Control API

โปรเจกต์นี้เป็น API ที่ใช้ Flask เพื่อควบคุมรถหุ่นยนต์ โดย Raspberry Pi จะรับข้อมูลจาก ESP8266 ผ่านการสื่อสารแบบ Serial

## ข้อกำหนดเบื้องต้น

1. **Python**: ตรวจสอบให้แน่ใจว่าคุณได้ติดตั้ง Python ในระบบของคุณแล้ว
2. **Flask**: ติดตั้ง Flask และ dependencies อื่นๆ โดยใช้คำสั่ง `pip install -r requirements.txt` หลังจากที่โคลนรีโพซิทอรีเรียบร้อยแล้ว

## การติดตั้ง

1. **โคลนรีโพซิทอรี**:
    ```bash
    git clone https://github.com/saipanm/robot-car-project.git
    cd back-end
    ```

2. **ติดตั้ง dependencies**:
    ```bash
    pip install -r requirements.txt
    ```

## การตั้งค่า

1. **ตั้งค่าการเชื่อมต่อ Serial**:
    - ตรวจสอบให้แน่ใจว่า ESP8266 ถูกเชื่อมต่อกับพอร์ต Serial ที่ถูกต้องของ Raspberry Pi
    - ปรับพอร์ต Serial ในโค้ดหากจำเป็น:
      ```python
      ser = serial.Serial('/dev/serial0', 9600, timeout=1)  # แทนที่ '/dev/serial0' ด้วยพอร์ตที่ถูกต้อง
      ```

## การรัน API

1. **สร้างbashfileเริ่มรัน Flask API**:

    สร้าง file name `start.sh` และเขียนโค้ดดังนี้:

    ```bash
        export FLASK_APP=robot_control_api.py  
        export FLASK_ENV=production
        gunicorn -w 4 -b 0.0.0.0:1212 robot_control_api:app  
    ```
2. **รัน API อัตโนมัติใช้ pm2 โดยรันจาก bash file**:
    ```bash
    pm2 start start_api.sh
    ```


## API Endpoints

### 1. เคลื่อนที่หุ่นยนต์

- **Endpoint**: `/api/move`
- **Method**: `POST`
- **คำอธิบาย**: เคลื่อนที่หุ่นยนต์ในทิศทางที่กำหนด
- **ตัวอย่างคำขอ**:
    ```json
    {
        "direction": "forward", "reverse", "left", "right", "stop"
    }
    ```
- **การตอบสนอง**:
    ```json
    {
        "status": "moving <direction>",
        "response": "<response from esp>"
    }
    ```

### 2. ตรวจสอบสถานะของ API และการเชื่อมต่อ Serial

- **Endpoint**: `/api/status`
- **Method**: `GET`
- **คำอธิบาย**: ตรวจสอบสถานะของ API และการเชื่อมต่อ Serial
- **การตอบสนอง**:
    ```json
    {
        "status": "API is running",
        "serial_connection": "connected" , "disconnected"
    }
    ```

## คำอธิบายโค้ด

### การสื่อสารแบบ Serial

ฟังก์ชัน **`send_command`** ส่งคำสั่งไปยัง ESP8266 และรอรับการตอบสนอง

 ```python
    def send_command(command):
        if ser and ser.is_open:
            ser.write((command + "\n").encode('utf-8'))  
            print(f"Sent to esp: {command}")

            response = ser.readline().decode('utf-8', errors='ignore').strip()
            if response:
                print(f"esp response: {response}")
                return response
            else:
                print("No response from esp.")
                return "No response"
        else:
            print("Error: Serial connection is not open.")
            return "No connection"
  ```

### API Resources

- **MoveResource**: จัดการคำขอ POST เพื่อควบคุมการเคลื่อนที่ของหุ่นยนต์
  
  ```python
        class MoveResource(Resource):
            def post(self):
                
                data = request.json
                direction = data.get("direction")

                if not direction:
                    return {"error": "No direction provided"}, 400

                valid_directions = ["forward", "reverse", "left", "right", "stop"]
                if direction not in valid_directions:
                    return {"error": "Invalid direction"}, 400

                response = send_command(direction)
                return {"status": f"moving {direction}", "response": response}

    ```

- **StatusResource**: จัดการคำขอ GET เพื่อเช็คสถานะของ API และการเชื่อมต่อ Serial
    ```python
    class StatusResource(Resource):
        def get(self):
            connection_status = "connected" if ser and ser.is_open else "disconnected"
            return {"status": "API is running", "serial_connection": connection_status}
    ```
