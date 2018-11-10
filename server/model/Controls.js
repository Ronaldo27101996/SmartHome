var db = require('../Dbconnection');
var Controls={
    getCurrentStatus:function(callback){
        return db.query("Select * from control",callback);
    },
    // getUserById:function(id,callback){
    //     return db.query("select * from user where IdUser=? ",[id],callback);
    // },
    
    // addTimeOpen:function(TimeOpen,callback){
    //     return db.query("Insert into time_open(user,date,time) values(?,?,?)",[TimeOpen.user,TimeOpen.date,TimeOpen.time],callback);
    // },


};
 module.exports=Controls;
