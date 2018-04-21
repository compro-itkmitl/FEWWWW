const TelegramBot = require('node-telegram-bot-api');
const token = '572017543:AAFy1s2YoJf9a6kcUryIaoCKN9jUn9ftV_k';
const bot = new TelegramBot(token, {polling: true});
var NodeWebcam = require( 'node-webcam' );

//Default options 
var opts = {
    width: 1280,
    height: 720,
    quality: 100,
    delay: 0, 
    saveShots: true,
    output: "png",
    device: false,
    callbackReturn: "location",
    verbose: false
};

const usr = 454788039;
bot.sendMessage(usr, "Welcome To Feww Alert (I have awaken)");

bot.onText(/\/start/, (msg) => {
    exec('./a.out', (error, stdout, stderr) => {})
    .then(() => {
        console.log('--Initiate Succeed--');
        bot.sendMessage(msg.chat.id, "Select Option", {
        "reply_markup": {
            "keyboard": [["/sendpic"]]
            }
        });
    })
    .catch(() => {
        console.log('-- Initiate Fail --');
    });
});

bot.onText(/\/sendpic/, (msg) => {
    exec('node alert.js', (error, stdout, stderr) => {})
});
