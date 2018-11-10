var db = require('../Dbconnection');
var TimeOpen={
    getAllTimeOpen:function(callback){
        return db.query("Select * from time_open ORDER BY id DESC",callback);
    },
    // getUserById:function(id,callback){
    //     return db.query("select * from user where IdUser=? ",[id],callback);
    // },
    // getUserById1:function(id,pass,callback){
    //     return db.query("select * from user where IdUser=? AND Password=?",[id,pass],callback);
    // },
    addTimeOpen:function(TimeOpen,callback){
        return db.query("Insert into time_open(user,date,time) values(?,?,?)",[TimeOpen.user,TimeOpen.date,TimeOpen.time],callback);
    },
    // deleteUser:function(id,callback){
    //     return db.query("delete from user where IdUser=?",[id],callback);
    // },
    // updateUser:function(id,User,callback){
    //     return db.query("update user set IdUser=?,Password=?,Fname=?,LName=?,Birthday=?,Gender=?,avatar=? where IdUser=?",[User.IdUser,User.Password,User.Fname,User.LName,User.Birthday,User.Gender,User.avatar,id],callback);
    // }


};
 module.exports=TimeOpen;
