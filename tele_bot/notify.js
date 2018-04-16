const TelegramBot = require('node-telegram-bot-api');
const token = '572017543:AAFy1s2YoJf9a6kcUryIaoCKN9jUn9ftV_k';
const bot = new TelegramBot(token, {polling: true});


// notify
console.log('--notifying--');
const usr = 454788039;
bot.sendPhoto(usr,"test_picture.jpg",{caption : "Anonymous\nUnknow person"} );
console.log('--sending completed--');
setTimeout(function() {
    process.exit();
  }, 5000);
