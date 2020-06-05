// var x11 = require('x11');

// var Exposure = x11.eventMask.Exposure;
// var PointerMotion = x11.eventMask.PointerMotion;

// var lib1 = function(callback){
//   x11.createClient(function(err, display) {

//     if (!err) {
//       var X = display.client;
//       var root = display.screen[0].root;
//       var wid = X.AllocID();
  
//       //getImage
//       X.GetImage(2, root, 0, 0, width, height, 0xffffffff, function(err, image) {
//         image = image
  
//       })
  
//       // X.CreateWindow(
//       //   wid,
//       //   root, // new window id, parent
//       //   0,
//       //   0,
//       //   500,
//       //   500, // x, y, w, h
//       //   0,
//       //   0,
//       //   0,
//       //   0, // border, depth, class, visual
//       //   { eventMask: Exposure | PointerMotion } // other parameters
//       // );
//       // X.CreateWindow()
//       // X.MapWindow(wid);
//       // var gc = X.AllocID();
//       // X.CreateGC(gc, wid);
//       // var white = display.screen[0].white_pixel;
//       // var black = display.screen[0].black_pixel;
//       // cidBlack = X.AllocID();
//       // cidWhite = X.AllocID();
//       // X.CreateGC(cidBlack, wid, { foreground: black, background: white });
//       // X.CreateGC(cidWhite, wid, { foreground: white, background: black });
//       // X.on('event', function(ev) {
//       //   if (ev.type == 12) {
//       //     X.PolyFillRectangle(wid, cidWhite, [0, 0, 500, 500]);
//       //     X.PolyText8(wid, cidBlack, 50, 50, ['Hello, Node.JS!']);
//       //   }
//       // });
//       // X.on('error', function(e) {
//       //   console.log(e);
//       // });
  
  
//     } else {
//       console.log(err);
//     }
//   });
  
// }


// var lib2 = function(callback){
//   var x11 = require("node-x11");
  
//   x11.init() // connect on current user screen see $DISPLAY in shell

//   var screenshot = x11.getImage();
  
//   console.log(screenshot.width); // image width ->Number;
//   console.log(screenshot.height); // image height -> Number;
//   console.log(screenshot.depth); // image depth -> Number;
//  // console.log(screenshot.data); // image raw pixel -> Buffer;
//   // var fs = require('fs');
//   // fs.writeFileSync()
// }


// lib2()