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

#### ตัวอย่าง Code ของ Face Recognition
```c++
Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
for(int i=0;i<faces.size();i++){
    //point begin and end of faces
    Rect face_num = faces[i];
    Point f_begin(faces[i].x, faces[i].y);
    Point f_end(faces[i].x + faces[i].width , faces[i].y + faces[i].height);

    Rect crop = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
    Mat cropimage = gray_scale(crop);
    imshow("f", cropimage);

    rectangle(frame, face_num,CV_RGB(0, 255, 0), 2);

    int predict_label = -1;
    double confidence = 0.0;
    model -> predict(cropimage,predict_label, confidence);
    
    if(confidence == 0.0){
        int check = 0;
    }
    cout << confidence << endl;
    if(predict_label == 1){
        if(confidence < 50){
            name_user = "khing";
        }
        else{
            name_user = "unknown";
            
        }
        check += 1;
    }
```

#### ตัวอย่าง code ของส่วน Prediction
```c++
Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
	//read model
	model -> read("trainingdata.yml");
	
	//cascade face
	CascadeClassifier face_cascade;
	string classifier = "haarcascade_frontalface_alt.xml";
	face_cascade.load(classifier);

	string window = "cap_faceDetection";
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
### ตัวอย่าง รูปของการ Recognition
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

    bot.sendPhoto(msg.chat.id,"test_picture.jpg",{caption:})
    .then(() => {
        console.log('--sending completed--');
        console.log('--sended to '+msg.chat.username+'--');
    })
    .catch(() => {
        console.log('-- sending err --');
    });


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
|    [@MixPacharapon](https://github.com/MixPacharapon)    |     [@ khingbmc](https://github.com/khingbmc)     |     [@RawitSHIE](https://github.com/RawitSHIE)     |

# 👨‍🏫 Instructor

|<a href=""><img src="https://scontent.fbkk1-4.fna.fbcdn.net/v/t1.0-9/14611010_10153805956002331_6002362915012083123_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=fdf96ad3e3dd2eb670a52e234fe22660&oe=5B50638F" width="100px"></a>  |<a href=""><img src="https://scontent.fbkk1-5.fna.fbcdn.net/v/t1.0-9/10402732_10152130758782532_1878791821436724505_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=9b93596be0f28e499d113e10ed772f32&oe=5B72C5E5" width="100px"></a>  |
| :-: | :-: |
|ผศ. ดร. กิติ์สุชาติ พสุภา|ผศ. ดร. ปานวิทย์ ธุวะนุติ|


# 🔗Reference

 [OpenCV C++](https://opencv.org/)

 [node.js telegram bot api](https://github.com/yagop/node-telegram-bot-api)

[Telegram Bot Api - Telegram APIs Document](https://core.telegram.org/bots/api)


___


<p align="center">
<img src="img/it.jpg" width="200">

รายงานนี้เป็นส่วนหนึ่งของวิชา Computer Programming (รหัส 06016315)

คณะเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

</p>


___
