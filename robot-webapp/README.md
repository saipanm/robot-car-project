# robot-car-project

## คำแนะนำการเริ่มต้นใช้งานสำหรับการพัฒนาโปรเจค webapp ของ robot-car-project ใน raspberry pi4

1. **เปิด Terminal**: เริ่มต้นใช้งานโดยเปิดโปรแกรม Terminal เพื่อใช้คำสั่งต่างๆ

2. **ใช้คำสั่งพื้นฐาน**:

   - **`ls`**: ใช้เพื่อแสดงรายการไฟล์และโฟลเดอร์ทั้งหมดในตำแหน่งปัจจุบัน
     ```bash
     ls
     ```
     
   - **`cd <ชื่อไดเรกทอรี>`**: ใช้เพื่อเปลี่ยนไปยังไดเรกทอรีอื่น ตัวอย่างเช่น การเปลี่ยนไปยังโฟลเดอร์ `robot-car-project`
     ```bash
     cd robot-car-project
     ```

   - **`cd ..`**: ใช้เพื่อย้อนกลับไปยังไดเรกทอรีก่อนหน้า
     ```bash
     cd ..
     ```

   - **`pwd`**: ใช้เพื่อแสดงตำแหน่งปัจจุบัน (path) ว่าอยู่ที่ไหนในโครงสร้างไดเรกทอรีของระบบ
     ```bash
     pwd
     ```
     ตัวอย่างผลลัพธ์เมื่อใช้คำสั่ง `pwd` และกด Enter:
     ```bash
     /var/www/html/robot-car-project/robot-webapp
     ```

   ## การ ssh ผ่าน vscode

    1. กดตามรูปด้านล่าง

    ![image](../readme-picture/Screenshot%202567-11-02%20at%2020.20.55.png)

    2. กด Remote-SSH: Connect to Host... ตามรูปด้านล่าง

    ![image](../readme-picture/Screenshot%202567-11-02%20at%2020.21.53.png)

    3. พิม password และกด Enter
    ```bash
     earnpan
     ```
    4. กด Open Folder ตามรูปด้านล่าง

    ![image](../readme-picture/Screenshot%202567-11-02%20at%2020.23.20.png)

    5. กด Choose Folder ด้วย path ดังนี้
    ```bash
     /var/www/html/robot-car-project/robot-webapp
     ```
    6. แก้ไขไฟล์ได้ตามปกติ

    7. Save ไฟล์ โดยกด `ctrl + shift + p` บน VSCode แล้วพิมพ์ `save as root` แล้วกด Enter

    8. `cd` ไปที่โฟลเดอร์ `robot-webapp` แล้วพิมพ์คำสั่งด้านล่าง
        ```bash
        npm run build
        ```



