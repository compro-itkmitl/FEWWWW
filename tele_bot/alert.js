var NodeWebcam = require( 'node-webcam' );

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
    let exec = require('child_process').exec;
    setTimeout(function() {
        exec('node notify.js', (error, stdout, stderr) => {
        })
      }, 5000);
    console.log('--capture completed--');
});