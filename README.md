<img src="img/banner.png">

# 🔐 What is FEWWW 
Fewww คือ ระบบแจ้งเตือน โดยใช้ระบบ Face-Recognition เข้ามาช่วยเหลือในการตรวจจับหน้าบุคคล และการนำ Chat Service มาเป็นตัวแจ้งเตือนและควบคุมการทำงาน (Bot) โดยจุดประสงค์คือการแจ้งเตือน เมื่อเครื่องมือ detect ใบหน้าของบุคคลให้เจ้าของบ้านรับรู้และตอบสนองได้ท่วงทันเหตุการณ์

# 🛠 Component 
สิ่งที่เราใช้มาประกอบการทำ Project Fewww ก็มีดังนี้ <br>
* [Rasberry Pi 3 Model B](https://www.raspberrypi.org/)
* Computer Webcam (ทางเราใช้ [Logitech HD WEBCAM C310](https://www.logitech.com/en-us/product/hd-webcam-c310?crid=34))

ส่วนทางด้าน ภาษา
* C++ (OpenCV)👁
* Javascript (node-telegram-bot-api) 📲
* Python (Training Model) 👥

## 🔗 Requested Module
* [OpenCV2](https://opencv.org/)
* OpenCV Extra Module
* [Node Telegram bot Api](https://github.com/yagop/node-telegram-bot-api)


# 🗜️How did it work?
Fewww จะทำงานอยู่บน Raspberry-Pi โดย System ของเรานั้นจะแบ่งเป็น 2 ส่วนหลังนั้นก็คือ ส่วนของการ `Recognition` และ `Notifiation` ซึ่งส่วนของการ `Recognition` นั้นจะคอย ตรวจจับใบหน้าและจะเป็นส่วนที่คอย Trigger ให้ส่วน `Notifiation` ทำงานนั้นคือ การ Notify ผู้ใช้

## 👁 OpenCV2 C++


<img src="img/banner cv.png" >
ในส่วนของการจดจำใบหน้าเป็นเรื่องง่ายสำหรับคน แต่เป็นเรื่องยากสำหรับคอมพิวเตอร์ โดยทางคอมพิวเตอร์ได้มีอัลกอริทึกมมากมายแต่ทุกสิ่งนั้นได้มีพื้นฐานมาจาก เรขาคณิต โดยนำ จุดที่เป็นจุดแสดงถึงองค์ประกอบภายในใบหน้าและภายนอกมาสร้างเป็นสมการเวคเตอร์
ซึ่งในจุดนี้ เราใช้ library C++ ที่ชื่อว่า OpenCV (version 2) เข้ามาช่วย

### ตัวอย่าง Code ของ Face Recognition

```c++

```
และแน่นอนการที่จะให้ตัว FEWWW นั้นสามารถ Identify Face ได้ แน่นอนเราก็ต้องทำการ Training ให้ Program สามารถเรียนรู้จากรูปใบไหน้าได้ (Training Model) 
### ตัวอย่างรูปการ Trainning
<p align="center">
    <img src="img/training pic.PNG" >
</p>

### ตัวอย่าง Code การ Training Face Recognition
```python
'''create recognizer'''
rec = cv2.face.LBPHFaceRecognizer_create()

'''This is path go to dataset'''
path = 'user'

'''define function get img'''
def getimg(path):
	'''get image path and append to list imgpath'''
	
	imgpath = [os.path.join(path, f) for f in os.listdir(path)]

	'''create list of faces and Id'''
	faces, Id = [], []

	'''loop for in img path'''
	for p in imgpath:
		'''add img to face_img and connvert to grayscale'''
		if(p == "user/.DS_Store"):
			continue
		face_img = Image.open(p)
		
		face_np = np.array(face_img, 'uint8')
		Ids = int(os.path.split(p)[-1].split('.')[0][-1])
		faces.append(face_np)
		
		print(Ids)
		
		Id.append(Ids)
		
		cv2.imshow("train", face_np)
		cv2.waitKey(10)
	
	return Id, faces

Id, faces = getimg(path)

rec.train(faces, np.array(Id))
rec.save('trainingdata.yml')
cv2.destroyAllWindows()

```
### ตัวอย่าง รูปของการ Detect
<p align="center">
    <img src="img/detection.jpg" >
</p>



## 🔔 Telegram bot api
<img src="img/banner tele.png">

ในส่วนของการ Notify User นั้นอย่างที่เราได้กล่าวไว้ในข้างต้นว่าเราใช้ตัว Telegram Bot เป็นตัวส่งให้ User รับรู้ โดยภาษาที่ใช้สั่งตัว Telegram Bot ที่เราใช้คือ JavaScript (node.js) และใช้  [node.js telegram bot api](https://github.com/yagop/node-telegram-bot-api) 
ซึ่งตัว Node.js นี้จะเป็นตัวที่รอการ Trigger จาก C++ เมื่อมีการ detect เกิดขึ้น เพื่อส่งให้กับผู้ใช้

### ตัวอย่าง Code ของการส่งรูปไปยัง User
```js
const TelegramBot = require('node-telegram-bot-api');
const token = '<botToken>';
const bot = new TelegramBot(token, {polling: true});

setTimeout(function() {
    bot.sendPhoto(msg.chat.id,"test_picture.jpg",{caption:})
    .then(() => {
        console.log('--sending completed--');
        console.log('--sended to '+msg.chat.username+'--');
    })
    .catch(() => {
        console.log('-- sending err --');
    });
    }, 5000);

```

# 📲 Interface
ในส่วนของการใช้งานนั้น การทำงาน Feww จะทำการ Notify ไปผ่านท่าง `Feww Alert bot` เพื่อเตือนให้เรารู้ว่า ให้เรารับรู้ โดยเมื่อเราเริ่มการทำงานของ ระบบแล้ว เราก็สามารถปล่อยให้ Programme นั้น Run ไปได้เลย

### วิธีการของเริ่ม Program
เริ่มแรก ทำการเข้าไปใน folder ของ Code แล้วเพียงพิมพ์ `./app` เข้าไปยัง Terminal
```
./app
```


### รูปตัวอย่างของ การแจ้งเตือน
<p align="center">
<img src="img/telegramint.png">
</p>

# 👥Team Member

|<a href=""><img src="img/mix.jpg" width="100px"></a>  |<a href=""><img src="https://scontent.fbkk1-6.fna.fbcdn.net/v/t1.0-9/30440871_1518320704947507_229588219837022208_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=1eda5c9a906282e61ee3c5a8f75c4726&oe=5B5C09E1" width="100px"></a>  |<a href=""><img src="https://avatars0.githubusercontent.com/u/31315990?s=460&v=4" width="100px"></a>  |
| :-: | :-: | :-: |
|พชรพล พรหมมา|รฐนนท์ จันทนะสุคนธ์|รวิชญ์ โลหะขจรพันธ์|
|60070058 |      60070079      |      60070081      |
|    @MixPacharapon    |     @ khingbmc     |     @RawitSHIE     |

# 👨‍🏫 Instructor

|<a href=""><img src="https://scontent.fbkk1-4.fna.fbcdn.net/v/t1.0-9/14611010_10153805956002331_6002362915012083123_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=fdf96ad3e3dd2eb670a52e234fe22660&oe=5B50638F" width="100px"></a>  |<a href=""><img src="https://scontent.fbkk1-5.fna.fbcdn.net/v/t1.0-9/10402732_10152130758782532_1878791821436724505_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=9b93596be0f28e499d113e10ed772f32&oe=5B72C5E5" width="100px"></a>  |
| :-: | :-: |
|ผศ. ดร. กิติ์สุชาติ พสุภา|ผศ. ดร. ปานวิทย์ ธุวะนุติ|


# 🔗Reference

 [OpenCV C++](https://opencv.org/)

 [node.js telegram bot api](https://github.com/yagop/node-telegram-bot-api)

[Telegram bot api Document](https://github.com/yagop/node-telegram-bot-api)


___


<p align="center">
<img src="data:image/png;base64,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" width="200">

รายงานนี้เป็นส่วนหนึ่งของวิชา Computer Programming (รหัส 06016206)

คณะเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

</p>


___
