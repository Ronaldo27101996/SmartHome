var db = require('../Dbconnection');
var User={

    // getUserById:function(id,callback){
    //     return db.query("select * from user where IdUser=? ",[id],callback);
    // },
    getUserById:function(id,pass,callback){
        return db.query("select * from user where username=? AND password=?",[id,pass],callback);
    },



};
 module.exports=User;
