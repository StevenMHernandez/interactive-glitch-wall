var express = require('express');
var app = express();
var tumblr = require('tumblr.js');
var config = require('../bin/data/config.json');

var client = tumblr.createClient({
    consumer_key: config.tumblr.consumer_key,
    consumer_secret: config.tumblr.consumer_secret,
    token: config.tumblr.token,
    token_secret: config.tumblr.token_secret
});

app.get('/', function (req, res) {
    var file = './bin/data/' + req.query["image"] + '.jpg';
    client.photo(config.tumblr.url, {"tags": config.tumblr.tags, "data": file}, function (err, data) {
        if (err) {
            console.log(err);
        }
        console.log("success" + data);
    });
    res.send('ok.');
});

var server = app.listen(config.server.port, function () {
    console.log("Server started.");
});
