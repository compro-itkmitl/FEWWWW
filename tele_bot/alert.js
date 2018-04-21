var NodeWebcam = require( 'node-webcam' );

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
    console.log('--capture completed--');
    var image = "<img src='" + data + "'>";
    let exec = require('child_process').exec;
    setTimeout(function() {
        exec('node notify.js', (error, stdout, stderr) => {
        })
      }, 1000);
});