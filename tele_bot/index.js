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
    // bot.sendMessage(msg.chat.id, "Select Option", {
    //     "reply_markup": {
    //         "keyboard": [["/sendpic", "/openlive"]]
    //         }
    //     });
    exec('./a.out', (error, stdout, stderr) => {})
    .then(() => {
        console.log('--Initiate Succeed--');
    })
    .catch(() => {
        console.log('-- Initiate Fail --');
    });
});

bot.onText(/\/sendpic/, (msg) => {
    console.log('--received command--');
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
    });
// here to fix
    }).then(() => {
        bot.sendPhoto(usr,"test_picture.png")
    }).catch(() => {
        console.log('-- sending err --');
    });

