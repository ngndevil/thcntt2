var express = require('express');
var bodyParser = require("body-parser");
const cors = require('cors');
var mysql = require('mysql2');

var app = express();
app.use(cors());
app.use(express.static('public'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }))

//step 1:
var con = mysql.createConnection({
    host: "localhost",
    port: "3306",
    user: "root",
    password: "15032002Abc",
    insecureAuth : true,
    database: "SmartDB"
});
    

//step 2:
con.connect(function(err) {
    if (err) throw err;
    console.log("Connected!!!")
});
    
//RESTFull API
app.get('/xuatthongtinfarm', function (req, res) {
    var sql = "SELECT * FROM farm";
    con.query(sql, function(err, results) {
    if (err) throw err;
    res.send(results);
    })
})

app.get('/xuatthongtinsensor', function (req, res) {
    var sql = "SELECT * FROM SensorData";
    con.query(sql, function(err, results) {
    if (err) throw err;
    res.send(results);
    })
})

app.post('/themthongtinfarm', function (req, res) {
    var sql = "insert into farm (name, location, description, image) values('Farm 5' ,' 125 NY' , 'description her22e','5.jpg'); ";
    con.query(sql, function(err, results) {
        if (err) throw err;
        res.send("Them farm thanh cong!!!");
    });
});

app.post('/themthongtinsensor', function (req, res) {
    var sql = "insert into SensorData (temperature, humid, time, farmid) values  (floor(rand()*50), floor(rand()*100), NOW(), 3);";
    con.query(sql, function(err, results) {
        if (err) throw err;
        res.send("Them sensor thanh cong!!!");
    });
});

//server
var server = app.listen(5555, function () {
var host = server.address().address
var port = server.address().port
console.log("Example app listening at http://%s:%s", host, port)
})