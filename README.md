<img src="img/banner.png">

# What is FEWWW
Fewww คือ ระบบแจ้งเตือนบุคคลมาเยือนบ้าน โดยใช้ระบบ Face-Detection เข้ามาช่วยเหลือในการตรวจจับหน้าบุคคล

# Our Tool
สิ่งที่เราใช้มาประกอบการทำ Project Fewww ก็มีดังนี้ <br>
* Rasberry Pi 3 Model B
* Logitech Webcam

ส่วนทางด้วย Software
* C++ (OpenCV)
* Javascript (node-telegram-bot-api)
* Python

# How did it work?
Fewww จะทำงานอยู่บน Raspberry-Pi โดยจะคอยตรวจจับใบหน้าที่มาอยู่ในกล้อง โดย Feww จะทำการ Matching กับใบหน้าของบุคคลในบ้าน โดยถ้า ก็ทำการ Notify กับผู้ใช้ ผ่านทาง Telegram bot ที่ชื่อว่า Fewww Alert 

## openCV C++


```c++


```


## Telegram bot api
<img src="img/banner tele.png" >

```js
const TelegramBot = require('node-telegram-bot-api');
const token = '<botToken>';
const bot = new TelegramBot(token, {polling: true});

setTimeout(function() {
    bot.sendPhoto(msg.chat.id,"test_picture.jpg")
    .then(() => {
        console.log('--sending completed--');
        console.log('--sended to '+msg.chat.username+'--');
    })
    .catch(() => {
        console.log('-- sending err --');
    });
    }, 5000);

```
> 
# Interface



# Team Member

|<a href=""><img src="img/mix.jpg" width="100px"></a>  |<a href=""><img src="https://scontent.fbkk1-6.fna.fbcdn.net/v/t1.0-9/30440871_1518320704947507_229588219837022208_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=1eda5c9a906282e61ee3c5a8f75c4726&oe=5B5C09E1" width="100px"></a>  |<a href=""><img src="https://avatars0.githubusercontent.com/u/31315990?s=460&v=4" width="100px"></a>  |
| :-: | :-: | :-: |
|พชรพล พรหมมา|รฐนนท์ จันทนะสุคนธ์|รวิชญ์ โลหะขจรพันธ์|
|60070058 |      60070079      |      60070081      |
|    @    |     @ khingbmc     |     @RawitSHIE     |

# Instructor
|<a href=""><img src="https://scontent.fbkk1-4.fna.fbcdn.net/v/t1.0-9/14611010_10153805956002331_6002362915012083123_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=fdf96ad3e3dd2eb670a52e234fe22660&oe=5B50638F" width="100px"></a>  |<a href=""><img src="https://scontent.fbkk1-5.fna.fbcdn.net/v/t1.0-9/10402732_10152130758782532_1878791821436724505_n.jpg?_nc_fx=fbkk1-3&_nc_cat=0&oh=9b93596be0f28e499d113e10ed772f32&oe=5B72C5E5" width="100px"></a>  |
| :-: | :-: |
|ผศ. ดร. กิติ์สุชาติ พสุภา|ผศ. ดร. ปานวิทย์ ธุวะนุติ|

# Reference
 [OpenCV C++](https://github.com/yagop/node-telegram-bot-api)

 [node.js telegram bot api](https://github.com/yagop/node-telegram-bot-api)

[Telegram bot api Document](https://github.com/yagop/node-telegram-bot-api)

