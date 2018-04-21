var NodeWebcam = require( 'node-webcam' );
//Default options 
var opts = {
    width: 1920,
    height: 1080,
    quality: 100,
    delay: 0, 
    saveShots: true,
    output: "png",
    device: false,
    callbackReturn: "location",
    verbose: false
};

//Creates webcam instance 
var Webcam = NodeWebcam.create( opts );
//Will automatically append location output type 
Webcam.capture( "test_picture", function( err, data ) {} );
//Also available for quick use 
NodeWebcam.capture( "test_picture", opts, function( err, data ) {
});
//Get list of cameras 
Webcam.list( function( list ) {
    //Use another device 
    var anotherCam = NodeWebcam.create( { device: list[ 0 ] } );
});
//Return type with base 64 image 
var opts = {
    callbackReturn: "base64"
};
NodeWebcam.capture( "test_picture", opts, function( err, data ) {
    var image = "<img src='" + data + "'>";
});