const PORT = 3484;
var http = require('http')
var socketio = require('socket.io')
var connection = require('./Dbconnection');
var TimeOPEN = require('./model/TimeOpen');
var Controls = require('./model/Controls');

var User = require('./model/User');
var ip = require('ip');
var app = http.createServer();
var io = socketio(app);
app.listen(PORT);
console.log("Server nodejs chay tai dia chi: " + ip.address() + ":" + PORT)

// connection.connect(function(err) {
//   if (err) throw err;
//   var sql ="SELECT * FROM time_open";
//   connection.query(sql, function(err,results){
//     if(err) throw err;
//     console.log(results);
//   })
// });


//Khi có một kết nối được tạo giữa Socket Client và Socket Server
io.on('connection', function(socket) {
    console.log("Connected");
// socket.on('connection_ESP09', function(socket) {
//     console.log("ESP Connected");
socket.on('android_connect',function(data){
  console.log(" Android Connected");
  //get data status and send to android here
})
	var io_data = true
socket.on('ANDROID_LIGHT1_IO',function(data){
  console.log("\n ANDROID_LIGHT1_IO", data)
  io_data = data;
		//Cài đặt chuỗi JSON, tên biến JSON này là json
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_LIGHT1_IO', json) //Gửi lệnh LED với các tham số của của chuỗi JSON
		console.log("send LIGHT1_IO")
})
socket.on('ANDROID_LIGHT2_IO',function(data){
  console.log("\n  LIGHT2_IO", data)
  io_data = data;
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_LIGHT2_IO', json)
		console.log("send LIGHT2_IO")
})
socket.on('ANDROID_LIGHT3_IO',function(data){
  console.log("\n LIGHT3_IO", data)
  io_data = data;
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_LIGHT3_IO', json)
		console.log("send LIGHT3_IO")
})
socket.on('ANDROID_LIGHT4_IO',function(data){
  console.log("\n LIGHT4_IO", data)
  io_data = data;
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_LIGHT4_IO', json)
		console.log("send LIGHT4_IO")
})
socket.on('ANDROID_FAN_IO',function(data){
  console.log("\n FAN_IO", data)
  io_data = data;
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_FAN_IO', json)
		console.log("send FAN_IO")
})
socket.on('ANDROID_PUMP_IO',function(data){
  console.log("\n PUMP_IO", data)
  io_data = data;
		var json = {
			"io_data": io_data
		}
		io.sockets.emit('SEND_PUMP_IO', json)
		console.log("send PUMP_IO")
})
var prog=0;
// socket.on('LED1PROG',function(data){
//   console.log("\n LED1PROG", data)
//   prog = data;
//
// 		var json = {
// 			"prog": prog
// 		}
// 		io.sockets.emit('SENDLED1Prog', json)
// 		console.log("send Progress ESP1")
// })
// socket.on('LED2PROG',function(data){
//   console.log("\n LED2PROG", data)
//   prog = data;
// 		//Cài đặt chuỗi JSON, tên biến JSON này là json
// 		var json = {
// 			"prog": prog
// 		}
// 		io.sockets.emit('SENDLED2Prog', json)
// 		console.log("send Progress ESP2")
// })
// socket.on('LED3PROG',function(data){
//   console.log("\n LED3PROG", data)
//   prog = data;
// 		//Cài đặt chuỗi JSON, tên biến JSON này là json
// 		var json = {
// 			"prog": prog
// 		}
// 		io.sockets.emit('SENDLED3Prog', json)
// 		console.log("send Progress ESP3")
// })
// 	//Khi nhận được lệnh LED_STATUS
// 	socket.on('\n LED_STATUS', function(status) {
// 		console.log("recv LED", status)
// 	})
  socket.on('OPEN_DOOR',function(data){ // open the door by phone
      console.log("\n OPEN_DOOR_BYPHONE", data)
      var json = {
  			"open": data
  		}
  		io.sockets.emit('SEND_OPEN_DOOR', json)
  		console.log("SEND_OPEN_DOOR")
  })
  // socket.on('TIME_OPEN',function(data){ // open the door by card
  //     var time = new Date();
  //     var name = data;
  //     var minute=time.getMinutes()>9?time.getMinutes():"0"+time.getMinutes();
  //     // luu name and time vào database
  //     var save = {
  //       user: name.user,
  //       date:time.getDate() +"/"+ (time.getMonth()+1) +"/"+ time.getFullYear(),
  //       time:time.getHours() +":"+ minute+''};
  //     console.log("\n TIME_OPEN", save);
  //     TimeOPEN.addTimeOpen(save,function(err,rows){
  //         if(err){
  //             console.log(err);
  //         }  else{
  //             console.log(rows);
  //         }
  //     });
  //
  // })

  socket.on('HISTORY',function(data){
      console.log("\n HISTORY", data);
      // TimeOPEN.addTimeOpen(save,function(err,rows){
      //     if(err){
      //         console.log(err);
      //     }  else{
      //         console.log(rows);
      //     }
      // });
      var results= TimeOPEN.getAllTimeOpen(function(err,rows){
        if(err){
          console.log(err);
        }
        else{
          io.sockets.emit('HISTORY_SEND', rows);
        }

      });

  })
  socket.on('LOGIN',function(data){
      console.log("\n LOGIN", data);
      // TimeOPEN.addTimeOpen(save,function(err,rows){
      //     if(err){
      //         console.log(err);
      //     }  else{
      //         console.log(rows);
      //     }
      // });
      var results= User.getUserById(data["username"],data["pass"],function(err,rows){
        console.log(data["username"])
        if(err){
          console.log(err);
        }
        else{
          io.sockets.emit('LOGIN_SEND', rows);
            console.log(rows)
        }

      });

  })
var active=true;
  socket.on('ACTIVE_SECURITY',function(data){
    console.log("\n ACTIVE_SECURITY", data)
    active = data;
  		var json = {
  			"active": active
  		}
  		io.sockets.emit('SEND_ACTIVE_SECURITY', json)
  		console.log("send active")
  })

	//Khi socket client bị mất kết nối
	socket.on('disconnect', function() {
		console.log("disconnect")

	})
});
